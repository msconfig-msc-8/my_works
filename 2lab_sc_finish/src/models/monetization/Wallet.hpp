#ifndef WALLET_HPP
#define WALLET_HPP

#include <string>
#include <vector>
#include <ctime>
#include "../../exceptions/Exceptions.hpp"

/**
 * @file Wallet.hpp
 * @brief Определение класса Wallet для работы с финансами
 */

/**
 * @brief Структура транзакции
 * @details Хранит информацию об одной финансовой операции
 */
struct Transaction {
    std::string id;          ///< Уникальный идентификатор транзакции
    double amount;           ///< Сумма (положительная для пополнения, отрицательная для списания)
    std::string type;        ///< Тип транзакции (deposit, withdrawal, transfer)
    std::string description; ///< Описание транзакции
    std::time_t timestamp;   ///< Время транзакции
};

/**
 * @brief Класс кошелька пользователя
 * @details Предоставляет функциональность для управления балансом пользователя:
 *          пополнение, снятие, переводы между кошельками.
 * 
 * @par Пример использования:
 * @code
 * Wallet wallet1("user1");
 * Wallet wallet2("user2");
 * 
 * wallet1.deposit(1000.0, "Начальный депозит");
 * wallet1.transfer(wallet2, 250.0, "Перевод другу");
 * 
 * std::cout << "Баланс: " << wallet1.getBalance() << std::endl;
 * @endcode
 * 
 * @see Transaction
 */
class Wallet {
private:
    std::string userId_;              ///< ID владельца кошелька
    double balance_;                  ///< Текущий баланс
    std::string currency_;            ///< Валюта (по умолчанию RUB)
    std::vector<Transaction> transactions_; ///< История транзакций
    bool isLocked_;                   ///< Заблокирован ли кошелёк

public:
    /**
     * @brief Конструктор кошелька
     * @param userId ID владельца
     * @param currency Валюта (по умолчанию "RUB")
     */
    explicit Wallet(const std::string& userId, const std::string& currency = "RUB")
        : userId_(userId), balance_(0.0), currency_(currency), isLocked_(false) {}

    /**
     * @brief Получить ID владельца
     * @return Константная ссылка на ID пользователя
     */
    const std::string& getUserId() const { return userId_; }
    
    /**
     * @brief Получить текущий баланс
     * @return Текущий баланс в валюте кошелька
     */
    double getBalance() const { return balance_; }
    
    /**
     * @brief Получить валюту кошелька
     * @return Константная ссылка на код валюты
     */
    const std::string& getCurrency() const { return currency_; }
    
    /**
     * @brief Получить историю транзакций
     * @return Константная ссылка на вектор транзакций
     */
    const std::vector<Transaction>& getTransactions() const { return transactions_; }
    
    /**
     * @brief Проверить, заблокирован ли кошелёк
     * @return true если кошелёк заблокирован
     */
    bool isLocked() const { return isLocked_; }

    /**
     * @brief Получить отформатированный баланс
     * @return Строка с балансом и валютой (например, "1000.00 RUB")
     */
    std::string getFormattedBalance() const {
        return std::to_string(balance_) + " " + currency_;
    }

    /**
     * @brief Пополнить баланс
     * @param amount Сумма пополнения (должна быть > 0)
     * @param description Описание операции
     * @throws AccessDeniedException Если кошелёк заблокирован
     * @throws InvalidContentException Если сумма <= 0
     * 
     * @par Пример:
     * @code
     * wallet.deposit(500.0, "Пополнение с карты");
     * @endcode
     */
    void deposit(double amount, const std::string& description = "Deposit") {
        if (isLocked_) {
            throw AccessDeniedException("Wallet is locked");
        }
        if (amount <= 0) {
            throw InvalidContentException("Amount must be positive");
        }
        balance_ += amount;
        
        Transaction tx;
        tx.id = std::to_string(transactions_.size() + 1);
        tx.amount = amount;
        tx.type = "deposit";
        tx.description = description;
        tx.timestamp = std::time(nullptr);
        transactions_.push_back(tx);
    }

    /**
     * @brief Снять средства с баланса
     * @param amount Сумма снятия (должна быть > 0)
     * @param description Описание операции
     * @throws AccessDeniedException Если кошелёк заблокирован
     * @throws InvalidContentException Если сумма <= 0
     * @throws InsufficientBalanceException Если недостаточно средств
     * 
     * @par Пример:
     * @code
     * try {
     *     wallet.withdraw(200.0, "Оплата услуг");
     * } catch (const InsufficientBalanceException& e) {
     *     std::cout << "Недостаточно средств!" << std::endl;
     * }
     * @endcode
     */
    void withdraw(double amount, const std::string& description = "Withdrawal") {
        if (isLocked_) {
            throw AccessDeniedException("Wallet is locked");
        }
        if (amount <= 0) {
            throw InvalidContentException("Amount must be positive");
        }
        if (amount > balance_) {
            throw InsufficientBalanceException(amount, balance_);
        }
        balance_ -= amount;
        
        Transaction tx;
        tx.id = std::to_string(transactions_.size() + 1);
        tx.amount = -amount;
        tx.type = "withdrawal";
        tx.description = description;
        tx.timestamp = std::time(nullptr);
        transactions_.push_back(tx);
    }

    /**
     * @brief Перевести средства другому пользователю
     * @param recipient Кошелёк получателя
     * @param amount Сумма перевода
     * @throws AccessDeniedException Если кошелёк заблокирован
     * @throws InsufficientBalanceException Если недостаточно средств
     * 
     * @par Пример:
     * @code
     * Wallet sender("user1"), receiver("user2");
     * sender.deposit(1000.0);
     * sender.transfer(receiver, 500.0);
     * @endcode
     */
    void transfer(Wallet& recipient, double amount, const std::string& /*description*/ = "Transfer") {
        withdraw(amount, "Transfer to " + recipient.getUserId());
        recipient.deposit(amount, "Transfer from " + userId_);
    }

    /**
     * @brief Получить последние транзакции
     * @param limit Максимальное количество транзакций
     * @return Вектор последних транзакций
     */
    std::vector<Transaction> getHistory(size_t limit = 10) const {
        std::vector<Transaction> recent;
        size_t start = transactions_.size() > limit ? transactions_.size() - limit : 0;
        for (size_t i = start; i < transactions_.size(); i++) {
            recent.push_back(transactions_[i]);
        }
        return recent;
    }

    /**
     * @brief Заблокировать кошелёк
     * @details После блокировки операции deposit/withdraw/transfer недоступны
     */
    void lock() { isLocked_ = true; }
    
    /**
     * @brief Разблокировать кошелёк
     */
    void unlock() { isLocked_ = false; }
};

#endif // WALLET_HPP
