#pragma once

#include <vector>
#include "OrderBookEntry/OrderBookEntry.h"
#include "OrderBook/OrderBook.h"
#include "Wallet/Wallet.h"

class MerkelMain {
public:
    /**
    * Constructor()
    */
    MerkelMain();

    /**
    * Initializer()
    */
    void init();

private:

    /**
     * Print Menu List
     * @param null
     * @return cout values
     */
    static void printMenu();
    /**
     * Print Help List
     * @param null
     * @return cout values
     */
    static void printHelp();
    /**
     * Print Market Values (e.g trade volume, maximum ask price, number of ask price etc.)
     * @param null
     * @return cout values
     */
    void printMarketStats();
    /**
     * Print Market Values (e.g trade volume, maximum ask price, number of ask price etc.)
     * @param null
     * @return cout values
     */
    void printAllExchangePairs();
    /**
     * Print Market Values (e.g trade volume, maximum ask price, number of ask price etc.)
     * @param string
     * @param OrderBookType
     * @return
     */
    void calculatePairPosition(const string& type, string& pair, OrderBookType action);
    /**
     * Get Ask Price for a particular trading pair
     * @param null
     * @return cout values
     */
    void enterAsk();
    /**
     * Get Bid Price for a particular trading pair
     * @param null
     * @return cout values
     */
    void enterBid();
    /**
     * Print Wallet Information
     * @param null
     * @return cout values
     */
    void printWallet();
    /**
     * Move on to next timeline
     * @param null
     * @return cout values
     */
    void gotoNextTimeframe();
    /**
     * Loads user options
     * @param null
     * @return cout values
     */
    void processUserOption(int userOption, const std::string& cmd);
    /**
     * Calculate Average Pricing for specific pair
     * @param string pair
     * @param OrderBookType bid/ask
     * @param string timestamp
     * @return cout values
     */
    void calculateAveragePairPrice(string &pair, OrderBookType action, string &timestamp);
    /**
     * Loads user options
     * @param string type
     * @param string pair
     * @param OrderBookType bid/ask
     * @return cout values
     */
    void predictNextFramePricing(string &type, string &product, OrderBookType action);
    /**
     * Predict next point should be bought or sold indicator based off MACD indication
     * @param string type
     * @param string Pair
     * @param OrderBookType bid/ask
     * @return void
     */
    void predictBuyOrSellIndicator(string &product, OrderBookType action);
    /**
     * Trade volume for each trading pair in the exchange
     * */
    void tradeVolumePerTimestamp();
    /**
     * Check for validity of exchange pair
     * @param string pair
     * @return bool
     */
    bool isProductValid(string &product);
    //Global private variable for timeframe tracking
    std::string currentTime;
    //Global private variable to initialized csv data
    OrderBook orderBook{"../20200601.csv"};
    //Global private variable for wallet tracking
    Wallet wallet;
};