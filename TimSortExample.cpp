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




Food* getRunHead(Food* head, int startIdx) {
    while (head != nullptr && startIdx > 0) {
        head = head->nextaddrress;
        startIdx--;
    }
    return head;
}

// Function to get the tail of the list
Food* getTail(Food* head) {
    if (head == nullptr) return nullptr;
    while (head->nextaddrress != nullptr) {
        head = head->nextaddrress;
    }
    return head;
}

void sortedInsert(Food*& sortedHead, Food* newNode) {
    if (sortedHead == nullptr || sortedHead->calories >= newNode->calories) {
        newNode->nextaddrress = sortedHead;
        sortedHead = newNode;
    } else {
        Food* current = sortedHead;
        while (current->nextaddrress != nullptr && current->nextaddrress->calories < newNode->calories) {
            current = current->nextaddrress;
        }
        newNode->nextaddrress = current->nextaddrress;
        current->nextaddrress = newNode;
    }
}

void insertionSortRun(Food*& start, int runSize) {
    if (start == nullptr || runSize <= 1) {
        return;
    }

    Food* sorted = nullptr;
    Food* current = start;
    Food* nextStart = nullptr;
    int count = 0;

    while (current != nullptr && count < runSize) {
        nextStart = current->nextaddrress;
        sortedInsert(sorted, current);
        current = nextStart;
        count++;
    }

    start = sorted;
    // Ensure the end of this sorted run points to the next part of the list
    Food* tail = sorted;
    while (tail->nextaddrress != nullptr) {
        tail = tail->nextaddrress;
    }
    tail->nextaddrress = nextStart;
}


Food* mergeLinkedList(Food* left, Food* right) {
    if (!left) return right;
    if (!right) return left;

    Food* mergedHead = nullptr;
    if (left->calories <= right->calories) {
        mergedHead = left;
        left = left->nextaddrress;
    } else {
        mergedHead = right;
        right = right->nextaddrress;
    }

    Food* mergedTail = mergedHead;
    while (left && right) {
        if (left->calories <= right->calories) {
            mergedTail->nextaddrress = left;
            left = left->nextaddrress;
        } else {
            mergedTail->nextaddrress = right;
            right = right->nextaddrress;
        }
        mergedTail = mergedTail->nextaddrress;
    }

    if (left) mergedTail->nextaddrress = left;
    else mergedTail->nextaddrress = right;

    return mergedHead;
}


void timSortLinkedList(Food*& head, int n) {
    // Sorting individual runs
    for (int i = 0; i < n; i += RUN) {
        Food* runHead = getRunHead(head, i);
        insertionSortRun(runHead, min(RUN, n - i));
        // Update head if sorting the first run
        if (i == 0) head = runHead;
    }

    // Merging runs
    for (int size = RUN; size < n; size = 2 * size) {
        Food* curr = head;
        Food* tail = nullptr;

        while (curr != nullptr) {
            Food* left = curr;
            Food* right = getRunHead(curr, size);
            curr = getRunHead(right, size);

            Food* merged = mergeLinkedList(left, right);

            if (tail == nullptr) {
                head = merged;
            } else {
                tail->nextaddrress = merged;
            }

            tail = getTail(merged);
        }
    }
}


int main() {
    NutrientClass nutrientClass;

    // Load data and get the array
    // nutrientClass.LoadFromFile("Nutrients_Info.csv");
    // int Size = nutrientClass.getListSize(); 
    // FoodCalorieArray* foodCalorieArray = nutrientClass.getFoodCalorieArray();

    // cout << "Array before sorting: " << endl;
    // nutrientClass.printHeader();
    // // Print array before sorting
    // for (int i = 0; i < Size; ++i) {
    //     // cout << "Row " << i+1 << " ";
    //     foodCalorieArray[i].print();
    // }

    // auto timestart = high_resolution_clock::now();
    // // Sort the array
    // timSort(foodCalorieArray, Size);

    // cout << endl << "Array after sorting: " << endl;
    // nutrientClass.printHeader();
    // // Print array after sorting
    // for (int i = 0; i < Size; ++i) {
    //     // cout << "Row " << i << ": ";
    //     foodCalorieArray[i].print();
    // }

    // nutrientClass.binarySearch(foodCalorieArray, 505, Size);
    // auto timeend = high_resolution_clock::now();

    // auto durationgap = duration_cast<microseconds>(timeend - timestart);
    // cout << "Time taken by Tim Sort algorithm is: " << durationgap.count() << " microseconds" << endl;
    // // Clean up
    // delete[] foodCalorieArray;

    nutrientClass.LoadFromFile("Nutrients_Info.csv");

    // Assuming getHead() returns a pointer to the head of the linked list
    Food* head = nutrientClass.getHead();

    // Assuming getListSize() returns the number of elements in the list
    int listSize = nutrientClass.getListSize();

    // Print the linked list before sorting
    cout << "Linked List before sorting:" << endl;
    nutrientClass.DisplayLinkedList();

    // Sort the linked list using TimSort
    timSortLinkedList(head, listSize); // Make sure timSortLinkedList is accessible here, potentially as a friend function

    // Update the head in nutrientClass in case it has changed
    nutrientClass.setHead(head);

    // Print the linked list after sorting
    cout << "\nLinked List after sorting:" << endl;
    nutrientClass.DisplayLinkedList();

    return 0;
}