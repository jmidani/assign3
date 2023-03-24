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
  if (counter == maxAppointments - 1) {
    return false;
  }
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
  } else {
    cout << "Maximum appointments per day is 50.\n";
  }
}
void Mechanic::setMaxAppointments(int max) {
  if (max >= 0 && max < 50) {
    maxAppointments = max;
  } else {
    cout << "Maximum appointments per day is 50.\n";
  }
}
void Mechanic::setAppointment(int hr, int min) {
  if (hr >= 0 && hr < 24) {
    appointment[counter].hour = hr;
  } 
  else {
    cout << "Hours cannot be set to less than 0 or more than 24.\n";
  }
  if (min >= 0 && min < 60) {
    appointment[counter].minute = min;
  }
  else {
    cout << "Minutes cannot be set to less than 0 or more than 59.\n";
  }

  for (int i = 0; i <= counter; i++) {
    if (appointment[i].hour > appointment[i + 1].hour) {
      Appointment temp = appointment[i + 1];
      appointment[i+1] = appointment[i];
      appointment[i] = temp;
    }
    if (appointment[i].hour == appointment[i + 1].hour) {
      if (appointment[i].minute > appointment[i + 1].minute) {
        Appointment temp = appointment[i + 1];
        appointment[i+1] = appointment[i];
        appointment[i] = temp;
      }
    }
  }
  counter++;
}
int Mechanic::getCounter() { return counter; }
Appointment Mechanic::getAppointments(int number) {
  return appointment[number];
}
void Mechanic::printAppointments() {
  for (int i = 0; i < counter; i++) {
    cout << i + 1 << ". " << (appointment + i)->hour << ":"
         << (appointment + i)->minute << endl;
  }
}
Mechanic &Mechanic::setAppointment(Appointment customerAppointment) {
  appointment[counter]=customerAppointment;// no validation as appointment // validated in customer class
  for (int i = 0; i <= counter; i++) {
    if (appointment[i].hour > appointment[i + 1].hour) {
      Appointment temp = appointment[i + 1];
      appointment[i+1] = appointment[i];
      appointment[i] = temp;
    }
    if (appointment[i].hour == appointment[i + 1].hour) {
      if (appointment[i].minute > appointment[i + 1].minute) {
        Appointment temp = appointment[i + 1];
        appointment[i+1] = appointment[i];
        appointment[i] = temp;
      }
    }
  }
  counter++;
  return *this;
}