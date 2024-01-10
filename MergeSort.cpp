#include "NutrientClass.h"  

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

// 对外提供的排序接口
void sortLinkedList(NutrientClass& nutrientData) {
    Food* sortedHead = mergeSort(nutrientData.getHead());
    nutrientData.setHead(sortedHead);
}

int main() {
    NutrientClass nutrientData;

    nutrientData.LoadFromFile("Nutrients_Info.csv");

    std::cout << "Before Sorting:" << std::endl;
    nutrientData.DisplayLinkedList();

    sortLinkedList(nutrientData);

    std::cout << "\n\n\nAfter Sorting:" << std::endl;
    nutrientData.DisplayLinkedList();

    return 0;
}
