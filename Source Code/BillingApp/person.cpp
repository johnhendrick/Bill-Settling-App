#include "person.h"
#include <limits>


Person::Person()
{

}

void Person::init()
{
    setName();
    setMoney();
}

void Person::setName(const string &name)
{
    _name = name;
}

void Person::setMoney(double m)
{
    _money = m;
}

void Person::init(const string &name, double m)
{
    setName( name );
    setMoney( m );
}

void Person::setName() {
    cout << "\nEnter a name:\t\t";
    cin >> _name;
}

void Person::setMoney() {
    char pound = 156;
    cout << "Enter the amount paid:\t"<<pound;
    _money = validDouble();

}

void Person::setShouldReceive(double shouldReceive){
    _shouldReceive = shouldReceive;
}

double Person::validDouble()
{
    double x;
    cin >> x;
    while (cin.fail()==1)
    {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "Bad input. Enter a number: ";
        cin >> x;
    }
    return x;
}
