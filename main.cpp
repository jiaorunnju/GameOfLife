/*************************************************************************
# File Name: main.cpp
# Author :Jiaorun
 ************************************************************************/

#include "model.h"
#include <iostream>

int main(){
    int a,b;
    std::cin>>a>>b;
    Model* p = Model::getInstance(a,b);
    p->start();
}
