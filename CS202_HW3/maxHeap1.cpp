#include "maxHeap1.h"


// Default constructor
maxHeap::maxHeap() : size(0) {

}

bool maxHeap::heapIsEmpty() const {
    return (size == 0);
}


void maxHeap::heapInsert(const Patient &newItem) {

    // Place the new item at the end of the heap
    items[size] = newItem;

    // Trickle new item up to its proper position
    int place = size;
    int parent = (place - 1)/2;
    while ( (place > 0) && (items[place] > items[parent]) ) {
        Patient temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place - 1)/2;
    }
    ++size;
}


void maxHeap::heapDelete(Patient &rootItem) {
    if (heapIsEmpty()){

    }
    else {
        rootItem = items[0];
        items[0] = items[--size];
        heapRebuild(0);
    }
}


void maxHeap::heapRebuild(int root) {
    int child = 2 * root + 1;    // index of root's left child, if any
    if (child < size) {
        // root is not a leaf so that it has a left child
        int rightChild = child + 1;    // index of a right child, if any
        // If root has right child, find larger child
        if ((rightChild < size) &&
            (items[rightChild] > items[child]))
            child = rightChild;    // index of larger child

        // If root’s item is smaller than larger child, swap values
        if (items[root] < items[child]) {
            Patient temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            // transform the new subtree into a heap
            heapRebuild(child);
        }
    }
}


