// Завдання 1
// Створіть додаток Калькулятор. Потрібно підтримувати операції +, -, *, /.

// Реалізувати меню без використання операторів if і switch за допомогою масиву покажчиків на функції.

#include <iostream>
using namespace std;

int add(int n, int m)
{
    return n + m;
}
int subtract(int n, int m)
{
    return n - m;
}
int multiply(int n, int m)
{
    return n * m;
}
int devide(int n, int m)
{
    if (m != 0) return n / m;
    cout << "It's impossible to divide by 0!\n";
    return 0;
}

// int main()
// {
//     int n, m, choice;
//     int (*operations[])(int, int) = {add, subtract, multiply, devide};
//     while (true)
//     {
//         cout << "Enter first number: ";
//         cin >> n;
//         cout << "Enter second number: ";
//         cin >> m;
//         cout << "Choose operation (0: +, 1: -, 2: *, 3: /, 4: Exit): ";
//         cin >> choice;
        
        
//     if (choice == 4) break;
//     if (choice >=0 && choice < 4)
//     {
//         cout<<"The result is: "<< operations[choice](n, m)<< endl;
//     } else{
//         cout<<"Invalid input!";
//     }
    
//     }
    

//     return 0;
// }



// Завдання 2
// Написати програму, що містить функцію, яка приймає як аргумент 
// покажчики на три масиви та розмір масивів, заносить у масив C суми елементів масивів А і В. Розмір масивів однаковий.

void listthree(int* ptrA, int* ptrB, int* ptrC, int size)
{
    for (int i = 0; i < size; i++) {
        ptrC[i] = ptrA[i] + ptrB[i];
    }
}

int main()
{
    const int size = 5;
    int one[size] = { 1, 2, 3, 4, 5};
    int two[size] = { 6, 7, 8, 9, 10};
    int three[size];
    
    int* ptrA = one;
    int* ptrB = two;
    int* ptrC = three;
    
    listthree(ptrA, ptrB, ptrC, size);
    
    cout << "Result array: ";
    for (int i = 0; i < size; i++) {
        cout << three[i] << " ";
    }
    cout << endl;


    return 0;
}




