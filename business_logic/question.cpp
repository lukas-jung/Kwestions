#include "question.h"
#include <algorithm>

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

void Question::set_option_at_index(std::size_t index, ResponseOption option)
{
    response_options_.at(index) = option;
}

bool Question::move_option_from_to(std::size_t from, std::size_t to)
{
    if (from == to || from >= response_options_.size() || to >= response_options_.size()) {
        return false;
    }

    if (from < to) {
        std::rotate(response_options_.begin() + from,
                    response_options_.begin() + from + 1,
                    response_options_.begin() + to + 1);
    } else {
        std::rotate(response_options_.begin() + to,
                    response_options_.begin() + from,
                    response_options_.begin() + from + 1);
    }
    return true;
}

void Question::set_text(const std::string &text)
{
    text_ = text;
}

} // namespace kwestions
