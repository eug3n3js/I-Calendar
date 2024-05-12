#ifndef LOCEXPRESSION_H
#define LOCEXPRESSION_H
#include "expression.h"

/**
 * @class LocationExpression
 * @brief This class stands for evaluating events by Attribute location
*/
class LocationExpression : public Expression {
    std::string location;
    std::string comparison;
public:
/**
 * @brief Constructor of the LocationExpression
 * @param location string that represents target location
 * @param comparison string that represents comparing operator for evaluating events ==, !=
 */ 
    LocationExpression(const std::string& location, const std::string& comparison);
/**
 * @brief Destructor of the LocationExpression
 * 
 * */ 
    ~LocationExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */  
    bool evaluate(const Event& event) const override;
};

#endif