#pragma once

#include "../OrderBookEntry/OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader {

public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV ();

    static std::vector<std::string> tokenise(const std::string& csvLine, char separator);

    static OrderBookEntry stringsToOBE(std::string price,std::string amount,std::string timestamp,std::string product,OrderBookType orderType);
private:
    static OrderBookEntry stringsToOBE(const std::vector<string>& strings);
    static void write_csv(std::string filename,std::vector<OrderBookEntry> entries);
};