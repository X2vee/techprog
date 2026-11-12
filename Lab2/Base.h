#ifndef BASE_H
#define BASE_H

#include <iostream>

class Base {
private:
    char* carrier; // Перевозчик

public:
    // Конструкторы и деструктор
    Base();
    Base(const char* newCarrier);
    Base(const Base& other);
    virtual ~Base();

    // Геттеры и сеттеры
    const char* getCarrier() const;
    void setCarrier(const char* newCarrier);

    // Виртуальные методы
    virtual void print() const = 0;
    virtual Base* clone() const = 0;
    virtual const char* getType() const = 0;

    // Переопределение операторов
    Base& operator=(const Base& other);
};

#endif