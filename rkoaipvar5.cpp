#include <iostream>
#include <vector>
#include <string>
#include <cstring>  // для strstr, strchr
#include <iomanip>  // для форматирования вывода

int main() {
    std::vector<std::string> logs = {
        "VOLT:230.1;CURR:12.3;POW:2829.23",
        "VOLT:229.8;CURR:12.4;POW:2850.17",
        "VOLT:231.0;CURR:12.2;POW:2824.20"
    };

    std::vector<double> voltage, current, power;

    for (const auto& line : logs) {
        const char* cstr = line.c_str();

        // Извлекаем VOLT
        const char* vpos = strstr(cstr, "VOLT:");
        const char* cpos = strstr(cstr, "CURR:");
        const char* ppos = strstr(cstr, "POW:");

        double volt = 0.0, curr = 0.0, powr = 0.0;

        if (vpos && cpos && ppos) {
            volt = atof(vpos + 5);  // 5 символов после "VOLT:"
            curr = atof(cpos + 5);
            powr = atof(ppos + 4);
        }

        voltage.push_back(volt);
        current.push_back(curr);
        power.push_back(powr);
    }

    // d) Средняя мощность и энергия
    double sum_power = 0.0;
    for (double p : power) sum_power += p;
    double avg_power = sum_power / power.size();

    // Период = 1 сек, энергия = P * t = P * N * 1 с
    // В джоулях, переводим в мегаджоули (делим на 1e6)
    double total_energy_J = sum_power * 1; // 1 секунда на каждое измерение
    double total_energy_MJ = total_energy_J / 1e6 * power.size();

    // e) Отклонение более 2%
    int dev_index = -1;
    for (size_t i = 0; i < power.size(); ++i) {
        double deviation = std::abs(power[i] - avg_power) / avg_power * 100.0;
        if (deviation > 2.0) {
            dev_index = i + 1; // номер измерения (1-based)
            break;
        }
    }

    // Вывод
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Power: " << avg_power << " W\n";
    std::cout << "Total Energy: " << (sum_power / 1e6) << " MJ\n";
    if (dev_index != -1)
        std::cout << "Deviation >2% at measurement #" << dev_index << "\n";
    else
        std::cout << "No deviation >2%\n";

    return 0;
}
