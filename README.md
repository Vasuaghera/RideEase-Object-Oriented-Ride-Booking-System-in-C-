# 🔖 Project Title

RideEase: Object-Oriented Ride Booking System in C++

# 📝 Description

RideEase is a console-based C++ application that simulates a ride-sharing service, designed to showcase Object-Oriented Programming (OOP) principles and a user-friendly interface. The system allows users to register as riders or drivers, book rides, manage trips, recharge wallets, rate drivers, and view system data through a menu-driven console interface. It leverages the `<bits/stdc++.h>` library to include essential C++ Standard Template Library (STL) components, ensuring robust functionality and input validation.

The core idea is to provide a simplified yet functional ride-booking system, emphasizing OOP concepts like encapsulation, inheritance, polymorphism, and abstraction, while maintaining an intuitive user experience with formatted outputs and clear prompts.

# 🚀 Features

- Register riders and drivers with validated inputs (name, phone, location).
- Request rides, specifying source, destination, and distance, with automatic fare calculation (base $20 + $10/km).
- Complete or cancel trips, updating driver availability and rider wallet balance.
- Recharge rider wallets to fund rides.
- Rate drivers (1.0–5.0) after completed trips, calculating an average rating.
- Display all registered users (riders and drivers) and trips in formatted, table-like outputs.
- Validate inputs using regex for names (alphabetic), phone numbers (10 digits), and locations (letters, spaces, commas).
- Provide a polished console UI with bordered menus, descriptive prompts, and clear feedback messages.

# 🛠️ Tech Stack

- **Language**: C++17
- **Library**: `<bits/stdc++.h>` (includes STL components like `<iostream>`, `<vector>`, `<string>`, `<iomanip>`, `<regex>`, `<limits>`)
- **Tools**: C++ compiler (e.g., g++), Git for version control, terminal/command-line interface

# 🎓 Key Concepts

- **Object-Oriented Programming (OOP)**:
  - **Encapsulation**: Private/protected data in classes (`User`, `Rider`, `Driver`, `Trip`) with public methods for controlled access.
  - **Inheritance**: `User` as an abstract base class, extended by `Rider` and `Driver`.
  - **Polymorphism**: Virtual `display()` method overridden in `Rider` and `Driver` for dynamic dispatch in `showAllUsers`.
  - **Abstraction**: Abstract `User` class and `RideSystem` methods hide implementation details.
- **Dynamic Memory Management**: Pointers for `Rider`, `Driver`, and `Trip` objects, with a destructor in `RideSystem` to prevent memory leaks.
- **Static Member**: `Trip::tripCounter` for unique trip IDs.
- **Regex Validation**: Ensures proper input formats (e.g., `^[a-zA-Z]+$` for names, `^[0-9]{10}$` for phone numbers).
- **Console UI Design**: Uses `<iomanip>` (`setw`, `left`, `fixed`) for aligned, table-like outputs and bordered menus.

# 📦 Prerequisites

- C++ compiler supporting C++17 (e.g., g++ 7.0 or later).
- Git (for cloning the repository).
- Terminal or command-line interface (e.g., Bash, Command Prompt).

# 🔧 Setup

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/your-username/RideEase.git
   cd RideEase
   ```
2. **Compile the Code**:

   ```bash
   g++ -std=c++17 main.cpp -o rideease
   ```
3. **Run the Program**:

   ```bash
   ./rideease
   ```

# 💡 Usage

1. Launch RideEase to see the welcome message and main menu.
2. Choose options (1–10) using numeric input:
   - **1**: Register a rider (e.g., name: Vasu, phone: 1234567890, location: Ahmedabad).
   - **2**: Register a driver (e.g., name: Aarya, car: GJ01FB0001).
   - **3**: Request a ride (enter rider ID, source, destination, distance).
   - **4**: Complete a trip (enter trip ID).
   - **5**: Cancel a trip (enter rider ID).
   - **6**: Recharge a rider’s wallet (enter rider ID and amount).
   - **7**: Rate a driver (enter trip ID and rating).
   - **8**: View all registered users.
   - **9**: View all trips.
   - **10**: Exit the program.
3. Follow prompts for input (e.g., “Enter name (letters only, e.g., Vasu): ”).
4. Review formatted outputs for actions (e.g., registration success, trip details).

# 📋 Example Output

```
============================================
     Welcome to RideEase!
============================================
============================================
        RideEase - Main Menu
============================================
| 1. Register as Rider                     |
| 2. Register as Driver                    |
| 3. Request a Ride                        |
| 4. Complete a Trip                       |
| 5. Cancel a Trip                         |
| 6. Recharge Rider Wallet                 |
| 7. Rate a Driver                         |
| 8. View All Users                        |
| 9. View All Trips                        |
| 10. Exit                                 |
============================================
Enter your choice (1-10): 1

=== Register Rider ===
Enter name (letters only, e.g., Vasu): Vasu
Enter phone (10 digits, e.g., 1234567890): 1234567890
Enter location (letters/spaces, e.g., Ahmedabad): Ahmedabad
Enter initial wallet balance (e.g., 100.50): 100.50
ID: 1 Rider Vasu registered successfully!
---------------------

Enter your choice (1-10): 8

====================================
         All Registered Users
====================================
Riders:
------------------------------------
| [Rider] ID:    1, Name: Vasu           , Phone: 1234567890, Location: Ahmedabad      , Balance: $100.50 |
------------------------------------
Drivers:
------------------------------------
| No drivers registered.          |
------------------------------------
```

# 📁 Project Structure

- **main.cpp**:
  - Contains all source code for RideEase.
  - **Classes**:
    - `User`: Abstract base class with ID, name, phone, and pure virtual `display()`.
    - `Rider`: Manages rider location and wallet balance.
    - `Driver`: Manages driver car number, rating, location, and availability.
    - `Trip`: Handles trip details (source, destination, fare, status).
    - `RideSystem`: Coordinates the system, storing riders, drivers, and trips.
  - **Functions**:
    - `displayMenu()`: Shows the main menu with options.
    - `main()`: Runs the menu-driven interface and processes user inputs.

# 🗒️ Notes

- The project uses `<bits/stdc++.h>` to include most C++ STL libraries (e.g., `<iostream>`, `<vector>`, `<string>`, `<iomanip>`, `<regex>`) for simplicity. In production, specific headers are recommended for portability and faster compilation.
- Data is stored in-memory and not persisted across sessions (no file I/O).
- Input validation is robust for registration (regex for names, phone, location) but limited for numeric inputs in `main` (e.g., menu choice, balance).
- The `srand(time(0))` call in `RideSystem` is unused and could be removed.
- RideEase is a learning project, and contributions or feedback are welcome to improve its functionality or code quality.

# 🤝 Contributing

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/your-feature`).
3. Commit your changes (`git commit -m "Add your feature"`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Open a pull request on GitHub.

# 👤 Author

Vasu Aghera\
GitHub: \[Vasuaghera\]\
(Replace `your-username` with your GitHub handle)
