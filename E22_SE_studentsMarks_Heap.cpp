/*
Problem Statement: E22
Read the marks obtained by students of second year in an online examination 
of a particular subject. Find out the maximum and minimum marks obtained 
in that subject. Use heap data structure. Analyze the algorithm.
*/

#include <iostream>
using namespace std;

void maxHeapify(int arr[], int n, int i) {
    int largest = i; 
    int l = 2*i + 1; 
    int r = 2*i + 2; 

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        maxHeapify(arr, n, largest);
    }
}

void minHeapify(int arr[], int n, int i) {
    int smallest = i; 
    int l = 2*i + 1; 
    int r = 2*i + 2; 

    if (l < n && arr[l] < arr[smallest])
        smallest = l;

    if (r < n && arr[r] < arr[smallest])
        smallest = r;

    if (smallest != i) {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        minHeapify(arr, n, smallest);
    }
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    int marks[100]; // assuming max 100 students
    cout << "Enter marks:\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> marks[i];
    }

    // Build Max-Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(marks, n, i);

    int maxMarks = marks[0];

    // Build Min-Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(marks, n, i);

    int minMarks = marks[0];

    cout << "\nMaximum Marks: " << maxMarks << endl;
    cout << "Minimum Marks: " << minMarks << endl;

    return 0;
}
