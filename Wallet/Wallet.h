#include <string>
#include <map>
#include "../OrderBookEntry/OrderBookEntry.h"

class Wallet {
public:
    /*Constructor*/
    Wallet();
    /* Insert currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /* Remove currency to the wallet */
    bool removeCurrency(std::string type, double amount);
    /* Insert currency to the wallet */
    bool containsCurrency(std::string type, double amount);
    /* Checks if the wallet can cope with thi ask or bid */
    bool canFulfillOrder(const OrderBookEntry& order);
    /* Generate String representation of the wallet */
    std::string toString();
    /* Assume the order was made by the owner of the wallet*/
    void processSale(OrderBookEntry& sale);
private:
    std::map<std::string, double> currencies;

};