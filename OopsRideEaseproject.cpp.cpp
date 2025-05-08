#include<bits/stdc++.h>
using namespace std;

class User {
    
    protected:
        int id;
        string name;
        string phone;
    
    public:
        User(int id, const string& name, const string& phone) : id(id), name(name), phone(phone) {}
        virtual void display() const = 0;
        int getId() const { return id; }
        string getName() const { return name; }
        string getPhone() const { return phone; }
};

class Rider : public User {
    
    string location;
    double walletBalance;

    public:
        Rider(int id, const string& name, const string& phone, const string& location, double balance)
            : User(id, name, phone), location(location), walletBalance(balance) {}

        string getLocation() const { return location; }
        double getBalance() const { return walletBalance; }
        void deductFare(double fare) { walletBalance -= fare; }
        void addFunds(double amount) { walletBalance += amount; }

    void display() const override {
        cout << "| [Rider] ID: " << setw(4) << id
             << ", Name: " << setw(15) << left << name
             << ", Phone: " << phone
             << ", Location: " << setw(15) << left << location
             << ", Balance: $" << fixed << setprecision(2) << walletBalance << " |\n";
    }
};

class Driver : public User {

    string carNumber;
    double rating;
    string location;
    bool available;

    public:
        Driver(int id, const string& name, const string& phone, const string& carNumber, const string& location)
            : User(id, name, phone), carNumber(carNumber), location(location), rating(5.0), available(true) {}

        string getCarNumber() const { return carNumber; }
        string getLocation() const { return location; }
        double getRating() const { return rating; }
        bool isAvailable() const { return available; }

        void setAvailable(bool status) { available = status; }
        void updateRating(double newRating) { rating = (rating + newRating) / 2.0; }

        void display() const override {
            cout << "| [Driver] ID: " << setw(4) << id
                << ", Name: " << setw(15) << left << name
                << ", Phone: " << phone
                << ", Car: " << setw(10) << left << carNumber
                << ", Location: " << setw(15) << left << location
                << ", Rating: " << fixed << setprecision(1) << rating
                << ", Available: " << (available ? "Yes" : "No") << " |\n";
        }
};

class Trip {

    static int tripCounter;
    int tripId;
    Rider* rider;
    Driver* driver;
    string source;
    string destination;
    double distance;
    double fare;
    string status;

    double calculateFare() const {
        const double baseFare = 20.0;
        const double costPerKm = 10.0;
        return baseFare + (costPerKm * distance);
    }

public:

    Trip(Rider* rider, Driver* driver, const string& source, const string& destination, double distance)
        : rider(rider), driver(driver), source(source), destination(destination), distance(distance), status("Started") {
        tripId = ++tripCounter;
        fare = calculateFare();
    }

    int getTripId() const { return tripId; }
    string getStatus() const { return status; }
    Rider* getRider() const { return rider; }
    Driver* getDriver() const { return driver; }

    void completeTrip() {
        if (status == "Started") {
            status = "Completed";
            driver->setAvailable(true);
            rider->deductFare(fare);
            cout << "Trip completed. Fare $" << fare << " deducted from rider.\n";
        }
    }

    void cancelTrip() {
        if (status == "Started") {
            status = "Cancelled";
            driver->setAvailable(true);
            cout << "Trip cancelled successfully.\n";
        }
    }

    void display() const {
        cout << "| [Trip ID: " << setw(4) << tripId << "] "
             << "Rider: " << setw(15) << left << rider->getName()
             << ", Driver: " << setw(15) << left << driver->getName()
             << ", From: " << setw(15) << left << source
             << ", To: " << setw(15) << left << destination
             << ", Distance: " << fixed << setprecision(2) << distance << " km"
             << ", Fare: $" << fixed << setprecision(2) << fare
             << ", Status: " << status << " |\n";
    }
};

int Trip::tripCounter = 0;

class RideSystem {
    
    vector<Rider*> riders;
    vector<Driver*> drivers;
    vector<Trip*> trips;
    int userIdCounter = 0;

public:
    RideSystem() { srand(time(0)); }
    ~RideSystem() {
        for (auto r : riders) delete r;
        for (auto d : drivers) delete d;
        for (auto t : trips) delete t;
    }

