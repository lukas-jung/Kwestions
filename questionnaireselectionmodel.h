#ifndef QUESTIONNAIRESELECTIONMODEL_H
#define QUESTIONNAIRESELECTIONMODEL_H

#include "business_logic/questionnaire.h"
#include <QAbstractListModel>

class QuestionnaireSelectionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QuestionnaireSelectionModel(std::vector<kwestions::Questionnaire> *questionnaires,
                                QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<kwestions::Questionnaire> *questionnaires_;
};

#endif // QUESTIONNAIRESELECTIONMODEL_H
