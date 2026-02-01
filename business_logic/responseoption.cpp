#include "responseoption.h"

namespace qwestions {

ResponseOption::ResponseOption(std::string text)
    : m_text(text)
{}

const std::string &ResponseOption::text() const
{
    return m_text;
}

} // namespace qwestions
