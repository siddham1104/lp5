#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

// Sequential merge function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential merge sort function
void sequentialMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel merge function
void parallelMerge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Parallel merge sort function
void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                parallelMergeSort(arr, l, m);
            }
#pragma omp section
            {
                parallelMergeSort(arr, m + 1, r);
            }
        }
#pragma omp parallel sections
        {
#pragma omp section
            {
                parallelMerge(arr, l, m, r);
            }
        }
    }
}
// Function to generate random array
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10000; // Random numbers between 0 and 999
    }
}

// Function to display array elements
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << "; ";
    }
    cout << endl;
}

int main() {
    const int SIZE = 10000;
    int arr[SIZE], arr_parallel[SIZE];

    // Generate random array
    generateRandomArray(arr, SIZE);

    //displayArray(arr,SIZE);
    
    // Sequential merge sort
    clock_t startTime = clock();
    sequentialMergeSort(arr, 0, SIZE - 1);
    clock_t endTime = clock();
    
    displayArray(arr,SIZE);
    
    cout << "Sequential Merge Sort Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    // Generate random array again for parallel sorting
    generateRandomArray(arr_parallel, SIZE);

    //displayArray(arr_parallel,SIZE);
    
    // Parallel merge sort
    startTime = clock();
    parallelMergeSort(arr_parallel, 0, SIZE - 1);
    endTime = clock();
    
    displayArray(arr_parallel,SIZE);
    
    cout << "Parallel Merge Sort Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}