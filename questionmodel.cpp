#include "questionmodel.h"

QuestionModel::QuestionModel(kwestions::Questionnaire *questionnaire, QObject *parent)
    : QAbstractItemModel(parent)
    , questionnaire_(questionnaire)
{
    // questions_.push_back(kwestions::Question("Hello?"));
    // questions_.push_back(kwestions::Question("Hello? Anyone there?"));
    // questions_.push_back(kwestions::Question("Helloooooo?"));
}

QVariant QuestionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QString("Question");
    }
    return QVariant();
}

QModelIndex QuestionModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column);
    }

    return QModelIndex();
}

QModelIndex QuestionModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int QuestionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return questionnaire_ ? questionnaire_->questions().size() : 0;
}

int QuestionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return 1;
}

QVariant QuestionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole && questionnaire_) {
        const kwestions::Question &question = questionnaire_->questions()[index.row()];
        return QVariant(QString::fromStdString(question.text()));
    }

    return QVariant();
}

void QuestionModel::append_question(kwestions::Question question)
{
    if (questionnaire_) {
        int insertion_position = questionnaire_->questions().size();
        beginInsertRows(QModelIndex(), insertion_position, insertion_position);

        questionnaire_->append_question(question);

        endInsertRows();
    }
}

void QuestionModel::set_questionnaire(kwestions::Questionnaire *questionnaire)
{
    beginResetModel();
    questionnaire_ = questionnaire;
    endResetModel();
}
