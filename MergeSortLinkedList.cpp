#include <chrono>
#include "NutrientClass.h"

using namespace std;
using namespace std::chrono;

// merge two sorted linked list
Food* merge(Food* a, Food* b) {
    Food* result = nullptr;

    if (a == nullptr) 
        return b;
    else if (b == nullptr) 
        return a;

    if (a->calories <= b->calories) {
        result = a;
        result->nextaddrress = merge(a->nextaddrress, b);
    } else {
        result = b;
        result->nextaddrress = merge(a, b->nextaddrress);
    }

    return result;
}

//find out the middle of the linked list and split it 
Food* getMiddle(Food* head) {
    if (head == nullptr || head->nextaddrress == nullptr) {
        return head;
    }

    Food* slow = head;
    Food* fast = head->nextaddrress;

    while (fast != nullptr) {
        fast = fast->nextaddrress;
        if (fast != nullptr) {
            slow = slow->nextaddrress;
            fast = fast->nextaddrress;
        }
    }

    return slow;
}

//merge sort
Food* mergeSort(Food* head) {
    if (head == nullptr || head->nextaddrress == nullptr) {
        return head;
    }

    Food* middle = getMiddle(head);
    Food* nextOfMiddle = middle->nextaddrress;

    middle->nextaddrress = nullptr;

    Food* left = mergeSort(head);
    Food* right = mergeSort(nextOfMiddle);

    Food* sortedList = merge(left, right);

    return sortedList;
}

void sortLinkedList(NutrientClass& nutrientData) {
    Food* sortedHead = mergeSort(nutrientData.getHead());
    nutrientData.setHead(sortedHead);
}

int main() {
    NutrientClass nutrientData;

    nutrientData.LoadFromFile("Nutrients_Info.csv");

    //Linked List

    std::cout << "Before Sorting:(Linked List)" << std::endl;
    nutrientData.printHeader();
    nutrientData.DisplayLinkedList();

    sortLinkedList(nutrientData);

    std::cout << "\n\n\nAfter Sorting:" << std::endl;
    nutrientData.printHeader();   
    nutrientData.DisplayLinkedList();

    auto timestart = high_resolution_clock::now();
    sortLinkedList(nutrientData);
    std::cout << "\n\n\nAfter Sorting:(Linked List)" << std::endl;
    nutrientData.DisplayLinkedList();

    auto timeend = high_resolution_clock::now();

    auto durationgap = duration_cast<microseconds>(timeend - timestart);
    cout << "Time taken by merge sort algorithm(Lineked List) is: " << durationgap.count() << " microseconds" << endl;
    
    return 0;
}