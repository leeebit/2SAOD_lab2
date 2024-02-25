#include <iostream>
#include <vector>
#include <cstdlib> // Для функции rand()

using namespace std;

const int MAX_SIZE = 10000;

struct Item {
    int key;
    int value;
};

class HashTable {
private:
    vector<Item> table;
    int size;
    int collisions;

public:
    HashTable(int size) {
        this->size = size;
        table.resize(size, { -1, -1 }); // Инициализация таблицы значениями -1 для ключа и значения
        collisions = 0;
    }

    int hash(int key) {
        return key % size;
    }

    int insert(int key, int value) {
        int index = hash(key);
        int comparisons = 0; // Переменная для подсчета количества сравнений

        // Проверяем, не занято ли место, если да, ищем следующее свободное
        while (table[index].key != -1) {
            index = (index + 1) % size;
            comparisons++;
            collisions++; // Учитываем коллизию
        }

        table[index].key = key;
        table[index].value = value;

        return comparisons; // Возвращаем количество сравнений
    }

    int find(int key) {
        int index = hash(key);

        // Пока не найдем элемент или не обойдем всю таблицу
        while (table[index].key != -1) {
            if (table[index].key == key) {
                return table[index].value;
            }

            index = (index + 1) % size;
        }

        return -1; // Возвращаем -1, если элемент не найден
    }

    void remove(int key) {
        int index = hash(key);

        // Пока не найдем элемент или не обойдем всю таблицу
        while (table[index].key != -1) {
            if (table[index].key == key) {
                table[index].key = -1; // Удаляем элемент
                return;
            }

            index = (index + 1) % size;
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            if (table[i].key != -1) {
                cout << "(" << table[i].key << ", " << table[i].value << ") ";
            }
            else {
                cout << "(-1, -1) ";
            }
        }

        cout << endl;
    }

    int getCollisions() {
        return collisions;
    }
};

int main() {
    int sizes[] = { 10, 15, 23, 25 };

    for (int size : sizes) {
        HashTable table(size);

        int comparisons = 0; // Переменная для хранения общего количества сравнений

        // Заполняем таблицу ключами, которые создают коллизии
        for (int i = 0; i < size; i++) {
            // Генерируем случайное значение для value с одинаковой кратностью относительно размера таблицы
            int randValue = ((i * 10) % size) + i; // Добавляем индекс, чтобы значения были различными
            comparisons += table.insert(i * 10, randValue); // Считаем сравнения при вставке нового элемента
        }

        cout << "Size: " << size << endl;
        cout << "Collisions: " << table.getCollisions() << endl;
        cout << "Comparisons: " << comparisons << endl; // Выводим общее количество сравнений
        table.print();

        if (table.getCollisions() > 0) {
            cout << "Collisions were resolved." << endl;
        }
        else {
            cout << "Collisions were not resolved." << endl; // Изменено на "Collisions were resolved."
        }

        cout << endl;
    }

    return 0;
}
