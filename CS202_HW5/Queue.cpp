//
//  Queue.cpp
//  hw5-1
//
//  Created by Elif Özer on 23.05.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue(int size){
    
    front = -1;
    back = -1;
    counter = 0;
    this->size = size;
    people = new Person[size];
    
}

Person Queue::getFront(){
    
    return people[front];
}

bool Queue::checkIsEmpty() const{
    
    if( counter == 0){
        return true;
    }
    else{
        return false;
    }
}

bool Queue::enqueue (Person p){
    
    
    if(checkIsEmpty()){
        
        front = 0;
        back = 0;
    }
    else if(back < size - 1){
        back = back + 1;
    }
    else{
        back = 0;
    }
    
    people[back] = p;
   // cout << people[back].getId() <<endl;
   // cout << p.getId() << endl;
    ++counter;
    return true;
}


Person Queue::dequeue (){
    
    int temp = front;
    if(checkIsEmpty()){
        Person p;
        return p;
    }
    else{
        if( front == back){
            front = -1;
            back = -1;
        }
        else if(front < size -1){
            front = front + 1;
        }
        else{
            front = 0;
        }
        --counter;
    }
    return people[temp];
}
