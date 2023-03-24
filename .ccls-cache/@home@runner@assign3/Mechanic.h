#ifndef MECHANIC_H
#define MECHANIC_H
#include <iostream>
#include <string>
#include "Person.h"
#include "Appointment.h"
using namespace std;

class Mechanic: public Person{
    private:
    int counter;
    int maxAppointments;
    Appointment *appointment;
    public:
    Mechanic(); // Default constructor initalizes counter=0 and maxAppointments=50
    Mechanic(int); // Constructor that initalizes maximum appointments
    bool isAvailable(Appointment); // Checks if mechanic is available at specific time
    void setCounter(int); // Sets counter to indicate number of appointments
    void setMaxAppointments(int); // Sets maximum appointments, can't exceede 50
    void setAppointment(int,int); // Sets appointment and sorts all ascendingly
    Mechanic &setAppointment(Appointment); // Sets appointment and sorts all ascendingly
    int getCounter(); // Gets current number of appointments
    Appointment getAppointments(int); // Gets nth appointment
    void printAppointments();
    ~Mechanic();
};
#endif