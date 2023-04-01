#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>

//123456789
using namespace std;
void NewTable(), ShowTable(), SaveTable(), LoadTable(), Sort(), Search();
int SortNumber(int j), SortMileage(int j), SortBrand(int j);
//10. Регистрационный номер автомобиля, марка, пробег.
//Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур.В перечень функций входят :
//·        ввод записи таблицы с клавиатуры;
//·        загрузка и сохранение  таблицы в текстовом файле;
//·        просмотр таблицы;
//·        сортировка таблицы в порядке возрастания заданного поля;
//·        поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
//·        удаление записи;
//·        изменение(редактирование) записи;
//·        вычисление с проверкой и использованием всех по заданному условию и формуле(например, общая сумма на всех счетах).

struct car {
    char number[30];
    char brand[30];
    int mileage;
};

// Уровень 3 - представление таблицы

struct table {
    int len;   // текущая размерность массива
    car* TBL;                            // массив структурированных переменных
} TableOfCar;

int main()
{
    int command = -1;
    setlocale(LC_ALL, "Rus");
    printf("Введите номер функции которую хотите использовать:\n");
    printf("0. Остановить программу\n");
    printf("1. Ввод данных с клавиатуры\n");
    printf("2. Загрузка данных из тектового файла\n");
    printf("3. Сохранение данных в тектовый файл\n");
    printf("4. Просмотр таблицы\n");
    printf("5. Сортировка таблицы в порядке возрастания заданного поля\n");
    printf("6. Поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению\n");
    printf("7. Удаление запии\n");
    printf("8. Изменение записи\n");

    while (true) {
        printf("Введите команду: ");
        scanf("%d", &command);

        switch (command) {
        case 0:

            break;
        case 1:
            NewTable();
            break;
        case 2:
            LoadTable();
            break;
        case 3:
            SaveTable();
            break;
        case 4:
            ShowTable();
            break;
        case 5:
            Sort();
            break;
        case 6:
            Search();
            break;
        case 7:
            printf("нет");
            break;
        case 8:
            printf("нет");
            break;
        default:
            printf("Неправильный ввод.\n");
        }

    }
}

void NewTable() {
    printf("Введите количество элементов таблицы: ");
    scanf("%d", &TableOfCar.len);
    TableOfCar.TBL = new car[TableOfCar.len];
    for (int i = 0; i < TableOfCar.len; i++) {
        printf("Регистрационный номер автомобиля: ");
        scanf("%s", &TableOfCar.TBL[i].number);
        printf("Марка: ");
        scanf("%s", &TableOfCar.TBL[i].brand);
        printf("Пробег: ");
        scanf("%d", &TableOfCar.TBL[i].mileage);
        printf("");
    }
}

void ShowTable() {
    for (int i = 0; i < TableOfCar.len; i++) {
        cout << left << i + 1 << ". " << setw(12) << left << TableOfCar.TBL[i].number << setw(20) << left << TableOfCar.TBL[i].brand << setw(12) << left << TableOfCar.TBL[i].mileage << endl;
    }
}

void SaveTable() {
    ofstream out;
    out.open("table.txt");
    if (out.is_open())
    {
        out << TableOfCar.len << endl;

        for (int i = 0; i < TableOfCar.len; i++) {
            out << TableOfCar.TBL[i].number << " " << TableOfCar.TBL[i].brand << " " << TableOfCar.TBL[i].mileage << endl;
        }

        cout << "Сохранено" << endl;
    }

    out.close();     // закрываем файл
}

void LoadTable() {
    ifstream in("table.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        int len;
        in >> len;
        TableOfCar.TBL = new car[len];
        TableOfCar.len = len;

        for (int i = 0; i < len; i++) {
            in >> TableOfCar.TBL[i].number >> TableOfCar.TBL[i].brand >> TableOfCar.TBL[i].mileage;
        }

        cout << "Загружено" << endl;
    }
    in.close();     // закрываем файл
}

void Sort() {
    int command = -1;;

    cout << "Введите номер функции которую хотите использовать: " << endl;
    cout << "1. Сортировка по регистрацинному номеру " << endl;
    cout << "2. Сортировка по бренду " << endl;
    cout << "3. Сортировка по пробегу " << endl;
    cin >> command;

    for (int i = 0; i < TableOfCar.len - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < TableOfCar.len - i - 1; j++) {

            if (command == 1) {
                if (SortNumber(j)) {
                    swap(TableOfCar.TBL[j], TableOfCar.TBL[j + 1]);
                    swapped = true;
                }
            }

            if (command == 2) {
                if (SortBrand(j)) {
                    swap(TableOfCar.TBL[j], TableOfCar.TBL[j + 1]);
                    swapped = true;
                }
            }

            if (command == 3) {
                if (SortMileage(j)) {
                    swap(TableOfCar.TBL[j], TableOfCar.TBL[j + 1]);
                    swapped = true;
                }
            }

        }
        if (!swapped) break;
    }

}

