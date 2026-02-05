#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addquestiondialog.h"
#include "questionmodel.h"
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

private:
    Ui::MainWindow *ui;
    QuestionModel *questionItemModel_;
    QPointer<AddQuestionDialog> addQuestionDialog_;
};
#endif // MAINWINDOW_H
