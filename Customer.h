#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Appointment.h"
#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class Customer : public Person {
private:
  string MechanicID;
  Appointment appointment;

public:
  Customer(); // Default constructor initalizes all to 0
  Customer(string, string, int, int); // Constructor initalizes id and appointment using input
  void setMechanicID(string); // Sets Mechanic's ID
  void setAppointment(int, int);   // Sets Appointment time
  string getMechanicID();          // Returns Mechanic's ID
  Appointment getAppointment();    // Returns Appointment time
  bool operator<(Customer); // Returns true if time of object1 is less than object2
  bool operator>(Customer); // Returns true if time of object1 is more than object2
  bool operator==(Customer); // Returns true if times are equal
};
#endif
