#include "Mechanic.h"
#include "Appointment.h"
#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

Mechanic::~Mechanic(){
  delete[] appointment;
}
Mechanic::Mechanic() {
  counter = 0;
  maxAppointments = 50;
  appointment=new Appointment[maxAppointments];
}
Mechanic::Mechanic(int max) {
  counter = 0;
  setMaxAppointments(max);
  appointment=new Appointment[maxAppointments];
}

bool Mechanic::isAvailable(Appointment customerAppointment) {
  // Checks if fully booked
  if (counter == maxAppointments - 1) {
    return false;
  }
  // Checks rest of appointments
  for (int i = 0; i < counter + 1; i++) {
    if ((appointment + i)->hour == customerAppointment.hour &&
        (appointment + i)->minute == customerAppointment.minute) {
      return false;
    }
  }
  return true;
}

void Mechanic::setCounter(int c) {
  if (c >= 0 && c < 50) {
    counter = c;
  } 
  else {
    cout << "Maximum appointments per day is 50.\n";
  }
}

void Mechanic::setMaxAppointments(int max) {
  if (max >= 0 && max < 50) {
    maxAppointments = max;
  } 
  else {
    cout << "Maximum appointments cannot exceed 50.\n";
  }
}

void Mechanic::setAppointment(int hr, int min) {
  string name=getName();
  bool valid=true;
  Appointment temp;
  
  // Time validation
  if (hr >= 0 && hr < 24) {
    appointment[counter].hour = hr;
  } 
  else {
    cout << "Hours cannot be set to less than 0 or more than 24.\n"<<name<<"'s appointment "<<counter+1<<" cancelled.\n";
    valid=false;
  }
  if (min >= 0 && min < 60) {
    appointment[counter].minute = min;
  }
  else {
    cout << "Minutes cannot be set to less than 0 or more than 59.\n"<<name<<"'s appointment "<<counter+1<<" cancelled.\n";
    valid=false;
  }

  // Sorts appointments accendingly
  for (int i = 0; i < counter; i++) {
    if (appointment[i].hour > appointment[i + 1].hour) {
      temp = appointment[i + 1];
      appointment[i+1] = appointment[i];
      appointment[i] = temp;
    }
    if (appointment[i].hour == appointment[i + 1].hour) {
      if (appointment[i].minute > appointment[i + 1].minute) {
        temp = appointment[i + 1];
        appointment[i+1] = appointment[i];
        appointment[i] = temp;
      }
    }
  }

  // If not valid won't increment counter
  if(valid){
  counter++;
  }
}

int Mechanic::getCounter() { 
  return counter; 
}

Appointment Mechanic::getAppointments(int number) {
  return appointment[number];
}

void Mechanic::printAppointments() {
  for (int i = 0; i < counter; i++) {
    (appointment+i)->print();
  }
}

Mechanic &Mechanic::setAppointment(Appointment customerAppointment) {
  appointment[counter]=customerAppointment;// no validation as appointment validated in customer class
  Appointment temp;

  // Sort appointments ascendingly
  for (int i = 0; i < counter; i++) {
    if (appointment[i].hour > appointment[i + 1].hour) {
      temp = appointment[i + 1];
      appointment[i+1] = appointment[i];
      appointment[i] = temp;
    }
    if (appointment[i].hour == appointment[i + 1].hour) {
      if (appointment[i].minute > appointment[i + 1].minute) {
        temp = appointment[i + 1];
        appointment[i+1] = appointment[i];
        appointment[i] = temp;
      }
    }
  }
  counter++;
  return *this;
}