#include "notesmodel.h"

class NotesModel::NoteInfo
{
public:
};


NotesModel::NotesModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

NotesModel::~NotesModel()
{
}

int NotesModel::rowCount(const QModelIndex &) const
{
    return 23;//mNotes.size();
}

int NotesModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QModelIndex();

    //const int row = index.row();
    //const int column = index.column();
    switch(role)
    {
    case Qt::DisplayRole: return "54654";
    //case Qt::EditRole: return "123";
    }

    return QModelIndex();
}



Qt::ItemFlags NotesModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

bool NotesModel::hasChildren(const QModelIndex &parent) const
{
    return false;
}
