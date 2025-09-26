#include <iostream>
using namespace std;

int main() {    
    setlocale(LC_ALL, "RU");
    double speed;
    cout << "Введите скорость автомобиля (км/ч): ";
    cin >> speed;

    if (speed < 60) {
        cout << "Скорость в пределах нормы" << endl;
    }
    else if (speed >= 60 && speed <= 80) {
        cout << "Вы приближаетесь к превышению скорости" << endl;
    }
    else {
        cout << "Превышение скорости!" << endl;
    }

    return 0;
}
