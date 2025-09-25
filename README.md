# Train-Reservation-System

# 🚆 Train Reservation System

A **modern terminal-based Train Reservation System** built in **C++**, featuring a full suite of functionalities including seat maps, booking, cancellation, and PNR-based ticketing, designed to simulate a real-world train reservation experience.

---

## 🔹 Features

1. **User Management**  
   - First-time registration or login with a single username/password.  
   - Persistent user data stored in CSV.  

2. **Train Management**  
   - Supports multiple trains with routes and multiple seat types:  
     - First Class  
     - Second Class  
     - Sleeper AC  
     - Sleeper Non-AC  
   - Seat availability stored persistently in CSV files.  

3. **Seat Map with Numbers**  
   - Visual representation of seat availability in the terminal:  
     - 🟩 = Available  
     - 🟥 = Booked  
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



**Main Menu:**  

