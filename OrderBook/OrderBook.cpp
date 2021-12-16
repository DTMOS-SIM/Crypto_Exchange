#include "OrderBook.h"
#include "../CSVReader/CSVReader.h"
#include <map>
#include <algorithm>

OrderBook::OrderBook(const char* fileName) {
    orders = CSVReader::readCSV();
}

/**
 * UOL Taught Feature
 * Get all known trading pairs
 * @return std::vector string
 */
std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& e: orders) {
        prodMap[e.product] = true;
    };

    // now flatten the map to a vector of strings
    for (auto const& e: prodMap) {
        products.push_back(e.first);
    };

    return products;
}

/**
 * Gets daily average price from specific trading pair
 * @param OrderBookType
 * @param string
 * @param string
 * @return std::vector OrderBookEntry
 */
double OrderBook::getSpecificPairAverage(const OrderBookType& type, const std::string& product, const std::string& timestamp) {
    double amount = 0;
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e: orders) {
        if (e.orderBookType == type &&
            e.product == product &&
            e.timestamp == timestamp) {
            amount += e.price;
            orders_sub.push_back(e);
        }
    }
    amount = amount/orders_sub.size();
    return amount;
}

/**
 * UOL Taught Feature
 * Get all orders from orderbook
 * @param OrderBookType
 * @param string
 * @param string
 * @return std::vector OrderBookEntry
 */
std::vector<OrderBookEntry> OrderBook::getOrders(const OrderBookType& type, const std::string& product, const std::string& timestamp) {
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e: orders) {
        if (e.orderBookType == type &&
            e.product == product &&
            e.timestamp == timestamp) {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

/**
 * UOL Taught Feature
 * Retrieves a list of each trading pair orderBookEntry object (e.g. ETH/BUSD)
 * @param product
 * @param timestamp
 * @return vector<OrderBookEntry>
 */
std::vector<OrderBookEntry> OrderBook::getAllSingleDayOrders(const std::string& product,const std::string& timestamp) {
    std::vector<OrderBookEntry> obj;
    for (OrderBookEntry& e: orders) {
        if(e.timestamp == timestamp && e.product == product) {
            obj.push_back(e);
        }
    }
    return obj;
}

/**
 * UOL Taught Feature
 * Get system earliest timings available
 * @param OrderBook
 * @return double
 */
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
    double max = orders[0].price;
    for(OrderBookEntry& e: orders)
    {
        if(e.price > max)
        {
            max = e.price;
        }
    }
    return max;
}

/**
 * UOL Taught Feature
 * Get system earliest timings available
 * @param std::vector OrderBookEntry
 * @return double
 */
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
    double min = orders[0].price;
    for(OrderBookEntry& e: orders)
    {
        if(e.price < min)
        {
            min = e.price;
        }
    }
    return min;
}

/**
 * UOL Taught Feature
 * Get system earliest timings available
 * @param string
 * @return string
 */
std::string OrderBook::getEarliestTime() {
    return orders[0].timestamp;
}

std::vector<std::string> OrderBook::getAllUniqueTimestamps() {
    std::string existingTimestamp = "";
    std::vector<std::string> timestamps_sub;
    for (OrderBookEntry& e: orders) {
        if (e.timestamp != existingTimestamp) {
            timestamps_sub.push_back(e.timestamp);
            existingTimestamp = e.timestamp;
        }
    }
    return timestamps_sub;
}

/**
 * UOL Taught Feature
 * Get next timestamp
 * @param string
 * @return string
 */
std::string OrderBook::getNextTime(std::string timestamp) {
    std::string next_timestamp = "";
    for(OrderBookEntry &e: orders) {
        if(e.timestamp > timestamp) {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if(next_timestamp == "") {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

/**
 * Computates the total trading volume of a particular day
 * @param vector<OrderBookEntry>
 * @return double
 */
double OrderBook::getDailyTradeVolume(vector<OrderBookEntry> &orders) {
    double orders_amount = 0;
    for (OrderBookEntry& e: orders) {
        orders_amount += e.amount;
    }
    return orders_amount;
}

/**
 * Get all orders
 * @return std::vector OrderBookEntry
 */
std::vector<OrderBookEntry> OrderBook::getAllOrders() {
    return orders;
}

/**
 * UOL Taught Feature
 * Insert new order into the orderbook
 * @param OrderBookEntry &order
 * @return OrderBook
 */
void OrderBook::insertOrder(OrderBookEntry& order) {
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

/**
 * UOL Taught Feature
 * Algorithm for Ask to Bid price matching
 * @param string product
 * @param string timestamp
 * @return std::vector orderBookEntry
 */
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                 product,
                                                 timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                 product,
                                                 timestamp);
    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry& ask : asks){
        for (OrderBookEntry& bid : bids) {
            if(bid.price >= ask.price) {
                OrderBookEntry sale {
                        ask.price,0,timestamp,product,OrderBookType::asksale
                };
                if(bid.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderBookType = OrderBookType::bidsale;
                }
                if(ask.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderBookType = OrderBookType::asksale;
                }

                if (bid.amount == ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if (bid.amount < ask.amount && bid.amount > 0) {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    return sales;
}
