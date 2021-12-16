#include "./MerkelMain.h"
#include "./CommandLine/CommandLine.h"
#include "Tokeniser/Tokeniser.h"
#include "_arithmetics/EMA_Optimiser/EMA_Optimiser.h"
#include <iostream>
#include <vector>

MerkelMain::MerkelMain() {}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void MerkelMain::init() {
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);
    while (true) {
        printMenu();

        //Get Command
        std::string line;
        int cmdValue;
        std::cout << "Please input your service:" << std::endl;
        std::getline(std::cin, line);
        cmdValue = CommandLine::cmdMapper(line);

        //Process Data
        processUserOption(cmdValue,line);
    }
}
#pragma clang diagnostic pop

/**
 * UOL Example to print start up menu
 * */
void MerkelMain::printMenu() {
    std::cout << "Welcome to CryptoExchange!" << std::endl;
    std::cout << "============== " << std::endl;
}

/**
 * Print cmd help
 * */
void MerkelMain::printHelp() {
    std::cout << "All the available commands are: " << std::endl;
    std::cout << "help" << std::endl;
    std::cout << "help <type>" << std::endl;
    std::cout << "prod" << std::endl;
    std::cout << "min < product > < bid | ask >" << std::endl;
    std::cout << "max < product > < bid | ask >" << std::endl;
    std::cout << "avg < product > < bid | ask > < timestamp >" << std::endl;
    std::cout << "predict < min | max > < product > < bid | ask >" << std::endl;
    std::cout << "indicator < product > < bid | ask >" << std::endl;
    std::cout << "volume" << std::endl;
    std::cout << "time" << std::endl;
    std::cout << "step" << std::endl;
}

/**
 * UOL Example to print market stats
 * */
void MerkelMain::printMarketStats() {
    for (std::string const &p: orderBook.getKnownProducts()) {
        // UOL Defined Parameters
        std::cout << "Products: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> fullEntry = orderBook.getAllSingleDayOrders(p, currentTime);
        std::cout << "Ask seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << "  " << "Min ask: "
                  << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Daily Trading Volume: " << OrderBook::getDailyTradeVolume(fullEntry) << std::endl;
        std::cout << " " << std::endl;
    }
}

/**
 * Trade volume for each trading pair in the exchange in current timestamp
 * */
void MerkelMain::tradeVolumePerTimestamp() {
    for (std::string const &p: orderBook.getKnownProducts()) {
        // UOL Defined Parameters
        std::cout << "Products: " << p << std::endl;
        std::vector<OrderBookEntry> fullEntry = orderBook.getAllSingleDayOrders(p, currentTime);
        std::cout << "Daily Trading Volume: " << OrderBook::getDailyTradeVolume(fullEntry) << std::endl;
        std::cout << " " << std::endl;
    }
}

/**
 * Print all available exchange pairs
 */
void MerkelMain::printAllExchangePairs() {
    std::cout << "All Available Trading Pairs: " << std::endl;
    for (std::string const &p: orderBook.getKnownProducts()) {
        std::cout << p << std::endl;
    }
}

/**
 * Calculate Pair Price based on bid or ask
 * @param string type
 * @param OrderBookType bid/ask
 * @param string action
 * @return void
 */
void MerkelMain::calculatePairPosition(const std::string& type, std::string& pair, OrderBookType action) {
    bool valid = isProductValid(pair);
    if(valid) {
        if (type == "min") {
            switch (action) {
                case OrderBookType::ask: {
                    std::vector<OrderBookEntry> entry = orderBook.getOrders(action, pair, currentTime);
                    std::cout << "Min ask: " << OrderBook::getLowPrice(entry) << std::endl;
                    break;
                }
                case OrderBookType::bid: {
                    std::vector<OrderBookEntry> entry = orderBook.getOrders(action, pair, currentTime);
                    std::cout << "Min bid: " << OrderBook::getLowPrice(entry) << std::endl;
                    break;
                }
            }

        }
        else if (type == "max") {
            switch (action) {
                case OrderBookType::bid: {
                    std::vector<OrderBookEntry> entry = orderBook.getOrders(action, pair, currentTime);
                    std::cout << "Max bid: " << OrderBook::getHighPrice(entry) << std::endl;
                    break;
                }
                case OrderBookType::ask: {
                    std::vector<OrderBookEntry> entry = orderBook.getOrders(action, pair, currentTime);
                    std::cout << "Max ask: " << OrderBook::getHighPrice(entry) << std::endl;
                    break;
                }
            }
        }
        else {
            std::cout << "Invalid order book type. Please re-enter command again." << std::endl;
        }
    }
    else {
        std::cout << "Invalid exchange pair. Please re-enter command again." << std::endl;
    }
}

/**
 * Calculate Average Pair Price for certain time frame
 * @param string pair
 * @param OrderBookType bid/ask
 * @param string timestamp
 * @return void
 */
