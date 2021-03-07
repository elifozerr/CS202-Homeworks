//
//  FriendNet.h
//  hw5-1
//
//  Created by Elif Özer on 21.05.2020.
//  
//

#ifndef FriendNet_h
#define FriendNet_h

#include "Person.h"
#include "Queue.h"
#include <string>

using namespace std;



class FriendNet{
    
public:

    FriendNet();
    
    // constructor
    FriendNet(const string fileName);
    
    // copy constructor
    FriendNet(const FriendNet& aNet);
    
    // destructor
    ~FriendNet();
    
    //returns Person object whose name is parameter string namePerson
    Person getPersonByName(string namePerson);
    
    bool checkAdjacent (Person p, int index);
    
    //breadth first traversal function
    //this bft will be used in listFriends function
    //returns the names that person can access with given hop number
    string * bft (int hop, Person p,int & sizeNames);
    
    void listFriends(const string personName, const int hopNo);
    
    //bft function
    //this function will be used in displayAverageDegree() function
    double bft (Person p, bool *visited);
    
    void displayAverageDegrees();
    
    
    void displayDiameters();
    
    
private:

    int sizeOfNet;
    Person * listOfPeople;
    
};


#endif /* FriendNet_h */
