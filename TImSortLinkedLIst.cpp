#include <chrono>
#include "NutrientClass.h"

using namespace std;
using namespace std::chrono;


using namespace std;
// Utility function to get the start of a run
Food* getRunStart(Food* head, int startIndex) {
    Food* current = head;
    while (startIndex > 0 && current != nullptr) {
        current = current->nextaddrress;
        --startIndex;
    }
    return current;
}

// Utility function to get the tail of a run
Food* getTail(Food* start, int runSize) {
    while (runSize > 1 && start != nullptr && start->nextaddrress != nullptr) {
        start = start->nextaddrress;
        --runSize;
    }
    return start;
}

// Function to merge two sorted runs
Food* sortedMerge(Food* a, Food* b) {
    Food dummy;
    Food* tail = &dummy;
    dummy.nextaddrress = nullptr;

    while (a != nullptr && b != nullptr) {
        if (a->calories <= b->calories) {
            tail->nextaddrress = a;
            a = a->nextaddrress;
        } else {
            tail->nextaddrress = b;
            b = b->nextaddrress;
        }
        tail = tail->nextaddrress;
    }

    tail->nextaddrress = (a != nullptr) ? a : b;
    return dummy.nextaddrress;
}

// Function for insertion sort on a sub-list
void insertionSort(Food*& start, int runSize) {
    if (start == nullptr || runSize < 2) return;

    Food* sorted = nullptr;
    Food* current = start;

    while (runSize > 0 && current != nullptr) {
        Food* next = current->nextaddrress;
        Food* sortedPrev = nullptr;
        Food* sortedCurr = sorted;

        while (sortedCurr != nullptr && sortedCurr->calories < current->calories) {
            sortedPrev = sortedCurr;
            sortedCurr = sortedCurr->nextaddrress;
        }

        current->nextaddrress = sortedCurr;
        if (sortedPrev == nullptr) sorted = current;
        else sortedPrev->nextaddrress = current;

        current = next;
        --runSize;
    }

    start = sorted;
}

void timSortLinkedList(Food*& head, int n, const int RUN) {
    for (int i = 0; i < n; i += RUN) {
        Food* runStart = getRunStart(head, i);
        insertionSort(runStart, RUN);

        Food* runEnd = getTail(runStart, RUN);
        Food* nextRunStart = (runEnd != nullptr) ? runEnd->nextaddrress : nullptr;

        if (i == 0) head = runStart;
        if (runEnd != nullptr) runEnd->nextaddrress = nullptr;
    }

    for (int size = RUN; size < n; size *= 2) {
        Food* current = head;
        Food* prevTail = nullptr;
        Food* newHead = nullptr;

        while (current != nullptr) {
            Food* left = current;
            Food* leftEnd = getTail(left, size);

            if (leftEnd == nullptr) break;

            Food* right = leftEnd->nextaddrress;
            leftEnd->nextaddrress = nullptr;

            Food* rightEnd = getTail(right, size);
            Food* remaining = (rightEnd != nullptr) ? rightEnd->nextaddrress : nullptr;
            if (rightEnd != nullptr) rightEnd->nextaddrress = nullptr;

            Food* merged = sortedMerge(left, right);

            if (prevTail == nullptr) newHead = merged;
            else prevTail->nextaddrress = merged;

            prevTail = getTail(merged, size * 2);
            current = remaining;
        }

        head = newHead;
    }
}


// Main function
int main() {
    NutrientClass nutrientClass;
    // Load data
    nutrientClass.LoadFromFile("Nutrients_Info.csv");

    cout << "Linked list before sorting:" << endl;
    nutrientClass.DisplayLinkedList();

    // Sorting
    const int RUN = 328;
    Food* sortedHead = nutrientClass.getHead();
    auto timestart = high_resolution_clock::now();
    timSortLinkedList(sortedHead, nutrientClass.getListSize(), RUN);
    nutrientClass.setHead(sortedHead);

    cout << "\nLinked list after sorting:" << endl;
    nutrientClass.printHeader();
    nutrientClass.DisplayLinkedList();

    nutrientClass.binarySearchLinkedList(505);
    auto timeend = high_resolution_clock::now();

    auto durationgap = duration_cast<microseconds>(timeend - timestart);
    cout << "Time taken by Tim Sort algorithm(Linked List) is: " << durationgap.count() << " microseconds" << endl;
    return 0;
}
