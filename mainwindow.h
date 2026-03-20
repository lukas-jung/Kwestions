#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addquestiondialog.h"
#include "newquestionnairedialog.h"
#include "questionmodel.h"
#include "questionnaireselectionmodel.h"
#include <memory>
#include <QMainWindow>
#include <QPointer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAddQuestionDialog();
    void createNewQuestionnaire();

private:
    Ui::MainWindow *ui;
    std::vector<std::unique_ptr<kwestions::Questionnaire>> questionnaires_;

    QuestionnaireSelectionModel *questionnaireSelectionModel_;
    QPointer<NewQuestionnaireDialog> newQuestionnaireDialog_;

    QuestionModel *questionItemModel_;
    QPointer<AddQuestionDialog> addQuestionDialog_;
};
#endif // MAINWINDOW_H
