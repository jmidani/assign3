#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

Person::Person(){
    Name="";
    ID="";
    Age=0;
}
Person &Person::setName(string name){
    Name=name;
    return *this;
}
Person &Person::setID(string id){
    ID=id;
    return *this;
}
Person &Person::setAge(int age){
    Age=age;
    return *this;
}
string Person::getName(){
    return Name;
}
string Person::getID(){
    return ID;
}
int Person::getAge(){
    return Age;
}
void Person::printInfo(){
    string name=(*this).getName();
    string id=(*this).getID();
    int age=(*this).getAge();
    cout<<"Name: "<<name<<"\nAge: "<<age<<"\nID: "<<id<<endl;
}