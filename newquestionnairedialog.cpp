#include "newquestionnairedialog.h"
#include "ui_newquestionnairedialog.h"

NewQuestionnaireDialog::NewQuestionnaireDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewQuestionnaireDialog)
{
    ui->setupUi(this);
}

NewQuestionnaireDialog::~NewQuestionnaireDialog()
{
    delete ui;
}

std::unique_ptr<kwestions::Questionnaire> NewQuestionnaireDialog::questionnaire()
{
    return std::make_unique<kwestions::Questionnaire>(ui->lineEdit->text().toStdString());
}
