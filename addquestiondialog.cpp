#include "addquestiondialog.h"
#include "ui_addquestiondialog.h"

AddQuestionDialog::AddQuestionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddQuestionDialog)
    , question_ptr_(std::make_unique<qwestions::Question>())
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    responseOptionModel_ = new ResponseOptionModel(question_ptr_.get(), this);
    ui->treeView->setModel(responseOptionModel_);

    responseOptionModel_->append_empty_response_option();
    responseOptionModel_->append_empty_response_option();
    responseOptionModel_->append_empty_response_option();
}

AddQuestionDialog::~AddQuestionDialog()
{
    delete ui;
}

std::unique_ptr<qwestions::Question> AddQuestionDialog::get_and_reset_question()
{
    auto question_ptr = std::exchange(question_ptr_, std::make_unique<qwestions::Question>());
    responseOptionModel_->reset_question(question_ptr_.get());

    question_ptr->set_text(ui->plainTextEdit->toPlainText().toStdString());
    return question_ptr;
}

// void AddQuestionDialog::accept()
// {
//     m_question_text = ui->plainTextEdit->toPlainText();
//     QDialog::accept();
// }
