//
//  Patient.h
//  cs202_hw3
//
//  Created by Elif Özer on 22.04.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//

#ifndef Patient_h
#define Patient_h
class Patient{
    
public:
    
    //default constructor
    Patient();
    
    Patient(int idNumber, int pri, int arrive, int service);
    
    //returns id
    int getId();
    
    //returns priority
    int getPriority();
    
    //returns arrival time
    int getArrTime();
    
    //returns examination time
    int getServiceT();
    
    void setEnterTime(int a);
    
    int getEnterTime();
    
    void setOutTime(int x);
    
    int getOutTime();
    
    void operator=(const Patient& patient);

    
    int idNo;
    int priority;
    int arrivalTime;  //in minutes
    int serviceTime; //examination *tim**e in minutes
    int enterTime;
    int outTime;
};

inline bool operator<(const Patient &p1, const Patient &p2){
    if(p1.priority != p2.priority){
        return p1.priority < p2.priority;
    }
    else{
        return p1.arrivalTime > p2.arrivalTime;
    }
}
inline bool operator>(const Patient &p1, const Patient &p2){
    if(p1.priority != p2.priority){
        return p1.priority > p2.priority;
    }
    else{
        return p1.arrivalTime < p2.arrivalTime;
    }
}

#endif /* Patient_h */
