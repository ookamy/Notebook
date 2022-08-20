#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class NotesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit NotesModel(QObject *parent = nullptr);
    ~NotesModel();
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool hasChildren(const QModelIndex &parent) const override;

private:
    class NoteInfo;
    QVector<NoteInfo> mNotes;
};

#endif // NOTESMODEL_H
