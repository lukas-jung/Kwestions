#include "addquestiondialog.h"
#include "ui_addquestiondialog.h"

AddQuestionDialog::AddQuestionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddQuestionDialog)
    , question_uptr_(std::make_unique<kwestions::Question>())
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    responseOptionModel_ = new ResponseOptionModel(question_uptr_.get(), this);
    ui->treeView->setModel(responseOptionModel_);

    connect(ui->toolButton,
            &QToolButton::clicked,
            responseOptionModel_,
            &ResponseOptionModel::append_empty_response_option);
}

AddQuestionDialog::~AddQuestionDialog()
{
    delete ui;
}

std::unique_ptr<kwestions::Question> AddQuestionDialog::get_and_reset_question()
{
    auto question_uptr = std::exchange(question_uptr_, std::make_unique<kwestions::Question>());
    responseOptionModel_->reset_question(question_uptr_.get());

    question_uptr->set_text(ui->plainTextEdit->toPlainText().toStdString());
    return question_uptr;
}

// void AddQuestionDialog::accept()
// {
//     m_question_text = ui->plainTextEdit->toPlainText();
//     QDialog::accept();
// }
