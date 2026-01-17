#include "addquestiondialog.h"
#include "ui_addquestiondialog.h"

AddQuestionDialog::AddQuestionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddQuestionDialog)
{
    ui->setupUi(this);
    // setWindowFlag(Qt::Sheet, true);
}

AddQuestionDialog::~AddQuestionDialog()
{
    delete ui;
}
