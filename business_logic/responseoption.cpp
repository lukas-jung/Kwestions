#include "responseoption.h"

namespace qwestions {

ResponseOption::ResponseOption(std::string text)
    : text_(text)
{}

const std::string &ResponseOption::text() const
{
    return text_;
}

} // namespace qwestions
