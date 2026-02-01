#include "questionmodel.h"

QuestionModel::QuestionModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_questions.push_back(qwestions::Question("Hello?"));
    m_questions.push_back(qwestions::Question("Hello? Anyone there?"));
    m_questions.push_back(qwestions::Question("Helloooooo?"));
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

    return m_questions.size();
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
        const qwestions::Question &question = m_questions.at(index.row());
        return QVariant(QString::fromStdString(question.text()));
    }

    return QVariant();
}

void QuestionModel::appendQuestion(qwestions::Question question)
{
    int insertion_position = m_questions.size();
    beginInsertRows(QModelIndex(), insertion_position, insertion_position);

    m_questions.push_back(question);

    endInsertRows();
}
