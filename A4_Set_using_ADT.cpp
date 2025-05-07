/*
A4 : 
        "To create ADT that implement the "set" concept. a. Add (new Element) -Place a value into the set , b. Remove (element) Remove the value c. Contains (element) Return true if element is in collection, d. Size () Return number of values in collection Iterator () Return an iterator used to loop over collection, e. Intersection of two sets , f. Union of two sets, g. Difference between two sets, h. Subset "
*/
#include <iostream>
using namespace std;

const int MAX = 100;

class Set {
    int data[MAX];
    int count;

public:
    Set() {
        count = 0;
    }

    bool contains(int val) {
        for (int i = 0; i < count; ++i)
            if (data[i] == val)
                return true;
        return false;
    }

    void add(int val) {
        if (!contains(val)) {
            if (count < MAX)
                data[count++] = val;
            else
                cout << "Set is full.\n";
        }
    }

    void remove(int val) {
        for (int i = 0; i < count; ++i) {
            if (data[i] == val) {
                for (int j = i; j < count - 1; ++j)
                    data[j] = data[j + 1];
                count--;
                return;
            }
        }
    }

    int size() {
        return count;
    }

    void iterator() {
        cout << "{ ";
        for (int i = 0; i < count; ++i)
            cout << data[i] << " ";
        cout << "}\n";
    }

    Set intersection(Set other) {
        Set result;
        for (int i = 0; i < count; ++i)
            if (other.contains(data[i]))
                result.add(data[i]);
        return result;
    }

    Set unionSet(Set other) {
        Set result;
        for (int i = 0; i < count; ++i)
            result.add(data[i]);
        for (int i = 0; i < other.count; ++i)
            result.add(other.data[i]);
        return result;
    }

    Set difference(Set other) {
        Set result;
        for (int i = 0; i < count; ++i)
            if (!other.contains(data[i]))
                result.add(data[i]);
        return result;
    }

    bool isSubset(Set other) {
        for (int i = 0; i < count; ++i)
            if (!other.contains(data[i]))
                return false;
        return true;
    }
};

// ---------- Main ----------
int main() {
    Set set1, set2, result;
    int choice, val;

    do {
        cout << "\n---- SET ADT MENU ----\n";
        cout << "1. Add to Set1\n2. Add to Set2\n3. Remove from Set1\n4. Contains (Set1)\n";
        cout << "5. Size of Set1\n6. Display Set1\n7. Union\n8. Intersection\n9. Difference (Set1 - Set2)\n";
        cout << "10. Is Set1 subset of Set2?\n11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter element to add to Set1: ";
            cin >> val;
            set1.add(val);
            break;
        case 2:
            cout << "Enter element to add to Set2: ";
            cin >> val;
            set2.add(val);
            break;
        case 3:
            cout << "Enter element to remove from Set1: ";
            cin >> val;
            set1.remove(val);
            break;
        case 4:
            cout << "Enter element to check in Set1: ";
            cin >> val;
            cout << (set1.contains(val) ? "Found\n" : "Not Found\n");
            break;
        case 5:
            cout << "Size of Set1: " << set1.size() << endl;
            break;
        case 6:
            cout << "Set1: ";
            set1.iterator();
            break;
        case 7:
            result = set1.unionSet(set2);
            cout << "Union: ";
            result.iterator();
            break;
        case 8:
            result = set1.intersection(set2);
            cout << "Intersection: ";
            result.iterator();
            break;
        case 9:
            result = set1.difference(set2);
            cout << "Difference (Set1 - Set2): ";
            result.iterator();
            break;
        case 10:
            cout << (set1.isSubset(set2) ? "Set1 is a subset of Set2\n" : "Set1 is not a subset\n");
            break;
        case 11:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 11);

    return 0;
}
