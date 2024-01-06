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

    return 0;
}