    void registerRider(const string& name, const string& phone, const string& location, double balance) {
        if (!isValidName(name)) {
            cout << "Invalid name. Name should only contain alphabetic characters.\n";
            return;
        }
        if (!isValidPhone(phone)) {
            cout << "Invalid phone number. Phone should only contain digits and have 10 digits.\n";
            return;
        }
        if (!isValidLocation(location)) {
            cout << "Invalid location. Location should not be empty and may contain only letters, spaces, and commas.\n";
            return;
        }
        if (balance < 0) {
            cout << "Invalid balance. Balance cannot be negative.\n";
            return;
        }
        
        riders.push_back(new Rider(++userIdCounter, name, phone, location, balance));
        cout << "ID : " << userIdCounter <<" Rider " << name << " registered successfully!\n " ;
    }

    void registerDriver(const string& name, const string& phone, const string& carNumber, const string& location) {
        if (!isValidName(name)) {
            cout << "Invalid name. Name should only contain alphabetic characters.\n";
            return;
        }
        if (!isValidPhone(phone)) {
            cout << "Invalid phone number. Phone should only contain digits and have 10 digits.\n";
            return;
        }
        if (!isValidLocation(location)) {
            cout << "Invalid location. Location should not be empty and may contain only letters, spaces, and commas.\n";
            return;
        }
        drivers.push_back(new Driver(++userIdCounter, name, phone, carNumber, location));
        cout << "ID : " << userIdCounter << " Driver " << name << " registered successfully!\n";
    }

    bool isValidName(const string& name) {
        return regex_match(name, regex("^[a-zA-Z]+$"));
    }

    bool isValidPhone(const string& phone) {
        return regex_match(phone, regex("^[0-9]{10}$"));
    }
    
    bool isValidLocation(const string& location) {
        return !location.empty() && regex_match(location, regex("^[a-zA-Z, ]+$"));
    }

    void requestRide(int riderId, const string& source, const string& destination, double distance) {
        if (source.empty() || destination.empty() || distance <= 0) {
            cout << "Invalid trip details.\n";
            return;
        }

        Rider* rider = nullptr;
        for (auto r : riders) if (r->getId() == riderId) rider = r;

        if (!rider) {
            cout << "Rider not found.\n";
            return;
        }

        for (auto d : drivers) {
            if (d->isAvailable()) {
                Trip* trip = new Trip(rider, d, source, destination, distance);
                double estimatedFare = 20.0 + (10.0 * distance);
                if (rider->getBalance() < estimatedFare) {
                    cout << "Insufficient wallet balance. Required: $" << estimatedFare << ", Available: $" << rider->getBalance() << endl;
                    delete trip;
                    return;
                }
                d->setAvailable(false);
                trips.push_back(trip);
                cout << "\nRide successfully started:\n";
                trip->display();
                return;
            }
        }
        cout << "No available drivers currently.\n";
    }

    void completeTrip(int tripId) {
        for (auto trip : trips) {
            if (trip->getTripId() == tripId && trip->getStatus() == "Started") {
                trip->completeTrip();
                return;
            }
        }
        cout << "No active trip found for completion.\n";
    }

    void cancelTrip(int riderId) {
        bool found = false;
        for (auto trip : trips) {
            if (trip->getRider()->getId() == riderId && trip->getStatus() == "Started") {
                trip->cancelTrip();
                found = true;
                break;
            }
        }
        if (!found) cout << "No active trip found for cancellation.\n";
    }

    void rechargeWallet(int riderId, double amount) {
        for (auto r : riders) {
            if (r->getId() == riderId) {
                r->addFunds(amount);
                cout << "Wallet recharged. New balance: $" << fixed << setprecision(2) << r->getBalance() << endl;
                return;
            }
        }
        cout << "Rider not found.\n";
    }

    void rateDriver(int tripId, double rating) {
        for (auto t : trips) {
            if (t->getTripId() == tripId && t->getStatus() == "Completed") {
                if (rating >= 1.0 && rating <= 5.0) {
                    t->getDriver()->updateRating(rating);
                    cout << "Thanks for rating the driver!\n";
                } else {
                    cout << "Invalid rating. Must be between 1 and 5.\n";
                }
                return;
            }
        }
        cout << "Trip not found or not completed yet.\n";
    }

    void showAllUsers() const {
        cout << "\n====================================\n";
        cout << "         All Registered Users       \n";
        cout << "====================================\n";
        cout << "Riders:\n";
        cout << "------------------------------------\n";
        if (riders.empty()) {
            cout << "| No riders registered.           |\n";
        } else {
            for (auto r : riders) r->display();
        }
        cout << "------------------------------------\n";
        cout << "Drivers:\n";
        cout << "------------------------------------\n";
        if (drivers.empty()) {
            cout << "| No drivers registered.          |\n";
        } else {
            for (auto d : drivers) d->display();
        }
        cout << "------------------------------------\n";
    }

