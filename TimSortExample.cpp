#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "NutrientClass.h"


using namespace std;

int main() {
    NutrientClass nutrientClass;

    nutrientClass.LoadFromFile("Nutrients_Info.csv");
    nutrientClass.DisplayLinkedList();
    cout << endl;

    int Size = nutrientClass.getListSize(); 

    FoodCalorieArray* foodCalorieArray = nutrientClass.getFoodCalorieArray();

    for (int i = 0; i < Size; ++i) {
        // cout << "Row " << i+1 << " ";
        foodCalorieArray[i].print();
    }


    delete[] foodCalorieArray;


    return 0;
}
