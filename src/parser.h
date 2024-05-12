#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include "time.h"
#include "event.h"
#include "expression.h"

/**
 * @class Parser
 * @brief Class that proccess parsing prompt and creates evaluation expression 
 * */  
class Parser {
    std::string expression;
    int pos;
public:
/**
 * @brief Constructor of Parser Class
 * @param expression string to be parsed
 * */  
    Parser(const std::string& expression);
/**
 * @brief method that produces evaluation expression. 
 * */  
    std::shared_ptr<Expression> parse();
/**
 * @brief method for parsing date 
 * */  
    Time parseDate();
private:
/**
 * @brief parses single terms and operators & | 
 * */  
    std::shared_ptr<Expression> parseExpression();
/**
 * @brief parses single term (!) if no terms found then parses factors
 * */  
    std::shared_ptr<Expression> parseTerm();
/**
 * @brief parses single factors (date=="....") and expressions with ( ,)
 * */  
    std::shared_ptr<Expression> parseFactor();
/**
 * @brief method for parsing duration 
 * */  
    Time parseDuration();
/**
 * @brief method for parsing comparison operators (!=, ==, <, >) 
 * */  
    std::string parseComparisonOperator();
/**
 * @brief method for parsing single string of factor
 * */ 
    std::string parseString();
/**
 * @brief helper method to check if string can be coverted to integer
 * @param s string to be converted
 * */ 
    bool isNumber(const std::string & s);
};

#endif