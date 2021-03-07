//
//  simulator.cpp
//  cs202_hw3
//
//  Created by Elif Özer on 22.04.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//

#include <stdio.h>
#include "maxHeap1.h"
#include "Patient.h"
#include "Doctor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

int main(int argc, char* argv[]){

    int patientNumber;
    ifstream myFile;
    myFile.open(argv[1]);

    stringstream ss(argv[2]);
    int requiredAverageTime;
    ss>> requiredAverageTime;


    myFile >> patientNumber;


    Patient* pList = new Patient[patientNumber];

    int patientData[4];

    for(int i = 0;i< patientNumber; i++){
        myFile >> patientData[0] >> patientData[1]>> patientData[2] >>patientData[3];
        Patient* addedPatient = new Patient(patientData[0], patientData[1],patientData[2], patientData[3]);
        pList[i] = *addedPatient;
    }


    int size = patientNumber;


    float avWaitTime = numeric_limits<int>::max();
    float tttmp = avWaitTime;

    int counter =0;
    int drSize = 1;
    int outedTime;
    bool avl = true;
    bool notAvl = false;
    int timeOfWait = 0;
    bool outputIteration = false;

    do{
        if(outputIteration){

            drSize= drSize-1;
            cout <<"Min number of doctors required " <<drSize<<endl;
            cout <<"Simulation w/ " <<drSize <<" dr " <<endl;
        }
        counter  =0;
        int sum = 0;
        int time = 0;
        int index = 0; //to count patient number

        Doctor * drList = new Doctor[drSize]; //create dr array

        for(int i = 0; i < drSize; i ++){
            // new doctor with id i
            drList[i] = Doctor(i);
        }


        maxHeap maxHeap;
        //change the time of doctors
        //if doctor's patient gone, make doctors available
        while(!maxHeap.heapIsEmpty() || index < size){
            for(int i = 0; i<drSize;  i++){
               if(drList[i].availableTime == time){

                    drList[i].setAvailable(true);
               }
                //infinite loop here
            }


        //if new patient comes, add it to heap according to its priority
            while(index <size && (pList[index].getArrTime()==time)){
                maxHeap.heapInsert(pList[index]);
                index++; //to look at new patient //counter
            }

        //now we send patients to the doctors, if there is any available //doctor
            for(int j = 0; j<  drSize ; j++){

                if(!maxHeap.heapIsEmpty() && drList[j].ifAvaliable()){
                    counter++;
                    Patient deleted;
                    maxHeap.heapDelete(deleted);
                    outedTime = time + deleted.getServiceT();
                    deleted.setOutTime(outedTime);
                    drList[j].setAvailable(notAvl);
                    drList[j].availableTime = deleted.getOutTime();
                   timeOfWait = time - deleted.getArrTime();



                    sum += timeOfWait;


                    if(outputIteration){
                        cout <<"Doctor"<<j<<" "<<"take the patient "<<deleted.getId()<<" at minute "<<time <<"(wait: "<< timeOfWait <<"minutes"<<endl;
                    }

                }

            }
            time ++;
        }
        if(outputIteration)
            cout << "Average wait time:" <<avWaitTime<< endl;

        tttmp = avWaitTime;

        avWaitTime = sum / (float)counter ;
        if(avWaitTime<requiredAverageTime) {
            outputIteration = true;
        }

        drSize++;


    }while(tttmp > requiredAverageTime);

    myFile.close();
}