void MerkelMain::calculateAveragePairPrice(std::string& pair, OrderBookType action, std::string& timesteps) {
    double averagePrice = 0;
    bool valid = isProductValid(pair);
    if(valid) {
        for (int i = 0; i < stoi(timesteps); ++i) {
            averagePrice += orderBook.getSpecificPairAverage(action, pair, currentTime);
            currentTime = orderBook.getNextTime(currentTime);
        }
        averagePrice = averagePrice / stoi(timesteps);
        std::cout << "Average Price for " << timesteps << " timesteps is : " << averagePrice << std::endl;
    }
    else {
        std::cout << "Invalid exchange pair. Please re-enter command again." << std::endl;
    }
}

/**
 * Calculate Average Pair Price for certain time frame
 * @param string type
 * @param string Pair
 * @param OrderBookType bid/ask
 * @return void
 */
void MerkelMain::predictNextFramePricing(std::string& type, std::string& product, OrderBookType action) {
    double averagePrice = 0;
    bool valid = isProductValid(product);
    if(valid) {
        for (int i = 0; i < 10; ++i) {
            //Get current time frame average
            averagePrice += orderBook.getSpecificPairAverage(action, product, currentTime);
            //Iterate across 10 points (equivalent of SMA 10 days)
            currentTime = orderBook.getNextTime(currentTime);
        }
        averagePrice = averagePrice / 10;
        std::cout << "The predicted price for next timestamp is : " << averagePrice << std::endl;
    } else {
        std::cout << "Invalid exchange pair. Please re-enter command again." << std::endl;
    }
}

/**
 * Predict next point should be bought or sold indicator based off MACD indication
 * @param string type
 * @param string Pair
 * @param OrderBookType bid/ask
 * @return void
 */
void MerkelMain::predictBuyOrSellIndicator(std::string &product, OrderBookType action) {
    bool valid = isProductValid(product);
    if(valid) {
        //get all unique timestamps
        std::vector<std::string> timestamps = orderBook.getAllUniqueTimestamps();
        //Get all orders
        std::vector<OrderBookEntry> orders = orderBook.getAllOrders();
        //MACD Calculations
        double macd = EMA_Optimiser::MACDCalculator(timestamps, orders, product, action);
        if(macd < 0) {
            //Do not sell and continue buying if possible
            std::cout << "MACD Points: " << macd << std::endl;
            std::cout << "Do not buy and continue selling if possible" << std::endl;
        }
        else if(macd > 0) {
            //Do not buy and continue selling if possible
            std::cout << "MACD Points: " << macd << std::endl;
            std::cout << "Do not sell and continue buying if possible" << std::endl;
        }
        else {
            //Do not sell and buy as there are no movement predicted
            std::cout << "MACD Points: " << macd << std::endl;
            std::cout << "Do not sell and buy as there are no movement predicted" << std::endl;
        }
    } else {
        std::cout << "Invalid exchange pair. Please re-enter command again." << std::endl;
    }
}

/**
 * UOL Example to enter ask
 * */
void MerkelMain::enterAsk() {
    std::cout << "Mark an ask - enter the amount: product,price,amount eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterAsk Bad Input! " << input << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                    tokens[1],
                    tokens[2],
                    currentTime,
                    tokens[0],
                    OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            } else {
                std::cout << "Insufficient Dollars. " << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << "MerkelMain::enterAsk Bad Input " << std::endl;
        }
    }
    std::cout << "You Typed: " << input << std::endl;
}

/**
 * UOL Example to enter bid
 * */
void MerkelMain::enterBid() {
    std::cout << "Make a bid - enter the amount" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterBid Bad Input! " << input << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                    tokens[1],
                    tokens[2],
                    currentTime,
                    tokens[0],
                    OrderBookType::bid
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            } else {
                std::cout << "Insufficient Dollars. " << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << "MerkelMain::enterBid Bad Input " << std::endl;
        }
    }
    std::cout << "You Typed: " << input << std::endl;
}

/**
 * UOL Example to print wallet Data
 * */
void MerkelMain::printWallet() {
    std::cout << wallet.toString() << std::endl;
}

/**
 * UOL Example to move to the next batch of processing on next timeframe
 * */
