#ifndef NAMEEXPRESSION_H
#define NAMEEXPRESSION_H
#include "expression.h"

/**
 * @class NameExpression
 * @brief This class stands for filtering events by Attribute Name
*/
class NameExpression : public Expression {
    std::string name;
    std::string comparison;
public:
/**
 * @brief Constructor of the NameExpression
 * @param name string that represents target Name attribute value
 * @param comparison string that represents comparing operator for evaluating events ==, !=
 */ 
    NameExpression(const std::string& name, const std::string& comparison);
/**
 * @brief Destructor of the NameExpression
 * 
 * */ 
    ~NameExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */  
    bool evaluate(const Event& event) const override;
};

#endif