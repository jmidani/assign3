#include "Appointment.h"
#include "Customer.h"
#include "Mechanic.h"
#include "Queue.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void mechanic_info(Mechanic *, string, int); // Fills array of Mechanic, reads from file
void customer_info(Customer *, string, int); // Fills array of Customer, reads from file
void customer_queue(Mechanic *, Customer *, int, int); // Finds customer an available mechanic or cancells appointment
bool findMechanic(Appointment, int, Mechanic *, Customer &); // Check mechanics' availability
void queue_sort(int, Queue<Customer> &, Customer *); // Sorts customers in a queue by appointment time
void print(int, int, Queue<Customer> &, Mechanic *, Customer *); // Displays queue of customers

int main() {
  int mechanics_available = 3, numCustomers = 5;
  string Mfile = "mechanics.txt", Cfile = "customers.txt";
  Mechanic *mechanics = new Mechanic[mechanics_available];
  Customer *customers = new Customer[numCustomers];
  Queue<Customer> line(numCustomers);
  
  customer_info(customers, Cfile, numCustomers);
  cout << endl;
  mechanic_info(mechanics, Mfile, mechanics_available);
  cout << endl;
  customer_queue(mechanics, customers, mechanics_available, numCustomers);
  cout << endl;
  queue_sort(numCustomers, line, customers);
  cout << "Order of appointments: " << endl;
  print(numCustomers, mechanics_available, line, mechanics, customers);

  delete[] mechanics;
  delete[] customers;

  return 0;
}

void mechanic_info(Mechanic *person, string filename, int size) {
  ifstream file;
  file.open(filename);
  int count = 0, age, appointments, hr, min;
  Appointment temp;
  string name, id;
  
  while (!file.eof()) {
    file >> name >> age >> id >> appointments;
    (person + count)->setName(name).setAge(age).setID(id);
    for (int i = 0; i < appointments; i++) {
      file >> hr;
      file >> min;
      (person + count)->setAppointment(hr, min);
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

void customer_queue(Mechanic *mechanics, Customer *customers, int numMechanics, int numCustomers) {
  Appointment customerAppointment;
  string name;
  
  // Finds mechanic for all customers
  for (int i = 0; i < numCustomers; i++) {
    customerAppointment = (customers + i)->getAppointment();
    bool appointmentFound = findMechanic(customerAppointment, numMechanics, mechanics, *(customers + i));

    // Prints error message in none found
    if (!appointmentFound) {
      name = (customers + i)->getName();
      cout << "No available mechanics at ";
      customerAppointment.print();
      cout << name << "'s appointment was cancelled.\n" << endl;
    }
  }
}

bool findMechanic(Appointment customerAppointment, int numMechanics, Mechanic *mechanics, Customer &customers) {
  for (int i = 0; i < numMechanics; i++) {
    if ((mechanics + i)->isAvailable(customerAppointment)) {
      string ID = (mechanics + i)->getID();
      customers.setMechanicID(ID); // Sets customer's mechanic ID
      (mechanics + i)->setAppointment(customerAppointment); // Adds customer to appointments
      return true;
    }
  }
  return false;
}

void queue_sort(int size, Queue<Customer> &line, Customer *customers) {
  Customer temp;
  
  // Loop to sort customers in order of appointment
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (customers[i] > customers[j]) {
        temp = customers[i];
        customers[i] = customers[j];
        customers[j] = temp;
      }
    }
  }
  // Once sorted inserts them in a queue
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

  // For every customer
  for (int i = 0; i < Csize; i++) {
    line.Pop(nextInLine);
    name = nextInLine.getName();
    time = nextInLine.getAppointment();
    id = nextInLine.getMechanicID();

    // Finds mechanic with the ID
    for (int j = 0; j < Msize; j++) {
      temp = mechanics[j].getID();
      if (temp == id) {
        mechName = mechanics[j].getName();
      }
    }
    
    // so cancelled appointments dont get printed
    if (id != "") { 
      cout << name << " has an appointment at " << time.hour << ":"
           << time.minute << " with " << mechName << endl;
    }
  }
}