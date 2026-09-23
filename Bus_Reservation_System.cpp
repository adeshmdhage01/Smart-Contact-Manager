#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

// ============================================================
// Passenger Class
// ============================================================

class Passenger {
private:
    int passengerId;
    string name;
    int age;
    string gender;
    string phone;

public:
    Passenger() {
        passengerId = 0;
        age = 0;
    }

    Passenger(int passengerId, string name, int age,
              string gender, string phone) {
        this->passengerId = passengerId;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->phone = phone;
    }

    int getPassengerId() const {
        return passengerId;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    string getGender() const {
        return gender;
    }

    string getPhone() const {
        return phone;
    }
};


// ============================================================
// Bus Class
// ============================================================

class Bus {
private:
    int busId;
    string busNumber;
    string source;
    string destination;
    string departureTime;
    int totalSeats;
    double fare;

    vector<bool> seats;

public:

    Bus() {
        busId = 0;
        totalSeats = 0;
        fare = 0;
    }

    Bus(int busId,
        string busNumber,
        string source,
        string destination,
        string departureTime,
        int totalSeats,
        double fare) {

        this->busId = busId;
        this->busNumber = busNumber;
        this->source = source;
        this->destination = destination;
        this->departureTime = departureTime;
        this->totalSeats = totalSeats;
        this->fare = fare;

        seats.resize(totalSeats + 1, false);
    }

    int getBusId() const {
        return busId;
    }

    string getBusNumber() const {
        return busNumber;
    }

    string getSource() const {
        return source;
    }

    string getDestination() const {
        return destination;
    }

    string getDepartureTime() const {
        return departureTime;
    }

    int getTotalSeats() const {
        return totalSeats;
    }

    double getFare() const {
        return fare;
    }

    bool isSeatAvailable(int seatNumber) const {

        if (seatNumber < 1 || seatNumber > totalSeats) {
            return false;
        }

        return !seats[seatNumber];
    }

    bool bookSeat(int seatNumber) {

        if (seatNumber < 1 || seatNumber > totalSeats) {
            return false;
        }

        if (seats[seatNumber]) {
            return false;
        }

        seats[seatNumber] = true;

        return true;
    }

    bool cancelSeat(int seatNumber) {

        if (seatNumber < 1 || seatNumber > totalSeats) {
            return false;
        }

        if (!seats[seatNumber]) {
            return false;
        }

        seats[seatNumber] = false;

        return true;
    }

    int getAvailableSeats() const {

        int count = 0;

        for (int i = 1; i <= totalSeats; i++) {

            if (!seats[i]) {
                count++;
            }
        }

        return count;
    }

    void displaySeats() const {

        cout << "\n========== SEAT LAYOUT ==========\n\n";

        for (int i = 1; i <= totalSeats; i++) {

            if (seats[i]) {
                cout << "[XX] ";
            }
            else {
                cout << "[" << setw(2) << setfill('0')
                     << i << "] ";
            }

            if (i % 4 == 0) {
                cout << endl;
            }
        }

        cout << setfill(' ');

        cout << "\nXX = Booked\n";
        cout << "Numbers = Available\n";
    }
};


// ============================================================
// Reservation Class
// ============================================================

class Reservation {
private:
    int reservationId;
    int busId;
    int seatNumber;
    Passenger passenger;
    double amount;
    bool active;

public:

    Reservation() {
        reservationId = 0;
        busId = 0;
        seatNumber = 0;
        amount = 0;
        active = true;
    }

    Reservation(int reservationId,
                int busId,
                int seatNumber,
                Passenger passenger,
                double amount) {

        this->reservationId = reservationId;
        this->busId = busId;
        this->seatNumber = seatNumber;
        this->passenger = passenger;
        this->amount = amount;
        this->active = true;
    }

    int getReservationId() const {
        return reservationId;
    }

    int getBusId() const {
        return busId;
    }

    int getSeatNumber() const {
        return seatNumber;
    }

    Passenger getPassenger() const {
        return passenger;
    }

    double getAmount() const {
        return amount;
    }

    bool isActive() const {
        return active;
    }

    void cancelReservation() {
        active = false;
    }

    void display() const {

        cout << "\n---------------------------------------\n";

        cout << "Reservation ID : " << reservationId << endl;
        cout << "Passenger Name : "
             << passenger.getName() << endl;

        cout << "Age            : "
             << passenger.getAge() << endl;

        cout << "Gender         : "
             << passenger.getGender() << endl;

        cout << "Phone          : "
             << passenger.getPhone() << endl;

        cout << "Bus ID         : " << busId << endl;

        cout << "Seat Number    : " << seatNumber << endl;

        cout << "Amount         : Rs. "
             << fixed << setprecision(2)
             << amount << endl;

        cout << "Status         : "
             << (active ? "CONFIRMED" : "CANCELLED")
             << endl;

        cout << "---------------------------------------\n";
    }
};


// ============================================================
// Bus Reservation System
// ============================================================

class BusReservationSystem {

private:

