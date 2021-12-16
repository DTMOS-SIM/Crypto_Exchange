#include <vector>
#include <iostream>
#include "Wallet.h"
#include "../CSVReader/CSVReader.h"

Wallet::Wallet() {

}

void Wallet::insertCurrency(std::string type, double amount) {
    double balance;
    if(amount < 0) {
        throw std::exception{};
    }
    if(currencies.count(type) == 0) {
        balance = 0;
    } else {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::containsCurrency(std::string type, double amount) {
    return currencies.count(type) != 0 && currencies[type] >= amount;
}

std::string Wallet::toString() {
    std::string s;
    for (std::pair<const std::string,double> pair: currencies) {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::removeCurrency(std::string type, double amount) {
    double balance;
    if(amount < 0) {
        return false;
    }
    if(currencies.count(type) == 0) {
        return false;
    } else {
        if(containsCurrency(type,amount)) {
            currencies[type] -= amount;
            return true;
        } else {
            return false;
        }
    }
}

bool Wallet::canFulfillOrder(const OrderBookEntry& order) {
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');

    //ASK
    if (order.orderBookType == OrderBookType::ask) {
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Wallet::canFulfillOrder " << currency << ":" << amount << std::endl;
        return containsCurrency(currency, amount);
    }

    //BID
    if (order.orderBookType == OrderBookType::bid) {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        return containsCurrency(currency, amount);
    }
    return false;
}

void Wallet::processSale(OrderBookEntry &sale) {
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

    //ASK
    if (sale.orderBookType == OrderBookType::asksale) {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }

    //BID
    if (sale.orderBookType == OrderBookType::bidsale) {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}
