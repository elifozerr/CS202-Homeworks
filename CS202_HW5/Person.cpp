//
//  Person.cpp
//  hw5-1
//
//  Created by Elif Özer on 22.05.2020.
//  
//

#include <stdio.h>
#include "Person.h"

Person::Person(){
    
    name = "";
    id = 0;
    degree = 0;
    listOfFriendsID = NULL;
}

Person::Person(string name, int id, int degree){
    
    this->name = name;
    this->id = id;
    this->degree = degree;
    
}

void Person::setName(string nameOfPerson){
    name = nameOfPerson;
}

string Person::getName(){
    return name;
}

void Person::setId(int idOfPerson){
    id = idOfPerson;
}

int Person::getId(){
    return id;
}

void Person::setDegree(int degreeOfPerson){
    degree = degreeOfPerson;
}

int Person::getDegree(){
    return degree;
}

int* Person::getListOfFriends(){
    
    return listOfFriendsID;
}

void Person::operator=(const Person &person){
    
    name   = person.name;
    id     = person.id;
    degree = person.degree;
    listOfFriendsID = person.listOfFriendsID;
    
}
