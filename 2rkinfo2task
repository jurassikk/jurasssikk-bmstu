#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>

class BankAccount {
protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;

public:
    BankAccount(const std::string& accNum, const std::string& owner, double initialBalance = 0.0)
        : accountNumber(accNum), ownerName(owner), balance(initialBalance) {
        if (initialBalance < 0) {
            throw std::invalid_argument("Начальный баланс не может быть отрицательным");
        }
    }

    virtual ~BankAccount() {}

    virtual void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма пополнения должна быть положительной");
        }
        balance += amount;
        std::cout << "Счет " << accountNumber << " пополнен на " << amount 
                  << " руб. Новый баланс: " << balance << " руб." << std::endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма снятия должна быть положительной");
        }
        if (amount > balance) {
            throw std::invalid_argument("Недостаточно средств на счете");
        }
        balance -= amount;
        std::cout << "Со счета " << accountNumber << " снято " << amount 
                  << " руб. Новый баланс: " << balance << " руб." << std::endl;
    }

    std::string getAccountNumber() const { return accountNumber; }
    std::string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }

    virtual void displayInfo() const {
        std::cout << "\n=== Информация о банковском счете ===" << std::endl;
        std::cout << "Номер счета: " << accountNumber << std::endl;
        std::cout << "Владелец: " << ownerName << std::endl;
        std::cout << "Баланс: " << std::fixed << std::setprecision(2) 
                  << balance << " руб." << std::endl;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& accNum, const std::string& owner, 
                   double initialBalance = 0.0, double rate = 5.0)
        : BankAccount(accNum, owner, initialBalance), interestRate(rate) {
        if (rate < 0) {
            throw std::invalid_argument("Процентная ставка не может быть отрицательной");
        }
    }

    void applyInterest() {
        double interest = balance * (interestRate / 100.0);
        balance += interest;
        std::cout << "На счет " << accountNumber << " начислены проценты: " 
                  << interest << " руб. по ставке " << interestRate << "%" << std::endl;
        std::cout << "Новый баланс: " << balance << " руб." << std::endl;
    }

    double getInterestRate() const { return interestRate; }

    void setInterestRate(double rate) {
        if (rate < 0) {
            throw std::invalid_argument("Процентная ставка не может быть отрицательной");
        }
        interestRate = rate;
        std::cout << "Процентная ставка по счету " << accountNumber 
                  << " изменена на " << rate << "%" << std::endl;
    }

    void displayInfo() const override {
        BankAccount::displayInfo();
        std::cout << "Процентная ставка: " << interestRate << "%" << std::endl;
        std::cout << "Доход за год: " << std::fixed << std::setprecision(2)
                  << (balance * interestRate / 100.0) << " руб." << std::endl;
    }
};

void demonstrateBankOperations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ БАНКОВСКОЙ СИСТЕМЫ ===\n" << std::endl;

    try {
        std::cout << "1. Создание обычного банковского счета:" << std::endl;
        BankAccount regularAccount("40817810099910004321", "Иванов Иван Иванович", 50000.0);
        regularAccount.displayInfo();

        std::cout << "\n2. Операции с обычным счетом:" << std::endl;
        regularAccount.deposit(15000.0);
        regularAccount.withdraw(8000.0);
        regularAccount.displayInfo();

        std::cout << "\n3. Создание сберегательного счета:" << std::endl;
        SavingsAccount savingsAccount("42307810100009876543", "Петрова Анна Сергеевна", 100000.0, 7.5);
        savingsAccount.displayInfo();

        std::cout << "\n4. Операции со сберегательным счетом:" << std::endl;
        savingsAccount.deposit(50000.0);
        savingsAccount.withdraw(20000.0);
        
        std::cout << "\n5. Начисление процентов по сберегательному счету:" << std::endl;
        savingsAccount.applyInterest();
        
        std::cout << "\n6. Изменение процентной ставки:" << std::endl;
        savingsAccount.setInterestRate(8.2);
        savingsAccount.applyInterest();
        
        std::cout << "\n7. Финальная информация по всем счетам:" << std::endl;
        regularAccount.displayInfo();
        savingsAccount.displayInfo();

    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    }
}

void demonstrateAccountArray() {
    std::cout << "\n\n=== РАБОТА С МАССИВОМ СЧЕТОВ ===" << std::endl;
    
    std::vector<BankAccount*> accounts;
    
    accounts.push_back(new BankAccount("40817810200001234567", "Сидоров Алексей", 30000.0));
    accounts.push_back(new SavingsAccount("42305810300007654321", "Козлова Мария", 150000.0, 6.5));
    accounts.push_back(new SavingsAccount("42301810400005555555", "Смирнов Дмитрий", 80000.0, 7.0));
    
    for (auto account : accounts) {
        account->displayInfo();
        account->deposit(10000.0);
        
        SavingsAccount* savings = dynamic_cast<SavingsAccount*>(account);
        if (savings != nullptr) {
            savings->applyInterest();
        }
        
        std::cout << std::endl;
    }
    
    for (auto account : accounts) {
        delete account;
    }
}

int main() {
    std::cout << "БАНКОВСКАЯ СИСТЕМА" << std::endl;
    std::cout << "==================" << std::endl;
    
    demonstrateBankOperations();
    demonstrateAccountArray();
    
    std::cout << "\nПрограмма завершена успешно!" << std::endl;
    
    return 0;
}
