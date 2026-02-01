#include "question.h"

namespace qwestions {

Question::Question() {}

Question::Question(std::string text)
    : m_text(text)
{}

const std::string &Question::text() const
{
    return m_text;
}

const std::span<const ResponseOption> Question::options() const
{
    return m_response_options;
}

void Question::appendOption(ResponseOption option)
{
    m_response_options.push_back(option);
}

void Question::setOptionAtIndex(size_t index, ResponseOption option)
{
    m_response_options.at(index) = option;
}

void Question::setText(const std::string &text)
{
    m_text = text;
}

} // namespace qwestions
