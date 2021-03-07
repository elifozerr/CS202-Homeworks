//
//  maxHeap1.h
//  cs202_hw3
//
//  Created by Elif Özer on 22.04.2020.
//  Copyright © 2020 Elif Özer. All rights reserved.
//

#ifndef maxHeap1_h
#define maxHeap1_h
#include "Patient.h"

const int MAX_HEAP = 2000;

class maxHeap {
public:
    maxHeap();				// default constructor
    // copy constructor and destructor are supplied by the compiler

    bool heapIsEmpty() const;
    void heapInsert(const Patient &newItem);
    void heapDelete(Patient &rootItem);

protected:
    void heapRebuild(int root);		// Converts the semiheap rooted at
    // index root into a heap
private:
    Patient items[MAX_HEAP];	// array of heap items
    int size;            	// number of heap items
};


#endif /* maxHeap1_h */
