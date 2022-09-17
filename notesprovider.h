#ifndef NOTESPROVIDER_H
#define NOTESPROVIDER_H

#include <memory>
#include <QString>
#include <QDateTime>
#include <optional>

struct NoteHeader
{
    int id;
    QString title;
    QDateTime createdDateTime;
};

class Note
{
    NoteHeader header;
    QString content;
};


class NotesProvider
{
public:
    NotesProvider(const QString& path);

    bool removeNote(int id);
    bool appendNote(const Note& note);
    bool updateNote(const Note& note);
    QVector<NoteHeader> getHeaders() const;
    std::optional<Note> getNote(int id) const;

private:
    NotesProvider(const NotesProvider&) = delete;
    NotesProvider& operator=(const NotesProvider&) = delete;

    class Impl;
    std::unique_ptr<Impl> mImpl;
};

#endif // NOTESPROVIDER_H
