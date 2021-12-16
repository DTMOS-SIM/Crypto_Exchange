cmake_minimum_required(VERSION 3.0)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp OrderBookEntry/OrderBookEntry.cpp OrderBookEntry/OrderBookEntry.h MerkelMain.cpp MerkelMain.h Tokeniser/Tokeniser.cpp Tokeniser/Tokeniser.h CSVReader/CSVReader.cpp CSVReader/CSVReader.h OrderBook/OrderBook.cpp OrderBook/OrderBook.h Wallet/Wallet.cpp Wallet/Wallet.h CommandLine/CommandLine.cpp CommandLine/CommandLine.h _arithmetics/EMA_Optimiser/EMA_Optimiser.cpp _arithmetics/EMA_Optimiser/EMA_Optimiser.h)
