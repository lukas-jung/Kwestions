#ifndef RESPONSEOPTIONMODEL_H
#define RESPONSEOPTIONMODEL_H

#include "business_logic/question.h"
#include <QAbstractItemModel>

class ResponseOptionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ResponseOptionModel(kwestions::Question *question_ptr, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void append_empty_response_option();

    void reset_question(kwestions::Question *question_ptr);

private:
    kwestions::Question *question_ptr_;
};

#endif // RESPONSEOPTIONMODEL_H
