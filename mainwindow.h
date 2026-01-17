#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addquestiondialog.h"
#include <QMainWindow>
#include <QPointer>
#include <QStandardItemModel>

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
    QStandardItemModel *m_itemModel;
    QPointer<AddQuestionDialog> m_addQuestionDialog;
};
#endif // MAINWINDOW_H
