#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;

class Person{
    private:
    string Name;
    string ID;
    int Age;

    public:
    Person(); // Defult constructor initalizes data to blank
    Person &setName(string); // Sets Name 
    Person &setID(string); // Sets ID number
    Person &setAge(int); // Sets Age
    string getName(); // Returns Name
    string getID(); // Returns ID number
    int getAge(); // Returns Age
    void printInfo(); // Prints all info
};
#endif