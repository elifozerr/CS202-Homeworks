//
//  FriendNet.cpp
//  hw5-1
//
//  Created by Elif Özer on 21.05.2020.
//
//

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include "FriendNet.h"

using namespace std;

FriendNet::FriendNet(){
    
    listOfPeople = NULL;
    sizeOfNet =0;
}

// constructor
FriendNet::FriendNet(const string fileName){
    
    int size = 0;
    int degree = 0;
    string line = "";
    int idOfPerson = 0;
    string personName = "";
    int* friendsList = NULL;
    
    ifstream myFile(fileName.c_str());
    //string fileN = fileName;
    //myFile.open(fileName);
    
    if ( !myFile){
        cout << "File does not exist !" << endl;
        listOfPeople = NULL;
        sizeOfNet =0;
    
    }
    else{
        string readLine;
        myFile >> size;
        sizeOfNet = size;
        listOfPeople = new Person[size];
        for(int i = 0; i < size; i++){
            
            Person p;
            
            myFile >> idOfPerson;
            p.setId(idOfPerson);
            //cout << p.id <<"  ";
            
            myFile >> personName;
            p.setName(personName);
           // cout << p.name<< "  ";
            
            myFile >> degree;
            p.setDegree(degree);
            //cout << p.degree<< "     ";
            
            //friendsList = new int[degree];
            p.listOfFriendsID = new int[degree];
            
            for(int j = 0; j<degree; j++){
                myFile >> p.listOfFriendsID[j];
                //cout << p.listOfFriendsID[j] << "   " ;
            }
            listOfPeople[i]= p;
            //cout <<endl;
        }
        
        friendsList = NULL;
        delete [] friendsList;
    }
    myFile.close();
}

// copy constructor
FriendNet::FriendNet(const FriendNet& aNet){
    
    sizeOfNet = aNet.sizeOfNet;
    
    listOfPeople = new Person[aNet.sizeOfNet];
    
    for(int i = 0; i< sizeOfNet; i++){
        listOfPeople[i] = aNet.listOfPeople[i];
    }
    
}

// destructor
FriendNet::~FriendNet(){
    
    listOfPeople = NULL;
    delete [] listOfPeople;
    
}

//this function returns person by its name
//this function will be used in the listFriends() function
Person FriendNet::getPersonByName(string namePerson){
    
    Person p;
    p.setName("");
    for(int i = 0; i < sizeOfNet; i ++){
        if(listOfPeople[i].name == namePerson){
            return (listOfPeople[i]);
        }
    }
    return p;
}

//this function checks whether the paramater Person P and Person at given index(parameter) are adjacent
bool FriendNet::checkAdjacent(Person p, int index){
    
    bool adj = false;
    for(int i = 0; i < sizeOfNet; i++){
        if(p.listOfFriendsID[i] == index){
            adj = true;
            break;
        }
    }
    return adj;
}

//breadth first traversal function
//this bft will be used in listFriends function
//returns the names that person can access with given hop number
string * FriendNet::bft (int hop, Person p, int & sizeNames){
    
    string * names = new string [sizeOfNet];   //we return this array so that we can print names in listPeople function
    string name = p.getName();
    Queue q(sizeOfNet*2);              //create queue
    sizeNames =  0;
    int index = 0;          //represents the index of name array
    
    bool * visited = new bool [sizeOfNet];
    //initially all vertices are unvisited
    for(int i = 0; i < sizeOfNet ; i++){
        visited [i] = false;
    }
    
    int visitedId = p.getId();
    visited[visitedId] = true;
    
    q.enqueue(p);
    
    //to detect the level
    Person a2;
    q.enqueue(a2);
    
    int level = 0;
    while(q.checkIsEmpty() == false && level < hop){
           
        Person tempP= q.dequeue();
        if(tempP.getName()== ""){
            Person a;
            q.enqueue(a);
            level++;
            continue;
        }
        for(int j = 0; j < tempP.degree ; j ++){
            int k = tempP.listOfFriendsID[j];
                if(visited[k]==false){
                    q.enqueue(listOfPeople[k]);
                    names[index] = listOfPeople[k].getName();
                    index ++;
                    sizeNames++;
                    visited[k] = true;
                }
        }
        
    }
    
    
    visited = NULL;
    delete [] visited;
    return names;
    
}

//It lists the names of all people that are accessible from a given person, whose name is personName,
// within the given number hopNo
void FriendNet::listFriends(const string personName, const int hopNo){
    
    if(hopNo <= 0){
        cout<<"People accessible from "<<personName<<" within "<<hopNo<< " hops : NOBODY" <<endl;
        return;
    }
    else{
        Person person;
        person = getPersonByName(personName);
        string * nameList= NULL;
        if(person.getName() == ""){
            cout << personName << " does not exist in the network" << endl;
            return;
        }
        else{
            int degreeOfP = 0;
            degreeOfP = person.getDegree();
        
            if(degreeOfP <= 0){
                cout<<"People accessible from "<<personName<<" within "<<hopNo << " hops : NOBODY" <<endl;
                return;
            }
            else{
                int idOfP = 0;
                idOfP = person.getId();
                int size = 0;
                nameList = bft (hopNo, person, size);
                cout<<"People accessible from "<<personName<<" within "<<hopNo << " hops : " ;
                for (int i = 0; i < size; i ++){
                    if(i != size -1){
                    cout << nameList[i] << " , " ;
                    }
                    else{
                        cout << nameList[i];
                    }
                }
                cout <<endl;
            }
        
        }
        nameList = NULL;
        delete [] nameList;
    }
    
    
}

