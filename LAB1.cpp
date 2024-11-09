#include <iostream>
#include <conio.h>

using namespace std;

unsigned const order = sizeof(short int) * 8;
unsigned const orderD = sizeof(int) * 8;
unsigned mask = 1;
short choice;
short a;
double d;
char direction;
int position;

void printBinaryInt(int a){
    // для отрицательных - дополнительный код (сначала перевод модуля, потом реверс с 0 на 1, потом +1)
    cout << "Число short int: " << a << endl;
    mask = 1 << (order - 1);
    cout << "Двоичное представление short int: ";
    for (int i = 0; i < sizeof(short int) * 8; i++) {
        cout << ((a & mask) ? 1 : 0);
        mask = mask >> 1;
        if (i == 0 || i == 7) {
            cout << " ";
        }
    }
    cout << endl;
}

void printBinaryDouble(double d) {
    // 1 бит - знак; 2-12 биты - порядок; 13-64 биты - мантисса
    cout << "Число double: " << d << endl;
    mask = 1 << (orderD - 1);
    cout << "Двоичное представление double: ";
    union DoubleBits {
        double value;
        unsigned int uDouble[2];
    };
    DoubleBits db;
    db.value = d;
    for (int i = 0; i < 64; i++)
    {
        if (i < 32)
        {
            cout << ((db.uDouble[1] & mask) ? 1 : 0);
            mask = mask >> 1;
            if (i == 0 || i == 11)
                cout << " ";
        }
        else
        {
            cout << ((db.uDouble[0] & mask) ? 1 : 0);
            mask = mask >> 1;
        }
    }
}

int rotateLeftShort(int value, int pos) {
    return (value << pos) | (value >> (order - pos));
}

int rotateRightShort(int value, int pos) {
    return (value >> pos) | (value << (order - pos));
}

int changeIntNumber(int value, int pos, char dir) {
    if (dir == 'l') {
        return rotateLeftShort(value, pos);
    }
    else {
        if (dir == 'r') {
            return rotateRightShort(value, pos);
        }
    }
}

unsigned long long rotateLeftDouble(unsigned long long value, int pos) {
    return (value << pos) | (value >> (orderD - pos));
}

unsigned long long rotateRightDouble(unsigned long long value, int pos) {
    return (value >> pos) | (value << (orderD - pos));
}

double changeDoubleNumber(double d, int pos, char dir) {
    union doubleBits {
        double value;
        unsigned long long integer;
    };
    doubleBits db;
    db.value = d;
    if (dir == 'r') {
        db.integer = rotateRightDouble(db.integer, pos);
    }
    else if (dir == 'l') {
        db.integer = rotateLeftDouble(db.integer, pos);
    }
    return db.value;
}

void menu() {
    setlocale(0, "");
    system("cls");
    cout << "Что будем делать?\n";
    cout << "1. Ввести short int\n";
    cout << "2. Ввести double\n";
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "Введите число типа short int: ";
        cin >> a;
        system("cls");
        printBinaryInt(a);
        cout << "\nНажмите любую кнопку для продолжения..";
        _getch();
        cout << "\nВ какую сторону сдвиг (r - right, l - left): ";
        cin >> direction;
        cout << "На сколько бит сдвиг: ";
        cin >> position;
        a = changeIntNumber(a, position, direction);
        printBinaryInt(a);
        cout << "\nНажмите любую кнопку для выхода в меню..";
        _getch();
        break;
    case 2:
        cout << "Введите число типа double: ";
        cin >> d;
        printBinaryDouble(d);
        cout << "\nНажмите любую кнопку для продолжения..";
        _getch();
        cout << "\nВ какую сторону сдвиг (r - right, l - left): ";
        cin >> direction;
        cout << "На сколько бит сдвиг: ";
        cin >> position;
        d = changeDoubleNumber(d, position, direction);
        printBinaryDouble(d);
        cout << "\nНажмите любую кнопку для выхода в меню..";
        _getch();
        break;
    default:
        cout << "повторите попытку";
        break;
    }
    menu();
}

int main()
{
    menu();
}

