#ifndef NEWQUESTIONNAIREDIALOG_H
#define NEWQUESTIONNAIREDIALOG_H

#include "business_logic/questionnaire.h"
#include <QDialog>

namespace Ui {
class NewQuestionnaireDialog;
}

class NewQuestionnaireDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewQuestionnaireDialog(QWidget *parent = nullptr);
    ~NewQuestionnaireDialog();

    kwestions::Questionnaire questionnaire();

private:
    Ui::NewQuestionnaireDialog *ui;
};

#endif // NEWQUESTIONNAIREDIALOG_H
