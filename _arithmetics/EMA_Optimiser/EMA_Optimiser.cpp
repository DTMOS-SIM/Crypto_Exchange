#include <iostream>
#include "EMA_Optimiser.h"
EMA_Optimiser::EMA_Optimiser()= default;;
EMA_Optimiser::~EMA_Optimiser()= default;

double EMA_Optimiser::SMA26Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders,std::string& product, OrderBookType action) {
    double totalAmount = 0;
    //Timestamps from 27th day from the latest timestamp to 2nd day from the latest timestamp
    for (unsigned int i = timestamps.size() - 27; i < timestamps.size(); i++) {
        double amount = 0;
        int counter = 0;
        //calculate amount through the timestamps for every eligible pair
        for (OrderBookEntry& e: orders) {
            if (e.orderBookType == action &&
                e.product == product &&
                e.timestamp == timestamps[i]) {
                amount += e.price;
                counter++;
            }
        }
        if(counter != 0) {
            amount = amount / counter;
            totalAmount += amount;
        }
    }
    totalAmount = totalAmount / 26;
    return totalAmount;
}

double EMA_Optimiser::SMA12Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders,std::string& product, OrderBookType action) {
    double totalAmount = 0;
    //Timestamps from 27th day from the latest timestamp to 2nd day from the latest timestamp
    for (unsigned int i = timestamps.size() - 13; i < timestamps.size(); i++) {
        double amount = 0;
        int counter = 0;
        //calculate amount through the timestamps for every eligible pair
        for (OrderBookEntry& e: orders) {
            if (e.orderBookType == action &&
                e.product == product &&
                e.timestamp == timestamps[i]) {
                amount += e.price;
                counter++;
            }
        }
        if(counter != 0) {
            amount = amount / counter;
            totalAmount += amount;
        }
    }
    totalAmount = totalAmount / 12;
    return totalAmount;
}

double EMA_Optimiser::EMA26Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders, std::string& product, OrderBookType action, double &sma26) {
    double amount = 0;
    int counter = 0;
    //calculate amount through the timestamps for every eligible pair
    for (OrderBookEntry& e: orders) {
        if (e.orderBookType == action &&
            e.product == product &&
            e.timestamp == timestamps.back()) {
            amount += e.price;
            counter++;
        }
    }
    if(counter != 0) {
        amount = amount / counter;
    }
    //EMA Formula Substitution
    // Smoothing Factor presumes to be 2
    amount = ( amount * ( 2 / (26+1) ) ) + (sma26 * ( 1 - ( 2 / (26-1) ) ) );
    return amount;
}

double EMA_Optimiser::EMA12Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders, std::string& product, OrderBookType action, double &sma12) {
    double amount = 0;
    int counter = 0;
    //calculate amount through the timestamps for every eligible pair
    for (OrderBookEntry& e: orders) {
        if (e.orderBookType == action &&
            e.product == product &&
            e.timestamp == timestamps.back()) {
            amount += e.price;
            counter++;
        }
    }
    if(counter != 0) {
        amount = amount / counter;
    }
    //EMA Formula Substitution
    // Smoothing Factor presumes to be 2
    amount = ( amount * ( 2 / (12+1) ) ) + (sma12 * ( 1 - ( 2 / (12-1) ) ) );
    return amount;
}

double EMA_Optimiser::MACDCalculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders, std::string& product, OrderBookType action) {
    //Calculate the 26 points SMA to act as 1st day of EMA
    double sma26 = SMA26Calculator(timestamps,orders, product, action);
    double ema26New = EMA26Calculator(timestamps,orders, product, action, sma26);
    std::cout << "SMA 26 Points: " << sma26 << std::endl;
    std::cout << "EMA 26 Points: " << ema26New << std::endl;
    //Calculate the 12 points SMA to act as 1st day of EMA
    double sma12 = SMA12Calculator(timestamps,orders, product, action);
    double ema12New = EMA12Calculator(timestamps,orders, product, action, sma12);
    std::cout << "SMA 12 Points: " << sma12 << std::endl;
    std::cout << "EMA 12 Points: " << ema12New << std::endl;
    return ema12New - ema26New;
};
