#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    questionnaires_.emplace_back();
    questionnaires_.emplace_back();
    questionnaires_.emplace_back();
    questionnaires_.emplace_back();
    questionnaires_.at(0).set_title("banana0");
    questionnaires_.at(1).set_title("banana1");
    questionnaires_.at(2).set_title("banana2");
    questionnaires_.at(3).set_title("banana3");

    questionnaireSelectionModel_ = new QuestionnaireSelectionModel(&questionnaires_, this);

    questionItemModel_ = new QuestionModel(nullptr, this);

    ui->comboBox->setModel(questionnaireSelectionModel_);
    ui->treeView->setModel(this->questionItemModel_);

    connect(ui->comboBox, &QComboBox::currentIndexChanged, [this](int index) {
        this->questionItemModel_->set_questionnaire(index == -1 ? nullptr
                                                                : &questionnaires_.at(index));
    });
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

