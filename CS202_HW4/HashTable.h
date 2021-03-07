//
//  HashTable.h
//  cs202_hw4_1
//
//  Elif Özer
//  21602495
//  CS202-3

#ifndef HashTable_h
#define HashTable_h

class HashTable{
    
public:
    
    enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
    
    HashTable();
    
    //initializes table with size
    HashTable( const int tabSize, const CollisionStrategy option );
    
    //deletes the dynamic memory
    ~HashTable();
    
    //primary hash function
    int primaryHash(int key);
    
    
    //second hash function for the double hash function strategy
    //this function reverse the digits of the number
    int hash2(int key);
    
    //function for collision resoulion strategy
    int f(int index, int key);
    
    //hash
    int hash(int key, int i);
    
    //inserts item and return true if item is insertes
    bool insert( const int item );
    
    //remove the given item and return true if item is removed
    bool remove( const int item );
    
    //search the given item and return true if item is found
    //also return # of probes
    bool search( const int item, int& numProbes );
    
    //display the hash table's rows
    void display();
    
    //analyze the average number of successful and unsuccesful search
    void analyze( double& numSuccProbes, double& numUnsuccProbes );
    
    
private:
    
    CollisionStrategy collision;
    int tableSize;
    int currentSize;
    int * hashItems;
    bool * deleted;
    bool * emptyCheck;
    bool * occupied;
   
    
};

#endif /* HashTable_h */
