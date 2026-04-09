#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H

#include "business_logic/question.h"
#include "business_logic/questionnaire.h"
#include <QAbstractItemModel>

class QuestionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    QuestionModel(kwestions::Questionnaire *questionnaire_ptr, QObject *parent = nullptr);

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

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Drag & Drop:
    bool dropMimeData(const QMimeData *data,
                      Qt::DropAction action,
                      int row,
                      int column,
                      const QModelIndex &parent) override;

    Qt::DropActions supportedDropActions() const override;

    // Custom methods:

    bool move_row_from_to(int source_row, int destination_row);
    void append_question(kwestions::Question question);
    void delete_question_at(std::size_t i);
    void set_question_at(std::size_t i, kwestions::Question question);

    void set_questionnaire(kwestions::Questionnaire *questionnaire_ptr);

private:
    kwestions::Questionnaire *questionnaire_ptr_;
};

#endif // QUESTIONMODEL_H
