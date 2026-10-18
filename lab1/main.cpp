#include <iostream>
#include <windows.h>
#include <stdexcept>
#include "Keeper.h"

int main() {
    SetConsoleCP(1251);           
    SetConsoleOutputCP(1251);

    Keeper keeper;
    int choice = 0;
    bool isRunning = true;
    while (isRunning) {
        std::cout << "\n--- Главное меню ---" << std::endl;
        std::cout << "1. Добавить перевозчика" << std::endl;
        std::cout << "2. Удалить перевозчика" << std::endl;
        std::cout << "3. Изменить данные перевозчика" << std::endl;
        std::cout << "4. Вывести список всех перевозчиков" << std::endl;
        std::cout << "5. Сохранить данные в файл" << std::endl;
        std::cout << "6. Загрузить данные из файла" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Ваш выбор: ";

        try {
            if (!(std::cin >> choice)) {
                throw std::invalid_argument("Ошибка: введен некорректный символ! Ожидалось число.");
            }

            switch (choice) {
            case 1: {
                int type;
                std::cout << "Выберите тип перевозчика:\n1. Самолёт\n2. Поезд\n3. Автомобиль\nВаш выбор: ";
                std::cin >> type;

                Base* newItem = nullptr;
                if (type == 1) newItem = new Airplane();
                else if (type == 2) newItem = new Train();
                else if (type == 3) newItem = new Car();
                else throw std::invalid_argument("Ошибка: неверный тип перевозчика!");

                newItem->input();
                keeper.addItem(newItem);
                std::cout << "Объект успешно добавлен!" << std::endl;
                break;
            }
            case 2: {
                keeper.printAll();
                if (keeper.getCount() > 0) {
                    int index;
                    std::cout << "Введите номер объекта для удаления (начиная с 1): ";
                    std::cin >> index;
                    keeper.removeItem(index - 1);
                    std::cout << "Объект успешно удален!" << std::endl;
                }
                break;
            }
            case 3: {
                keeper.printAll();
                if (keeper.getCount() > 0) {
                    int index;
                    std::cout << "Введите номер объекта для изменения (начиная с 1): ";
                    std::cin >> index;
                    keeper.getItem(index - 1)->input();
                    std::cout << "Данные объекта успешно изменены!" << std::endl;
                }
                break;
            }
            case 4:
                keeper.printAll();
                break;
            case 5: {
                char filename[256];
                std::cout << "Введите имя файла для сохранения (например, data.txt): ";
                std::cin >> filename;
                keeper.saveToFile(filename);
                break;
            }
            case 6: {
                char filename[256];
                std::cout << "Введите имя файла для загрузки (например, data.txt): ";
                std::cin >> filename;
                keeper.loadFromFile(filename);
                break;
            }
            case 0:
                isRunning = false;
                std::cout << "Выход из программы..." << std::endl;
                break;
            default:
                std::cout << "Ошибка: такого пункта меню не существует!" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n'); 
        }
    }

    return 0;
}