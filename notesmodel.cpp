#include "notesmodel.h"

namespace
{
    QVariant ColumnFromNotesHeader(const NoteHeader& noteHeader, int column)
    {
        switch(column)
        {
            case 0: return QVariant(noteHeader.title);
            case 1: return QVariant(noteHeader.createdDateTime);
        }

        return QVariant();
    }
}


NotesModel::NotesModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

NotesModel::~NotesModel()
{
}

int NotesModel::rowCount(const QModelIndex &) const
{
    return mNotes.size();
}

int NotesModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();
    const int column = index.column();
    switch(role)
    {
    case Qt::DisplayRole: return ColumnFromNotesHeader(mNotes[row], column);
    }

    return QVariant();
}


Qt::ItemFlags NotesModel::flags([[maybe_unused]] const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
}

bool NotesModel::hasChildren([[maybe_unused]] const QModelIndex &parent) const
{
    return false;
}

bool NotesModel::removeRows(int row, int count, const QModelIndex &)
{
    if (row < 0 || row >= mNotes.size() || count < 1 || row + count >= mNotes.size())
        return false;

    beginRemoveRows(QModelIndex(), row, row + (count - 1));
    mNotes.remove(row, count);
    endRemoveRows();

    return true;
}

void NotesModel::setNotes(const QVector<NoteHeader> &notesHeaders)
{
    beginResetModel();
    mNotes = notesHeaders;
    endResetModel();
}

void NotesModel::insertNotes(int index, const QVector<NoteHeader> &notesHeaders)
{
    if (notesHeaders.isEmpty())
        return;

    beginInsertRows(QModelIndex(), index, index + (notesHeaders.size() - 1));
    mNotes.append(notesHeaders);
    std::rotate(mNotes.begin() + index, mNotes.end() - notesHeaders.size(), mNotes.end());
    endInsertRows();
}
