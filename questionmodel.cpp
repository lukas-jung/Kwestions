#include "questionmodel.h"
#include <QMimeData>

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

Qt::ItemFlags QuestionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags | Qt::ItemIsDropEnabled;
    }

    return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled;
}

bool QuestionModel::dropMimeData(
    const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (parent.isValid()) {
        return false;
    }

    if (data == nullptr || action != Qt::MoveAction) {
        return false;
    }

    QList<QString> mime_types = mimeTypes();
    if (mime_types.isEmpty()) {
        return false;
    }

    QString mime_type = mime_types.at(0);
    if (!data->hasFormat(mime_type)) {
        return false;
    }

    if (row > rowCount(parent)) {
        row = rowCount(parent);
    }

    if (row == -1) {
        row = rowCount(parent);
    }

    QByteArray encoded = data->data(mime_type);
    QDataStream stream(&encoded, QDataStream::ReadOnly);

    int source_row;
    stream >> source_row;

    return move_row_from_to(source_row, row);
}

Qt::DropActions QuestionModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

bool QuestionModel::move_row_from_to(int source_row, int destination_row)
{
    if (!beginMoveRows(QModelIndex(), source_row, source_row, QModelIndex(), destination_row)) {
        return false;
    }

    // The business logic can't work with the +1 shifted indices that appear when moving downwards.
    int destination_index = destination_row;
    if (destination_row > source_row) {
        destination_index--;
    }

    questionnaire_ptr_->move_question_from_to(source_row, destination_index);

    endMoveRows();
    return true;
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
