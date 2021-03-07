//
//  Doctor.cpp
//  cs202_hw3
//
//  Created by Elif Özer on 22.04.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//

#include <stdio.h>

#include "Doctor.h"


Doctor::Doctor(){
    idDoctor = 0;
    available = true;
    availableTime = 0;
}

Doctor::Doctor(int id){
    this->idDoctor = id;
    available = true;
    availableTime = 0;
}

int Doctor::getId(){
    return idDoctor;
}


void Doctor::setAvailable(bool a){
    available = a;
}

bool Doctor::ifAvaliable(){
    
    //available = true;
    
   // if(time < outedTime){
   //     available = false;
  //  }
    return available;
}
