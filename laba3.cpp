#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << *(*(matrix + i) + j) << "\t";
        }
        cout << endl;
    }
}
// идз 10
// Функция для заполнения матрицы 3*3 случайными числами
void fillMatrixRandom(int** matrix, int size, int minVal, int maxVal) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % (maxVal - minVal + 1) + minVal;
        }
    }
}

// Функция для вычисления определителя матрицы 3*3
int calculateDeterminant3x3(int** matrix) {
    cout << "Шаги вычисления определителя:\n";
    cout << "Определитель = A11 * (A22 * A33 - A23 * A32) - A12 * (A21 * A33 - A23 * A31) + A13 * (A21 * A32 - A22 * A31)\n";

    int term1 = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
    cout << "Первый член = " << matrix[0][0] << " * (" << matrix[1][1] << " * " << matrix[2][2] << " - " << matrix[1][2] << " * " << matrix[2][1] << ") = " << term1 << endl;

    int term2 = matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    cout << "Второй член = " << matrix[0][1] << " * (" << matrix[1][0] << " * " << matrix[2][2] << " - " << matrix[1][2] << " * " << matrix[2][0] << ") = " << term2 << endl;

    int term3 = matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    cout << "Третий член = " << matrix[0][2] << " * (" << matrix[1][0] << " * " << matrix[2][1] << " - " << matrix[1][1] << " * " << matrix[2][0] << ") = " << term3 << endl;

    int determinant = term1 - term2 + term3;
    cout << "Определитель = " << term1 << " - " << term2 << " + " << term3 << " = " << determinant << endl;

    return determinant;
}

// Функция для заполнения матрицы по схеме A с выводом процесса заполнения
void fillMatrixSpiral(int** matrix, int n) {
    int value = 1;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        // Заполняем верхнюю строку
        for (int i = left; i <= right; ++i) {
            matrix[top][i] = value++;
        }
        top++;
        cout << "Матрица после заполнения верхней строки:\n";
        printMatrix(matrix, n);

        // Заполняем правый столбец
        for (int i = top; i <= bottom; ++i) {
            matrix[i][right] = value++;
        }
        right--;
        cout << "Матрица после заполнения правого столбца:\n";
        printMatrix(matrix, n);

        // Заполняем нижнюю строку
        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                matrix[bottom][i] = value++;
            }
            bottom--;
            cout << "Матрица после заполнения нижней строки:\n";
            printMatrix(matrix, n);
        }

        // Заполняем левый столбец
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                matrix[i][left] = value++;
            }
            left++;
            cout << "Матрица после заполнения левого столбца:\n";
            printMatrix(matrix, n);
        }
    }
}

// Функция для заполнения матрицы по схеме Б с выводом процесса заполнения
void fillMatrixSnake(int** matrix, int n) {
    int value = 1;
    for (int j = 0; j < n; ++j) {
        if (j % 2 == 0) { // Заполняем сверху вниз
            for (int i = 0; i < n; ++i) {
                *(*(matrix + i) + j) = value++;
            }
        }
        else { // Заполняем снизу вверх
            for (int i = n - 1; i >= 0; --i) {
                *(*(matrix + i) + j) = value++;
            }
        }
        // Вывод текущего состояния матрицы после заполнения столбца
        cout << "Матрица после заполнения столбца " << j + 1 << ":\n";
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                cout << *(*(matrix + x) + y) << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
}


// Функция для перестановки блоков матрицы по схемам a, b, c, d
void rearrangeBlocks(int** matrix, int n, char scheme) {
    int half = n / 2;
    int temp;

    switch (scheme) {
    case 'a': { // Перестановка по схеме a (по часовой стрелке)
        for (int i = 0; i < half; ++i) {
            for (int j = 0; j < half; ++j) {
                // Сохранение первого блока
                temp = *(*(matrix + i) + j);

                // Первый блок -> Второй блок
                *(*(matrix + i) + j) = *(*(matrix + i + half) + j);

                // Второй блок -> Третий блок
                *(*(matrix + i + half) + j) = *(*(matrix + i + half) + j + half);

                // Третий блок -> Четвертый блок
                *(*(matrix + i + half) + j + half) = *(*(matrix + i) + j + half);

                // Четвертый блок -> Первый блок
                *(*(matrix + i) + j + half) = temp;
            }
        }
        break;
    }

    case 'b': // Перестановка по схеме b
        for (int i = 0; i < half; ++i) {
            for (int j = 0; j < half; ++j) {
                // Первый блок <-> Четвертый блок
                swap(*(*(matrix + i) + j), *(*(matrix + i + half) + j + half));

                // Второй блок <-> Третий блок
                swap(*(*(matrix + i) + j + half), *(*(matrix + i + half) + j));
            }
        }

        break;

    case 'c': { // Перестановка по схеме c (по диагонали: первый со вторым, третий с четвертым)
        for (int i = 0; i < half; ++i) {
            for (int j = 0; j < half; ++j) {
                // Блок 1 (верхний левый) <-> Блок 4 (нижний правый)
                swap(*(*(matrix + i) + j), *(*(matrix + i + half) + j));

                // Блок 2 (верхний правый) <-> Блок 3 (нижний левый)
                swap(*(*(matrix + i) + j + half), *(*(matrix + i + half) + j + half));
            }
        }
        break;
    }

    case 'd': // Перестановка по схеме d
        for (int i = 0; i < half; ++i) {
            for (int j = 0; j < half; ++j) {
                // Первый блок <-> Второй блок
                swap(*(*(matrix + i) + j), *(*(matrix + i) + j + half));

                // Третий блок <-> Четвертый блок
                swap(*(*(matrix + i + half) + j), *(*(matrix + i + half) + j + half));
            }
        }
        break;

    default:
        cout << "Неверная схема перестановки!" << endl;
    }
}
// Shaker Sort (Сортировка шейкером)
void shakerSort(int* arr, int size) {
    bool swapped = true;
    int start = 0;
    int end = size - 1;

    while (swapped) {
        swapped = false;

        // Проход слева направо
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        end--;

        // Если не было перестановок, массив уже отсортирован
        if (!swapped) break;

        swapped = false;

        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        start++;
    }
}

// Преобразование матрицы в массив для сортировки
void matrixToArray(int** matrix, int n, int* array) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(array + k++) = *(*(matrix + i) + j);
        }
    }
}

