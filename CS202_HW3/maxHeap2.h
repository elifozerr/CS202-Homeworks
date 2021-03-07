//
// Created by Monster on 24.04.2020.
//

#ifndef CS202_HW_2_MAXHEAP2_H
#define CS202_HW_2_MAXHEAP2_H

#include "Patient.h"

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
    Patient *items;	// array of heap items
    int size;
    int maxSize;
};


#endif //CS202_HW_2_MAXHEAP2_H
