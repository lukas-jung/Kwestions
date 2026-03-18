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

kwestions::Questionnaire NewQuestionnaireDialog::questionnaire()
{
    return kwestions::Questionnaire(ui->lineEdit->text().toStdString());
}
