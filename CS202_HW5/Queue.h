//
//  Queue.h
//  hw5-1
//
//  Created by Elif Özer on 23.05.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
#include "Person.h"

#include <string>

using namespace std;

class Queue{
    
public:

    Queue(int size);
    
  //  void createStack();
    
    Person getFront();
    
    bool checkIsEmpty() const;
    
    bool enqueue (Person p);
    
    Person dequeue ();
    
//private:
    
    int size;
    Person *people;
    int front;
    int back;
    int counter;
    
};
#endif /* Queue_h */
