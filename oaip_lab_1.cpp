#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    const int N = 10;
    int a[N];

    cout << "Введите " << N << " целых чисел (через Enter или пробел): ";
    for (int i = 0; i < N; ++i) {
        cout << "a[" << i << "] = ";
        cin >> a[i];
    }

    cout << "\nВведённый массив:\n";
    for (int i = 0; i < N; ++i) cout << a[i] << (i < N - 1 ? " " : "\n");

    int sum = 0;
    for (int i = 0; i < N; ++i) sum += a[i];
    cout << "Сумма элементов массива: " << sum << "\n";

    int mx = a[0];
    for (int i = 1; i < N; ++i)
        if (a[i] > mx) mx = a[i];
    cout << "Максимальный элемент: " << mx << "\n";

    for (int i = 1; i < N; ++i) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] < key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }

    cout << "\nМассив после сортировки (по убыванию):";
    for (int i = 0; i < N; ++i) cout << a[i] << (i < N - 1 ? " " : "\n");

    return 0;
}