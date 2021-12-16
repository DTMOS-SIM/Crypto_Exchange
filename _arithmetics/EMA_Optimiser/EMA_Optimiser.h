#include <vector>
#include "../../OrderBookEntry/OrderBookEntry.h"

class EMA_Optimiser {
public:
    EMA_Optimiser();
    ~EMA_Optimiser();
    static double SMA26Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders, std::string& product, OrderBookType action);
    static double SMA12Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders,std::string& product, OrderBookType action);
    static double EMA26Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders, std::string& product, OrderBookType action, double &sma26);
    static double EMA12Calculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders, std::string& product, OrderBookType action, double &sma12);
    static double MACDCalculator(std::vector<std::string> &timestamps, std::vector<OrderBookEntry> &orders, std::string& product, OrderBookType action);
private:
};
