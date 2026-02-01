#include "addquestiondialog.h"
#include "ui_addquestiondialog.h"

AddQuestionDialog::AddQuestionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddQuestionDialog)
    , m_question()
    , m_response_option_model(m_question, this)
{
    ui->setupUi(this);
    ui->treeView->setModel(&m_response_option_model);
    setAttribute(Qt::WA_DeleteOnClose);

    m_response_option_model.appendEmptyResponseOption();
    m_response_option_model.appendEmptyResponseOption();
    m_response_option_model.appendEmptyResponseOption();
}

AddQuestionDialog::~AddQuestionDialog()
{
    delete ui;
}

qwestions::Question AddQuestionDialog::question()
{
    m_question.setText(ui->plainTextEdit->toPlainText().toStdString());
    return m_question;
}

// void AddQuestionDialog::accept()
// {
//     m_question_text = ui->plainTextEdit->toPlainText();
//     QDialog::accept();
// }
