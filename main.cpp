#include <iostream>

using namespace std;

// Определяем структуру Product для хранения данных о продукте
struct Product {
    char name[100]; // Название продукта
    double price;   // Цена продукта
};

// Функция для вывода массива продуктов на экран
void display(Product products[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << "Название: " << products[i].name
            << ", Стоимость: " << products[i].price << endl;
    }
}

// Реализация пузырьковой сортировки по убыванию стоимости
void bubbleSort(Product products[], int n, int& comparisons, int& swaps) {
    comparisons = swaps = 0; // Инициализация счётчиков для сравнений и обменов
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparisons; // Увеличиваем счётчик сравнений
            if (products[j].price < products[j + 1].price) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
                ++swaps; // Увеличиваем счётчик обменов
            }
        }
    }
}

// Реализация сортировки выбором по убыванию стоимости
void selectionSort(Product products[], int n, int& comparisons, int& swaps) {
    comparisons = swaps = 0; // Инициализация счётчиков для сравнений и обменов
    for (int i = 0; i < n - 1; ++i) {
        int maxIndex = i; // Предполагаем, что текущий элемент максимальный
        for (int j = i + 1; j < n; ++j) {
            ++comparisons; // Увеличиваем счётчик сравнений
            if (products[j].price > products[maxIndex].price) {
                maxIndex = j; // Обновляем индекс максимального элемента
            }
        }
        if (maxIndex != i) {
            Product temp = products[i];
            products[i] = products[maxIndex];
            products[maxIndex] = temp;
            ++swaps; // Увеличиваем счётчик обменов
        }
    }
}

// Функция, используемая в быстрой сортировке для разделения массива
int partition(Product products[], int low, int high, int& comparisons,
    int& swaps) {
    double pivot = products[high].price; // Опорный элемент
    int i = low - 1; // Индекс меньшего элемента
    for (int j = low; j < high; ++j) {
        ++comparisons; // Увеличиваем счётчик сравнений
        if (products[j].price >= pivot) {
            ++i;
            Product temp = products[i];
            products[i] = products[j];
            products[j] = temp;
            ++swaps; // Увеличиваем счётчик обменов
        }
    }
    Product temp = products[i + 1];
    products[i + 1] = products[high];
    products[high] = temp;
    ++swaps; // Увеличиваем счётчик обменов
    return i + 1; // Возвращаем индекс опорного элемента
}

// Функция быстрой сортировки (рекурсивный алгоритм)
void quickSort(Product products[], int low, int high, int& comparisons,
    int& swaps) {
    if (low < high) {
        int pi = partition(products, low, high, comparisons, swaps);
        quickSort(products, low, pi - 1, comparisons, swaps);
        quickSort(products, pi + 1, high, comparisons, swaps);
    }
}

// Функция для восстановления свойства максимальной кучи
void heapify(Product products[], int n, int i, int& comparisons, int& swaps) {
    int largest = i; // Предполагаем, что текущий узел - наибольший
    int left = 2 * i + 1; // Индекс левого дочернего узла
    int right = 2 * i + 2; // Индекс правого дочернего узла

    // Проверка, больше ли левый дочерний узел текущего наибольшего
    if (left < n) {
        ++comparisons;
        if (products[left].price > products[largest].price) {
            largest = left; // Обновляем индекс наибольшего
        }
    }

    // Проверка, больше ли правый дочерний узел текущего наибольшего
    if (right < n) {
        ++comparisons;
        if (products[right].price > products[largest].price) {
            largest = right; // Обновляем индекс наибольшего
        }
    }

    // Если наибольший элемент не корень, меняем местами и рекурсивно
    // восстанавливаем кучу
    if (largest != i) {
        Product temp = products[i];
        products[i] = products[largest];
        products[largest] = temp;
        ++swaps;
        heapify(products, n, largest, comparisons,
            swaps); // Рекурсивный вызов для поддерева
    }
}

