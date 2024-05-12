#ifndef DATEEXPRESSION_H
#define DATEEXPRESSION_H
#include "time.h"
#include "expression.h"

/**
 * @class DateExpression
 * @brief This class stands for evaluating events by Attribute date
*/
class DateExpression : public Expression {
    Time date;
    std::string comparison;
public:
/**
 * @brief Constructor of the DateExpression
 * @param date comparing value for evaluating events by date attribute
 * @param comparison string that represents comparing operator for evaluating events
 */ 
    DateExpression(const Time& date, const std::string& comparison);
/**
 * @brief Destructor of the DateExpression
 * 
 * */ 
    ~DateExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */ 
    bool evaluate(const Event& event) const override;
};

#endif