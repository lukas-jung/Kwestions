#ifndef QUESTIONNAIRESELECTIONMODEL_H
#define QUESTIONNAIRESELECTIONMODEL_H

#include "business_logic/questionnaire.h"
#include <memory>
#include <QAbstractListModel>

//TODO: Selection model is a bad name because it is used in Qt. Rename it!

class QuestionnaireSelectionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QuestionnaireSelectionModel(
        std::vector<std::unique_ptr<kwestions::Questionnaire>> *questionnaires_ptr,
        QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Custom methods:
    void append_questionnaire(std::unique_ptr<kwestions::Questionnaire> questionnaire_uptr);

private:
    std::vector<std::unique_ptr<kwestions::Questionnaire>> *questionnaires_ptr_;
};

#endif // QUESTIONNAIRESELECTIONMODEL_H
