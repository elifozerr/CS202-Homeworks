//
//  Person.h
//  hw5-1
//
//  Created by Elif Özer on 22.05.2020.
//  
//

#ifndef Person_h
#define Person_h
#include <string>

using namespace std;

class Person{
    
public:

    Person();
    
    Person(string name, int id, int degree);
    
    void setName(string nameOfPerson);
    string getName();
    
    void setId(int idOfPerson);
    int getId();
    
    void setDegree(int degreeOfPerson);
    int getDegree();
    
    int * getListOfFriends();
    
    void operator=(const Person& person);
    
private:

    string name;
    int id;              //id of person
    int * listOfFriendsID; //contains id numbers of person's friends
    int degree;
    
    friend class FriendNet;
    
};
#endif /* Person_h */
