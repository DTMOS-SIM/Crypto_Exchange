enum class CmdValue {
    help = 1,
    prod = 2,
    min = 3,
    max = 4,
    avg = 5,
    predict = 6,
    current = 7,
    step = 8,
    hProd = 9,
    hMin = 10,
    hMax = 11,
    hAvg = 12,
    hPredict = 13,
    hCurrent = 14,
    hStep = 15,
    indicator = 16,
    volume = 17
};

class CommandLine {
private:
public:
    static int cmdMapper(std::string item);
    /**
     * Constructor()
     */
    CommandLine();
    /**
    * Initializer()
    */
    void init();
};
