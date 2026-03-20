#include "questionmodel.h"

QuestionModel::QuestionModel(kwestions::Questionnaire *questionnaire_ptr, QObject *parent)
    : QAbstractItemModel(parent)
    , questionnaire_ptr_(questionnaire_ptr)
{}

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

    return questionnaire_ptr_ ? questionnaire_ptr_->questions().size() : 0;
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

    if (role == Qt::DisplayRole && questionnaire_ptr_) {
        const kwestions::Question &question = questionnaire_ptr_->questions()[index.row()];
        return QVariant(QString::fromStdString(question.text()));
    }

    return QVariant();
}

void QuestionModel::append_question(kwestions::Question question)
{
    if (questionnaire_ptr_) {
        int insertion_position = questionnaire_ptr_->questions().size();
        beginInsertRows(QModelIndex(), insertion_position, insertion_position);

        questionnaire_ptr_->append_question(question);

        endInsertRows();
    }
}

void QuestionModel::set_questionnaire(kwestions::Questionnaire *questionnaire_ptr)
{
    beginResetModel();
    questionnaire_ptr_ = questionnaire_ptr;
    endResetModel();
}
