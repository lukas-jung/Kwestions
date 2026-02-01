#ifndef RESPONSEOPTION_H
#define RESPONSEOPTION_H

#include <string>

namespace qwestions {

class ResponseOption
{
public:
    explicit ResponseOption(std::string text);
    const std::string &text() const;

private:
    std::string m_text;
};

} // namespace qwestions

#endif // RESPONSEOPTION_H
