#include "loadConfig.h"
#include <fstream>
 
bool Conf::loadConfig(int & window_width, int & column_width) const {
    std::ifstream in("./config/calendar.config");
    if (!in.is_open()){
        return false;
    }
    std::string param;
    int value, window = 0, column = 0;
    while (!in.eof()){
        in >> param;
        in >> value;
        if (param == "WINDOW_WIDTH"){
            window = value;
        }
        if (param == "COLUMN_WIDTH"){
            column = value;
        }
    }
    in.close();
    if (window > 90 && column > 25){
        window_width = column;
        column_width = window;
    } else {
        return false;
    }
    return true;
}
