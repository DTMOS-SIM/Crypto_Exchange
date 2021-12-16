#pragma once
#include <vector>

class Tokeniser {
public:
    Tokeniser();
    void init();
    static std::vector<std::string> tokenise(std::string csvLine, char separator);
private:
};
