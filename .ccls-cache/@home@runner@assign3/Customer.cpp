#include "Customer.h"
#include "Appointment.h"
#include "Person.h"
using namespace std;

Customer::Customer() {
  MechanicID = "";
  appointment.hour = 0;
  appointment.minute = 0;
}
Customer::Customer(string name, string id, int hr, int min) {
  setName(name);
  MechanicID = id;
  setAppointment(hr, min);
}
void Customer::setMechanicID(string id) {
  MechanicID = id;
}
void Customer::setAppointment(int hr, int min) {
  if (hr >= 0 && hr < 24) {
    appointment.hour = hr;
  } else {
    cout << "Hours cannot be set to less than 0 or more than 24.\n";
  }
  if (min >= 0 && min < 60) {
    appointment.minute = min;
  } else {
    cout << "Minutes cannot be set to less than 0 or more than 59.\n";
  }
}
string Customer::getMechanicID() { return MechanicID; }

Appointment Customer::getAppointment() { return appointment; }

bool Customer::operator<(Customer x) {
  if (appointment.hour < x.appointment.hour) {
    return true;
  } else if (appointment.hour == x.appointment.hour &&
             appointment.minute < x.appointment.minute) {
    return true;
  } else if (appointment.hour == x.appointment.hour &&
             appointment.minute == x.appointment.minute) {
    if (MechanicID < x.MechanicID) {
      return true;
    }
  }
    return false;
  }
  bool Customer::operator>(Customer x) {
    if (appointment.hour > x.appointment.hour) {
      return true;
    } else if (appointment.hour == x.appointment.hour &&
               appointment.minute > x.appointment.minute) {
      return true;
    } /*else if (appointment.hour == x.appointment.hour &&
              appointment.minute == x.appointment.minute) {
      if (MechanicID > x.MechanicID) {
        return true;
      }
    }*/
    return false;
  }
  bool Customer::operator==(Customer x) {
    if (appointment.hour == x.appointment.hour &&
        appointment.minute == x.appointment.minute) {
      return true;
    }
    return false;
  }
