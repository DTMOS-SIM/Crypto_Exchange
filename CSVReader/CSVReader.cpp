#include <iostream>
#include "CSVReader.h"
#include <fstream>

CSVReader::CSVReader() {

};

std::vector<OrderBookEntry> CSVReader::readCSV() {
    std::vector<OrderBookEntry> entries;
    std::string line;
    std::string a, b, c, d, e;
    //std::ifstream csvFile{"../20200601.csv"};
    if (FILE *fp = std::fopen("../20200601.csv", "r")) {
        char buff[2500];
        while (fgets(buff, 2048, fp) != NULL) {
            line = buff;
            line.substr(0, line.length() - 2);
            if(reinterpret_cast<const char *>(line[line.length()]) == ".") {
                line.substr(0, line.length() - 1);
            }
            //std::cout << line << std::endl;
            OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
            entries.push_back(obe);
        }
    }
    /*if (csvFile.is_open()) {
    while (std::getline(csvFile, line)) {
        try {
            OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
            entries.push_back(obe);
        }
        catch (const std::exception &e) {
            std::cout << "CSVReader::readCSV bad data" << std::endl;
        }
    }
    write_csv("../20200317_test.csv", entries);
    }*/
    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    return entries;
};



std::vector<std::string> CSVReader::tokenise(const std::string &csvLine, char separator) {
    std::vector<std::string> tokens;

    signed int start, end;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0);

    do {
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end)
            break;

        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.emplace_back(token);

        start = end + 1;
    } while (end > 0);

    return tokens;
};

OrderBookEntry CSVReader::stringsToOBE(const std::vector<string> &tokens) {
    double price, amount;
    string timestamp, exchange, call;
    string p, a;
    if (tokens.size() != 5) {
        std::cout << "Bad Line" << std::endl;
        throw std::exception{};
    }
    try {
        timestamp = tokens[0];
        exchange = tokens[1];
        call = tokens[2];
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
        //std::cout << price << ":" << amount << std::endl;

    } catch (const std::exception &e) {
        std::cout << "Bad Float!" << std::endl;
        throw;
    }

    OrderBookEntry obe{
            price,
            amount,
            tokens[0],
            tokens[1],
            OrderBookEntry::stringToOrderBookType(tokens[2])
    };

    return obe;
};

void CSVReader::write_csv(std::string filename, std::vector<OrderBookEntry> entries) {
    // Create an output filestream object
    std::ofstream myFile(filename);
    string a, b, c, d, e;
    for (unsigned int i = 0; i < entries.size(); i++) {
        switch (entries[i].orderBookType) {
            case OrderBookType::bid:
                a = "bid";
            case OrderBookType::ask:
                a = "ask";
        }
        b = entries[i].product;
        c = entries[i].timestamp;
        d = to_string(entries[i].amount);
        e = to_string(entries[i].price);

        // Send the column name to the stream
        myFile << "Row: ";
        myFile << c + "," + b + "," + a + "," + d + "," + e << "\n";
    }
    // Close the file
    myFile.close();
};

OrderBookEntry
CSVReader::stringsToOBE(std::string priceString, std::string amountString, std::string timestamp, std::string product,
                        OrderBookType orderType) {
    double price, amount;
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
        std::cout << price << ":" << amount << std::endl;

    } catch (const std::exception &e) {
        std::cout << "CSVReader::stringsToOBE Bad Float!" << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad Float!" << amountString << std::endl;
        throw;
    }

    OrderBookEntry obe{
            price,
            amount,
            timestamp,
            product,
            orderType
    };

    return obe;
}
