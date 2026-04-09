#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeView>

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
                                                                : questionnaires_.at(index).get());
    });

    connect(ui->newQuestionnaireButton,
            &QPushButton::clicked,
            this,
            &MainWindow::createNewQuestionnaire);

    connect(ui->treeView,
            &QAbstractItemView::doubleClicked,
            this,
            &MainWindow::showEditQuestionDialog);

    connect(ui->addQuestionButton, &QPushButton::clicked, this, &MainWindow::showAddQuestionDialog);
    connect(ui->removeQuestionButton, &QPushButton::clicked, this, &MainWindow::removeQuestion);
    connect(ui->removeQuestionnaireButton,
            &QPushButton::clicked,
            this,
            &MainWindow::removeQuestionnaire);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAddQuestionDialog()
{
    if (!addQuestionDialog_) {
        addQuestionDialog_ = new AddQuestionDialog(std::make_unique<kwestions::Question>(), this);
        connect(addQuestionDialog_, &QDialog::accepted, [this]() {
            questionItemModel_->append_question(*this->addQuestionDialog_->get_and_reset_question());
        });
    }
    addQuestionDialog_->open();
}

void MainWindow::removeQuestion()
{
    QModelIndex current_index = ui->treeView->currentIndex();

    if (current_index.isValid() && current_index.row() != -1) {
        questionItemModel_->delete_question_at(current_index.row());
    }
}

void MainWindow::showEditQuestionDialog(const QModelIndex &index)
{
    int current_questionnaire_index = ui->comboBox->currentIndex();
    if (current_questionnaire_index == -1) {
        return;
    }
    kwestions::Questionnaire *current_questionnaire_ptr
        = questionnaires_.at(current_questionnaire_index).get();

    int current_question_index = index.row();
    std::unique_ptr<kwestions::Question> question_uptr = std::make_unique<kwestions::Question>(
        current_questionnaire_ptr->questions()[current_question_index]);

    if (!addQuestionDialog_) {
        addQuestionDialog_ = new AddQuestionDialog(std::move(question_uptr), this);
        connect(addQuestionDialog_, &QDialog::accepted, [this, current_question_index]() {
            questionItemModel_->set_question_at(current_question_index,
                                                *this->addQuestionDialog_->get_and_reset_question());
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

void MainWindow::removeQuestionnaire()
{
    int current_i = ui->comboBox->currentIndex();

    if (current_i != -1) {
        questionnaireSelectionModel_->delete_questionnaire_at(current_i);
    }
}
