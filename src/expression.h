#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "event.h"
/**
 * @class Expression
 * @brief Abstract class that represents Expression for filtering events by specific prompt
*/
class Expression {
public:
    /**
 * @brief Abstract method that evaluetes Event for fitting expression
 * @param event Event that will be evaluated
 * 
 * */ 
    virtual bool evaluate(const Event& event) const = 0;
};

#endif