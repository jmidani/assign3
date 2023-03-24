#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <iostream>
using namespace std;

struct Appointment{
    int hour=0; // Hour from 00-23
    int minute=0; // Minute from 0-59
  void print(){
    cout<<hour<<":"<<minute<<endl;
  }
};
#endif