// Пирамидальная сортировка по убыванию
void heapSort(Product products[], int n, int& comparisons, int& swaps) {
    comparisons = swaps = 0;

    // Построение максимальной кучи
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(products, n, i, comparisons, swaps);
    }

    // Извлечение элементов из кучи по одному
    for (int i = n - 1; i >= 0; --i) {
        // Перемещаем текущий корень (максимальный элемент) в конец массива
        Product temp = products[0];
        products[0] = products[i];
        products[i] = temp;
        ++swaps;

        // Восстанавливаем кучу для уменьшенного массива
        heapify(products, i, 0, comparisons, swaps);
    }

    // Обратный порядок массива для сортировки по убыванию
    for (int i = 0; i < n / 2; ++i) {
        Product temp = products[i];
        products[i] = products[n - i - 1];
        products[n - i - 1] = temp;
    }
}

// Функция для ввода данных о продуктах с валидацией
void inputProducts(Product products[], int& n) {
    cout << "Введите количество продуктов: ";
    cin >> n; // Ввод количества продуктов

    for (int i = 0; i < n; ++i) { // Цикл по количеству продуктов
        cout << "Введите название продукта " << i + 1 << ": ";
        cin >> products[i].name; // Ввод названия продукта

        // Ввод стоимости с валидацией
        while (true) {
            cout << "Введите стоимость продукта " << i + 1 << ": ";
            cin >> products[i].price; // Ввод стоимости продукта

            if (cin.fail()) { // Проверка на нечисловой ввод
                cin.clear();    // Сброс состояния потока
                cin.ignore(10000, '\n'); // Игнорировать некорректный ввод
                cout << "Ошибка: введите корректное числовое значение для стоимости."
                    << endl;
            }
            else {
                cin.ignore(10000, '\n'); // Очищаем входной буфер
                break; // Ввод корректен, выходим из цикла
            }
        }
    }
}

// Основное меню программы
void menu() {
    const int MAX_PRODUCTS = 100; // Максимальное количество продуктов
    Product products[MAX_PRODUCTS]; // Массив для хранения продуктов
    int n = 0;  // Текущее количество продуктов
    int choice; // Выбор пользователя

    do {
        // Отображаем меню для пользователя
        cout << "\nМеню:\n";
        cout << "1. Ввод данных\n";
        cout << "2. Вывод исходных данных\n";
        cout << "3. Сортировка пузырьком\n";
        cout << "4. Сортировка выбором\n";
        cout << "5. Быстрая сортировка\n";
        cout << "6. Пирамидальная сортировка\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт меню: ";
        cin >> choice; // Считываем выбор

        if (choice == 1) { // Ввод данных
            inputProducts(products, n);
        }
        else if (choice == 2) { // Вывод исходных данных
            display(products, n);
        }
        else if (choice == 3) { // Сортировка пузырьком
            int comparisons, swaps;
            bubbleSort(products, n, comparisons, swaps);
            cout << "Сортировка пузырьком завершена.\n";
            cout << "Число сравнений: " << comparisons << ", Число обменов: " << swaps
                << endl;
            display(products, n);
        }
        else if (choice == 4) { // Сортировка выбором
            int comparisons, swaps;
            selectionSort(products, n, comparisons, swaps);
            cout << "Сортировка выбором завершена.\n";
            cout << "Число сравнений: " << comparisons << ", Число обменов: " << swaps
                << endl;
            display(products, n);
        }
        else if (choice == 5) { // Быстрая сортировка
            int comparisons = 0, swaps = 0;
            quickSort(products, 0, n - 1, comparisons, swaps);
            cout << "Быстрая сортировка завершена.\n";
            cout << "Число сравнений: " << comparisons << ", Число обменов: " << swaps
                << endl;
            display(products, n);
        }
        else if (choice == 6) { // Пирамидальная сортировка
            int comparisons = 0, swaps = 0;
            heapSort(products, n, comparisons, swaps);
            cout << "Пирамидальная сортировка завершена.\n";
            cout << "Число сравнений: " << comparisons << ", Число обменов: " << swaps
                << endl;
            display(products, n);
        }
    } while (
        choice !=
        0); // Цикл продолжается до тех пор, пока пользователь не выберет выход
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    menu();   // Запускаем главное меню
    return 0; // Возвращаем 0 для успешного завершения программы
}
