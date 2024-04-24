#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void sequentialbubble(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelbubble(int arr[], int n)
{
#pragma omp parallel for shared(arr)
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; j += 1)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void generaterandomarray(int arr[], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}

void displayarray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i]<<";";
    }

    cout << endl;
}

int main()
{

    const int size = 10;
    int arr[size];

    generaterandomarray(arr, size);

    clock_t startTime = clock();
    sequentialbubble(arr, size);
    clock_t endTime = clock();
    displayarray(arr,size);
    cout << "performance:" << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;
    ;

    generaterandomarray(arr, size);

    startTime = clock();
    parallelbubble(arr, size);
    endTime = clock();
    displayarray(arr,size);
    cout << "performance:" << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;
    ;

    return 0;
}