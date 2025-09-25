#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

// ANSI colors
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"

struct Train {
    string name;
    string route;
    map<string,int> maxSeats;                  // max seats per type
    map<string,vector<bool>> seatStatus;       // true=available, false=booked
};

class TrainReservationSystem {
private:
    map<int, Train> trains;
    int lastPNR;

public:
    TrainReservationSystem() { lastPNR = 1000; loadTrains(); }

    void loadTrains() {
        ifstream in("trains.csv");
        if(!in.is_open()) {
            // default trains
            trains[1] = {"Express 101", "City A ➝ City B", {{"First Class",10},{"Second Class",20},{"Sleeper AC",10},{"Sleeper Non-AC",10}}, {}};
            trains[2] = {"Express 202", "City B ➝ City C", {{"First Class",5},{"Second Class",25},{"Sleeper AC",10},{"Sleeper Non-AC",10}}, {}};
            trains[3] = {"Express 303", "City A ➝ City C", {{"First Class",8},{"Second Class",20},{"Sleeper AC",12},{"Sleeper Non-AC",10}}, {}};
            // initialize seatStatus
            for(auto &t : trains)
                for(auto &s : t.second.maxSeats)
                    t.second.seatStatus[s.first] = vector<bool>(s.second,true);
            saveTrains();
            return;
        }
        trains.clear();
        string line; getline(in,line); // skip header
        while(getline(in,line)){
            stringstream ss(line);
            int no; string name,route; ss>>no>>name>>route;
            Train tr; tr.name=name; tr.route=route;
            for(auto &stype : vector<string>{"First Class","Second Class","Sleeper AC","Sleeper Non-AC"}){
                int available; ss>>available;
                tr.maxSeats[stype]=available;
                tr.seatStatus[stype]=vector<bool>(available,true);
            }
            trains[no]=tr;
        }
        in.close();
    }

    void saveTrains() {
        ofstream out("trains.csv");
        out<<"TrainNo Name Route FC SC SAC SNC\n";
        for(auto &t : trains){
            out<<t.first<<" "<<t.second.name<<" "<<t.second.route<<" ";
            for(auto &s: vector<string>{"First Class","Second Class","Sleeper AC","Sleeper Non-AC"}){
                int avail=0;
                for(bool b : t.second.seatStatus[s]) if(b) avail++;
                out<<avail<<" ";
            }
            out<<"\n";
        }
        out.close();
    }

    int generatePNR() { return lastPNR++; }

    void generateTicket(int pnr,string username, Train train,string seatType,vector<int> seats){
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        char dateStr[20]; strftime(dateStr,sizeof(dateStr),"%d-%m-%Y",now);

        string filename = "ticket_PNR"+to_string(pnr)+".txt";
        ofstream ticket(filename);
        ticket<<"================ TICKET ================\n";
        ticket<<"PNR Number   : "<<pnr<<"\n";
        ticket<<"Username     : "<<username<<"\n";
        ticket<<"Train Name   : "<<train.name<<"\n";
        ticket<<"Route        : "<<train.route<<"\n";
        ticket<<"Seat Type    : "<<seatType<<"\n";
        ticket<<"Seats Booked : ";
        for(int i=0;i<seats.size();i++){
            ticket<<seats[i];
            if(i<seats.size()-1) ticket<<",";
        }
        ticket<<"\nDate         : "<<dateStr<<"\n";
        ticket<<"=======================================\n";
        ticket.close();
        cout<<GREEN<<"🟢 Ticket generated: "<<filename<<RESET<<endl;
    }

    void displaySeatMap(int trainNumber){
        if(trains.find(trainNumber)==trains.end()){ cout<<RED<<"❌ Invalid Train Number!\n"<<RESET; return; }
        Train &t = trains[trainNumber];
        cout<<CYAN<<"\nSeat Map for "<<t.name<<" ("<<t.route<<")"<<RESET<<endl;
        for(auto &s : t.seatStatus){
            cout<<MAGENTA<<"\n"<<s.first<<" ("<<count(s.second.begin(),s.second.end(),true)<<" seats available):"<<RESET<<endl;
            for(int i=0;i<s.second.size();i++){
                if(s.second[i]) cout<<"🟩"<<i+1<<" ";
                else cout<<"🟥"<<i+1<<" ";
                if((i+1)%10==0) cout<<endl;
            }
            cout<<endl;
        }
    }

    void bookTicket(int trainNumber,string seatType,vector<int> seats,string username){
        if(trains.find(trainNumber)==trains.end()){ cout<<RED<<"❌ Invalid Train Number!\n"<<RESET; return; }
        Train &t = trains[trainNumber];
        for(int s: seats){
            if(s<1 || s>t.seatStatus[seatType].size() || !t.seatStatus[seatType][s-1]){
                cout<<RED<<"❌ Seat "<<s<<" is not available!\n"<<RESET; return;
            }
        }
        for(int s: seats) t.seatStatus[seatType][s-1]=false;
        saveTrains();
        int pnr=generatePNR();
        cout<<GREEN<<"🟢 "<<seats.size()<<" seat(s) booked for "<<t.name<<" (PNR: "<<pnr<<")"<<RESET<<endl;
        ofstream out("bookings.csv",ios::app);
        out<<"PNR"<<pnr<<","<<username<<","<<t.name<<","<<t.route<<","<<seatType<<",";
        for(int i=0;i<seats.size();i++){ out<<seats[i]; if(i<seats.size()-1) out<<"/"; }
        out<<"\n"; out.close();
        generateTicket(pnr,username,t,seatType,seats);
    }

