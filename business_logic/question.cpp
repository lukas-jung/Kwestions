#include "question.h"

namespace kwestions {

Question::Question(std::string text)
    : text_(text)
{}

const std::string &Question::text() const
{
    return text_;
}

const std::span<const ResponseOption> Question::options() const
{
    return response_options_;
}

void Question::append_option(ResponseOption option)
{
    response_options_.push_back(option);
}

void Question::set_option_at_index(size_t index, ResponseOption option)
{
    response_options_.at(index) = option;
}

void Question::set_text(const std::string &text)
{
    text_ = text;
}

} // namespace kwestions
