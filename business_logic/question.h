#ifndef QUESTION_H
#define QUESTION_H

#include "responseoption.h"
#include <span>
#include <string>
#include <vector>

namespace kwestions {

class Question
{
public:
    Question() = default;
    explicit Question(std::string text);

    const std::string &text() const;
    const std::span<const ResponseOption> options() const;
    void append_option(ResponseOption option);
    void set_option_at_index(std::size_t index, ResponseOption option);
    bool move_option_from_to(std::size_t from, std::size_t to);

    void set_text(const std::string &text);

private:
    std::string text_;
    std::vector<ResponseOption> response_options_;
};

} // namespace kwestions

#endif // QUESTION_H
