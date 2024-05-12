#ifndef READER_H
#define READER_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <chrono>
#include "event.h"

/**
 * @class CSVFileRW
 * @brief Class that implements writing of of event objects to file and loading events from file csv
 * */  
class CSVFileRW {
	std::string filename;
    std::string header;
public:
/**
 * @brief Constructor of CSVFileRW. Throws logic_error() if file is not csv
 * @param fname name of file
 * */  
	CSVFileRW(const std::string & fname);
/**
 * @brief method that reads event from file, prepare them and makes vector of shared_ptr events
 * */  
	std::vector<std::shared_ptr<Event>> read() const;
/**
 * @brief method that writes event from vector of shared_ptr events to file
 * @param events to be written to file
 * */  
    void write(std::vector<std::shared_ptr<Event>> events) const;
private:
/**
 * @brief helper function to test if string could be converted to integer
 * @param str tested string
 * */  
	bool is_int(std::string str) const;
/**
 * @brief method that makes from vector of strings event object. Throws logic_error() is there was some problems with creating
 * @param row vector of strings to be converted into event object
 * */  
	std::vector<std::shared_ptr<Event>> make_event(const std::vector<std::string> & row) const;
};


#endif