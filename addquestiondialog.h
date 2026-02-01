#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include "business_logic/question.h"
#include "responseoptionmodel.h"

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

    qwestions::Question question();

    // public slots:
    //     void accept() override;

private:
    Ui::AddQuestionDialog *ui;

    qwestions::Question m_question;

    ResponseOptionModel m_response_option_model;
};

#endif // ADDQUESTIONDIALOG_H
