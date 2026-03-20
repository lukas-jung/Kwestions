#include "questionnaireselectionmodel.h"

QuestionnaireSelectionModel::QuestionnaireSelectionModel(
    std::vector<std::unique_ptr<kwestions::Questionnaire>> *questionnaires, QObject *parent)
    : QAbstractListModel(parent)
    , questionnaires_(questionnaires)
{}

int QuestionnaireSelectionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return questionnaires_->size();
}

QVariant QuestionnaireSelectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return QVariant(questionnaires_->at(index.row())->title().c_str());
    } else {
        return QVariant();
    }
}

void QuestionnaireSelectionModel::append_questionnaire(
    std::unique_ptr<kwestions::Questionnaire> questionnaire_uptr)
{
    int insertion_position = questionnaires_->size();
    beginInsertRows(QModelIndex(), insertion_position, insertion_position);

    questionnaires_->push_back(std::move(questionnaire_uptr));

    endInsertRows();
}
