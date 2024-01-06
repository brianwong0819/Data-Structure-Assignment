#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "NutrientClass.h"

using namespace std;

// Function to remove all quotes and commas from a string
string cleanField(const string& field) {
    string result;
    for (char c : field) {
        if (c != ',' && c != '"') result += c;
    }
        return result;
}

string getNextField(stringstream& ss) {
    string field, part;
    if (!getline(ss, part, ',')) return "";

    if (part.size() > 0 && part[0] == '"') {
        // Combine fields until the closing quote is found
        do {
            field += part;
            if (part.size() > 0 && part.back() == '"') {
                break;
            }
            field += ",";
        } while (getline(ss, part, ','));
    } else {
        field = part;
    }

    return cleanField(field);
}



int main() {
    NutrientClass nutrientClass;

    ifstream nutrientCSVFile("Nutrients_Info.csv");
    if (!nutrientCSVFile.is_open()) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    string line, header;
    getline(nutrientCSVFile, header); // Skip the header line

    while (getline(nutrientCSVFile, line)) {
        stringstream ss(line);
        string food = getNextField(ss);
        string measure = getNextField(ss);
        string grams = getNextField(ss);
        string calories = getNextField(ss);
        string protein = getNextField(ss);
        string fat = getNextField(ss);
        string sat_fat = getNextField(ss);
        string fibre = getNextField(ss);
        string carbs = getNextField(ss);
        string category = getNextField(ss);

        // Insert into the linked list
        nutrientClass.InserttoEnd(food, measure, stoi(grams), stoi(calories), stoi(protein), stoi(fat), stoi(sat_fat), stod(fibre), stod(carbs), category);
    }

    nutrientClass.DisplayLinkedList();

    return 0;
}