void MerkelMain::gotoNextTimeframe() {
    std::cout << "Going to next time frame. " << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry &sale: sales) {
        std::cout << "Sales price: " << sale.price << "amount " << sale.amount << std::endl;
        if (sale.username == "simuser") {
            wallet.processSale(sale);
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

/**
 * Check for Product Validity
 * @param userOption
 * @param cmd
 */
bool MerkelMain::isProductValid(std::string& product) {
    bool valid = false;
    for (std::string const &p: orderBook.getKnownProducts()) {
        if(product == p)
            valid = true;
    }
    return valid;
}

/**
 * UOL Example to map user input into respective commands
 * */
void MerkelMain::processUserOption(int userOption,const std::string& cmd = "") {
    auto cmdList = Tokeniser::tokenise(cmd, ' ');
    switch (userOption) {
        case 0: {
            std::cout << "Invalid choice." << std::endl;
            break;
        }
        case 1: {
            printHelp();
            break;
        }
        case 2: {
            printAllExchangePairs();
            break;
        }
        case 3: {
            if(cmdList[2] == "bid") {
                calculatePairPosition("min", cmdList[1], OrderBookType::bid);
                break;
            }
            else if(cmdList[2] == "ask") {
                calculatePairPosition("min", cmdList[1], OrderBookType::ask);
                break;
            }
            else {
                std::cout << "Error in book order type (neither ask nor bid)" << std::endl;
            }
        }
        case 4: {
            if(cmdList[2] == "bid") {
                calculatePairPosition("max", cmdList[1], OrderBookType::bid);
                break;
            }
            else if(cmdList[2] == "ask") {
                calculatePairPosition("max", cmdList[1], OrderBookType::ask);
                break;
            }
            else {
                std::cout << "Error in book order type (neither ask nor bid)" << std::endl;
            }
        }
        case 5: {
            if(cmdList[2] == "bid") {
                calculateAveragePairPrice(cmdList[1], OrderBookType::bid, cmdList[3]);
            }
            else if(cmdList[2] == "ask"){
                calculateAveragePairPrice(cmdList[1], OrderBookType::ask, cmdList[3]);
            }
            else {
                std::cout << "Error in book order type (neither ask nor bid)" << std::endl;
            }
            break;
        }
        case 6: {
            if(cmdList[3] == "ask") {
                predictNextFramePricing(cmdList[1],cmdList[2],OrderBookType::ask);
            }
            else if(cmdList[3] == "bid") {
                predictNextFramePricing(cmdList[1],cmdList[2],OrderBookType::bid);
            }
            else {
                std::cout << "Error in book order type (neither ask nor bid)" << std::endl;
            }
            break;
        }
        case 7: {
            std::cout << "Current time: " << currentTime << std::endl;
            break;
        }
        case 8: {
            gotoNextTimeframe();
            std::cout << "Now at: " << currentTime << std::endl;
            break;
        }
        case 9:{
            std::cout << "List All Available Exchange Pairs" << std::endl;
            std::cout << "Input: prod" << std::endl;
            std::cout << "Response: ETH/BTC,DOGE/BTC etc." << std::endl;
            std::cout << " " << std::endl;
            break;
        }
        case 10: {
            std::cout << "Find minimum bid or ask for product in current time step" << std::endl;
            std::cout << "Input: min <exchange_pair> ask" << std::endl;
            std::cout << "Response: The min ask for ETH/BTC is 1.0" << std::endl;
            std::cout << " " << std::endl;
            break;
        }
        case 11: {
            std::cout << "Find maximum bid or ask for product in current time step" << std::endl;
            std::cout << "Input: max <exchange_pair> ask" << std::endl;
            std::cout << "Response: The max ask for ETH/BTC is 1.0" << std::endl;
            std::cout << " " << std::endl;
            break;
        }
        case 12: {
            std::cout << "Compute average ask or bid for the sent product over the sent number of time steps." << std::endl;
            std::cout << "Input: avg ETH/BTC ask 10" << std::endl;
            std::cout << "Response: The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
            std::cout << " " << std::endl;
            break;
        }
        case 13: {
            std::cout << "Predict max or min ask or bid for the sent product for the next timestep" << std::endl;
            std::cout << "Input: predict max ETH/BTC bid" << std::endl;
            std::cout << "Response: The predicted ETH/BTC max bid price is 15" << std::endl;
            std::cout << " " << std::endl;
            break;
        }
        case 14: {
            std::cout << "State current time in dataset, i.e. which timeframe are we looking at" << std::endl;
            std::cout << "Input: time" << std::endl;
            std::cout << "Response: 2020/03/17 17:01:24" << std::endl;
            std::cout << " " << std::endl;
            break;
        }
        case 15: {
            std::cout << "Move to next time step" << std::endl;
            std::cout << "Input: step" << std::endl;
            std::cout << "Response: now at 2020/03/17 17:01:30" << std::endl;
            std::cout << " " << std::endl;
            break;
        }
        case 16: {
            if(cmdList[2] == "ask") {
                predictBuyOrSellIndicator(cmdList[1],OrderBookType::ask);
            }
            else if(cmdList[2] == "bid") {
                predictBuyOrSellIndicator(cmdList[1],OrderBookType::bid);
            }
            else {
                std::cout << "Error in book order type (neither ask nor bid)" << std::endl;
            }
            break;
        }
        case 17: {
            tradeVolumePerTimestamp();
        }
    }
}