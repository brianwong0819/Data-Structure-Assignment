#include <chrono>
#include "NutrientClass.h"
using namespace std;
using namespace std::chrono;

void heapify(FoodCalorieArray arr[], int n, int i)
{
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild].calories > arr[largest].calories)
    {
        largest = leftChild;
    }

    if (rightChild < n && arr[rightChild].calories > arr[largest].calories)
    {
        largest = rightChild;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(FoodCalorieArray arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    NutrientClass nutrientClass;
    nutrientClass.LoadFromFile("Nutrients_Info.csv");

    int size = nutrientClass.getListSize();
    FoodCalorieArray* arr = nutrientClass.getFoodCalorieArray();

    cout << "Before Sorting:" << endl;
    nutrientClass.printHeader();
    for (int i = 0; i < size; ++i)
    {
        arr[i].print();
    }

    auto timestart = high_resolution_clock::now();
    heapSort(arr, size);

    cout << "\nAfter Sorting:" << endl;
    nutrientClass.printHeader();
    for (int i = 0; i < size; ++i)
    {
        arr[i].print();
    }

    auto timeend = high_resolution_clock::now();
    auto durationgap = duration_cast<microseconds>(timeend - timestart);
    cout << "Time taken by heap sort algorithm(Array) is: " << durationgap.count() << " microseconds" << endl;

    delete[] arr;

    return 0;
}
