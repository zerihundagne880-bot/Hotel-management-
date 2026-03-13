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
        cout << "\nየክፍል ቁጥር: "; cin >> room_no;
        cout << "ስም: "; cin.ignore(); cin.getline(name, 30);
        cout << "አድራሻ: "; cin.getline(address, 50);
        cout << "ስልክ: "; cin.getline(phone, 15);
        cout << "ቀናት: "; cin >> days;
        total_bill = days * 500;
        cout << "\n--- ተመዝግቧል! ---\n";
    }
    void show_guest() {
        cout << "\nክፍል: " << room_no << " | ስም: " << name << " | ሂሳብ: " << total_bill << " ብር\n";
    }
    int getRoomNo() { return room_no; }
    float getBill() { return total_bill; }
    char* getName() { return name; }
};

bool login() {
    string pass;
    cout << "\nየይለፍ ቃል ያስገቡ: "; cin >> pass;
    return (pass == "admin123");
}

void check_out(int r) {
    ifstream inFile("hotel.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Hotel h; bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&h), sizeof(Hotel))) {
        if (h.getRoomNo() == r) {
            found = true;
            cout << "\n--- ደረሰኝ ---\nእንግዳ: " << h.getName() << "\nክፍያ: " << h.getBill() << " ብር\n";
        } else outFile.write(reinterpret_cast<char*>(&h), sizeof(Hotel));
    }
    inFile.close(); outFile.close();
    remove("hotel.dat"); rename("temp.dat", "hotel.dat");
    if (!found) cout << "\nክፍሉ አልተገኘም!\n";
}

int main() {
    if (!login()) { cout << "ስህተት!"; return 0; }
    Hotel h; int ch;
    while (true) {
        cout << "\n1.መመዝገብ 2.ማየት 3.መውጣት 4.ዝጋ\nምርጫ: "; cin >> ch;
        if (ch == 1) {
            ofstream out("hotel.dat", ios::binary | ios::app);
            h.add_guest(); out.write(reinterpret_cast<char*>(&h), sizeof(Hotel));
            out.close();
        } else if (ch == 2) {
            ifstream in("hotel.dat", ios::binary);
            while (in.read(reinterpret_cast<char*>(&h), sizeof(Hotel))) h.show_guest();
            in.close();
        } else if (ch == 3) {
            int r; cout << "የክፍል ቁጥር: "; cin >> r; check_out(r);
        } else if (ch == 4) break;
    }
    return 0;
}
