#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите количество машин, произведённых на фабрике: ";
    cin >> n;

    unsigned long long factorial = 1; 
    int i = 1;

    cout << "\nРост производительности:\n";

    while (i <= n) {
        factorial *= i;
        cout << i << "! = " << factorial << endl; 
        i++;
    }

    cout << "\nИтого: " << n << "! = " << factorial << endl;

    return 0;
}
