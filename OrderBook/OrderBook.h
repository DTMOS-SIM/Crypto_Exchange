#pragma once
#include "../OrderBookEntry/OrderBookEntry.h"
#include "../CSVReader/CSVReader.h"
#include <vector>

class OrderBook {
public:
    explicit OrderBook(const char* fileName);
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders(const OrderBookType& type,
                                          const std::string& product,
                                          const std::string& timestamp);
    std::vector<OrderBookEntry> OrderBook::getAllSingleDayOrders(const std::string& product, const std::string& timestamp);
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(vector<OrderBookEntry> &orders);
    static double getDailyTradeVolume(std::vector<OrderBookEntry>& orders);
    std::string getEarliestTime();
    std::string getNextTime(std::string timestamp);
    void insertOrder(OrderBookEntry& order);
    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
    double getSpecificPairAverage(const OrderBookType &type, const string &product, const string &timestamp);
    std::vector<string> getAllUniqueTimestamps();
    vector<OrderBookEntry> getAllOrders();
private:
    std::vector<OrderBookEntry> orders;
};