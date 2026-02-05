#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H

#include "business_logic/question.h"
#include <QAbstractItemModel>

class QuestionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit QuestionModel(QObject *parent = nullptr);

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

    // Custom methods:

    void append_question(qwestions::Question question);

private:
    std::vector<qwestions::Question> questions_;
};

#endif // QUESTIONMODEL_H
