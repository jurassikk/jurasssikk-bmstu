#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Book {
    string title;
    string author;
    int year;
};

void createBooksFile() {
    cout << "=== СОЗДАНИЕ БИБЛИОТЕКИ КНИГ ===" << endl;
    cout << "Введите информацию о книгах (пустая строка в названии для завершения):" << endl;
    
    ofstream file("books.txt");
    
    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл!" << endl;
        return;
    }
    
    while (true) {
        cout << endl << "========================================" << endl;
        
        string title;
        cout << "Введите название книги: ";
        getline(cin, title);
        
        if (title.empty()) {
            cout << "Завершение ввода данных." << endl;
            break;
        }
        
        string author;
        cout << "Введите автора книги: ";
        getline(cin, author);
        
        if (author.empty()) {
            cout << "Ошибка: автор не может быть пустым!" << endl;
            continue;
        }
        
        string yearStr;
        cout << "Введите год выпуска: ";
        getline(cin, yearStr);
        
        bool isNumber = true;
        for (char c : yearStr) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        
        if (!isNumber || yearStr.empty()) {
            cout << "Ошибка: год должен быть числом!" << endl;
            continue;
        }
        
        int year = stoi(yearStr);
        
        file << title << "|" << author << "|" << year << endl;
        cout << "Книга '" << title << "' успешно добавлена!" << endl;
    }
    
    file.close();
    
    ofstream logFile("output.txt", ios::app);
    logFile << "Создан файл books.txt с начальными данными" << endl;
    logFile.close();
}

vector<Book> readAllBooks() {
    vector<Book> books;
    ifstream file("books.txt");
    
    if (!file.is_open()) {
        return books;
    }
    
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos) {
            Book book;
            book.title = line.substr(0, pos1);
            book.author = line.substr(pos1 + 1, pos2 - pos1 - 1);
            book.year = stoi(line.substr(pos2 + 1));
            
            books.push_back(book);
        }
    }
    
    file.close();
    return books;
}

void writeBooksToFile(const vector<Book>& books) {
    ofstream file("books.txt");
    
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для записи!" << endl;
        return;
    }
    
    for (const Book& book : books) {
        file << book.title << "|" << book.author << "|" << book.year << endl;
    }
    
    file.close();
}

void searchBookByTitle() {
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "Файл books.txt не найден! Сначала создайте библиотеку." << endl;
        return;
    }
    file.close();
    
    string searchTitle;
    cout << "Введите название книги для поиска: ";
    getline(cin, searchTitle);
    
    if (searchTitle.empty()) {
        cout << "Ошибка: название для поиска не может быть пустым!" << endl;
        return;
    }
    
    vector<Book> books = readAllBooks();
    vector<Book> foundBooks;
    
    for (const Book& book : books) {
        if (book.title.find(searchTitle) != string::npos) {
            foundBooks.push_back(book);
        }
    }
    
    if (!foundBooks.empty()) {
        cout << endl << "Найдено книг: " << foundBooks.size() << endl;
        for (int i = 0; i < foundBooks.size(); i++) {
            cout << i + 1 << ". '" << foundBooks[i].title << "' - " 
                 << foundBooks[i].author << " (" << foundBooks[i].year << "г.)" << endl;
        }
        
        ofstream logFile("output.txt", ios::app);
        logFile << "Поиск книги по названию '" << searchTitle << "': найдено " << foundBooks.size() << " книг" << endl;
        logFile.close();
    } else {
        cout << "Книги с названием '" << searchTitle << "' не найдены." << endl;
        
        ofstream logFile("output.txt", ios::app);
        logFile << "Поиск книги по названию '" << searchTitle << "': не найдено" << endl;
        logFile.close();
    }
}

bool compareByAuthor(const Book& a, const Book& b) {
    return a.author < b.author;
}

bool compareByYear(const Book& a, const Book& b) {
    return a.year < b.year;
}

void sortBooks() {
    vector<Book> books = readAllBooks();
    
    if (books.empty()) {
        cout << "В библиотеке нет книг для сортировки!" << endl;
        return;
    }
    
    cout << endl << "=== СОРТИРОВКА КНИГ ===" << endl;
    cout << "1. Сортировка по автору" << endl;
    cout << "2. Сортировка по году выпуска" << endl;
    
    string choice;
    cout << "Выберите тип сортировки (1 или 2): ";
    getline(cin, choice);
    
    if (choice == "1") {
        sort(books.begin(), books.end(), compareByAuthor);
        cout << "Книги отсортированы по автору:" << endl;
        
        ofstream logFile("output.txt", ios::app);
        logFile << "Сортировка книг по автору" << endl;
        logFile.close();
    } else if (choice == "2") {
        sort(books.begin(), books.end(), compareByYear);
        cout << "Книги отсортированы по году выпуска:" << endl;
        
        ofstream logFile("output.txt", ios::app);
        logFile << "Сортировка книг по году выпуска" << endl;
        logFile.close();
    } else {
        cout << "Неверный выбор!" << endl;
        return;
    }
    
    writeBooksToFile(books);
    
    for (int i = 0; i < books.size(); i++) {
        cout << i + 1 << ". '" << books[i].title << "' - " 
             << books[i].author << " (" << books[i].year << "г.)" << endl;
    }
}

