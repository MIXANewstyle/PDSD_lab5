#include "SetLab5_Ushakov.h"
#include <iostream>

// Используем, чтобы не писать std::
using namespace std;

// --- Вспомогательный метод ---
int MySet::getRandomInt(int minVal, int maxVal) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    return dist(gen);
}

// --- F1. Конструктор по умолчанию ---
MySet::MySet() {
    // std::set создается пустым по умолчанию.
}

// --- F5. Параметризованный конструктор ---
MySet::MySet(int count, int minVal, int maxVal, char setRule) {
    // _elements уже пустой

    // Проверка возможности создания (та же логика, что в ЛР 2, 3, 4)
    int availableCount = 0;
    for (int i = minVal; i <= maxVal; ++i) {
        if (setRule == 'A' && i % 9 == 0) availableCount++;
        else if (setRule == 'B' && i % 3 == 0) availableCount++;
        else if (setRule != 'A' && setRule != 'B') availableCount++;
    }

    if (count > availableCount) {
        cerr << "Ошибка F5: Невозможно создать множество. "
            << "Требуемое кол-во (" << count
            << ") > чем доступно (" << availableCount << ")" << endl;
        return;
    }

    // Цикл генерации
    int elementsAdded = 0;
    int attempts = 0;
    int maxAttempts = count * 150 + 1000;

    while (elementsAdded < count && attempts < maxAttempts) {
        int randomValue = getRandomInt(minVal, maxVal);
        attempts++;

        // Проверяем правило
        bool passesRule = false;
        if (setRule == 'A') passesRule = (randomValue % 9 == 0);
        else if (setRule == 'B') passesRule = (randomValue % 3 == 0);
        else passesRule = true;

        if (passesRule) {
            // Используем AddElement (F4), который теперь вызывает std::set::insert
            if (this->AddElement(randomValue)) {
                elementsAdded++;
            }
        }
    }
}

// --- F8. Деструктор ---
MySet::~MySet() {
    // std::set сам управляет своей памятью.
    // Ничего делать не нужно.
}

// --- F2. Пустое множество? ---
bool MySet::IsEmpty() const {
    // Используем метод контейнера
    return _elements.empty();
}

// --- F3. Проверка принадлежности ---
bool MySet::IsInSet(int value) const {
    // Используем std::set::count (возвращает 1, если элемент есть, 0 - если нет)
    return _elements.count(value) > 0;
}

// --- F4. Добавление элемента ---
bool MySet::AddElement(int value) {
    // std::set::insert возвращает pair<iterator, bool>
    // .second (bool) равен 'true', если вставка произошла (элемент был новым)
    // и 'false', если элемент уже был в множестве.
    return _elements.insert(value).second;
}

// --- F6. Мощность множества ---
int MySet::GetPower() const {
    // Используем метод контейнера
    return _elements.size();
}

// --- F7. Вывод в строку ---
string MySet::GetSetAsString(char separator) const {
    if (this->IsEmpty()) { // F2
        return "Множество пустое";
    }

    stringstream ss;
    // (Элементы в std::set всегда отсортированы)
    for (auto it = _elements.begin(); it != _elements.end(); ++it) {
        ss << *it;

        auto next_it = it;
        ++next_it;
        if (next_it != _elements.end()) {
            ss << separator;
        }
    }
    return ss.str();
}

// --- F9. Подмножество? ---
bool MySet::IsSubset(const MySet& otherSet) const {
    // Используем std::includes из <algorithm>
    // Проверяем, что 'otherSet' (B) включает в себя 'this' (A)
    return std::includes(otherSet._elements.begin(), otherSet._elements.end(),
        this->_elements.begin(), this->_elements.end());
}

// --- F1E0. Равенство? ---
bool MySet::IsEqual(const MySet& otherSet) const {
    // std::set имеет встроенный оператор ==
    // Он сравнивает размеры и поэлементно
    return this->_elements == otherSet._elements;
}

// --- F11. Объединение ---
MySet MySet::Union(const MySet& otherSet) const {
    MySet result; // F1
    // Используем std::set_union из <algorithm>
    std::set_union(_elements.begin(), _elements.end(),
        otherSet._elements.begin(), otherSet._elements.end(),
        // Вывод (куда вставлять)
        std::inserter(result._elements, result._elements.begin()));
    return result;
}

// --- F12. Пересечение ---
MySet MySet::Intersection(const MySet& otherSet) const {
    MySet result; // F1
    // Используем std::set_intersection
    std::set_intersection(_elements.begin(), _elements.end(),
        otherSet._elements.begin(), otherSet._elements.end(),
        std::inserter(result._elements, result._elements.begin()));
    return result;
}

// --- F13. Разность ---
MySet MySet::Difference(const MySet& otherSet) const {
    MySet result; // F1
    // Используем std::set_difference
    std::set_difference(_elements.begin(), _elements.end(),
        otherSet._elements.begin(), otherSet._elements.end(),
        std::inserter(result._elements, result._elements.begin()));
    return result;
}

// --- F14. Симметричная разность ---
MySet MySet::SymmetricDifference(const MySet& otherSet) const {
    MySet result; // F1
    // Используем std::set_symmetric_difference
    std::set_symmetric_difference(_elements.begin(), _elements.end(),
        otherSet._elements.begin(), otherSet._elements.end(),
        std::inserter(result._elements, result._elements.begin()));
    return result;
}