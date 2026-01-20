#ifndef QUESTION_H
#define QUESTION_H

#include <string>

namespace qwestions {

class Question
{
public:
    explicit Question(std::string text);
    const std::string &text() const;

private:
    std::string m_text;
};

} // namespace qwestions

#endif // QUESTION_H
