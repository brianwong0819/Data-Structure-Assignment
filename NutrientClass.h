#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Food
{
    string food;
    string measure;
    int grams;
    int protein;
    int calories;//hh
    int fat;
    int sat_fat;
    double fibre;
    double carbs;
    string category;
    Food* nextaddrress;
};

struct FoodCalorieArray {
    string food;
    string measure;
    int grams;
    int calories;
    int protein;
    int fat;
    int sat_fat;
    double fibre;
    double carbs;
    string category;

    // Default constructor
    FoodCalorieArray() : food(""), measure(""), grams(0), calories(0), protein(0), fat(0), sat_fat(0), fibre(0.0), carbs(0.0), category("") {}

    // Constructor with parameters
    FoodCalorieArray(string f, string m, int g, int c, int p, int ft, int sf, double fb, double cb, string cat) : food(f), measure(m), grams(g), calories(c), protein(p), fat(ft), sat_fat(sf), fibre(fb), carbs(cb), category(cat) {}


    void print() const {
        cout << left << setw(50) << food
            << setw(25) << measure
            << setw(10) << grams
            << setw(10) << calories
            << setw(10) << protein
            << setw(10)<< fat
            << setw(10) << sat_fat
            << setw(10) << fibre
            << setw(10) << carbs
            << setw(20) << category;
            cout << endl; 
    }
};


class NutrientClass
{
    Food* head;
    int size;

public:
    
    NutrientClass(){
        head = nullptr;
        size = 0;
    }

    Food* getHead() const {
        return head;
    }

    void setHead(Food* newHead) {
        head = newHead;
    }

    int getListSize() const {
            return size;
        }

    void printHeader(){
         cout << left << setw(50) << "Food"
            << setw(25) << "Measure"
            << setw(10) << "Grams"
            << setw(10) << "Calories"
            << setw(10) << "Protein"
            << setw(10)<< "Fat"
            << setw(10) << "Sat_fat"
            << setw(10) << "Fibre"
            << setw(10) << "Carbs"
            << setw(20) << "Category";
            cout << endl;
    }

    Food* CreateNewNode(string food, string measure, int grams,int calories, int protein, int fat, int sat_fat, double fibre, int carbs, string category){
        Food* newnode = new Food;
        newnode->food = food;
        newnode->measure = measure;
        newnode->grams = grams;
        newnode->calories = calories;
        newnode->protein = protein;
        newnode->fat = fat;
        newnode->sat_fat = sat_fat;
        newnode->fibre = fibre;
        newnode->carbs = carbs;
        newnode->category = category;
        newnode->nextaddrress = nullptr;
        return newnode; 
    }

    void DisplayLinkedList() {
        Food* current = head;
        while (current != nullptr)
        {
            cout << left << setw(50) << current->food
            << setw(25) << current->measure
            << setw(10) << current->grams
            << setw(10) << current->calories
            << setw(10) << current->protein
            << setw(10)<< current->fat
            << setw(10) << current->sat_fat
            << setw(10) << current->fibre
            << setw(10) << current->carbs
            << setw(20) << current->category;
            current = current->nextaddrress;
            cout << endl; 
        }
        cout << "Total rows: " << size;
    }

    void InserttoFront(string food, string measure, int grams,int calories, int protein, int fat, int sat_fat, double fibre, int carbs, string category){
        Food* newnode = CreateNewNode(food, measure, grams, calories, protein, fat, sat_fat, fibre, carbs, category);

        if (head == nullptr)
        {
            head = newnode;
            size++; 
            return;
        }
        else
        {
            newnode->nextaddrress = head;
            head = newnode;
            size++;
            return;
        }
    }

    void InserttoEnd(string food, string measure, int grams,int calories, int protein, int fat, int sat_fat, double fibre, int carbs, string category){
        Food* newnode = CreateNewNode(food, measure, grams, calories, protein, fat, sat_fat, fibre, carbs, category);

        if (head == nullptr)
        {
            head = newnode;
            size ++;
            return;
        }
        else
        {
            Food* current = head;
            while (current->nextaddrress != nullptr)
            {
                current = current->nextaddrress;
            }
            current->nextaddrress = newnode;
            size++;
            return;
        }
    }

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

    void LoadFromFile(const string& filename){
        ifstream nutrientCSVFile("Nutrients_Info.csv");
        if (!nutrientCSVFile.is_open()) {
            cout << "Failed to open file." << endl;
            return;
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
            InserttoEnd(food, measure, stoi(grams), stoi(calories), stoi(protein), stoi(fat), stoi(sat_fat), stod(fibre), stod(carbs), category);
        }
    }

    // Function to create and return the array
    FoodCalorieArray* getFoodCalorieArray() {
        FoodCalorieArray* arr = new FoodCalorieArray[size];
        Food* current = head;
        int index = 0;

        while (current != nullptr) {
            arr[index] = FoodCalorieArray(current->food, current->measure, current->grams, current->calories, 
            current->protein, current->fat, current->sat_fat, current->fibre, current->carbs, current->category);
            current = current->nextaddrress;
            ++index;
            }

            return arr;
    }

    bool binarySearch(FoodCalorieArray arr[], int targetCalories, int size)
    {
        int lastIndex = size - 1; //last index
        int firstIndex = 0; //first index

        while (firstIndex <= lastIndex) //worst case = O(logbase2 n)
        {
            int midIndex = (firstIndex + lastIndex) / 2;

            if (arr[midIndex].calories == targetCalories) //best case - always first found answer: O(1)
            {
                cout << "Food Name: " << arr[midIndex].food << ", Calories: " << arr[midIndex].calories << endl;
                return true;
            }

            if (arr[midIndex].calories < targetCalories)
            {
                firstIndex = midIndex + 1;
            }
            else
            {
                lastIndex = midIndex - 1;
            }
        }
        cout << "No calories found in the array.";
        return false;
    }

    void binarySearchLinkedList(int targetCalories) {
        Food* start = head;
        Food* end = nullptr;

        while (start != end) {
            Food* slow = start;
            Food* fast = start->nextaddrress;

            while (fast != end) {
                fast = fast->nextaddrress;
                if (fast != end) {
                    slow = slow->nextaddrress;
                    fast = fast->nextaddrress;
                }
            }

            Food* mid = slow;

            
            if (mid->calories == targetCalories) {
                std::cout << "\nFound food with " << targetCalories << " calories: " << mid->food << std::endl;
                return;
            } else if (mid->calories < targetCalories) {
                start = mid->nextaddrress;
            } else {
                end = mid;
            }
        }

        cout << "\nNo food found with " << targetCalories << " calories." << endl;
    }
};