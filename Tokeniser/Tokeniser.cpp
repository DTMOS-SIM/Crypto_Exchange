#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Tokeniser.h"

Tokeniser::Tokeniser() {}

void Tokeniser::init() {
    std::vector<std::string> tokens;
    std::ifstream csvFile{"../20200317.csv"};
    std::string line;
    if(csvFile.is_open())
    {
        std::cout << "File open" << std::endl;
        std::cout << "Read line" << std::endl;
        while(std::getline(csvFile, line))
        {
            //std::cout << line << std::endl;
            tokens = tokenise(line, ' ');
            if(tokens.size() != 5)
            {
                std::cout << "Bad Line" << std::endl;
                continue;
            }
            try {
                double price = std::stod(tokens[3]);
                double amount = std::stod(tokens[4]);
                std::cout << price << ":" << amount << std::endl;
            } catch (std::exception& e) {
                std::cout << "Bad Float!" << std::endl;
                break;
            }
        }
    }
    else
    {
        std::cout << "Could not open file" << std::endl;
    }
}

std::vector<std::string> Tokeniser::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;

    signed int start, end;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0);

    do {
        end = csvLine.find_first_of(separator, start);

        if(start == csvLine.length() || start == end)
            break;

        if(end >= 0)
            token = csvLine.substr(start,end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.emplace_back(token);

        start = end + 1;
    }
    while (end > 0);

    return tokens;
}