void addBookToFile() {
    cout << endl << "=== ДОБАВЛЕНИЕ НОВОЙ КНИГИ ===" << endl;
    
    string title;
    cout << "Введите название книги: ";
    getline(cin, title);
    
    if (title.empty()) {
        cout << "Ошибка: название не может быть пустым!" << endl;
        return;
    }
    
    string author;
    cout << "Введите автора книги: ";
    getline(cin, author);
    
    if (author.empty()) {
        cout << "Ошибка: автор не может быть пустым!" << endl;
        return;
    }
    
    string yearStr;
    cout << "Введите год выпуска: ";
    getline(cin, yearStr);
    
    bool isNumber = true;
    for (char c : yearStr) {
        if (!isdigit(c)) {
            isNumber = false;
            break;
        }
    }
    
    if (!isNumber || yearStr.empty()) {
        cout << "Ошибка: год должен быть числом!" << endl;
        return;
    }
    
    int year = stoi(yearStr);
    
    ofstream file("books.txt", ios::app);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл!" << endl;
        return;
    }
    
    file << title << "|" << author << "|" << year << endl;
    file.close();
    
    cout << "Книга '" << title << "' успешно добавлена в библиотеку!" << endl;
    
    ofstream logFile("output.txt", ios::app);
    logFile << "Добавлена новая книга: '" << title << "' - " << author << " (" << year << "г.)" << endl;
    logFile.close();
}

void searchBooksByYear() {
    vector<Book> books = readAllBooks();
    
    if (books.empty()) {
        cout << "Библиотека пуста!" << endl;
        return;
    }
    
    string yearStr;
    cout << "Введите максимальный год выпуска: ";
    getline(cin, yearStr);
    
    bool isNumber = true;
    for (char c : yearStr) {
        if (!isdigit(c)) {
            isNumber = false;
            break;
        }
    }
    
    if (!isNumber || yearStr.empty()) {
        cout << "Ошибка: год должен быть числом!" << endl;
        return;
    }
    
    int maxYear = stoi(yearStr);
    vector<Book> foundBooks;
    
    for (const Book& book : books) {
        if (book.year <= maxYear) {
            foundBooks.push_back(book);
        }
    }
    
    if (!foundBooks.empty()) {
        cout << endl << "Книги выпущенные не позднее " << maxYear << " года:" << endl;
        for (int i = 0; i < foundBooks.size(); i++) {
            cout << i + 1 << ". '" << foundBooks[i].title << "' - " 
                 << foundBooks[i].author << " (" << foundBooks[i].year << "г.)" << endl;
        }
        
        ofstream logFile("output.txt", ios::app);
        logFile << "Поиск книг до " << maxYear << " года: найдено " << foundBooks.size() << " книг" << endl;
        logFile.close();
    } else {
        cout << "Книг выпущенных не позднее " << maxYear << " года не найдено." << endl;
        
        ofstream logFile("output.txt", ios::app);
        logFile << "Поиск книг до " << maxYear << " года: не найдено" << endl;
        logFile.close();
    }
}

void displayAllBooks() {
    vector<Book> books = readAllBooks();
    
    if (books.empty()) {
        cout << "Библиотека пуста!" << endl;
        return;
    }
    
    cout << endl << "=== ВСЕ КНИГИ В БИБЛИОТЕКЕ (" << books.size() << ") ===" << endl;
    for (int i = 0; i < books.size(); i++) {
        cout << i + 1 << ". '" << books[i].title << "' - " 
             << books[i].author << " (" << books[i].year << "г.)" << endl;
    }
    
    ofstream logFile("output.txt", ios::app);
    logFile << "Просмотр всех книг: всего " << books.size() << " книг" << endl;
    logFile.close();
}

void mainMenu() {
    while (true) {
        cout << endl << "================================================" << endl;
        cout << "           БИБЛИОТЕКА КНИГ - ГЛАВНОЕ МЕНЮ" << endl;
        cout << "================================================" << endl;
        cout << "1. Создать новую библиотеку книг" << endl;
        cout << "2. Показать все книги" << endl;
        cout << "3. Добавить новую книгу" << endl;
        cout << "4. Поиск книги по названию" << endl;
        cout << "5. Сортировка книг (по автору или году)" << endl;
        cout << "6. Поиск книг по году выпуска" << endl;
        cout << "7. Выход" << endl;
        cout << "================================================" << endl;
        
        string choice;
        cout << "Выберите действие (1-7): ";
        getline(cin, choice);
        
        if (choice == "1") {
            createBooksFile();
        } else if (choice == "2") {
            displayAllBooks();
        } else if (choice == "3") {
            addBookToFile();
        } else if (choice == "4") {
            searchBookByTitle();
        } else if (choice == "5") {
            sortBooks();
        } else if (choice == "6") {
            searchBooksByYear();
        } else if (choice == "7") {
            cout << "Выход из программы. Все операции сохранены в output.txt" << endl;
            
            ofstream logFile("output.txt", ios::app);
            logFile << "Завершение работы программы" << endl;
            logFile.close();
            
            break;
        } else {
            cout << "Неверный выбор! Пожалуйста, введите число от 1 до 7." << endl;
        }
    }
}

int main() {
    ofstream logFile("output.txt");
    logFile.close();
    
    cout << "Добро пожаловать в программу управления библиотекой книг!" << endl;
    mainMenu();
    
    return 0;
}
