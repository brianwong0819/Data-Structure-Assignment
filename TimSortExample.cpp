#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include "NutrientClass.h"


using namespace std;
using namespace std::chrono;

const int RUN = 32;

void insertionSort(FoodCalorieArray arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        FoodCalorieArray temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j].calories > temp.calories) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void merge(FoodCalorieArray arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    FoodCalorieArray* left = new FoodCalorieArray[len1];
    FoodCalorieArray* right = new FoodCalorieArray[len2];

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        if (left[i].calories <= right[j].calories) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }

    delete[] left;
    delete[] right;
}

void timSort(FoodCalorieArray arr[], int n) {
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + 31), (n - 1)));

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

int main() {
    NutrientClass nutrientClass;

    // Load data and get the array
    nutrientClass.LoadFromFile("Nutrients_Info.csv");
    int Size = nutrientClass.getListSize(); 
    FoodCalorieArray* foodCalorieArray = nutrientClass.getFoodCalorieArray();

    cout << "Array before sorting: " << endl;
    nutrientClass.printHeader();
    // Print array before sorting
    for (int i = 0; i < Size; ++i) {
        // cout << "Row " << i+1 << " ";
        foodCalorieArray[i].print();
    }

    auto timestart = high_resolution_clock::now();
    // Sort the array
    timSort(foodCalorieArray, Size);

    cout << endl << "Array after sorting: " << endl;
    nutrientClass.printHeader();
    // Print array after sorting
    for (int i = 0; i < Size; ++i) {
        // cout << "Row " << i << ": ";
        foodCalorieArray[i].print();
    }

    nutrientClass.binarySearch(foodCalorieArray, 505, Size);
    auto timeend = high_resolution_clock::now();

    auto durationgap = duration_cast<microseconds>(timeend - timestart);
    cout << "Time taken by Tim Sort algorithm is: " << durationgap.count() << " microseconds" << endl;
    // Clean up
    delete[] foodCalorieArray;

    return 0;
}