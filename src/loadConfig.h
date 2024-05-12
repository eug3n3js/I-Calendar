#ifndef LOAD_H
#define LOAD_H

/**
 * @class Conf
 * @brief Class helper for loading configuration data
 * */ 
class Conf {
public:
/**
 * @brief Loads data and save it to corresponding variables
 * @param window_width saves defined width of window
 * @param column_width saves defined width of column for printing event
 * */ 
    bool loadConfig(int & window_width, int & column_width) const;
};
#endif