#include "Appointment.h"
#include "Customer.h"
#include "Mechanic.h"
#include "Queue.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void mechanic_info(Mechanic *, string,
                   int); // Fills array of mechanics, reads from file
void customer_info(Customer *, string, int);
void customer_queue(Mechanic *, Customer *, int, int);
bool findMechanic(Appointment, int, Mechanic *, Customer);
void queue_sort(int, Queue<Customer> &, Customer *);
void print(int, int, Queue<Customer> &, Mechanic *, Customer *);

int main() {
  int mechanics_available = 2, numCustomers = 3;
  string Mfile = "mechanics.txt", Cfile = "customers.txt";
  Mechanic *mechanics = new Mechanic[mechanics_available];
  Customer *customers = new Customer[numCustomers];

  Queue<Customer> line(numCustomers);
  customer_info(customers, Cfile, numCustomers);
  mechanic_info(mechanics, Mfile, mechanics_available);

  customer_queue(mechanics, customers, mechanics_available, numCustomers);
  queue_sort(numCustomers,line,customers);
  print(numCustomers, mechanics_available, line, mechanics, customers);

  delete[] mechanics;
  delete[] customers;

  return 0;
}

void mechanic_info(Mechanic *person, string filename, int size) {
  ifstream file;
  file.open(filename);
  int count = 0;
  Appointment temp;
  string name, id;
  int age, appointments;
  while (!file.eof()) {
    file >> name >> age >> id >> appointments;
    (person + count)->setName(name).setAge(age).setID(id);
    for (int i = 0; i < appointments; i++) {
      file >> temp.hour;
      file >> temp.minute;
      (person + count)->setAppointment(temp);
    }
    count++;
  };
  file.close();
}

void customer_info(Customer *person, string filename, int numCustomers) {
  ifstream file;
  file.open(filename);
  int hr, min, count = 0;
  string name, appointment;
  while (!file.eof()) {
    file >> name >> hr >> min;
    (person + count)->setName(name);
    (person + count)->setAppointment(hr, min);
    count++;
  };
  file.close();
}

void customer_queue(Mechanic *mechanics, Customer *customers, int numMechanics,int numCustomers) {
  for (int i = 0; i < numCustomers; i++) {
    Appointment customerAppointment = (customers + i)->getAppointment();
    bool appointmentFound = findMechanic(customerAppointment, numMechanics,
                                         mechanics, *(customers + i));
    if (!appointmentFound) {
      string name = (customers + i)->getName();
      cout << "No available mechanics. " << name
           << "'s appointment was cancelled.\n";
    }
  }
}

bool findMechanic(Appointment customerAppointment, int numMechanics, Mechanic *mechanics, Customer customers) {
  for (int i = 0; i < numMechanics; i++) {
    if ((mechanics + i)->isAvailable(customerAppointment)) {
      string ID = (mechanics + i)->getID();
      customers.setMechanicID(ID);
      (mechanics + i)->setAppointment(customerAppointment);
      return true;
    }
  }
  return false;
} // error here

void queue_sort(int size, Queue<Customer> &line, Customer *customers) {
  Customer temp;
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (customers[i] > customers[j]) {
        temp = customers[i];
        customers[i] = customers[j];
        customers[j] = temp;
      }
    }
  }
  for (int i = 0; i < size; i++) {
    line.Push(customers[i]);
  }
}

void print(int Csize, int Msize, Queue<Customer> &line, Mechanic *mechanics, Customer *customers) {
  Customer nextInLine;
  Appointment time;
  string name, id;
  string mechName;
  string temp;

  for (int i = 0; i < Csize; i++) {
    line.Pop(nextInLine);
    name = nextInLine.getName();
    time = nextInLine.getAppointment();
    id=nextInLine.getMechanicID();
    cout << "id" << id << endl;

    for (int j = 0; j < Msize; j++) {
      temp = mechanics[j].getID();
      if (temp == id) {
        mechName = mechanics[j].getName();
      }
    }
      cout << name << " has an appointment at " << time.hour << ":"
           << time.minute << " with" << mechName << endl;
     // so cancelled appointments dont get printed
  }
}