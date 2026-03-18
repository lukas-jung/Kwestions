#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    questionnaireSelectionModel_ = new QuestionnaireSelectionModel(&questionnaires_, this);

    questionItemModel_ = new QuestionModel(nullptr, this);

    ui->comboBox->setModel(questionnaireSelectionModel_);
    ui->treeView->setModel(this->questionItemModel_);

    connect(ui->comboBox, &QComboBox::currentIndexChanged, [this](int index) {
        this->questionItemModel_->set_questionnaire(index == -1 ? nullptr
                                                                : &questionnaires_.at(index));
    });

    connect(ui->addQuestionButton, &QPushButton::clicked, this, &MainWindow::showAddQuestionDialog);
    connect(ui->newQuestionnaireButton,
            &QPushButton::clicked,
            this,
            &MainWindow::createNewQuestionnaire);
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

void MainWindow::createNewQuestionnaire()
{
    if (!newQuestionnaireDialog_) {
        newQuestionnaireDialog_ = new NewQuestionnaireDialog(this);
        connect(newQuestionnaireDialog_, &QDialog::accepted, [this]() {
            questionnaireSelectionModel_->append_questionnaire(
                this->newQuestionnaireDialog_->questionnaire());
        });
    }
    newQuestionnaireDialog_->open();
}
