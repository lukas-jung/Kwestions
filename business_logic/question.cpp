#include "question.h"

namespace qwestions {

Question::Question(std::string text)
    : m_text(text)
{}

const std::string &Question::text() const
{
    return m_text;
}

} // namespace qwestions
