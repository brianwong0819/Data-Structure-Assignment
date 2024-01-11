#include <chrono>
#include "NutrientClass.h"

using namespace std;
using namespace std::chrono;

void merge(FoodCalorieArray arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    FoodCalorieArray *L = new FoodCalorieArray[n1];
    FoodCalorieArray *R = new FoodCalorieArray[n2];

    // copy data to temporary array
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].calories <= R[j].calories) {
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

    delete [] L;
    delete [] R;
}

void mergeSort(FoodCalorieArray arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    NutrientClass nutrientData;

    nutrientData.LoadFromFile("Nutrients_Info.csv");
    int Size = nutrientData.getListSize(); 
    FoodCalorieArray* foodCalorieArray = nutrientData.getFoodCalorieArray();

    cout << "Array before sorting: " << endl;
    nutrientData.printHeader();
    for (int i = 0; i < Size; ++i) {
        cout << "Row " << i+1 << " ";
        foodCalorieArray[i].print(i + 1);
    }

    auto timestart = high_resolution_clock::now();
    mergeSort(foodCalorieArray, 0, Size - 1);


    cout << endl << "\n\nArray after sorting: " << endl;
    nutrientData.printHeader();
    for (int i = 0; i < Size; ++i) {
        cout << "Row " << i << ": ";
        foodCalorieArray[i].print(i + 1);
    }

    nutrientData.binarySearch(foodCalorieArray, 505, Size);
    auto timeend = high_resolution_clock::now();

    auto durationgap = duration_cast<microseconds>(timeend - timestart);
    cout << "Time taken by merge sort algorithm(Array) is: " << durationgap.count() << " microseconds" << endl;
    delete[] foodCalorieArray;
    
}
