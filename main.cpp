/*
CMPE242 - Term Project
*/


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
using namespace std;

class Sort {
private:
    int step = 1;

    void printStep(string label, string operation, int arr[], int n) {
        cout << left << setw(10) << label << "Step " << setw(8) << step << setw(20) << operation;

        display(arr, n);
        step++;
    }

    void heapify(int arr[], int n, int i, int fullSize, long long &opCount, bool showSteps) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        opCount += 5;

        opCount++;
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
            opCount++;
        }

        opCount++;
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
            opCount++;
        }

        opCount++;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            opCount += 3;

            if (showSteps)
                printStep("Heap", "heapify swap", arr, fullSize);

            heapify(arr, n, largest, fullSize, opCount, showSteps);
            opCount++;
        }
    }

public:
    void heapSort(int arr[], int n, long long &opCount, bool showSteps) {
        step = 1;

        for (int i = n / 2 - 1; i >= 0; i--) {
            opCount++;
            heapify(arr, n, i, n, opCount, showSteps);
        }

        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            opCount += 3;

            if (showSteps)
                printStep("Heap", "max to end swap", arr, n);

            heapify(arr, i, 0, n, opCount, showSteps);
            opCount++;
        }
    }

    void quickSort(int arr[], int low, int high) {
        cout << "Ekleyin abi" << endl;
    }

    void insertionSort(int arr[], int n, long long &opCount, bool showSteps) {
        step = 1;

        for (int i = 1; i < n; i++) {
            opCount++;

            int key = arr[i];
            opCount++;

            int j = i - 1;
            opCount++;

            bool shifted = false;

            while (j >= 0 && arr[j] > key) {
                opCount += 2;

                arr[j + 1] = arr[j];
                opCount++;

                shifted = true;
                opCount++;

                if (showSteps)
                    printStep("Insertion", "insertion shift", arr, n);

                j--;
                opCount++;
            }

            opCount++;

            arr[j + 1] = key;
            opCount++;

            if (showSteps && shifted)
                printStep("Insertion", "insertion place", arr, n);
        }
    }

    void selectionSort(int arr[], int n, long long &opCount, bool showSteps) {
        step = 1;

        for (int i = 0; i < n - 1; i++) {
            opCount++;
            int min_idx = i;
            opCount++;

            for (int j = i + 1; j < n; j++) {
                opCount++;
                opCount++;
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                    opCount++;
                }
            }

            opCount++;
            if (min_idx != i) {
                swap(arr[min_idx], arr[i]);
                opCount += 3;

                if (showSteps)
                    printStep("Selection", "selection swap", arr, n);
            }
        }
    }

    void compareAllAlgorithms() {
        int sizes[] = {100, 200, 300, 1000};
        int repeat = 20;

        cout << left << setw(15) << "Algorithm" << setw(12) << "n" << setw(12) << "Repeat" << setw(18)
        << "Avg opCount" << setw(15) << "T/n" << setw(15) << "T/n^2" << setw(15) << "T/logn" << endl;

        for (int a = 1; a <= 4; a++) {
            for (int s = 0; s < 4; s++) {
                int n = sizes[s];
                long long totalCost = 0;

                for (int r = 0; r < repeat; r++) {
                    int* arr = new int[n];

                    for (int i = 0; i < n; i++) {
                        arr[i] = rand() % 10000;
                    }

                    long long opCount = 0;

                    if (a == 1) { quickSort(arr, 0, n - 1); }
                    else if (a == 2) { insertionSort(arr, n, opCount, false); }
                    else if (a == 3) { heapSort(arr, n, opCount, false); }
                    else if (a == 4) { selectionSort(arr, n, opCount, false); }

                    totalCost += opCount;
                    delete[] arr;
                }

                double avg = totalCost / (double)repeat;

                string name;
                if (a == 1) name = "Quick";
                else if (a == 2) name = "Insertion";
                else if (a == 3) name = "Heap";
                else name = "Selection";

                cout << left << setw(15) << name << setw(12) << n << setw(12)
                << repeat << setw(18) << avg << setw(15) << avg / n << setw(15)
                << avg / (n * n) << setw(15) << avg / log2(n) << endl;
            }

            cout << endl;
        }
    }

    void display(int arr[], int n) {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";

        cout << endl;
    }
};

int main() {
    srand(time(0));

    Sort s;

    int arr[] = {45, 12, 89, 33, 7, 24};
    int n = sizeof(arr) / sizeof(arr[0]);

    int choice;

    cout << "Original Array: ";
    s.display(arr, n);

    cout << "\n1. Quick Sort\n";
    cout << "2. Insertion Sort\n";
    cout << "3. Heap Sort\n";
    cout << "4. Selection Sort\n";
    cout << "5. Compare All Algorithms Cost Table\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        s.quickSort(arr, 0, n - 1);
        break;

    case 2: {
        long long opCount = 0;
        s.insertionSort(arr, n, opCount, true);
        cout << "Total opCount: " << opCount << endl;
        break;
    }

    case 3: {
        long long opCount = 0;
        s.heapSort(arr, n, opCount, true);
        cout << "Total opCount: " << opCount << endl;
        break;
    }

    case 4: {
        long long opCount = 0;
        s.selectionSort(arr, n, opCount, true);
        cout << "Total opCount: " << opCount << endl;
        break;
    }

    case 5:
        s.compareAllAlgorithms();
    break;
    
    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}