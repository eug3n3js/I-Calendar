#include "participantsExpression.h"

ParticipantsExpression::ParticipantsExpression(const std::string& participant_, const std::string& comparison_): participant(participant_), comparison(comparison_) {}
bool ParticipantsExpression::evaluate(const Event& event) const {
    if (event.participants().size() == 0){
        return false;
    }
    if (comparison == "==") {
        return event.participants().count(participant) > 0;
    } else if (comparison == "!=") {
        return event.participants().count(participant) == 0;
    } else {
        throw std::logic_error("   ");
    }
}