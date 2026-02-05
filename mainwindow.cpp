#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    questionItemModel_ = new QuestionModel(this);

    ui->treeView->setModel(this->questionItemModel_);

    connect(ui->addQuestionButton, &QPushButton::clicked, this, &MainWindow::showAddQuestionDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAddQuestionDialog()
{
    if (!addQuestionDialog_) {
        addQuestionDialog_ = new AddQuestionDialog(this);
        connect(addQuestionDialog_, &QDialog::accepted, [this]() {
            questionItemModel_->append_question(*this->addQuestionDialog_->get_and_reset_question());
        });
    }
    addQuestionDialog_->open();
}

