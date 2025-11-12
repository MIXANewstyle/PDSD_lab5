#pragma once

#include <string>
#include <sstream>
#include <random>
#include <set>          // !!! Подключаем set !!!
#include <algorithm>    // !!! Для set_union, set_intersection и т.д. !!!
#include <iterator>     // !!! Для std::inserter !!!

// Класс "Множество" на основе std::set
class MySet {
private:
    // --- Параметр класса ---
    std::set<int> _elements; // Вместо std::list<int>

    // --- Вспомогательный метод (нужен для F5) ---
    int getRandomInt(int minVal, int maxVal);

public:
    // --- Методы класса (F1-F14) ---

    // F1. Конструктор по умолчанию (создание пустого множества)
    MySet();

    // F5. Параметризованный конструктор (создание множества)
    MySet(int count, int minVal, int maxVal, char setRule = ' ');

    // F8. Деструктор (пустой)
    ~MySet();

    // F2. Пустое множество?
    bool IsEmpty() const;

    // F3. Проверка принадлежности (используем std::set::count)
    bool IsInSet(int value) const;

    // F4. Добавление элемента (используем std::set::insert)
    bool AddElement(int value);

    // F6. Мощность множества (используем std::set::size)
    int GetPower() const;

    // F7. Вывод в строку
    std::string GetSetAsString(char separator) const;

    // F9. Подмножество? (используем std::includes)
    bool IsSubset(const MySet& otherSet) const;

    // F10. Равенство? (используем std::set::operator==)
    bool IsEqual(const MySet& otherSet) const;

    // F11. Объединение (используем std::set_union)
    MySet Union(const MySet& otherSet) const;

    // F12. Пересечение (используем std::set_intersection)
    MySet Intersection(const MySet& otherSet) const;

    // F13. Разность (используем std::set_difference)
    MySet Difference(const MySet& otherSet) const;

    // F14. Симметричная разность (используем std::set_symmetric_difference)
    MySet SymmetricDifference(const MySet& otherSet) const;
};