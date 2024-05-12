#ifndef NOTEXPRESSION_H
#define NOTEXPRESSION_H
#include "expression.h"
#include <memory>

/**
 * @class NotExpression
 * @brief This class evaluates Not logical expression operand of filtrating prompt like !a
*/
class NotExpression : public Expression {
    std::shared_ptr<Expression> operand;
public:
/**
 * @brief Constructor of the OrExpression
 * @param operand pointer to expression of Not operand

 */ 
    NotExpression(std::shared_ptr<Expression> operand);
/**
 * @brief Destructor of the NotExpression
 * 
 * */ 
    ~NotExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */ 
    bool evaluate(const Event& event) const override;
};

#endif