    vector<Bus> buses;
    vector<Reservation> reservations;

    int nextReservationId;

public:

    BusReservationSystem() {

        nextReservationId = 1001;

        loadDefaultBuses();
    }


    // --------------------------------------------------------
    // Add Default Buses
    // --------------------------------------------------------

    void loadDefaultBuses() {

        buses.push_back(
            Bus(
                1,
                "MH12-AB-1010",
                "Pune",
                "Mumbai",
                "08:00 AM",
                20,
                450
            )
        );

        buses.push_back(
            Bus(
                2,
                "MH14-CD-2020",
                "Pune",
                "Nashik",
                "09:30 AM",
                24,
                550
            )
        );

        buses.push_back(
            Bus(
                3,
                "MH12-EF-3030",
                "Mumbai",
                "Pune",
                "05:00 PM",
                20,
                450
            )
        );

        buses.push_back(
            Bus(
                4,
                "MH15-GH-4040",
                "Pune",
                "Nagpur",
                "07:00 PM",
                32,
                950
            )
        );

        buses.push_back(
            Bus(
                5,
                "MH20-IJ-5050",
                "Nashik",
                "Pune",
                "06:30 AM",
                24,
                550
            )
        );
    }


    // --------------------------------------------------------
    // Display Header
    // --------------------------------------------------------

    void displayHeader() {

        cout << "\n";
        cout << "=====================================================\n";
        cout << "             BUS RESERVATION SYSTEM\n";
        cout << "=====================================================\n";
    }


    // --------------------------------------------------------
    // Display All Buses
    // --------------------------------------------------------

    void displayAllBuses() {

        displayHeader();

        cout << left
             << setw(8) << "ID"
             << setw(18) << "Bus Number"
             << setw(15) << "Source"
             << setw(15) << "Destination"
             << setw(15) << "Departure"
             << setw(12) << "Seats"
             << setw(12) << "Fare"
             << endl;

        cout << string(95, '-') << endl;

        for (const Bus& bus : buses) {

            cout << left
                 << setw(8) << bus.getBusId()
                 << setw(18) << bus.getBusNumber()
                 << setw(15) << bus.getSource()
                 << setw(15) << bus.getDestination()
                 << setw(15) << bus.getDepartureTime()
                 << setw(12) << bus.getAvailableSeats()
                 << "Rs. " << bus.getFare()
                 << endl;
        }
    }


    // --------------------------------------------------------
    // Search Bus
    // --------------------------------------------------------

    void searchBus() {

        string source;
        string destination;

        cout << "\nEnter Source: ";
        cin >> source;

        cout << "Enter Destination: ";
        cin >> destination;

        bool found = false;

        cout << "\n========== AVAILABLE BUSES ==========\n";

        for (const Bus& bus : buses) {

            if (
                bus.getSource() == source &&
                bus.getDestination() == destination
            ) {

                found = true;

                cout << "\nBus ID       : "
                     << bus.getBusId();

                cout << "\nBus Number   : "
                     << bus.getBusNumber();

                cout << "\nRoute        : "
                     << bus.getSource()
                     << " -> "
                     << bus.getDestination();

                cout << "\nDeparture    : "
                     << bus.getDepartureTime();

                cout << "\nAvailable    : "
                     << bus.getAvailableSeats();

                cout << "\nFare         : Rs. "
                     << bus.getFare();

                cout << "\n";
            }
        }

        if (!found) {
            cout << "\nNo bus found for this route.\n";
        }
    }


    // --------------------------------------------------------
    // Find Bus
    // --------------------------------------------------------

    Bus* findBus(int busId) {

        for (Bus& bus : buses) {

            if (bus.getBusId() == busId) {
                return &bus;
            }
        }

        return nullptr;
    }


    // --------------------------------------------------------
    // Book Ticket
    // --------------------------------------------------------

