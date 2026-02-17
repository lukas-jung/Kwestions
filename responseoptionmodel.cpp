#include "responseoptionmodel.h"

#include "business_logic/responseoption.h"
#include <QMimeData>

namespace {
enum class ResponseOptionCol : int { number = 0, text = 1 };
}

ResponseOptionModel::ResponseOptionModel(kwestions::Question *question_ptr, QObject *parent)
    : QAbstractItemModel(parent)
    , question_ptr_(question_ptr)
{}

QVariant ResponseOptionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (ResponseOptionCol(section)) {
        case ResponseOptionCol::number:
            return QString("Nummer");
        case ResponseOptionCol::text:
            return QString("Antwortmöglichkeit");
        default:
            break;
        }
    }
    return QVariant();
}

QModelIndex ResponseOptionModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column);
    }

    return QModelIndex();
}

QModelIndex ResponseOptionModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int ResponseOptionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return question_ptr_->options().size();
}

int ResponseOptionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return 2;
}

QVariant ResponseOptionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (ResponseOptionCol(index.column()) == ResponseOptionCol::number) {
        switch (role) {
        case Qt::DisplayRole:
            return QVariant(index.row() + 1);
        default:
            return QVariant();
        }
    } else if (ResponseOptionCol(index.column()) == ResponseOptionCol::text) {
        if (role != Qt::DisplayRole && role != Qt::EditRole) {
            return QVariant();
        } else {
            const kwestions::ResponseOption &option = question_ptr_->options()[index.row()];

            if (option.text().empty() && role == Qt::DisplayRole) {
                return QVariant("<LEERE ANTWORT>");
            }

            return QVariant(QString::fromStdString(option.text()));
        }
    } else {
        return QVariant();
    }
}

Qt::ItemFlags ResponseOptionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags | Qt::ItemIsDropEnabled;
    }

    const Qt::ItemFlags flags = QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled;

    switch (ResponseOptionCol(index.column())) {
    case ResponseOptionCol::number:
        return flags;
    case ResponseOptionCol::text:
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    default:
        return Qt::NoItemFlags;
    }
}

bool ResponseOptionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // std::cout << value.typeName() << std::endl;
    if (data(index, role) != value) {
        question_ptr_->set_option_at_index(index.row(),
                                           kwestions::ResponseOption(
                                               value.toString().toStdString()));

        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

bool ResponseOptionModel::dropMimeData(
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

bool ResponseOptionModel::move_row_from_to(int source_row, int destination_row)
{
    if (!beginMoveRows(QModelIndex(), source_row, source_row, QModelIndex(), destination_row)) {
        return false;
    }

    // The business logic can't work with the +1 shifted indices that appear when moving downwards.
    int destination_index = destination_row;
    if (destination_row > source_row) {
        destination_index--;
    }

    question_ptr_->move_option_from_to(source_row, destination_index);

    endMoveRows();
    return true;
}

Qt::DropActions ResponseOptionModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

void ResponseOptionModel::append_empty_response_option()
{
    int insertion_position = question_ptr_->options().size();
    beginInsertRows(QModelIndex(), insertion_position, insertion_position);

    question_ptr_->append_option(kwestions::ResponseOption(""));

    endInsertRows();
}

void ResponseOptionModel::reset_question(kwestions::Question *question_ptr)
{
    beginResetModel();
    question_ptr_ = question_ptr;
    endResetModel();
}
