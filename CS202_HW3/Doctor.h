//
//  Doctor.h
//  cs202_hw3
//
//  Created by Elif Özer on 22.04.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//

#ifndef Doctor_h
#define Doctor_h

class Doctor{
    
public:
    
    Doctor();
    
    Doctor(int id);
    
    int getId();
    
    
    void setAvailable(bool a);
    
    bool ifAvaliable();

    bool available;
    int availableTime;
    int idDoctor;
    
};
#endif /* Doctor_h */
