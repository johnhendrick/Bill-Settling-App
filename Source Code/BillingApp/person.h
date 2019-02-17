#ifndef PERSON_H
#define PERSON_H


#pragma once
#include <string>
#include <iostream>
using namespace std;

class Person
{
public:
    Person();
    void setName();
    void setMoney();
    void init();
    /// ###
    void setName( const string &name );
    void setMoney( double m);
    void init( const string &name  , double m );
    /// ###
    string getName(){ return _name; }
    double getMoney(){ return _money; }
    double getShouldReceive() { return _shouldReceive; }
    void setShouldReceive(double shouldReceive);
    double validDouble();


private:
    string _name;
    double _money;
    double _shouldReceive;	//positive means person should receive money, negative means pay somebody
};


#endif // PERSON_H
