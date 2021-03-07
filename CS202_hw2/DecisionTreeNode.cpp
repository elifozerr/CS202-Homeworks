/**
* Author: Elif Özerr
*ID: 21602495
* Section: 3
* Assignment: 2
*/

#include "DecisionTreeNode.h"
#include <cmath>

DecisionTreeNode::DecisionTreeNode(){
    item = 0;
    leftChild = NULL;
    rightChild = NULL;
    usedSamples = NULL;
    leftUsedSamples = NULL;
    rightUsedSamples  = NULL;
    
}

DecisionTreeNode::DecisionTreeNode(const int& nodeItem){
    item = nodeItem;
}

DecisionTreeNode::DecisionTreeNode(const int& nodeItem, DecisionTreeNode *left,
                                   DecisionTreeNode *right){
    
    item = nodeItem;
    leftChild = left;
    rightChild = right;
}

double DecisionTreeNode::calculateEntropy(const int* classCounts, const int numClasses){
    int sum = 0;
    double a,b,entropy= 0;
    for(int i=0; i<numClasses; i++){
        sum = sum + *(classCounts + i);
    }
    for(int i=0; i<numClasses; i++){
        if(*(classCounts + i) != 0){
        a = (double)(*(classCounts + i)) /sum;
        b = log2(a);
        entropy = -(a*b) + entropy;
        }
    }
    
    return entropy;
}

double DecisionTreeNode::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId){
    
    
    int numClasses;
    numClasses = 0;
    
    double leftNo = 0;
    double rightNo = 0;
    int total  = 0;
    
    for(int i=0 ; i<numSamples ; i ++){
        
        if(usedSamples[i]==1){
            total++;
            numClasses = labels[i];
            if( data[i][featureId]== 1){
                rightNo++;
            }
            else
                leftNo++;
        }
    }
    
    double probLeft; //left number/total
    double probRight; //right number/total
    probLeft = leftNo  / total;
    probRight = rightNo / total;
    
    
    int* leftClassCounts;
    leftClassCounts = new int[numClasses];
    
    int* rightClassCounts;
    rightClassCounts = new int[numClasses];
    
    int* currentClassCounts;
    currentClassCounts = new int[numClasses];
    
    
    for(int i = 0; i< numSamples ; i++){
        if(usedSamples[i]==1){
            currentClassCounts[labels[i]-1] += 1;
            
            if(data[i][featureId]==1){
                rightClassCounts[labels[i]-1] += 1;
            }
            else{
                leftClassCounts[labels[i]-1] += 1;
            }
        }
    }
    
    double HL;  //H(Left)
    HL = calculateEntropy(leftClassCounts, numClasses);
    
    double HR;  //H(Right)
    HR = calculateEntropy(rightClassCounts, numClasses);
    //cout << HR <<endl;
    
    double HS; //H(S)
    HS = ( probLeft * HL ) + (probRight * HR);
    //cout<< HS <<endl;
    
    double Hp;
    Hp = calculateEntropy(currentClassCounts, numClasses);
    double infoGain;
    infoGain = Hp - HS;
    
    return infoGain;
}



