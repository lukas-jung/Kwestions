#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

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

private:
    Ui::AddQuestionDialog *ui;
};

#endif // ADDQUESTIONDIALOG_H
