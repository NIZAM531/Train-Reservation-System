# Train-Reservation-System

# 🚆 Train Reservation System 

A **modern terminal-based Train Reservation System** built in **C++**, featuring a full suite of functionalities including seat maps, booking, cancellation, and PNR-based ticketing, designed to simulate a real-world train reservation experience.
[image_alt](https://github.com/NIZAM531/Train-Reservation-System/blob/main/wired-flat-1324-c-code-language.gif?raw=true)
---

## 🔹 Features

1. **User Management**  
   - First-time registration or login with a single username/password.  
   - Persistent user data stored in CSV.  

2. **Train Management**  
   - Supports multiple trains with routes and multiple seat types:  
   ```
     - First Class  
     - Second Class  
     - Sleeper AC  
     - Sleeper Non-AC
    ```
   - Seat availability stored persistently in CSV files.
   

3. **Seat Map with Numbers**  
   - Visual representation of seat availability in the terminal:  
    ```
     - 🟩 = Available  
     - 🟥 = Booked
    ``` 
   - Users can select specific seat numbers for booking or cancellation.  

4. **Booking & Cancellation**  
   - Book tickets with chosen seat numbers and type.  
   - Cancel tickets with seat selection.  
   - Auto-generated **PNR number** for every booking.  

5. **Ticket Generation**  
   - Generates a detailed ticket as a text file including:  
     - PNR  
     - Username  
     - Train name and route  
     - Seat type and booked seats  
     - Booking date  

6. **Booking History & PNR Search**  
   - View all your bookings with detailed info.  
   - Search for tickets using the PNR number.  

7. **Modern Terminal UI**  
   - Uses **ANSI colors** for a more interactive experience:  
     - 🟢 Success messages  
     - 🔴 Errors  
     - 🟡 Warnings  
   - Displays a clean, organized menu system.  

---
## 🖼️ Project Preview
```
══════════════ MAIN MENU ══════════════
[1] Show Available Trains
[2] Book Ticket
[3] Cancel Ticket
[4] View My Bookings
[5] Search by PNR
[6] Exit
══════════════════════════════════════
```
Enter your choice:

**Seat Map Display:**  
``Seat Map for Express 101 (City A ➝ City B)``
```
First Class (5 seats available):
🟩1 🟩2 🟩3 🟥4 🟩5

Second Class (10 seats available):
🟩1 🟩2 🟩3 🟩4 🟩5 🟥6 🟩7 🟩8 🟩9 🟩10

Sleeper AC (3 seats available):
🟩1 🟥2 🟩3

Sleeper Non-AC (2 seats available):
🟩1 🟩2```

```
\**Booking Seats:**\  


Enter Train Number: 1
```
Enter Seat Type (First Class, Second Class, Sleeper AC, Sleeper Non-AC): First Class
Enter seat numbers separated by space: 1 2
🟢 2 seat(s) booked for Express 101 (PNR: 1001)
🟢 Ticket generated: ticket_PNR1001.txt```

```
``**Ticket Example (`ticket_PNR1001.txt`):**``  


```
================ TICKET ================
``PNR Number : 1001
Username : john_doe
Train Name : Express 101
Route : City A ➝ City B
Seat Type : First Class
Seats Booked : 1,2
Date : 25-09-2025 ``
 ```
 ```
**Booking History & PNR Search:**  

📖 Booking History for john_doe:
``PNR1001,john_doe,Express 101,City A ➝ City B,First Class,1/2``

``Enter PNR number to search: 1001``
```
🟢 Booking found:
PNR1001,john_doe,Express 101,City A ➝ City B,First Class,1/2

---

## 💻 Technologies Used
```
- **Language:** C++  
- **File Storage:** CSV files for persistent storage of trains, users, and bookings  
- **Terminal Graphics:** ANSI color codes and Unicode characters for seat maps  
---
## 📝 How to Run
1. **Clone the repository:**  
```bash
git clone <repository-url>
```
Compile the program:
```g++ TrainReservationSystem.cpp -o TrainReservationSystem```
Run the program:
```./TrainReservationSystem```
``Follow on-screen instructions to register/login, view trains, select seats, book or cancel tickets, and generate tickets.``





