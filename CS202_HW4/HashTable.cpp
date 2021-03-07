//
//  HashTable.cpp
//  cs202_hw4_1
//
//  Elif Özer
//  21602495
//  CS202-3

#include "HashTable.h"
#include <stdio.h>
#include <iostream>
using namespace std;


//enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };

HashTable::HashTable(const int tabSize,const CollisionStrategy option){
    
    tableSize = tabSize;
    currentSize = 0;
    hashItems = new int[tableSize];
    collision = option;
    deleted = new bool[tableSize];
    occupied = new bool[tableSize];
    emptyCheck = new bool[tableSize];
    for(int i = 0; i < tableSize ; i ++){
        emptyCheck[i]  = true;
    }
    
}

//destructor
HashTable::~HashTable(){
    
    delete [] deleted;
    delete [] occupied;
    delete [] emptyCheck;
    delete [] hashItems;
}



int HashTable::primaryHash(int key){
   
    int size  = tableSize;
    int index = key % size;
    //hashHelp(size,key);
    return index;
}

//second hash function for double hashing
//reverse digits of the key
int HashTable::hash2(int key){
   
    int reversedKey = 0;
    int remaining = 0; //key mod 10
    
    while( key > 0){
        
        remaining = key % 10;
        reversedKey = ( reversedKey*10 )+ remaining;
        key = key / 10;
    }
    return reversedKey;
}

int HashTable::f(int index, int key){
    
    int h2=0;
    int item = hashItems[index];
    h2 = hash2(key);
    
    if(collision ==LINEAR){
        return index ;
    }
    else if(collision == QUADRATIC){
        return index * index;
    }
    //else collision will be double hashing
    else {
        return index * h2;
    }
    
}

int HashTable::hash(int key, int i){
    
    int index = 0;
    
    int a = primaryHash(key);
    index = (a + f(i, key)) % tableSize;
    
    return index;
}

bool HashTable::insert( const int item ){
    
    int index = 0; //index where the item is inserted
    bool inserted = false;
    
    //if item is already exist, return false
    for(int i = 0; i< tableSize; i++){
        if(hashItems[i]==item){
            cout <<  " is already in the table so " <<item ;
            return false;
            
        }
    }
    //
    //what if we want to insert the same value
        index = hash(item,0);//works as primary hash function
        if(emptyCheck[index]==true){
            
            hashItems[index] = item;
            occupied[index] = true;
            emptyCheck[index] = false;
            deleted[index]=false;
            currentSize++;
            inserted = true;
            //return true;
        }
        else{
            //find alternative cell
            for(int i = 0; i< tableSize; i++){
               
                index = hash(item, i);
                index = index % tableSize;
                if(emptyCheck[index]==true){
                    hashItems[index] = item;
                    occupied[index] = true;
                    deleted[index] = false;
                    emptyCheck[index] = false;
                    currentSize++;
                    inserted = true;
                    break;
                }
            }
        }
   // cout << item << " not inserted" << endl;
    return inserted; //for full table ?
}

bool HashTable::remove( const int item ){
    
    bool found = false;
    int index = hash(item, 0);
    
    for(int i = 0; i<= tableSize; i++){
        
        if(occupied[index] && hashItems[index]==item){
            occupied[index]=false;
            emptyCheck[index]=true;
            deleted[index]=true;
            currentSize--;
            found = true;
            //cout << item << " removed." << endl;
            return true;
        }
        index = hash(item, i);
    }
   
    //cout << item << " not removed." << endl;
    return false;
   
    
    
}

bool HashTable::search( const int item, int& numProbes ){
    
    int index = 0;
    numProbes = 0;
    bool found = false;
    
        //iterate the table
        for(int i = 0; i < tableSize; i++){
            index = hash(item,i);
            index = index % tableSize;
            if(emptyCheck[index]== true && deleted[index] == false){
               // cout <<item << " not found after " <<numProbes << " probes" <<endl ;
               // print = false;
                numProbes++;
                break;
            }
            if(hashItems[index]== item && deleted[index] == false){
                numProbes++;
                found = true;
               // cout << item << " found after " <<numProbes << " probes" << endl;
                break;
            }
            
            numProbes++;
        }
        
        //if(found== false && print==true){
            //cout << item << " not found after " <<numProbes << " probes" << endl;
       // }
        return found;
    
}

void HashTable::display(){
    cout << "TABLE: " << endl;
    for(int i = 0; i < tableSize; i ++){
        if(occupied[i] == false){
            cout << i << ":" << endl;
        }
        else{
            cout << i << ": " << hashItems[i] << endl;
        }
    }
    cout <<endl;
}

void HashTable::analyze( double& numSuccProbes, double& numUnsuccProbes ){
    
    numSuccProbes = 0;
    numUnsuccProbes = 0;
    double average = 0;
    double sumSucc = 0;
    double sumUnsucc = 0;
    double searchedItem = 0;
    int newIndex = 0;
    int numProbe = 0;
    //------successful search-----///
    int counter = 0;
    for(int i = 0; i < tableSize ; i++){
        if(occupied[i]){
            searchedItem = hashItems[i];
            search(searchedItem, numProbe);
            sumSucc += numProbe;
            counter++;
        }
    }
    average = sumSucc / counter;
    numSuccProbes = average;
    //------unsuccessful search----//
    if( collision == LINEAR || collision == QUADRATIC){
        for(int i =0; i< tableSize; i++){
            int numberOfProbes = 1;
            int tempI = i;
            while(!emptyCheck[tempI] && numberOfProbes <= tableSize){
                tempI = hash(i,numberOfProbes);
                newIndex = hash(i,numberOfProbes);
                numberOfProbes++;
            }
            sumUnsucc += numberOfProbes;
        }
        numUnsuccProbes = sumUnsucc / tableSize;
        
    }
    else{
        numUnsuccProbes = -1;
    }
    
    
}
