#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <cstring>
#include <stdexcept>

class Base {
protected:
    char* name; // Наименование перевозчика
    double cargoVolume;  // Объем перевозимого груза

public:
    Base();
    Base(const char* name, double cargoVolume);
    Base(const Base& other);

    virtual ~Base();

    virtual void input() = 0;
    virtual void print() const = 0;
    virtual Base* clone() const = 0; 
    virtual const char* getType() const = 0; 
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;

    const char* getName() const;
    void setName(const char* newName);

    double getCargoVolume() const;
    void setCargoVolume(double volume);
};

#endif 