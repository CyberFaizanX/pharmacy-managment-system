#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

const int MAX_MEDICINES = 100;
const string MEDICINES_FILE = "medi.txt";

struct Medicine {
    int id;
    string name;
    double mg;
    int quantity;
    double price;
};

int numMedicines = 0;

void validateInput(int& variable, const string& prompt) {
    while (true) {
        cout << prompt;
        if (cin >> variable && cin.peek() == '\n') {
            break;
        } else {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

void validateInput(double& variable, const string& prompt) {
    while (true) {
        cout << prompt;
        if (cin >> variable && cin.peek() == '\n') {
            break;
        } else {
            cout << "Invalid input. Please enter a valid double." << endl;
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        }
    }
} 

void validateInput(string& variable, const string& prompt) {
    cout << prompt;
    cin >> variable;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
}

void addMedicine() {
    Medicine newMedicine;
    
    validateInput(newMedicine.id, "Enter ID: ");
    validateInput(newMedicine.name, "Enter Name: ");
    validateInput(newMedicine.mg, "Enter MG: ");
    validateInput(newMedicine.quantity, "Enter Quantity: ");
    validateInput(newMedicine.price, "Enter Price: ");
    
    if (numMedicines < MAX_MEDICINES) {
        ofstream out(MEDICINES_FILE, ios::app);
        if (!out) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }
        out << newMedicine.id << endl
            << newMedicine.name << endl
            << newMedicine.mg << endl
            << newMedicine.quantity << endl
            << newMedicine.price << endl;
        out.close();
        numMedicines++;
        cout << "Medicine added successfully." << endl;
    } else {
        cout << "Error: Maximum medicines limit reached." << endl;
    }
}

void deleteMedicine() {
    int delID;
    cout << "Enter Medicine ID to delete: ";
    validateInput(delID, "");
    
    ifstream in(MEDICINES_FILE);
    if (!in) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    Medicine temp;
    bool found = false;
    ofstream out("temp.txt");
    while (in >> temp.id >> temp.name >> temp.mg >> temp.quantity >> temp.price) {
        if (temp.id != delID) {
            out << temp.id << endl
                << temp.name << endl
                << temp.mg << endl
                << temp.quantity << endl
                << temp.price << endl;
        } else {
            found = true;
        }
    }
    in.close();
    out.close();

    remove(MEDICINES_FILE.c_str());
    rename("temp.txt", MEDICINES_FILE.c_str());

    if (found) {
        cout << "Medicine deleted successfully." << endl;
        numMedicines--;
    } else {
        cout << "Medicine with ID " << delID << " not found." << endl;
    }
}

void displayAllMedicines() {
    ifstream in(MEDICINES_FILE);
    if (!in) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    Medicine temp;
    cout << "List of all medicines:\n";
    while (in >> temp.id >> temp.name >> temp.mg >> temp.quantity >> temp.price) {
        cout << "ID: " << temp.id << ", "
             << "Name: " << temp.name << ", "
             << "MG: " << temp.mg << ", "
             << "Quantity: " << temp.quantity << ", "
             << "Price: " << temp.price << endl;
    }
    in.close();
}

void saveMedicines() {
    // Functionality to save medicines is already included in addMedicine() function.
    // No need for a separate function.
    cout << "Medicines are automatically saved after addition." << endl;
}

int main() {
    int choice;
    do {
        cout << "\nPharmacy Management System\n";
        cout << "1. Add Medicine\n";
        cout << "2. Delete Medicine\n";
        cout << "3. Display All Medicines\n";
        cout << "4. Save Medicines\n";
        cout << "5. Clear Screen\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        validateInput(choice, "");

        switch(choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                deleteMedicine();
                break;
            case 3:
                displayAllMedicines();
                break;
            case 4:
                saveMedicines();
                break;
            case 5:
                system("cls");
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
