#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Queue{
    private:
    int max, front, back, counter;
    T *array;

    public:
    Queue(int); //Constructor initalizes empty queue
    Queue(T*,int); // Constructor creates a queue from preexisting array
    bool isEmpty(); // Checks if queue is empty
    bool isFull(); // Checks is queue is full
    void Push(T); // Enqueuing
    T Pop(); // Dequeueing
    T Peek(); // Returns last element in queue
    ~Queue(); // Destructor
};

template <class T>
Queue<T>::Queue (int m){
    max=m;
    front=0;
    back=-1;
    counter=0;
    array=new T[max];
}
template <class T>
Queue<T>::Queue(T *arr,int m){
    max=m;
    front=0;
    back=-1;
    counter=0;
    *array=new T[max];
    for (int i=0;i<max;i++){
        *(array+i)=*(arr+i);
    }
}
template <class T>
Queue<T>::~Queue(){
    cout<<"destructor q";
    delete [] array;
}
template <class T>
bool Queue<T>::isEmpty(){
    if (counter==0){
        return true;
    }
    return false;
}
template <class T>
bool Queue<T>::isFull(){
    if (counter==max){
        return true;
    }
    return false;
}
template <class T>
void Queue<T>::Push(T value){
    if (isFull()){
        cout<<"Queue is full, no more data can be added.\n";
    }
    else{
        back=(back+1)%max;
        *(array+back)=value;
        counter=counter+1;
    }
}
template <class T>
T Queue<T>::Pop(){
    if (isEmpty()){
        cout<<"Queue is empty, no data can be extracted.\n";
    }
    else{
        int current=front;
        front=(front+1)%max;
        counter=counter-1;
        return *(array+current);
    }
}
template <class T>
T Queue<T>::Peek(){
    return *(array+back);
}

#endif