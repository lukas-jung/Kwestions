#include "responseoptionmodel.h"

#include "business_logic/responseoption.h"

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

bool ResponseOptionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        question_ptr_->set_option_at_index(index.row(),
                                           kwestions::ResponseOption(
                                               value.toString().toStdString()));

        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ResponseOptionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    switch (ResponseOptionCol(index.column())) {
    case ResponseOptionCol::number:
        return QAbstractItemModel::flags(index);
    case ResponseOptionCol::text:
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    default:
        return Qt::NoItemFlags;
    }
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
