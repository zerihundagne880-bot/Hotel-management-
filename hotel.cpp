#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class Hotel {
    int room_no;
    char name[30], address[50], phone[15];
    int days;
    float total_bill;

public:
    void add_guest() {
        cout << "\nRoom Number: "; cin >> room_no;
        cout << "Guest Name: "; cin.ignore(); cin.getline(name, 30);
        cout << "Address: "; cin.getline(address, 50);
        cout << "Phone Number: "; cin.getline(phone, 15);
        cout << "Number of Days: "; cin >> days;
        total_bill = days * 500; // Rate of 500 per day
        cout << "\n--- Registration Successful! ---\n";
    }

    void show_guest() {
        cout << "\nRoom: " << room_no 
             << " | Name: " << name 
             << " | Bill: $" << total_bill << endl;
    }

    int getRoomNo() { return room_no; }
    float getBill() { return total_bill; }
    char* getName() { return name; }
};

// Simple Authentication
bool login() {
    string pass;
    cout << "\nEnter Admin Password: "; cin >> pass;
    return (pass == "admin123");
}

// Function to handle Check-out (Deletes record from file)
void check_out(int r) {
    ifstream inFile("hotel.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Hotel h; 
    bool found = false;

    if (!inFile) {
        cout << "\nError opening file or no records found.\n";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&h), sizeof(Hotel))) {
        if (h.getRoomNo() == r) {
            found = true;
            cout << "\n--- INVOICE ---" 
                 << "\nGuest: " << h.getName() 
                 << "\nTotal Payment: $" << h.getBill() << "\n";
            cout << "Checked out successfully!\n";
        } else {
            outFile.write(reinterpret_cast<char*>(&h), sizeof(Hotel));
        }
    }

    inFile.close(); 
    outFile.close();

    remove("hotel.dat"); 
    rename("temp.dat", "hotel.dat");

    if (!found) cout << "\nRoom not found or not occupied!\n";
}

int main() {
    if (!login()) { 
        cout << "Access Denied! Incorrect Password.\n"; 
        return 0; 
    }

    Hotel h; 
    int choice;

    while (true) {
        cout << "\n--- Hotel Management System ---";
        cout << "\n1. Book Room";
        cout << "\n2. View All Guests";
        cout << "\n3. Check-out (Bill)";
        cout << "\n4. Exit";
        cout << "\nSelect Option: "; 
        cin >> choice;

        if (choice == 1) {
            ofstream out("hotel.dat", ios::binary | ios::app);
            h.add_guest(); 
            out.write(reinterpret_cast<char*>(&h), sizeof(Hotel));
            out.close();
        } 
        else if (choice == 2) {
            ifstream in("hotel.dat", ios::binary);
            if (!in) {
                cout << "\nNo records found.\n";
            } else {
                while (in.read(reinterpret_cast<char*>(&h), sizeof(Hotel))) {
                    h.show_guest();
                }
            }
            in.close();
        } 
        else if (choice == 3) {
            int r; 
            cout << "Enter Room Number to Check-out: "; 
            cin >> r; 
            check_out(r);
        } 
        else if (choice == 4) {
            cout << "Exiting... Have a nice day!\n";
            break;
        } 
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
