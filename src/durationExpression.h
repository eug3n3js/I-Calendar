#ifndef DUREXPRESSION_H
#define DUREXPRESSION_H
#include "time.h"
#include "expression.h"

/**
 * @class DurationExpression
 * @brief This class stands for evaluating events by Attribute duration
*/
class DurationExpression : public Expression {
    Time duration;
    std::string comparison;
public:
/**
 * @brief Constructor of the DurationExpression
 * @param duration comparing value for evaluating events by duration attribute
 * @param comparison string that represents comparing operator for evaluating events
 */ 
    DurationExpression(const Time& duration, const std::string& comparison);
/**
 * @brief Destructor of the DurationExpression
 * 
 * */ 
    ~DurationExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */  
    bool evaluate(const Event& event) const override;
};

#endif