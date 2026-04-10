#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define MAX_SLOTS 50

class Vehicle {
public:
    string number;
    string type;
    time_t entryTime;

    Vehicle(string n, string t) {
        number = n;
        type = t;
        entryTime = time(0);
    }
};

vector<Vehicle> parking;
vector<string> recentVehicles;

// Add Vehicle
void addVehicle() {
    if (parking.size() >= MAX_SLOTS) {
        cout << "Parking Full!\n";
        return;
    }

    string num, type;
    cout << "Enter vehicle number: ";
    cin >> num;
    cout << "Enter type (Car/Bike): ";
    cin >> type;

    Vehicle v(num, type);
    parking.push_back(v);

    // Maintain last 5 vehicles
    recentVehicles.push_back(num);
    if (recentVehicles.size() > 5) {
        recentVehicles.erase(recentVehicles.begin());
    }

    cout << "Vehicle parked successfully!\n";
}

// Remove Vehicle
void removeVehicle() {
    string num;
    cout << "Enter vehicle number to remove: ";
    cin >> num;

    for (int i = 0; i < parking.size(); i++) {
        if (parking[i].number == num) {

            time_t exitTime = time(0);
            double duration = difftime(exitTime, parking[i].entryTime) / 60;

            cout << "Vehicle removed!\n";
            cout << "Parking Time: " << duration << " minutes\n";

            parking.erase(parking.begin() + i);
            return;
        }
    }

    cout << "Vehicle not found!\n";
}

// View Vehicles
void viewVehicles() {
    if (parking.empty()) {
        cout << "No vehicles parked.\n";
        return;
    }

    for (auto v : parking) {
        cout << "Number: " << v.number
             << ", Type: " << v.type
             << ", Entry Time: " << ctime(&v.entryTime);
    }
}

// Search Vehicle
void searchVehicle() {
    string num;
    cout << "Enter vehicle number: ";
    cin >> num;

    for (auto v : parking) {
        if (v.number == num) {
            cout << "Found: " << v.number << " (" << v.type << ")\n";
            return;
        }
    }

    cout << "Not found!\n";
}

// Show Recent Vehicles
void showRecent() {
    if (recentVehicles.empty()) {
        cout << "No recent vehicles.\n";
        return;
    }

    cout << "Last 5 Parked Vehicles:\n";
    for (string num : recentVehicles) {
        cout << num << endl;
    }
}

// Main Menu
int main() {
    int choice;

    while (true) {
        cout << "\n--- Smart Parking System ---\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. View Vehicles\n";
        cout << "4. Search Vehicle\n";
        cout << "5. Recent Vehicles\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addVehicle(); break;
            case 2: removeVehicle(); break;
            case 3: viewVehicles(); break;
            case 4: searchVehicle(); break;
            case 5: showRecent(); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}