int SortNumber(int j) {
    int i = 0;

    char* str1 = TableOfCar.TBL[j].number;
    char* str2 = TableOfCar.TBL[j + 1].number;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return 0;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }
    // если строки идентичны до конца одной из них, считаем более короткую строку меньшей
    if (str1[i] == '\0' && str2[i] != '\0') {
        return 0;
    }
    else if (str1[i] != '\0' && str2[i] == '\0') {
        return 1;
    }
    else {
        return 0; // если строки идентичны, возвращаем -1
    }
}

int SortBrand(int j) {
    int i = 0;

    char* str1 = TableOfCar.TBL[j].brand;
    char* str2 = TableOfCar.TBL[j + 1].brand;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return 0;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }
    // если строки идентичны до конца одной из них, считаем более короткую строку меньшей
    if (str1[i] == '\0' && str2[i] != '\0') {
        return 0;
    }
    else if (str1[i] != '\0' && str2[i] == '\0') {
        return 1;
    }
    else {
        return 0; // если строки идентичны, возвращаем -1
    }
}

int  SortMileage(int j) {
    if (TableOfCar.TBL[j].brand > TableOfCar.TBL[j + 1].brand) {
        return 1;
    }

    return 0;
}

void Search() {
    int command = -1;
    char char_value[20];
    int int_value = 0;
    int min_dif = INT_MAX;
    int closest_index = -1;
    int* mas_of_dif = new int[TableOfCar.len];
    cout << "Введите номер функции которую хотите использовать: " << endl;
    cout << "1. Поиск по регистрацинному номеру " << endl;
    cout << "2. Поиск по бренду " << endl;
    cout << "3. Поиск по пробегу " << endl;
    cin >> command;
    cout << "Введите строку для поиска: ";
    switch (command)
    {
    case 1:

        cin >> char_value;
        for (int i = 0; i < TableOfCar.len; i++) {
            int dif = 0;
            for (int j = 0; j < 20; j++) {
                if (TableOfCar.TBL[i].number[j] != char_value[j]) {
                    dif++;
                }
            }
            if (dif < min_dif) {
                min_dif = dif;
            }
            mas_of_dif[i] = dif;
        }

        for (int i = 0; i < TableOfCar.len; i++) {

            if (mas_of_dif[i] == min_dif) {
                cout << left << i + 1 << ". " << setw(12) << left << TableOfCar.TBL[i].number << setw(20) << left << TableOfCar.TBL[i].brand << setw(12) << left << TableOfCar.TBL[i].mileage << endl;
            }
        }
        break;
    case 2:
        cin >> char_value;
        for (int i = 0; i < TableOfCar.len; i++) {
            int dif = 0;
            for (int j = 0; j < 20; j++) {
                if (TableOfCar.TBL[i].brand[j] != char_value[j]) {
                    dif++;
                }
            }
            if (dif < min_dif) {
                min_dif = dif;
            }
            mas_of_dif[i] = dif;
        }

        for (int i = 0; i < TableOfCar.len; i++) {

            if (mas_of_dif[i] == min_dif) {
                cout << left << i + 1 << ". " << setw(12) << left << TableOfCar.TBL[i].number << setw(20) << left << TableOfCar.TBL[i].brand << setw(12) << left << TableOfCar.TBL[i].mileage << endl;
            }
        }
        break;
    case 3:
        cin >> int_value;
        for (int i = 0; i < TableOfCar.len; i++) {
            int dif = abs(TableOfCar.TBL[i].mileage - int_value);

            if (dif < min_dif) {
                min_dif = dif;
            }
            mas_of_dif[i] = dif;
        }
        for (int i = 0; i < TableOfCar.len; i++) {

            if (mas_of_dif[i] == min_dif) {
                cout << left << i + 1 << ". " << setw(12) << left << TableOfCar.TBL[i].number << setw(20) << left << TableOfCar.TBL[i].brand << setw(12) << left << TableOfCar.TBL[i].mileage << endl;
            }
        }
        break;
    default:
        cout << "Неправильный ввод" << endl;
        break;
    }

}
