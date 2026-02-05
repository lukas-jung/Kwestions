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
    Question() = default;
    explicit Question(std::string text);

    const std::string &text() const;
    const std::span<const ResponseOption> options() const;
    void append_option(ResponseOption option);
    void set_option_at_index(size_t index, ResponseOption option);

    void set_text(const std::string &text);

private:
    std::string text_;
    std::vector<ResponseOption> response_options_;
};

} // namespace qwestions

#endif // QUESTION_H
