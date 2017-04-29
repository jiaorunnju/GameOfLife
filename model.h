/*************************************************************************
# File Name: model.h
# Author :Jiaorun
 ************************************************************************/

#ifndef MODEL_H
#define MODEL_H

class Model
{
private:
    int x,y;
    static Model *single;
    bool *ptr1;
    bool *ptr2;
    bool *valid;
    bool *invalid;
    bool changed;

    void set(int,int);
    void erase(int,int);
    bool check(int,int);
    void update();
    Model(int,int);
    void init();

public:
    virtual ~Model();
    void start();
    static Model* getInstance(int a,int b);
};


#endif /* MODEL_H */
