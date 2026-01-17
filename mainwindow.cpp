#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

namespace {
void addQuestion(QStandardItemModel *model, QString question)
{
    model->setHorizontalHeaderLabels({"Question"});
    QStandardItem *root = model->invisibleRootItem();

    auto item = new QStandardItem(question);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    root->appendRow(item);
}
} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_itemModel = new QStandardItemModel(this);
    addQuestion(this->m_itemModel, "Hello?");
    addQuestion(this->m_itemModel, "Hello2?");
    addQuestion(this->m_itemModel, "Hello3?");

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
    }
    m_addQuestionDialog->open();
}

