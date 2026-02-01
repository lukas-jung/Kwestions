#ifndef QUESTION_H
#define QUESTION_H

#include "responseoption.h"
#include <span>
#include <string>
#include <vector>

namespace qwestions {

class Question
{
public:
    Question();
    explicit Question(std::string text);

    const std::string &text() const;
    const std::span<const ResponseOption> options() const;
    void appendOption(ResponseOption option);
    void setOptionAtIndex(size_t index, ResponseOption option);

    void setText(const std::string &text);

private:
    std::string m_text;
    std::vector<ResponseOption> m_response_options;
};

} // namespace qwestions

#endif // QUESTION_H
