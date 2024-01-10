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





void insertionSortRun(Food*& start, int runSize) {
    if (start == nullptr || runSize <= 1) {
        return; // No need to sort
    }

    Food* sorted = nullptr; // Initially, sorted part is empty
    Food* current = start;  // Starting node of the run
    Food* nextStart = nullptr;

    int count = 0; // To keep track of the number of nodes sorted

    // Sort only the first 'runSize' nodes
    while (current != nullptr && count < runSize) {
        nextStart = current->nextaddrress; // Store next node for the next iteration
        sortedInsert(sorted, current);     // Insert current node in sorted
        current = nextStart;               // Move to the next node in the run
        count++;
    }

    // Link back the sorted run with the remaining list
    start = sorted; // New start is the head of the sorted list
    while (sorted != nullptr && sorted->nextaddrress != nullptr) { // Find the end of the sorted list
        sorted = sorted->nextaddrress;
    }
    if (sorted != nullptr) {
        sorted->nextaddrress = nextStart; // Connect the end of the sorted list to the next unsorted part
    }
}

void sortedInsert(Food*& sortedHead, Food* newNode) {
    // Special case for the head end
    if (sortedHead == nullptr || sortedHead->calories >= newNode->calories) {
        newNode->nextaddrress = sortedHead;
        sortedHead = newNode;
    } else {
        // Locate the node before the point of insertion
        Food* current = sortedHead;
        while (current->nextaddrress != nullptr && current->nextaddrress->calories < newNode->calories) {
            current = current->nextaddrress;
        }
        newNode->nextaddrress = current->nextaddrress;
        current->nextaddrress = newNode;
    }
}

Food* mergeLinkedList(Food* left, Food* right) {
    // Base cases
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    // Start with the smaller element
    Food* head = nullptr;
    if (left->calories <= right->calories) {
        head = left;
        left = left->nextaddrress;
    } else {
        head = right;
        right = right->nextaddrress;
    }

    // Merge the remaining elements
    Food* current = head;
    while (left != nullptr && right != nullptr) {
        if (left->calories <= right->calories) {
            current->nextaddrress = left;
            left = left->nextaddrress;
        } else {
            current->nextaddrress = right;
            right = right->nextaddrress;
        }
        current = current->nextaddrress;
    }

    // Attach the remaining elements
    if (left != nullptr) {
        current->nextaddrress = left;
    } else {
        current->nextaddrress = right;
    }

    return head;
}

void timSortLinkedList(Food*& head, int n) {
    // Step 1: Sort individual sublists of size RUN
    for (int i = 0; i < n; i += RUN) {
        // Get the head of the next run
        Food* runHead = getRunHead(head, i);
        // Sort the run
        insertionSortRun(runHead, min(RUN, n - i));
    }

    // Step 2: Merge sorted runs
    for (int size = RUN; size < n; size = 2 * size) {
        Food* curr = head;
        Food* tail = nullptr;
        while (curr != nullptr) {
            // Left run
            Food* left = curr;
            // Right run starts after 'size' nodes from left run
            Food* right = getRunHead(curr, size);

            // Skip '2 * size' nodes for the next merge
            curr = getRunHead(right, size);

            // Merge left and right runs
            Food* merged = mergeLinkedList(left, right);

            // Connect the merged run with the previous part of the list
            if (tail == nullptr) {
                head = merged;
            } else {
                tail->nextaddrress = merged;
            }

            // Update tail to the end of the merged list
            tail = getTail(merged);
        }
    }
}

// Function to get the head of the run starting at 'startIdx' position
Food* getRunHead(Food* head, int startIdx) {
    while (head != nullptr && startIdx > 0) {
        head = head->nextaddrress;
        startIdx--;
    }
    return head;
}

// Function to get the tail of the list
Food* getTail(Food* head) {
    while (head != nullptr && head->nextaddrress != nullptr) {
        head = head->nextaddrress;
    }
    return head;
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