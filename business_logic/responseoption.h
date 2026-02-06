#ifndef RESPONSEOPTION_H
#define RESPONSEOPTION_H

#include <string>

namespace kwestions {

class ResponseOption
{
public:
    explicit ResponseOption(std::string text);
    const std::string &text() const;

private:
    std::string text_;
};

} // namespace kwestions

#endif // RESPONSEOPTION_H
