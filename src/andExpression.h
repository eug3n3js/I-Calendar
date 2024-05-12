#ifndef ANDEXPRESSION_H
#define ANDEXPRESSION_H
#include "expression.h"
#include <memory>
/**
 * @class AndExpression
 * @brief This class evaluates AND logical expression operand of filtrating prompt
*/
class AndExpression : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
/**
 * @brief Constructor of the AndExpression
 * @param left pointer to Left expression of And operand
 * @param right pointer to Right expression of And operand
 * 
 * */ 
    AndExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
/**
 * @brief Destructor of the AndExpression
 * 
 * */ 
    ~AndExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */ 
    bool evaluate(const Event& event) const override;
};


#endif