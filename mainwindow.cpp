#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_itemModel = new QuestionModel(this);

    ui->treeView->setModel(this->m_itemModel);

    connect(ui->addQuestionButton, &QPushButton::clicked, this, &MainWindow::showAddQuestionDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAddQuestionDialog()
{
    if (!m_addQuestionDialog) {
        m_addQuestionDialog = new AddQuestionDialog(this);
        connect(m_addQuestionDialog, &QDialog::accepted, [this]() {
            m_itemModel->appendQuestion(this->m_addQuestionDialog->question());
        });
    }
    m_addQuestionDialog->open();
}

