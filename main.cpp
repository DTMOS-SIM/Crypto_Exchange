#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry/OrderBookEntry.h"
#include "./MerkelMain.h"
#include "./Tokeniser/Tokeniser.h"
#include "CSVReader/CSVReader.h"

string input;
using namespace std;

int main() {
    MerkelMain app{};
    app.init();
}