//bft function
//this function will be used in displayAverageDegree() function
double FriendNet::bft(Person p, bool *visited ){
    
    int sizeOfComponent = 0;
    double average = 0;
    int sum = 0;
    
    int personId = p.getId();
    visited[personId] = true;
    
    Queue q(sizeOfNet);    //create queue
    q.enqueue(p);
    
    int * degreeListOfC = new int[sizeOfNet];
    
    int index = 1;
    degreeListOfC[0] = p.getDegree();
    
    while(q.checkIsEmpty() == false ){
       // cout << "- "<< endl;
        Person tempP= q.dequeue();
        for(int j = 0; j < tempP.degree ; j ++){
            int k = tempP.listOfFriendsID[j];
            if(visited[k]==false){
                q.enqueue(listOfPeople[k]);
                visited[k] = true;
                degreeListOfC[index] = listOfPeople[k].getDegree();
                index++;
            }
        }
    }
    //In this for loop, we find the sum in particular component
    for(int i = 0; i < index; i++){
        sum = sum + degreeListOfC[i];
    }
    sizeOfComponent = index;
    average = (double) sum / sizeOfComponent;
    
    degreeListOfC = NULL;
    delete [] degreeListOfC;
    
    return average;
    
}

void FriendNet::displayAverageDegrees(){
    
    int index = 0;
    double * averageList = new double [sizeOfNet]; //contains average degree of components.
    double average = 0;
    
    bool * checkVisited = new bool[sizeOfNet];
    for (int i = 0; i < sizeOfNet ; i++){
        checkVisited [i] = false;
    }
    
    int numberOfComponents = 0;
    
    for (int i =0 ; i <sizeOfNet ; i++){
        if(checkVisited[i] == false){
            average = bft(listOfPeople[i], checkVisited);
            averageList[index] =average;
            index++;
            numberOfComponents++;
        }
    }
    
    cout << "There are "<<numberOfComponents<<" connected components. The average degrees are:" <<endl;
    
    for(int i = 0; i < numberOfComponents ; i++){
        
        cout << "For component "<< i << ": " << averageList[i] << endl;
        
    }
    averageList = NULL;
    delete [] averageList;
    
    checkVisited = NULL;
    delete [] checkVisited;
    
}


//function to display diameters of connected components
//this function makes traversal in itself
//no helper function is needed for displayDiameters()
//first we find connected component, then its diameter.
void FriendNet::displayDiameters(){
    
    
    bool * visited = new bool [sizeOfNet];
    for(int i = 0;  i < sizeOfNet; i++){
        visited[i] = false;
    }
    
    int * listMaxPath = new int [sizeOfNet];
    int numberOfComponents = 0;

    for(int i = 0; i< sizeOfNet ; i++){
        
        //to divide graph into connected components and start bft to find connected component of unvisited person
        if(visited[i]==false){
            int compSize = 0;  //
            Person * peopleInComp = new Person [sizeOfNet]; //contains people in current component
            Queue q(sizeOfNet);    //create queue
            q.enqueue(listOfPeople[i]);
            visited[i] = true;
            peopleInComp[compSize] = listOfPeople[i];
            //bft
            while(q.checkIsEmpty() == false ){
                Person tempP= q.dequeue();
                for(int j = 0; j < tempP.degree ; j ++){
                    int k = tempP.listOfFriendsID[j];
                    //
                    if(visited[k]==false){
                        compSize++;
                        q.enqueue(listOfPeople[k]);
                        visited[k]=true;
                        peopleInComp[compSize] = listOfPeople[k]; //add person to component
                    }
                }
            } // now, we found component at this point
            int maxD = 0;
            
            //to find shortest path from each person in component to every other person in component
            for(int j= 0; j <= compSize; j++){
                bool * visited2 = new bool [sizeOfNet];
                for(int a = 0;  a < sizeOfNet; a++){
                    visited2[a] = false;
                }
                Queue q2(sizeOfNet);
                q2.enqueue(peopleInComp[j]);
                //to detect the level
                Person a2;
                q2.enqueue(a2);
                visited2[peopleInComp[j].getId()] = true;
                int diameter = -1;
                while(q2.checkIsEmpty() == false  ){
                    Person tempP= q2.dequeue();
    
                    if(tempP.getName()== ""){
                        //we are at next level now
                        Person a;
                        q2.enqueue(a);
                        diameter++;
                        //to check all people are visited
                        if(q2.getFront().getName()==""){
                            break;
                        }
                        continue;
                    }
                    //find friends of temp
                    for(int j = 0; j < tempP.degree ; j ++){
                        int k = tempP.listOfFriendsID[j];
                        if(visited2[k]==false){
                            q2.enqueue(listOfPeople[k]);
                            visited2[k]=true;
                        }
                    }
                }
                
                if(diameter > maxD){
                    maxD = diameter;
                }
            }
            listMaxPath[numberOfComponents] = maxD;
            numberOfComponents++;
        }
        
       
    }
    
    cout << "There are "<<numberOfComponents<<" connected components. The diameters are:" <<endl;
    
    for(int i = 0; i < numberOfComponents ; i++){
        
        cout << "For component "<< i << ": " << listMaxPath[i] << endl;
        
    }
    
    listMaxPath = NULL;
    delete [] listMaxPath;
    visited = NULL;
    delete []  visited;
    
    
}

