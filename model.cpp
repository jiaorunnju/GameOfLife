/*************************************************************************
# File Name: model.cpp
# Author :Jiaorun
 ************************************************************************/
#include "model.h"
#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const char EMPTY[] = "  ";
const char PIC[] = "[]";
Model* Model::single = nullptr;

Model::Model(int a,int b){
    this->x = a;
    this->y = b;
    ptr1 = new bool[x*y];
    ptr2 = new bool[x*y];
    valid = ptr1;
    invalid = ptr2;
    init();
}

Model* Model::getInstance(int a,int b){
    if(single == nullptr){
        initscr();
        curs_set(0);
        Model* p = new Model(a,b);
        single = p;
    }
    return single;
}

Model::~Model(){
    delete[] ptr1;
    delete[] ptr2;
}

void Model::start(){
    int ch;
    while((ch=getch())!='q'){
        for(int i=0; i<x; ++i){
            for(int j=0; j<y; ++j){
                if(valid[i*y+j]){
                    mvprintw(i,j*2,PIC);
                }else{
                    mvprintw(i,2*j,EMPTY);
                }
            }
        }
        changed = false;
        update();
    }
    endwin();
}

void Model::set(int a,int b){
    if(a<x && b<y && a>=0 && b>=0){
        invalid[a*y+b] = true;
    }
}

void Model::erase(int a,int b){
    if(a<x && b<y && a>=0 && b>=0){
        invalid[a*y+b] = false;
    }
}

void swap(bool* &a, bool* &b){
    bool* temp = a;
    a = b;
    b = temp;
}

void Model::update(){
    for(int i=0; i<x; ++i){
        for(int j=0; j<y;++j){
            if(check(i,j)){
                set(i,j);
            }else{
                erase(i,j);
            }
        }
    }
    swap(valid,invalid);
}

bool Model::check(int a,int b){
    int count = 0;
    int lowX = (a-1)>=0?a-1:a;
    int lowY = (b-1)>=0?b-1:b;
    int highX = (a+1)>=x?x-1:a+1;
    int highY = (b+1)>=y?y-1:b+1;

    for(int i=lowX; i<=highX; ++i){
        for(int j=lowY; j<=highY; ++j){
            if(i==a && j==b){
                continue;
            }
            if(valid[i*y+j]){
                //std::cout<<a<<" "<<b<<"\n";
                //std::cout<<lowX<<" "<<lowY<<" "<<highX<<" "<<highY<<std::endl;
                ++count;
            }
        }
    }

    if(count>=2 && count<=3 && valid[a*y+b]){
        //std::cout<<"point: "<<a<<" "<<b<<" is valid"<<std::endl;
        return true;
    }else if(count==3 && !valid[a*y+b]){
        //std::cout<<"point: "<<a<<" "<<b<<" is valid"<<std::endl;
        changed = true;
        return true;
    }else{
        if(valid[a*y+b]){
            changed = true;
        }
        return false;
    }
}

void Model::init(){
    srand((unsigned)time(0));
    int count = 0;
    while(count<x*y/2){
        int i = rand()%x;
        int j = rand()%y;
        if(!valid[i*y+j]){
            valid[i*y+j]=true;
            ++count;
        }
    }
}
