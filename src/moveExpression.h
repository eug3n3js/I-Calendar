#ifndef MOVEEXPRESSION_H
#define MOVEEXPRESSION_H
#include "expression.h"

/**
 * @class MoveExpression
 * @brief This class stands for evaluating events by Attribute Move
*/
class MoveExpression : public Expression {
    std::string moveable;
    std::string comparison;
public:
/**
 * @brief Constructor of the MoveExpression
 * @param moveable string that represents target value true, false
 * @param comparison string that represents comparing operator for evaluating events ==, !=
 */ 
    MoveExpression(const std::string& moveable, const std::string& comparison);
/**
 * @brief Destructor of the MoveExpression
 * 
 * */ 
    ~MoveExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */  
    bool evaluate(const Event& event) const override;
};

#endif