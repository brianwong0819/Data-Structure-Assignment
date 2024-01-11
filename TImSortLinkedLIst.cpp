#include <chrono>
#include "NutrientClass.h"


using namespace std;
using namespace std::chrono;

const int RUN = 32;


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
}