#include <iostream>
#include <cstdlib>
#include <chrono>
#include <random>
#include <cmath>
using namespace std;

const int N = 100;

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shakerSort(int* arr, int n) {
    int left = 0;
    int right = n - 1;
    bool swapped = true;

    while (swapped) {
        swapped = false;

        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        right--;

        for (int i = right; i > left; i--) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }

        left++;
    }
}

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortWrapper(int* arr, int n) {
    quickSort(arr, 0, n - 1);
}

void copyArray(int* source, int* destination) {
    for (int i = 0; i < N; i++) {
        destination[i] = source[i];
    }
}

int binarySearch(int* arr, int vvod, int start, int end) {
    if (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == vvod) {
            return mid;
        }
        else if (arr[mid] < vvod) {
            return binarySearch(arr, vvod, mid + 1, end);
        }
        else {
            return binarySearch(arr, vvod, start, mid - 1);
        }
    }
    return -1;
}

void mainMenu() {
    int arrOriginal[N];
    int arrWork[N];

    random_device random;
    mt19937 generator(random());
    uniform_int_distribution<> dist(-99, 99);

    for (int i = 0; i < N; i++) {
        arrOriginal[i] = dist(generator);
    }

    int choice;
    cout << "Введите номер задания (от 0 до 8) " << endl;
    cin >> choice;

    if (choice == 0) {
        cout << "Задание: Удалить элементы, кратные 3" << endl;
        copyArray(arrOriginal, arrWork);

        cout << "Массив ДО изменений:\n";
        for (int i = 0; i < N; i++) {
            cout << arrWork[i] << " ";
        }
        cout << "\n\n";

        int count = 0;
        int writeIndex = 0;

        for (int i = 0; i < N; i++) {
            if (arrWork[i] % 3 != 0 || arrWork[i] == 0) {
                arrWork[writeIndex] = arrWork[i];
                writeIndex++;
            } else {
                count++;
            }
        }

        cout << "Массив ПОСЛЕ удаления элементов, кратных 3:\n";
        for (int i = 0; i < writeIndex; i++) {
            cout << arrWork[i] << " ";
        }

        cout << "\n\nКоличество удаленных элементов: " << count << endl;
        cout << "Новый размер массива (без кратных 3): " << writeIndex << endl;
        cout << endl;
        mainMenu();
    }
    else if (choice == 1) {
        cout << "Задание 1" << endl;
        for (int i = 0; i < N; i++) {
            cout << arrOriginal[i] << " ";
        }
        cout << endl;
        mainMenu();
    }
    else if (choice == 2) {
        cout << "Задание 2" << endl;

        int typeOfSort;
        cout << "Выберите тип сортировки, который хотите использовать: " << endl
             << "1) Bubble Sort (Пузырьковая сортировка)" << endl
             << "2) Shaker Sort (Шейкерная сортировка)" << endl
             << "3) Selection Sort (Сортировка выбором)" << endl
             << "4) Insert Sort (Сортировка вставками)" << endl
             << "5) Quick Sort (Быстрая сортировка)" << endl;
        cin >> typeOfSort;

        if (typeOfSort == 1) {
            copyArray(arrOriginal, arrWork);
            cout << "сортировка bubble sort:\n";
            auto startBubble = chrono::high_resolution_clock::now();
            bubbleSort(arrWork, N);
            auto stopBubble = chrono::high_resolution_clock::now();
            auto durationBubble = chrono::duration_cast<chrono::microseconds>(stopBubble - startBubble);
            for (int i = 0; i < N; i++) {
                cout << arrWork[i] << " ";
            }
            cout << "\nВремя сортировки: " << durationBubble.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 2) {
            copyArray(arrOriginal, arrWork);
            cout << "сортировка Shaker Sort\n";
            auto startShaker = chrono::high_resolution_clock::now();
            shakerSort(arrWork, N);
            auto stopShaker = chrono::high_resolution_clock::now();
            auto durationShaker = chrono::duration_cast<chrono::microseconds>(stopShaker - startShaker);
            for (int i = 0; i < N; i++) {
                cout << arrWork[i] << " ";
            }
            cout << "\nВремя сортировки: " << durationShaker.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 3) {
            copyArray(arrOriginal, arrWork);
            cout << "сортировка Selection Sort\n";
            auto startSelection = chrono::high_resolution_clock::now();
            selectionSort(arrWork, N);
            auto stopSelection = chrono::high_resolution_clock::now();
            auto durationSelection = chrono::duration_cast<chrono::microseconds>(stopSelection - startSelection);
            for (int i = 0; i < N; i++) {
                cout << arrWork[i] << " ";
            }
            cout << "\nВремя сортировки: " << durationSelection.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 4) {
            copyArray(arrOriginal, arrWork);
            cout << "сортировка Insert Sort\n";
            auto startInsert = chrono::high_resolution_clock::now();
            insertSort(arrWork, N);
            auto stopInsert = chrono::high_resolution_clock::now();
            auto durationInsert = chrono::duration_cast<chrono::microseconds>(stopInsert - startInsert);
            for (int i = 0; i < N; i++) {
                cout << arrWork[i] << " ";
            }
            cout << "\nВремя сортировки: " << durationInsert.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 5) {
            copyArray(arrOriginal, arrWork);
            cout << "сортировка quick Sort\n";
            auto startQuick = chrono::high_resolution_clock::now();
            quickSortWrapper(arrWork, N);
            auto stopQuick = chrono::high_resolution_clock::now();
            auto durationQuick = chrono::duration_cast<chrono::microseconds>(stopQuick - startQuick);
            for (int i = 0; i < N; i++) {
                cout << arrWork[i] << " ";
            }
            cout << "\nВремя сортировки: " << durationQuick.count() << " микросекунд\n\n";
        }
        else {
            cout << "Неверный выбор сортировки!" << endl;
        }

        cout << endl;
        mainMenu();
    }
    else if (choice == 3) {
        cout << "Задание 3" << endl;
        copyArray(arrOriginal, arrWork);

        int maxBubbleNeots = arrWork[0];
        int minBubbleNeots = arrWork[0];
        auto startBubbleMaxNeots = chrono::high_resolution_clock::now();
        for (int i = 1; i < N; i++) {
            if (arrWork[i] < minBubbleNeots) {
                minBubbleNeots = arrWork[i];
            }
            if (arrWork[i] > maxBubbleNeots) {
                maxBubbleNeots = arrWork[i];
            }
        }
        auto stopBubbleMaxNeots = chrono::high_resolution_clock::now();
        auto durationBubbleMaxNeots = chrono::duration_cast<chrono::nanoseconds>(stopBubbleMaxNeots - startBubbleMaxNeots);

        bubbleSort(arrWork, N);
        int maxBubbleOts = arrWork[N-1];
        int minBubbleOts = arrWork[0];
        auto startBubbleMaxOts = chrono::high_resolution_clock::now();

        auto stopBubbleMaxOts = chrono::high_resolution_clock::now();
        auto durationBubbleMaxOts = chrono::duration_cast<chrono::nanoseconds>(stopBubbleMaxOts - startBubbleMaxOts);

        cout << "max: " << maxBubbleOts;
        cout << "\nmin: " << minBubbleOts;
        cout << "\nВремя поиска макс и мин элементов в неотсортированном массиве:" << durationBubbleMaxNeots.count() << " наносекунд";
        cout << "\nВремя поиска макс и мин элементов в отсортированном массиве:" << durationBubbleMaxOts.count() << " наносекунд";
        cout << endl;
        mainMenu();
    }
    else if (choice == 4) {
        cout << "Задание 4" << endl;
        copyArray(arrOriginal, arrWork);

        int maxBubbleNeots = arrWork[0];
        int minBubbleNeots = arrWork[0];
        for (int i = 1; i < N; i++) {
            if (arrWork[i] < minBubbleNeots) minBubbleNeots = arrWork[i];
            if (arrWork[i] > maxBubbleNeots) maxBubbleNeots = arrWork[i];
        }

        int srBubbleNeots = round((maxBubbleNeots + minBubbleNeots) / 2.0);
        cout << "Среднее значение макс и мин: " << srBubbleNeots << endl;

        int kolSrBubbleNeots = 0;
        auto startBubbleSrNeots = chrono::high_resolution_clock::now();

        cout << "Индексы элементов, равных ср значению в неотсортированном массиве: ";
        for (int i = 0; i < N; i++) {
            if (arrWork[i] == srBubbleNeots) {
                kolSrBubbleNeots += 1;
                cout << i << ' ';
            }
        }

        auto stopBubbleSrNeots = chrono::high_resolution_clock::now();
        auto durationBubbleSrNeots = chrono::duration_cast<chrono::nanoseconds>(stopBubbleSrNeots - startBubbleSrNeots);

        if (kolSrBubbleNeots == 0) {
            cout << "нет";
        }

        cout << "\nКоличество элементов равных среднему в неотсортированном массиве: " << kolSrBubbleNeots;
        cout << "\nВремя поиска в неотсортированном массиве: " << durationBubbleSrNeots.count() << " наносекунд";

        bubbleSort(arrWork, N);

        int maxBubbleOts = arrWork[N-1];
        int minBubbleOts = arrWork[0];

        int srBubbleOts = round((maxBubbleOts + minBubbleOts) / 2.0);
        cout << "\n\nВ отсортированном массиве:";
        cout << "\nСреднее значение макс и мин: " << srBubbleOts;

        int kolSrBubbleOts = 0;
        auto startBubbleSrOts = chrono::high_resolution_clock::now();

        cout << "\nИндексы элементов, равных ср значению в отсортированном массиве: ";
        for (int i = 0; i < N; i++) {
            if (arrWork[i] == srBubbleOts) {
                kolSrBubbleOts += 1;
                cout << i << ' ';
            }
        }

        auto stopBubbleSrOts = chrono::high_resolution_clock::now();
        auto durationBubbleSrOts = chrono::duration_cast<chrono::nanoseconds>(stopBubbleSrOts - startBubbleSrOts);

        if (kolSrBubbleOts == 0) {
            cout << "нет";
        }

        cout << "\nКоличество элементов равных среднему в отсортированном массиве: " << kolSrBubbleOts;
        cout << "\nВремя поиска в отсортированном массиве: " << durationBubbleSrOts.count() << " наносекунд";
        cout << endl;
        mainMenu();
    }
    else if (choice == 5) {
        cout << "Задание 5" << endl;
        copyArray(arrOriginal, arrWork);
        bubbleSort(arrWork, N);

        int a;
        cout << "\nВведите число а: ";
        cin >> a;
        int kolBubbleA = 0;

        for (int i = 0; i < N && arrWork[i] < a; i++) {
            kolBubbleA++;
        }

        cout << "Kоличество элементов в отсортированном массиве, которые меньше числа a: " << kolBubbleA;
        cout << endl;
        mainMenu();
    }
    else if (choice == 6) {
        cout << "Задание 6" << endl;
        copyArray(arrOriginal, arrWork);
        bubbleSort(arrWork, N);

        int b;
        cout << "\nВведите число b: ";
        cin >> b;
        int kolBubbleB = 0;

        for (int i = N - 1; i >= 0 && arrWork[i] > b; i--) {
            kolBubbleB++;
        }

        cout << "Kоличество элементов в отсортированном массиве, которые больше числа b: " << kolBubbleB;
        cout << endl;
        mainMenu();
    }
    else if (choice == 7) {
        cout << "Задание 7" << endl;
        copyArray(arrOriginal, arrWork);
        bubbleSort(arrWork, N);

        int vvod;
        cout << "\nВведите число: ";
        cin >> vvod;
        int kolVvodOb = 0;
        auto startObPoisk = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            if (arrWork[i] == vvod) {
                kolVvodOb += 1;
            }
        }
        if (kolVvodOb > 0) {
            cout << "Введенных чисел " << kolVvodOb;
        }
        else {
            cout << "Введенных чисел нет ";
        }
        auto stopObPoisk = chrono::high_resolution_clock::now();
        auto durationObPoisk = chrono::duration_cast<chrono::nanoseconds>(stopObPoisk - startObPoisk);
        cout << "\nВремя обычным перебором: " << durationObPoisk.count() << " наносекунд";

        auto startBin = chrono::high_resolution_clock::now();
        int result = binarySearch(arrWork, vvod, 0, N - 1);
        if (result == -1) {
            cout << "\nЭлемент не найден" << "\n";
        }
        else {
            cout << "\nЭлемент находится в позиции " << result << "\n";
        }
        auto stopBin = chrono::high_resolution_clock::now();
        auto durationBin = chrono::duration_cast<chrono::nanoseconds>(stopBin - startBin);
        cout << "Время бинарного поиска: " << durationBin.count() << " наносекунд";
        cout << endl;
        mainMenu();
    }
    else if (choice == 8) {
        cout << "Задание 8" << endl;
        copyArray(arrOriginal, arrWork);
        bubbleSort(arrWork, N);

        int index1;
        int index2;
        cout << "Введите 1 индекс который хотите поменять ";
        cin >> index1;
        cout << "Введите 2 индекс который хотите поменять ";
        cin >> index2;

        if (index1 >= 0 && index1 < N && index2 >= 0 && index2 < N) {
            auto startSwap = chrono::high_resolution_clock::now();
            swap(arrWork[index1], arrWork[index2]);
            auto stopSwap = chrono::high_resolution_clock::now();
            auto durationSwap = chrono::duration_cast<chrono::nanoseconds>(stopSwap - startSwap);
            cout << "Время swapa: " << durationSwap.count() << " наносекунд\n\n";
            for (int i = 0; i < N; i++) {
                cout << arrWork[i] << " ";
            }
        } else {
            cout << "Ошибка: индексы должны быть от 0 до " << N-1;
        }
        cout << endl;
        mainMenu();
    }
    else {
        mainMenu();
    }
}

int main() {
    setlocale(0, "RU");
    mainMenu();
    return 0;
}