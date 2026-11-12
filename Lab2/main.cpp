#include <iostream>
#include <windows.h>
#include <stdexcept>
#include "Train.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "=== Проверка иерархии классов Base и TRAIN ===" << std::endl;

    try {
        TRAIN t1;
        TRAIN t2("Москва", 102, 23, 55);
        std::cout << "Объект t2: " << t2 << std::endl;

        TRAIN t3(t2);
        std::cout << "Объект t3 (копия): " << t3 << std::endl;

        std::cout << "\nВведите данные для поезда t1:" << std::endl;
        std::cin >> t1;
        std::cout << "Введенный поезд t1: " << t1 << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }

    return 0;
}