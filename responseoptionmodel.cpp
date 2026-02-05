#include "responseoptionmodel.h"

#include "business_logic/responseoption.h"

ResponseOptionModel::ResponseOptionModel(qwestions::Question *question_ptr, QObject *parent)
    : QAbstractItemModel(parent)
    , question_ptr_(question_ptr)
{}

QVariant ResponseOptionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QString("Antwortmöglichkeit");
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

    return 1;
}

QVariant ResponseOptionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const qwestions::ResponseOption &option = question_ptr_->options()[index.row()];
        return QVariant(QString::fromStdString(option.text()));
    }

    return QVariant();
}

bool ResponseOptionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        question_ptr_->set_option_at_index(index.row(),
                                           qwestions::ResponseOption(
                                               value.toString().toStdString()));

        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ResponseOptionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void ResponseOptionModel::append_empty_response_option()
{
    int insertion_position = question_ptr_->options().size();
    beginInsertRows(QModelIndex(), insertion_position, insertion_position);

    question_ptr_->append_option(qwestions::ResponseOption(""));

    endInsertRows();
}

void ResponseOptionModel::reset_question(qwestions::Question *question_ptr)
{
    beginResetModel();
    question_ptr_ = question_ptr;
    endResetModel();
}