// Преобразование массива обратно в матрицу
void arrayToMatrix(int* array, int n, int** matrix) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(*(matrix + i) + j) = *(array + k++);
        }
    }
}

// Функция для выполнения арифметических операций на матрице
void modifyMatrix(int** matrix, int n, int factor, char operation) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (operation == '+') {
                *(*(matrix + i) + j) += factor;
            }
            else if (operation == '-') {
                *(*(matrix + i) + j) -= factor;
            }
            else if (operation == '*') {
                *(*(matrix + i) + j) *= factor;
            }
            else if (operation == '/') {
                if (factor != 0) {
                    *(*(matrix + i) + j) /= factor;
                }
                else {
                    cout << "Деление на 0 невозможно! Элемент остался неизменным." << endl;
                }
            }
        }
    }
}
int main() {
    srand(time(0));
    setlocale(0, "");
    while (true) {
        cout << "Выберите задание:\n";
        cout << "1 - Работа с квадратной матрицей (лаба)\n";
        cout << "2 -  Задание с матрицей 3*3 (вычисление определителя,идз 10)\n";
        cout << "0 - Выход\n";
        int task;
        cin >> task;

        if (task == 0) {
            cout << "Программа завершена.\n";
            break;
        }
        else if (task == 1) {
            int n;
            cout << "Введите порядок матрицы (6, 8, 10): ";
            cin >> n;

            // Создание динамической матрицы
            int** matrix = new int* [n];
            for (int i = 0; i < n; ++i) {
                matrix[i] = new int[n];
            }
            // Выбор схемы заполнения
            char choice;
            cout << "Выберите схему для заполнения матрицы:\n";
            cout << "a - Заполнение по схеме A (спираль)\n";
            cout << "b - Заполнение по схеме B (змейка)\n";
            cin >> choice;

            if (choice == 'a') {
                fillMatrixSpiral(matrix, n);
                cout << "Матрица, заполненная по схеме A (спираль):\n";
                printMatrix(matrix, n);
            }
            else if (choice == 'b') {
                fillMatrixSnake(matrix, n);
                cout << "Матрица, заполненная по схеме B (змейка):\n";
                printMatrix(matrix, n);
            }
            else {
                cout << "Неверный выбор! Программа завершена.\n";
            }


            // Перестановка блоков
            char scheme;
            cout << "Введите схему перестановки блоков (a, b, c, d): ";
            cin >> scheme;
            rearrangeBlocks(matrix, n, scheme);
            cout << "Матрица после перестановки блоков по схеме " << scheme << ":\n";
            printMatrix(matrix, n);



            // Сортировка элементов
            int* array = new int[n * n];
            matrixToArray(matrix, n, array);
            shakerSort(array, n * n);
            arrayToMatrix(array, n, matrix);
            cout << "Матрица после сортировки через shakerSort :\n";
            printMatrix(matrix, n);

            // Арифметические операции
            char operation;
            int factor;
            cout << "Выберите операцию с элементами матрицы:\n";
            cout << "+ - Увеличить на число\n";
            cout << "- - Уменьшить на число\n";
            cout << "* - Умножить на число\n";
            cout << "/ - Разделить на число\n";
            cin >> operation;
            cout << "Введите число для операции: ";
            cin >> factor;
            modifyMatrix(matrix, n, factor, operation);
            cout << "Матрица после выполнения операции:\n";
            printMatrix(matrix, n);

        }
        else if (task == 2) {
            // Код для матрицы 3*3 и вычисления определителя (idz 10)
            int size = 3;
            int** matrix = new int* [size];
            for (int i = 0; i < size; ++i) {
                matrix[i] = new int[size];
            }

            fillMatrixRandom(matrix, size, -30, 30);
            cout << "Матрица 3*3, заполненная случайными числами:\n";
            printMatrix(matrix, size);

            int determinant = calculateDeterminant3x3(matrix);
            cout << "Определитель матрицы: " << determinant << endl;

            for (int i = 0; i < size; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
        else {
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }

    return 0;
}



       









 