    void showAllTrips() const {
        cout << "\n====================================\n";
        cout << "         All Trips                  \n";
        cout << "====================================\n";
        if (trips.empty()) {
            cout << "| No trips recorded.              |\n";
        } else {
            for (auto t : trips) t->display();
        }
        cout << "------------------------------------\n";
    }
};

void displayMenu() {
    cout << "\n============================================\n";
    cout << "        Ride Sharing System - Main Menu      \n";
    cout << "============================================\n";
    cout << "| 1. Register as Rider                     |\n";
    cout << "| 2. Register as Driver                    |\n";
    cout << "| 3. Request a Ride                        |\n";
    cout << "| 4. Complete a Trip                       |\n";
    cout << "| 5. Cancel a Trip                         |\n";
    cout << "| 6. Recharge Rider Wallet                 |\n";
    cout << "| 7. Rate a Driver                         |\n";
    cout << "| 8. View All Users                        |\n";
    cout << "| 9. View All Trips                        |\n";
    cout << "| 10. Exit                                 |\n";
    cout << "============================================\n";
    cout << "Enter your choice (1-10): ";
}

int main() {
    RideSystem system;
    int choice;
    cout << "\n============================================\n";
    cout << "     Welcome to Ride Sharing System!        \n";
    cout << "============================================\n";

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\n";
        switch (choice) {
        case 1: {
            string name, phone, location;
            double balance;
            cout << "=== Register Rider ===\n";
            cout << "Enter name (letters only, e.g., Vasu): ";
            getline(cin, name);
            cout << "Enter phone (10 digits, e.g., 1234567890): ";
            getline(cin, phone);
            cout << "Enter location (letters/spaces, e.g., Ahmedabad ): ";
            getline(cin, location);
            cout << "Enter initial wallet balance (e.g., 100.50): ";
            cin >> balance;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.registerRider(name, phone, location, balance);
            cout << "---------------------\n";
            break;
        }
        case 2: {
            string name, phone, carNumber, location;
            cout << "=== Register Driver ===\n";
            cout << "Enter name (letters only, e.g., Aarya ): ";
            getline(cin, name);
            cout << "Enter phone (10 digits, e.g., 0987654321): ";
            getline(cin, phone);
            cout << "Enter car number (e.g., GJ01FB0001): ";
            getline(cin, carNumber);
            cout << "Enter location (letters/spaces, e.g., Ahmedabad): ";
            getline(cin, location);
            system.registerDriver(name, phone, carNumber, location);
            cout << "---------------------\n";
            break;
        }
        case 3: {
            int riderId;
            string source, destination;
            double distance;
            cout << "=== Request Ride ===\n";
            cout << "Enter rider ID (e.g., 1): ";
            cin >> riderId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter source (e.g., Sardardham): ";
            getline(cin, source);
            cout << "Enter destination (e.g., Nirma university): ";
            getline(cin, destination);
            cout << "Enter distance in km (e.g., 5.0): ";
            cin >> distance;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.requestRide(riderId, source, destination, distance);
            cout << "---------------------\n";
            break;
        }
        case 4: {
            int tripId;
            cout << "=== Complete Trip ===\n";
            cout << "Enter trip ID (e.g., 1): ";
            cin >> tripId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.completeTrip(tripId);
            cout << "---------------------\n";
            break;
        }
        case 5: {
            int riderId;
            cout << "=== Cancel Trip ===\n";
            cout << "Enter rider ID (e.g., 1): ";
            cin >> riderId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.cancelTrip(riderId);
            cout << "---------------------\n";
            break;
        }
        case 6: {
            int riderId;
            double amount;
            cout << "=== Recharge Wallet ===\n";
            cout << "Enter rider ID (e.g., 1): ";
            cin >> riderId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter amount to recharge (e.g., 50.0): ";
            cin >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.rechargeWallet(riderId, amount);
            cout << "---------------------\n";
            break;
        }
        case 7: {
            int tripId;
            double rating;
            cout << "=== Rate Driver ===\n";
            cout << "Enter trip ID (e.g., 1): ";
            cin >> tripId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter rating (1.0 to 5.0): ";
            cin >> rating;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.rateDriver(tripId, rating);
            cout << "---------------------\n";
            break;
        }
        case 8:
            system.showAllUsers();
            break;
        case 9:
            system.showAllTrips();
            break;
        case 10:
            cout << "============================================\n";
            cout << " Thank You for Using Ride Sharing System!   \n";
            cout << "============================================\n";
        break;
        default:
            cout << "Invalid choice! Please select a number between 1 and 10.\n";
        }
    } while (choice != 10);

    return 0;
}
