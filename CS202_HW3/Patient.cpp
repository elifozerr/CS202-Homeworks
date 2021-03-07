//
//  Patient.cpp
//  cs202_hw3
//
//  Created by Elif Özer on 22.04.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//



#include "Patient.h"

Patient::Patient(){
    
}

Patient::Patient(int idNumber, int pri, int arrive, int service){
    
    this->idNo        = idNumber;
    this->priority    = pri;
    this->arrivalTime = arrive;
    this->serviceTime = service;
    this->enterTime   = 0;
    this->outTime     = 0;
}

int Patient::getId(){
    
    return idNo;
}

int Patient::getPriority(){
    
    return priority;
}

int Patient::getArrTime(){
    
    return arrivalTime;
}

int Patient::getServiceT(){
    
    return serviceTime;
}

void Patient::setEnterTime(int a){
    enterTime = a;
}

int Patient::getEnterTime(){
    return enterTime;
}

void Patient::setOutTime(int x){
    outTime = x;
}

int Patient::getOutTime(){
    return outTime;
}
void Patient::operator=(const Patient& patient){
    
    idNo        = patient.idNo;
    priority    = patient.priority;
    serviceTime = patient.serviceTime;
    arrivalTime = patient.arrivalTime;
    
}
