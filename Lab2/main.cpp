#include <iostream>
#include <windows.h>
#include <stdexcept>
#include "Keeper.h"
#include "TextProcessor.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Keeper keeper;
    TextProcessor textProcessor;
    int choice = 0;
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\n--- Главное меню ---" << std::endl;
        std::cout << "1. Добавить поезд на указанную позицию" << std::endl;
        std::cout << "2. Удалить запись о поезде" << std::endl;
        std::cout << "3. Изменить данные о поезде" << std::endl;
        std::cout << "4. Вывести расписание всех поездов" << std::endl;
        std::cout << "5. Найти поезд по номеру" << std::endl;
        std::cout << "6. Проверить конструктор копирования Keeper" << std::endl;
        std::cout << "7. Найти в файле предложения с заданным числом слов" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Ваш выбор: ";

        try {
            if (!(std::cin >> choice)) {
                throw std::invalid_argument("Ошибка: введен некорректный символ! Ожидалось число.");
            }

            switch (choice) {
            case 1: {
                int pos;
                std::cout << "Введите позицию вставки (от 1 до " << (keeper.getCount() + 1) << "): ";
                if (!(std::cin >> pos)) {
                    throw std::invalid_argument("Ошибка: позиция должна быть числом!");
                }

                std::cout << "\n=== Ввод данных о поезде ===" << std::endl;
                TRAIN* newTrain = new TRAIN();
                try {
                    std::cin >> *newTrain;
                    keeper.insertItem(newTrain, pos - 1);
                }
                catch (...) {
                    delete newTrain;
                    throw;
                }
                std::cout << "Поезд успешно добавлен и упорядочен по номеру!" << std::endl;
                break;
            }
            case 2: {
                keeper.printAll();
                if (keeper.getCount() > 0) {
                    int index;
                    std::cout << "Введите номер записи для удаления (начиная с 1): ";
                    if (!(std::cin >> index)) {
                        throw std::invalid_argument("Ошибка: индекс должен быть числом!");
                    }
                    keeper.removeItem(index - 1);
                    std::cout << "Запись успешно удалена!" << std::endl;
                }
                break;
            }
            case 3: {
                keeper.printAll();
                if (keeper.getCount() > 0) {
                    int index;
                    std::cout << "Введите номер записи для изменения (начиная с 1): ";
                    if (!(std::cin >> index)) {
                        throw std::invalid_argument("Ошибка: индекс должен быть числом!");
                    }
                    keeper.editItem(index - 1);
                    std::cout << "Данные о поезде успешно изменены!" << std::endl;
                }
                break;
            }
            case 4:
                keeper.printAll();
                break;
            case 5: {
                int trainNum;
                std::cout << "Введите номер поезда для поиска: ";
                if (!(std::cin >> trainNum)) {
                    throw std::invalid_argument("Ошибка: номер поезда должен быть числом!");
                }
                keeper.findByTrainNumber(trainNum);
                break;
            }
            case 6: {
                std::cout << "\n--- Создание копии расписания ---" << std::endl;
                Keeper copyKeeper(keeper);
                copyKeeper.printAll();
                std::cout << "--- Выход из области видимости копии ---" << std::endl;
                break;
            }
            case 7: {
                char filename[256];
                int wordCount;
                std::cout << "Введите имя файла (например, text.txt): ";
                std::cin >> filename;
                textProcessor.setFilename(filename);

                std::cout << "Введите количество слов в предложении: ";
                if (!(std::cin >> wordCount)) {
                    throw std::invalid_argument("Ошибка: количество слов должно быть целым числом!");
                }
                textProcessor.printSentencesByWordCount(wordCount);
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