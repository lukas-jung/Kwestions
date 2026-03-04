#include "questionnaire.h"

namespace kwestions {

Questionnaire::Questionnaire() {}

const std::string &Questionnaire::title() const
{
    return title_;
}

void Questionnaire::set_title(const std::string &title)
{
    title_ = title;
}

const std::span<const Question> Questionnaire::questions() const
{
    return questions_;
}

void Questionnaire::append_question(Question question)
{
    questions_.push_back(question);
}

void Questionnaire::set_question_at_index(std::size_t index, Question question)
{
    questions_.at(index) = question;
}

bool Questionnaire::move_question_from_to(std::size_t from, std::size_t to)
{
    if (from == to || from >= questions_.size() || to >= questions_.size()) {
        return false;
    }

    if (from < to) {
        std::rotate(questions_.begin() + from,
                    questions_.begin() + from + 1,
                    questions_.begin() + to + 1);
    } else {
        std::rotate(questions_.begin() + to,
                    questions_.begin() + from,
                    questions_.begin() + from + 1);
    }
    return true;
}

} // namespace kwestions
