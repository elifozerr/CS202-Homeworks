/**
* Author: Elif Özerr
*ID: 21602495
* Section: 3
* Assignment: 2
*/

#ifndef DecisionTree_h
#define DecisionTree_h

#include "DecisionTreeNode.h"
#include <stdio.h>
#include <string>
using namespace std;


class DecisionTree{

public:
    
    DecisionTree();
    DecisionTree(DecisionTreeNode* nodePtr);
    DecisionTree(const int& rootItem);
    //DecisionTree(const int& rootItem, DecisionTreeNode& leftTree,
        //DecisionTreeNode& rightTree);
    
    
    double calculateEntropy(const int* classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
    
    
    bool isLeaf(DecisionTreeNode* treeNode,const int* labels,const int numSamples,bool* usedSamples);
    
    int getFeature(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples,bool* usedFeatures);
    
    void trainHelp(const bool** data, const int* labels, const int numSamples, const int numFeatures,
               bool* usedSamples, bool* usedFeatures,DecisionTreeNode* node,int selectedFeature);
    
    void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
    
    void train(const string fileName, const int numSamples, const int numFeatures);
    
    int predict(const bool* data);
    double test(const bool** data, const int* labels, const int numSamples);
    double test(const string fileName, const int numSamples);
    void print();
    
    void preOrderPrint(DecisionTreeNode* node, int&i);
    
    
    DecisionTreeNode* root;
    
    
};
#endif /* DecisionTree_hpp */
