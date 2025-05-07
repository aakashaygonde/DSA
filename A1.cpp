/* 
A1 : 
        "Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number. Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers"
*/

#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;
const int MAX_CHAIN = 5;

// ---------- FORWARD DECLARATION ----------
int hashFunc(string key);

// ---------- LINEAR PROBING ----------
struct Client {
    string name;
    string phone;
    bool occupied;

    Client() {
        name = "";
        phone = "";
        occupied = false;
    }
};

class HashTableLinear {
    Client table[TABLE_SIZE];

public:
    void insert(string name, string phone) {
        int index = hashFunc(name);
        int originalIndex = index;

        while (table[index].occupied) {
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                cout << "Hash table is full (Linear Probing)\n";
                return;
            }
        }

        table[index].name = name;
        table[index].phone = phone;
        table[index].occupied = true;
    }

    int search(string name) {
        int index = hashFunc(name);
        int comparisons = 1;

        while (table[index].occupied) {
            if (table[index].name == name)
                return comparisons;
            index = (index + 1) % TABLE_SIZE;
            comparisons++;
            if (comparisons > TABLE_SIZE)
                break;
        }
        return comparisons;
    }
};

// ---------- CHAINING ----------
struct ChainNode {
    string name;
    string phone;
    bool occupied;

    ChainNode() {
        name = "";
        phone = "";
        occupied = false;
    }
};

class HashTableChaining {
    ChainNode table[TABLE_SIZE][MAX_CHAIN];

public:
    void insert(string name, string phone) {
        int index = hashFunc(name);

        for (int i = 0; i < MAX_CHAIN; ++i) {
            if (!table[index][i].occupied) {
                table[index][i].name = name;
                table[index][i].phone = phone;
                table[index][i].occupied = true;
                return;
            }
        }

        cout << "Chain full at index " << index << " (Chaining)\n";
    }

    int search(string name) {
        int index = hashFunc(name);
        int comparisons = 0;

        for (int i = 0; i < MAX_CHAIN; ++i) {
            if (table[index][i].occupied) {
                comparisons++;
                if (table[index][i].name == name)
                    return comparisons;
            }
        }

        return comparisons;
    }
};

// ---------- HASH FUNCTION ----------
int hashFunc(string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); ++i)
        hash = (hash * 31 + key[i]) % TABLE_SIZE;
    return hash;
}

// ---------- MAIN ----------
int main() {
    HashTableLinear linear;
    HashTableChaining chaining;
    string insertedNames[100];
    int totalClients = 0;

    int choice;
    do {
        cout << "\n--- TELEPHONE DIRECTORY MENU ---\n";
        cout << "1. Insert Client\n";
        cout << "2. Search Client\n";
        cout << "3. Display Average Comparisons\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, phone;
            cout << "Enter client name: ";
            cin >> name;
            cout << "Enter phone number: ";
            cin >> phone;
            linear.insert(name, phone);
            chaining.insert(name, phone);
            insertedNames[totalClients++] = name;
            break;
        }
        case 2: {
            string name;
            cout << "Enter name to search: ";
            cin >> name;
            int l = linear.search(name);
            int c = chaining.search(name);
            cout << "Comparisons - Linear: " << l << ", Chaining: " << c << endl;
            break;
        }
        case 3: {
            if (totalClients == 0) {
                cout << "No clients inserted yet.\n";
                break;
            }
            int totalL = 0, totalC = 0;
            for (int i = 0; i < totalClients; ++i) {
                totalL += linear.search(insertedNames[i]);
                totalC += chaining.search(insertedNames[i]);
            }
            cout << "Average Comparisons:\n";
            cout << "Linear Probing: " << (float)totalL / totalClients << endl;
            cout << "Chaining: " << (float)totalC / totalClients << endl;
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
