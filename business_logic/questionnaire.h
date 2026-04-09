#ifndef QUESTIONNAIRE_H
#define QUESTIONNAIRE_H

#include "question.h"
#include <string>

namespace kwestions {

class Questionnaire
{
public:
    Questionnaire(std::string title = "");

    const std::string &title() const;
    void set_title(const std::string &title);

    const std::span<const Question> questions() const;
    void append_question(Question question);
    void set_question_at_index(std::size_t index, Question question);
    void delete_question_at(std::size_t i);

    bool move_question_from_to(std::size_t from, std::size_t to);

private:
    std::string title_;
    std::vector<Question> questions_;
};

} // namespace kwestions

#endif // QUESTIONNAIRE_H
