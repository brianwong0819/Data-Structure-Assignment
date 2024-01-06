#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <iomanip>

struct Food
{
    string food;
    string measure;
    int grams;
    int protein;
    int calories;
    int fat;
    int sat_fat;
    double fibre;
    double carbs;
    string category;
    Food* nextaddrress;
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

    
};

