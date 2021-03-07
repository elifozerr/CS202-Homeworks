//
//  main.cpp
//  cs202_hw4_1
//
//  Elif Özer
//  21602495
//  CS202-3



#include <fstream>
#include <sstream>
#include <iostream>
#include "HashTable.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    ifstream myFile;
    myFile.open("input.txt");
    string readLine; //
   
    
    //const int TABLE_SIZE = 11;
    HashTable hashTable = HashTable(11, HashTable::LINEAR);
    
  
    
    cout << "--------- HASH TABLE (LINEAR PROBING) --------" << endl;
    cout << endl ;
    
    while(getline(myFile,readLine)){
        
        string operation;
        int data;
        stringstream lineRead(readLine);
        lineRead >> operation;
        lineRead >> data ;
        if(operation == "I"){
            cout<< data;
            if(hashTable.insert(data)){
                cout << " inserted" << endl;
            }
            else{
                cout << " not inserted" << endl;
            }
        }
        else if(operation == "R"){
            cout<< data ;
            if(hashTable.remove(data)){
                cout << " removed" << endl;
            }
            else{
                cout << " not removed" <<endl;
            }
        }
        else{
            int numberOfProbes;
            cout<< data ;
            if(hashTable.search(data, numberOfProbes)){
                cout << " found after " << numberOfProbes << " probes" <<endl;
            }
            else{
                cout << " not found after " << numberOfProbes << " probes" <<endl;
            }
        }
        
    }
    hashTable.display();
    double numSuccProbes, numUnsuccProbes;
    hashTable.analyze(numSuccProbes, numUnsuccProbes);
    cout<< "Average number of successful probe: " << numSuccProbes<< endl;
    cout <<"Average number of unsuccessful probe: " << numUnsuccProbes <<endl;
    
    myFile.close();
    
    
    cout << "--------- HASH TABLE ( QUADRATIC PROBING) --------" << endl;
    cout << endl ;
    
    
    //
    ifstream myFile2;
    myFile2.open("input.txt");
    string readLine2;
    HashTable hashTable2 = HashTable(11, HashTable::QUADRATIC);
    
    
   while(getline(myFile2,readLine2)){
       
       string operation2;
       int data2;
       stringstream lineRead2(readLine2);
       lineRead2 >> operation2;
       lineRead2 >> data2 ;
       if(operation2 == "I"){
           cout<< data2;
           if(hashTable2.insert(data2)){
               cout << " inserted" << endl;
           }
           else{
               cout << " not inserted" << endl;
           }
       }
       else if(operation2 == "R"){
           cout<< data2 ;
           if(hashTable2.remove(data2)){
               cout << " removed" << endl;
           }
           else{
               cout << " not removed" <<endl;
           }
       }
       else{
           int numberOfProbes2;
           cout<< data2 ;
           if(hashTable2.search(data2, numberOfProbes2)){
               cout << " found after " << numberOfProbes2 << " probes" <<endl;
           }
           else{
               cout << " not found after " << numberOfProbes2 << " probes" <<endl;
           }
       }
       
   }
    hashTable2.display();
    double numSuccProbes2= 0;
    double numUnsuccProbes2 = 0;
    hashTable2.analyze(numSuccProbes2, numUnsuccProbes2);
    cout<< "Average number of successful probe: " << numSuccProbes2<< endl;
    cout <<"Average number of unsuccessful probe: " << numUnsuccProbes2 <<endl;
    
    myFile2.close();
    
    
    cout << "--------- HASH TABLE ( DOUBLE HASHING) --------" << endl;
    cout << endl ;
    
     ifstream myFile3;
     myFile3.open("input.txt");
     string readLine3;
     HashTable hashTable3 = HashTable(11, HashTable::DOUBLE);
     
     
    while(getline(myFile3,readLine3)){
        
        string operation3;
        int data3;
        stringstream lineRead3(readLine3);
        lineRead3 >> operation3;
        lineRead3 >> data3 ;
        if(operation3 == "I"){
            cout<< data3;
            if(hashTable3.insert(data3)){
                cout << " inserted" << endl;

            }
            else{
                cout << " not inserted" << endl;
            }
           // hashTable3.display();
        }
        else if(operation3 == "R"){
            cout<< data3 ;
            if(hashTable3.remove(data3)){
                cout << " removed" << endl;
            }
            else{
                cout << " not removed" <<endl;
            }
            //hashTable3.display();
        }
        else{
            int numberOfProbes3;
            cout<< data3 ;
            if(hashTable3.search(data3, numberOfProbes3)){
                cout << " found after " << numberOfProbes3 << " probes" <<endl;
            }
            else{
                cout << " not found after " << numberOfProbes3 << " probes" <<endl;
            }
            
        }
        
    }
    
    hashTable3.display();
    double numSuccProbes3= 0;
    double numUnsuccProbes3 = 0;
    hashTable3.analyze(numSuccProbes3, numUnsuccProbes3);
    cout<< "Average number of successful probe: " << numSuccProbes3<< endl;
    cout <<"Average number of unsuccessful probe: " << numUnsuccProbes3 <<endl;
    
    myFile3.close(); //end of main
}
