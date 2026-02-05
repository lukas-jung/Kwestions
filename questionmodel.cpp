#include "questionmodel.h"

QuestionModel::QuestionModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    questions_.push_back(qwestions::Question("Hello?"));
    questions_.push_back(qwestions::Question("Hello? Anyone there?"));
    questions_.push_back(qwestions::Question("Helloooooo?"));
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

    return questions_.size();
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

    if (role == Qt::DisplayRole) {
        const qwestions::Question &question = questions_.at(index.row());
        return QVariant(QString::fromStdString(question.text()));
    }

    return QVariant();
}

void QuestionModel::append_question(qwestions::Question question)
{
    int insertion_position = questions_.size();
    beginInsertRows(QModelIndex(), insertion_position, insertion_position);

    questions_.push_back(question);

    endInsertRows();
}
