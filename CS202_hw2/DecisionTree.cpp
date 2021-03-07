/**
* Author: Elif Özerr
*ID: 21602495
* Section: 3
* Assignment: 2
*/

#include "DecisionTreeNode.h"
#include "DecisionTree.h"

#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

DecisionTree::DecisionTree(){
    root = NULL;
}
DecisionTree::DecisionTree(DecisionTreeNode* nodePtr):root(nodePtr){
}

DecisionTree::DecisionTree(const int& rootItem){
    root = new DecisionTreeNode(rootItem,NULL,NULL);
}

double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses){
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

double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId){
    
    
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


bool DecisionTree::isLeaf(DecisionTreeNode* treeNode,const int* labels,const int numSamples                                                                                 ,bool*usedSamples ){
    
    int temp = 0;
    //we check the samples whether they are same or not
    //if all usedSamples (which are true) are same then it is a pure node
    for(int i = 0; i<numSamples -1; i++){
        if(usedSamples[i]==true){
            temp = labels[i];
            if(usedSamples[i+1]==true){
                if(temp != labels[i+1])
                    return false;
            }
        }
    }
    return true;
}

int DecisionTree::getFeature(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples, bool* usedFeatures){
    
    int featureId = 0; //this will be like counter
    double max = 0;     // to compare information gain of features
    double infoGain = 0;
    int selectedFeature  = 0;  //this will be the best feature w.r.t ınfoGain
    for(int i = 0; i<numFeatures ; i++){
        if(usedFeatures[i]==false){
            //if(!usedSamples[i]){
                infoGain = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples,                     featureId);
                if(infoGain > max){
                    max = infoGain;
                    selectedFeature = featureId;
                    //usedFeatures[i] = temp; //when the infoGain is max, this feature is used(true)
                }
            //}
            featureId++;
        }
    }
    return selectedFeature;
}

