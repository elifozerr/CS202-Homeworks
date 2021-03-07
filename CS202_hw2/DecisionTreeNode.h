/**
* Author: Elif Özerr
*ID: 21602495
* Section: 3
* Assignment: 2
*/

#ifndef DecisionTreeNode_h
#define DecisionTreeNode_h

#include <stdio.h>

class DecisionTreeNode{
    
public:
    
    DecisionTreeNode();
    DecisionTreeNode(const int& nodeItem);
    DecisionTreeNode(const int& nodeItem, DecisionTreeNode *left, DecisionTreeNode *right);
    double calculateEntropy(const int* classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
   
   
private:
    
    int item;
    bool *usedSamples;
    bool *rightUsedSamples;
    bool *leftUsedSamples;
    bool checkLeaf;
    DecisionTreeNode *nodePtr;
    DecisionTreeNode *rightChild;
    DecisionTreeNode *leftChild;
    //int classNo;
    //int featureId;
    friend class DecisionTree;
};

#endif /* DecisionTreeNode_hpp */
