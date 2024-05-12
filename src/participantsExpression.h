#ifndef PARTEXPRESSION_H
#define PARTEXPRESSION_H
#include "expression.h"

/**
 * @class ParticipantsExpression
 * @brief This class stands for evaluating events by testing existence of scific participant in participants attribute of event
*/
class ParticipantsExpression : public Expression {
    std::string participant;
    std::string comparison;
public:
/**
 * @brief Constructor of the ParticipantsExpression
 * @param participant string that represents participant that have to be participating this event
 * @param comparison string that represents comparing operator for evaluating events ==, !=
 */ 
    ParticipantsExpression(const std::string& participant, const std::string& comparison);
/**
 * @brief Destructor of the ParticipantsExpression
 * 
 * */ 
    ~ParticipantsExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */  
    bool evaluate(const Event& event) const override;
};

#endif