#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для поиска самой короткой общей подстроки между двумя словaми
string shortest_common_substring(const string& s1, const string& s2) {
    for (size_t len = 1; len <= min(s1.size(), s2.size()); ++len) {
        for (size_t i = 0; i <= s1.size() - len; ++i) {
            string sub = s1.substr(i, len);
            if (s2.find(sub) != string::npos) {
                return sub; // Возвращаем первую найденную общую подстроку
            }
        }
    }
    return "";
}

int main() {
    string line;
    cout << "Введите 10 слов через пробел: ";
    getline(cin, line);

    stringstream ss(line);
    vector<string> words;
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    if (words.size() != 10) {
        cout << "Ошибка: нужно ввести ровно 10 слов!" << endl;
        return 1;
    }

    // 1. Количество слов, начинающихся с буквы 'a'
    int count_a_start = 0;
    for (const auto& w : words) {
        if (!w.empty() && (w[0] == 'a' || w[0] == 'A')) count_a_start++;
    }
    cout << "Слов, начинающихся с 'a': " << count_a_start << endl;

    // 2. Длина самого короткого слова
    size_t min_len = words[0].size();
    for (const auto& w : words) {
        if (w.size() < min_len) min_len = w.size();
    }
    cout << "Длина самого короткого слова: " << min_len << endl;

    // 3. Количество букв 'a' в последнем слове
    int count_a_last = 0;
    for (char c : words.back()) {
        if (c == 'a' || c == 'A') count_a_last++;
    }
    cout << "Количество букв 'a' в последнем слове: " << count_a_last << endl;

    // 4. Преобразование всех букв в нижний регистр
    cout << "Слова в нижнем регистре: ";
    for (auto& w : words) {
        transform(w.begin(), w.end(), w.begin(), ::tolower);
        cout << w << " ";
    }
    cout << endl;

    // 5. Количество слов, у которых первый и последний символ совпадают
    int count_same_first_last = 0;
    for (const auto& w : words) {
        if (w.front() == w.back()) count_same_first_last++;
    }
    cout << "Слов с одинаковыми первой и последней буквами: " << count_same_first_last << endl;

    // 6. Самая короткая общая подстрока между двумя словами (берем первые два для примера)
    string common_sub = shortest_common_substring(words[0], words[1]);
    if (!common_sub.empty())
        cout << "Самая короткая общая подстрока между первыми двумя словами: " << common_sub << endl;
    else
        cout << "Общей подстроки между первыми двумя словами нет." << endl;

    return 0;
}
