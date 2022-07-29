#include<iostream>
#include "RBtree.h"

int main(){
    rbTree<int> mytree(2);
    for(int i =0; i < 10; i++)mytree.insertRBT(i);
    for(int i =0; i < 5; i++)mytree.deleteRBT(i);
    return 0;
}
