#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractTableModel>
#include <QVector>


#include <QDateTime>
#include <QString>

struct NoteHeader
{
    int id;
    QString title;
    QDateTime createdDateTime;
};


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
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    void setNotes(const QVector<NoteHeader>& notesHeaders);
    void insertNotes(int index, const QVector<NoteHeader>& notesHeaders);

private:
    QVector<NoteHeader> mNotes;
};

#endif // NOTESMODEL_H
