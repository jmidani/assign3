#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <iostream>
using namespace std;

struct Appointment{
    int hour; // Hour from 00-23
    int minute; // Minute from 0-59
  void print(){
    cout<<hour<<":"<<minute<<endl;
  }
};
#endif