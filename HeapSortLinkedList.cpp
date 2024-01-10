#include <chrono>
#include "NutrientClass.h"
using namespace std;
using namespace std::chrono;

Food* heapify(Food* arr, int size, int i)
{
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < size && arr[leftChild].calories > arr[largest].calories)
    {
        largest = leftChild;
    }

    if (rightChild < size && arr[rightChild].calories > arr[largest].calories)
    {
        largest = rightChild;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
    return arr;
}

Food* sortArray(Food* arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--)
    {
        int temp = arr[0].calories;
        arr[0].calories = arr[i].calories;
        arr[i].calories = temp;
        
        heapify(arr, i, 0);
    }

    return arr;
}

Food* heapSort(Food* head) {
    int size = 0;
    Food* current = head;
    while (current != nullptr) {
        size++;
        current = current->nextaddrress;
    }

    Food* arr = new Food[size];
    current = head;
    int index = 0;

    while (current != nullptr) {
        arr[index] = *current;
        current = current->nextaddrress;
        ++index;
    }

    sortArray(arr, size);

    current = head;
    for (int i = 0; i < size; ++i) {
        current->calories = arr[i].calories;
        current = current->nextaddrress;
    }

    delete[] arr;
    return head;
}

int main() {
    NutrientClass nutrientList;
    nutrientList.LoadFromFile("Nutrients_Info.csv");

    cout << "Before Sorting:(Linked List)" << endl;
    nutrientList.printHeader();
    nutrientList.DisplayLinkedList();

    auto timestart = high_resolution_clock::now();
    nutrientList.setHead(heapSort(nutrientList.getHead()));

    cout << "\n\n\nAfter Sorting:" << endl;
    nutrientList.printHeader();
    nutrientList.DisplayLinkedList();

    auto timeend = high_resolution_clock::now();

    auto durationgap = duration_cast<microseconds>(timeend - timestart);
    cout << "\nTime taken by merge sort algorithm(Lineked List) is: " << durationgap.count() << " microseconds" << endl;
    
    return 0;
}