    void bookTicket() {

        displayAllBuses();

        int busId;

        cout << "\nEnter Bus ID: ";
        cin >> busId;

        Bus* bus = findBus(busId);

        if (bus == nullptr) {

            cout << "\nInvalid Bus ID.\n";

            return;
        }

        if (bus->getAvailableSeats() == 0) {

            cout << "\nSorry! No seats available.\n";

            return;
        }

        bus->displaySeats();

        int seatNumber;

        cout << "\nEnter Seat Number: ";
        cin >> seatNumber;

        if (!bus->isSeatAvailable(seatNumber)) {

            cout << "\nSeat is not available.\n";

            return;
        }

        string name;
        int age;
        string gender;
        string phone;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter Passenger Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Gender: ";
        cin >> gender;

        cout << "Enter Phone Number: ";
        cin >> phone;

        int passengerId = 5000 + nextReservationId;

        Passenger passenger(
            passengerId,
            name,
            age,
            gender,
            phone
        );

        if (!bus->bookSeat(seatNumber)) {

            cout << "\nUnable to book seat.\n";

            return;
        }

        Reservation reservation(
            nextReservationId,
            busId,
            seatNumber,
            passenger,
            bus->getFare()
        );

        reservations.push_back(reservation);

        cout << "\n=======================================\n";
        cout << "        TICKET BOOKED SUCCESSFULLY\n";
        cout << "=======================================\n";

        cout << "Reservation ID : "
             << nextReservationId << endl;

        cout << "Passenger      : "
             << name << endl;

        cout << "Bus Number     : "
             << bus->getBusNumber() << endl;

        cout << "Route          : "
             << bus->getSource()
             << " -> "
             << bus->getDestination()
             << endl;

        cout << "Departure      : "
             << bus->getDepartureTime() << endl;

        cout << "Seat Number    : "
             << seatNumber << endl;

        cout << "Fare           : Rs. "
             << bus->getFare() << endl;

        cout << "=======================================\n";

        nextReservationId++;
    }


    // --------------------------------------------------------
    // Cancel Ticket
    // --------------------------------------------------------

    void cancelTicket() {

        int reservationId;

        cout << "\nEnter Reservation ID: ";
        cin >> reservationId;

        for (Reservation& reservation : reservations) {

            if (
                reservation.getReservationId() == reservationId &&
                reservation.isActive()
            ) {

                Bus* bus = findBus(
                    reservation.getBusId()
                );

                if (bus != nullptr) {

                    bus->cancelSeat(
                        reservation.getSeatNumber()
                    );
                }

                reservation.cancelReservation();

                cout << "\nTicket cancelled successfully.\n";

                cout << "Refund Amount: Rs. "
                     << reservation.getAmount()
                     << endl;

                return;
            }
        }

        cout << "\nReservation not found or already cancelled.\n";
    }


    // --------------------------------------------------------
    // Display All Reservations
    // --------------------------------------------------------

    void displayReservations() {

        if (reservations.empty()) {

            cout << "\nNo reservations found.\n";

            return;
        }

        cout << "\n=======================================\n";
        cout << "          ALL RESERVATIONS\n";
        cout << "=======================================\n";

        for (const Reservation& reservation : reservations) {

            reservation.display();
        }
    }


    // --------------------------------------------------------
    // Search Reservation
    // --------------------------------------------------------

    void searchReservation() {

        int reservationId;

        cout << "\nEnter Reservation ID: ";
        cin >> reservationId;

        for (const Reservation& reservation : reservations) {

            if (reservation.getReservationId() == reservationId) {

                reservation.display();

                return;
            }
        }

        cout << "\nReservation not found.\n";
    }


    // --------------------------------------------------------
    // Display Seats
    // --------------------------------------------------------

    void displayBusSeats() {

        int busId;

        displayAllBuses();

        cout << "\nEnter Bus ID: ";
        cin >> busId;

        Bus* bus = findBus(busId);

        if (bus == nullptr) {

            cout << "\nInvalid Bus ID.\n";

            return;
        }

        cout << "\nBus: "
             << bus->getBusNumber()
             << endl;

        cout << "Route: "
             << bus->getSource()
             << " -> "
             << bus->getDestination()
             << endl;

        bus->displaySeats();
    }


    // --------------------------------------------------------
    // Main Menu
    // --------------------------------------------------------

    void run() {

        int choice;

        do {

            displayHeader();

            cout << "\n";
            cout << "1. View All Buses\n";
            cout << "2. Search Bus by Route\n";
            cout << "3. View Seat Availability\n";
            cout << "4. Book Ticket\n";
            cout << "5. Cancel Ticket\n";
            cout << "6. View All Reservations\n";
            cout << "7. Search Reservation\n";
            cout << "8. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {

                case 1:
                    displayAllBuses();
                    break;

                case 2:
                    searchBus();
                    break;

                case 3:
                    displayBusSeats();
                    break;

                case 4:
                    bookTicket();
                    break;

                case 5:
                    cancelTicket();
                    break;

                case 6:
                    displayReservations();
                    break;

                case 7:
                    searchReservation();
                    break;

                case 8:
                    cout << "\nThank you for using "
                         << "Bus Reservation System!\n";
                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

            if (choice != 8) {

                cout << "\nPress Enter to continue...";

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                cin.get();
            }

        } while (choice != 8);
    }
};


// ============================================================
// Main Function
// ============================================================

int main() {

    BusReservationSystem system;

    system.run();

    return 0;
}