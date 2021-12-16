#include <string>
#include <vector>
#include "CommandLine.h"
#include "../Tokeniser/Tokeniser.h"

/**
 * Maps user options
 * @param string
 * @return int
*/
int CommandLine::cmdMapper(std::string item) {
    //Making use of tokeniser function to spilt the cmds
    std::vector<std::string> cmdList = Tokeniser::tokenise(item, ' ');
    // Constraining predict and avg parameters to 4 ONLY and ONLY predict and avg will have 4 COMPULSORY cmd parameter
    if(cmdList.size() == 4 && cmdList.front() == "avg" || cmdList.size() == 4 && cmdList.front() == "predict") {
        if (cmdList.front() == "avg")
            return static_cast<int>(CmdValue::avg);
        else if (cmdList.front() == "predict")
            return static_cast<int>(CmdValue::predict);
    }
    // Constraining min and mx parameters to 3 ONLY and ONLY min and max will have 3 COMPULSORY cmd parameter
    if(cmdList.size() == 3 && cmdList.front() == "min" || cmdList.size() == 3 && cmdList.front() == "max" || cmdList.size() == 3 && cmdList.front() == "indicator") {
        if (cmdList.front() == "min")
            return static_cast<int>(CmdValue::min);
        else if (cmdList.front() == "max")
            return static_cast<int>(CmdValue::max);
        else if (cmdList.front() == "indicator")
            return static_cast<int>(CmdValue::indicator);
    }
    // Constraining help cmd parameters to 2 ONLY and ONLY help <type> cmd will have 2 COMPULSORY cmd parameter
    if (cmdList.size() == 2 && cmdList.front() == "help") {
        if (cmdList.back() == "prod")
            return static_cast<int>(CmdValue::hProd);
        else if (cmdList.back() == "min")
            return static_cast<int>(CmdValue::hMin);
        else if (cmdList.back() == "max")
            return static_cast<int>(CmdValue::hMax);
        else if (cmdList.back() == "avg")
            return static_cast<int>(CmdValue::hAvg);
        else if (cmdList.back() == "predict")
            return static_cast<int>(CmdValue::hPredict);
        else if (cmdList.back() == "time")
            return static_cast<int>(CmdValue::hCurrent);
        else if (cmdList.back() == "step")
            return static_cast<int>(CmdValue::hStep);
    }
    // Constraining remaining singular parameter to 1 ONLY and ONLY 1 COMPULSORY cmd parameter
    else if (cmdList.size() == 1) {
        if (cmdList.front() == "help")
            return static_cast<int>(CmdValue::help);
        else if (cmdList.front() == "prod")
            return static_cast<int>(CmdValue::prod);
        else if (cmdList.front() == "time")
            return static_cast<int>(CmdValue::current);
        else if (cmdList.front() == "step")
            return static_cast<int>(CmdValue::step);
        else if (cmdList.front() == "volume")
            return static_cast<int>(CmdValue::volume);
    }
    // Returning invalid and (which is 0) re-loop the input call function
    else {
        return 0;
    }
}