    void cancelTicket(int trainNumber,string seatType,vector<int> seats,string username){
        if(trains.find(trainNumber)==trains.end()){ cout<<RED<<"❌ Invalid Train Number!\n"<<RESET; return; }
        Train &t = trains[trainNumber];
        for(int s: seats) if(s>=1 && s<=t.seatStatus[seatType].size()) t.seatStatus[seatType][s-1]=true;
        saveTrains();
        cout<<GREEN<<"🟢 "<<seats.size()<<" seat(s) canceled for "<<t.name<<RESET<<endl;
        ofstream out("bookings.csv",ios::app);
        out<<username<<",CANCELED,"<<t.name<<","<<t.route<<","<<seatType<<",";
        for(int i=0;i<seats.size();i++){ out<<seats[i]; if(i<seats.size()-1) out<<"/"; }
        out<<"\n"; out.close();
    }

    void viewBookingHistory(string username){
        ifstream in("bookings.csv"); string line; bool found=false;
        cout<<MAGENTA<<"\n📖 Booking History for "<<username<<":\n"<<RESET;
        while(getline(in,line)){ if(line.find(username)!=string::npos){ cout<<line<<endl; found=true; } }
        if(!found) cout<<YELLOW<<"🟡 No bookings found.\n"<<RESET;
    }

    void searchPNR(int pnr){
        ifstream in("bookings.csv"); string line; bool found=false;
        string pnrStr="PNR"+to_string(pnr);
        while(getline(in,line)){ if(line.find(pnrStr)!=string::npos){ cout<<GREEN<<"🟢 Booking found:\n"<<RESET<<line<<endl; found=true; break; } }
        if(!found) cout<<RED<<"❌ No booking found with PNR "<<pnr<<RESET<<endl;
    }
};

class UserSystem{
public:
    bool registerOrLogin(string &username){
        ifstream check("users.csv");
        if(!check.is_open() || check.peek()==ifstream::traits_type::eof()){
            cout<<"📝 First-time registration\nEnter username: "; cin>>username;
            string password; cout<<"Enter password: "; cin>>password;
            ofstream out("users.csv"); out<<username<<","<<password<<"\n"; out.close();
            cout<<GREEN<<"🟢 Registration successful!\n"<<RESET; return true;
        } else {
            bool loggedIn=false;
            while(!loggedIn){
                cout<<"Enter username: "; cin>>username;
                string password; cout<<"Enter password: "; cin>>password;
                ifstream in("users.csv"); string line;
                while(getline(in,line)){
                    size_t pos=line.find(',');
                    if(pos!=string::npos){
                        string storedUser=line.substr(0,pos);
                        string storedPass=line.substr(pos+1);
                        if(storedUser==username && storedPass==password){ 
                            cout<<GREEN<<"🟢 Login successful! Welcome "<<username<<"\n"<<RESET; 
                            loggedIn=true; break;
                        }
                    }
                }
                if(!loggedIn) cout<<RED<<"❌ Invalid username or password. Try again.\n"<<RESET;
            }
            return true;
        }
    }
};

vector<int> inputSeats() {
    cout<<"Enter seat numbers separated by space: ";
    string line; cin.ignore(); getline(cin,line);
    stringstream ss(line); int n; vector<int> seats;
    while(ss>>n) seats.push_back(n);
    return seats;
}

int main(){
    TrainReservationSystem trainSystem;
    UserSystem userSystem;
    string username;

    cout<<BLUE<<"=============================================\n"
        <<" 🚆 TRAIN RESERVATION SYSTEM\n"
        <<"=============================================\n"<<RESET;

    userSystem.registerOrLogin(username);

    int choice, trainNumber;
    string seatType;
    do{
        cout<<CYAN<<"\n══════════════ MAIN MENU ══════════════\n"<<RESET;
        cout<<GREEN<<"[1]"<<RESET<<" Show Available Trains\n";
        cout<<GREEN<<"[2]"<<RESET<<" Book Ticket\n";
        cout<<GREEN<<"[3]"<<RESET<<" Cancel Ticket\n";
        cout<<GREEN<<"[4]"<<RESET<<" View My Bookings\n";
        cout<<GREEN<<"[5]"<<RESET<<" Search by PNR\n";
        cout<<GREEN<<"[6]"<<RESET<<" Exit\n";
        cout<<CYAN<<"══════════════════════════════════════\n"<<RESET;
        cout<<"Enter your choice: "; cin>>choice;

        switch(choice){
            case 1: trainSystem.displaySeatMap(1); trainSystem.displaySeatMap(2); trainSystem.displaySeatMap(3); break;
            case 2:
                cout<<"Enter Train Number: "; cin>>trainNumber;
                trainSystem.displaySeatMap(trainNumber);
                cout<<"Enter Seat Type (First Class,Second Class,Sleeper AC,Sleeper Non-AC): "; cin.ignore(); getline(cin,seatType);
                trainSystem.bookTicket(trainNumber,seatType,inputSeats(),username); break;
            case 3:
                cout<<"Enter Train Number: "; cin>>trainNumber;
                trainSystem.displaySeatMap(trainNumber);
                cout<<"Enter Seat Type to cancel: "; cin.ignore(); getline(cin,seatType);
                trainSystem.cancelTicket(trainNumber,seatType,inputSeats(),username); break;
            case 4: trainSystem.viewBookingHistory(username); break;
            case 5: int pnrSearch; cout<<"Enter PNR number: "; cin>>pnrSearch; trainSystem.searchPNR(pnrSearch); break;
            case 6: cout<<GREEN<<"👋 Thank you for using Train Reservation System!\n"<<RESET; break;
            default: cout<<RED<<"❌ Invalid choice. Try again.\n"<<RESET;
        }
    }while(choice!=6);

    return 0;
}
