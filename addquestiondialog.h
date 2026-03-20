#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include "business_logic/question.h"
#include "responseoptionmodel.h"
#include <memory>

#include <QDialog>

namespace Ui {
class AddQuestionDialog;
}

class AddQuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddQuestionDialog(QWidget *parent = nullptr);
    ~AddQuestionDialog();

    std::unique_ptr<kwestions::Question> get_and_reset_question();

    // public slots:
    //     void accept() override;

private:
    Ui::AddQuestionDialog *ui;

    std::unique_ptr<kwestions::Question> question_ptr_;

    ResponseOptionModel *responseOptionModel_;
};

#endif // ADDQUESTIONDIALOG_H