//this function is recursive helper function for the train function
void DecisionTree::trainHelp(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples, bool* usedFeatures, DecisionTreeNode* treeNode,int selectedFeature){
    
    int id = 0;
    int classId= 0;
    id = getFeature(data,labels, numSamples,numFeatures,usedSamples, usedFeatures);
    usedFeatures[id] = true; //when the infoGain is max, this feature is used(true)
    
    treeNode = new DecisionTreeNode();
    treeNode->leftUsedSamples  = new bool [numSamples];
    treeNode->rightUsedSamples = new bool [numSamples];
    
    //we create used samples by using array which comes from train function
    for(int i = 0; i<numSamples;i++){
        treeNode->leftUsedSamples[i]  = usedSamples[i];
        
    }
    
    //we create used samples by using array which comes from train function
    for(int i = 0; i<numSamples;i++){
        
        treeNode->rightUsedSamples[i] = usedSamples[i];
    }
    
    //to change left usedSamples
    //send false samples to the leftUsedSamples as true
    for(int i = 0; i< numSamples; i++){
        if(data[i][selectedFeature]== true){
            treeNode->leftUsedSamples[i] = false;
        }
    }
    
    //to change right
    for(int i = 0; i<numSamples; i++){
        if(data[i][selectedFeature]== false){
            treeNode->rightUsedSamples[i] = false;
        }
    }
    
    //this is base case for recursion
    //if the node is leaf node (which means all samples are in the same class), we return
    if(isLeaf(treeNode,labels,numSamples,usedSamples)){
        for(int i = 0; i< numSamples; i++){
            if(usedSamples[i]==true){
                classId = labels[i];
            }
            else{
                classId = 0;
            }
        }
        treeNode->checkLeaf = true;
        treeNode->item = classId;
        return;
    }
    //function create child node untill it reaches leaf node
    else{
        treeNode->item = id;
        treeNode->checkLeaf = false; //it cant be leaf since it has feature id
        //for left
        trainHelp(data, labels, numSamples,  numFeatures, treeNode->leftUsedSamples, usedFeatures, treeNode->leftChild, id);
        //for right
        trainHelp(data, labels, numSamples,  numFeatures, treeNode->rightUsedSamples, usedFeatures, treeNode->rightChild, id);
    }
    
}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures){
    
    
    int item = 0;
    
    //DecisionTreeNode * leftChild  = NULL;
   // DecisionTreeNode * rightChild = NULL;
    
    //create rooe with no items
    root = new DecisionTreeNode(item, NULL, NULL);
    
    //create used samples
    root->usedSamples = new bool[numSamples];
    
    for(int i=0; i<numSamples; i++){
        root->usedSamples[i] = false;
    }
   
    //initially features are not used
    bool * usedFeatures = new bool[numSamples];
    for(int i=0; i<numFeatures; i++){
        usedFeatures[i] = false;
    }
    
    bool * usedSamples = new bool[numSamples];
    usedSamples = root->usedSamples;
    
    int selectedFeature = getFeature(data,labels, numSamples,numFeatures,usedSamples, usedFeatures);
    
    usedFeatures[selectedFeature] = true; //when the infoGain is max, this feature is used(true)
    root->item = selectedFeature; //root's feature is selected feature
    root->checkLeaf = false; //since root has feature ID it has child node
    
    for (int i = 0; i < numSamples; i++) {
        if (data[i][selectedFeature] == true) {
            usedSamples[i] = true;
        }
    } //now, we have used samples array for root node
    
    
    //to change left usedSamples
    //send false samples to the leftUsedSamples as true
    for(int i = 0; i< numSamples; i++){
        if(data[i][selectedFeature]== true){
            root->leftUsedSamples[i] = false;
        }
    }
    
    //to change right
    for(int i = 0; i<numSamples; i++){
        if(data[i][selectedFeature]== false){
            root->rightUsedSamples[i] = false;
        }
    }
    
    DecisionTreeNode * curNode = root;
    
    trainHelp(data,labels,numSamples, numFeatures, curNode->leftUsedSamples, usedFeatures,curNode->leftChild, selectedFeature);
    trainHelp(data,labels,numSamples, numFeatures, curNode->rightUsedSamples,        usedFeatures,curNode->rightChild, selectedFeature);
    
}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures){
    
    ifstream myFile;
    myFile.open(fileName);
    
    //create labels array which at the last column
    int * labels = new int[numSamples];
    for(int i = 0; i<numSamples ; i++){
        labels[i] = 0;
    }
     //create data table
    bool** data;
    data = new bool*[numSamples];
    
    //create the rows of data table with # of numFeature elements
    for(int i = 0; i< numSamples; i++){
        data[i] = new bool [numFeatures];
    }
    
    //fill the data table with zeros
    for(int j= 0; j<numSamples; j++){
        for(int i = 0; i< numFeatures; i++){
            data[j][i]  = 0;
        }
    }
    
    //get data from myFile "fileName"
    for(int a = 0; a < numSamples;a++){
        for (int b = 0; b< numFeatures;b++)
        {
            if(b!=numFeatures)
                myFile >> data[a][b];
            else{
                myFile>> labels[a];
            }
        }
    }
    
    //call given train function
    train((const bool**)data, labels, numSamples,numFeatures);
    myFile.close();
    
}
int DecisionTree::predict(const bool* data){
    
    DecisionTreeNode* currentNode;
    currentNode = root;
    
    int nodeItem = currentNode->item;
    int idClass= 0;
    
    while(nodeItem != 0){
        if(currentNode->checkLeaf==true){
            //here currentNode's item is labels[lastRow]
            idClass = currentNode->item;
            nodeItem= 0;
        }
        else{
            //here item is featureID
            if(data[currentNode->item]==false){
                currentNode = currentNode->leftChild;
                nodeItem = currentNode->item;
            }
            else{
                currentNode = currentNode->rightChild;
                nodeItem = currentNode->item;
            }
        }
    }
    
    return idClass;
}
double DecisionTree::test(const bool** data, const int* labels, const int numSamples){
    return 0;
}
double DecisionTree::test(const string fileName, const int numSamples){
    return 0;
}

void DecisionTree::print(){
    int x= 0;
    DecisionTreeNode* node = root;
    cout<< "DECISION TREE : "  <<endl;
    preOrderPrint(node, x);
    
}

//recursive helper function for print method
void DecisionTree::preOrderPrint(DecisionTreeNode* node, int&i){
    
    if(node==NULL){
        cout<< "No tree exists " <<endl;
        return;
    }
    else{
        if(node->checkLeaf == false){
            for(int a=0; a<i; a++){ //i is to determine the space for print
                cout<<"     "<<endl;
            }
            cout<<"CLASS = "<<node->item <<endl;
        }
        else{
            for(int j= 0; j<i; i++){
                cout<<"     "<<endl;
            }
            cout<< "Feature" << node->item <<endl;
        }
    }
    i++;
    preOrderPrint(node->leftChild,  i);
    preOrderPrint(node->rightChild, i);
}


