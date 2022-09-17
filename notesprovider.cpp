#include "notesprovider.h"

#include <QDirIterator>


class NotesProvider::Impl
{
public:
    Impl(const QString& path)
        : mPath(path)
    {
        QDir rootDir(path);
        if (!rootDir.exists())
        {
            //TODO: создать? выбрать стандартный путь?
        }

        rootDir.mkdir("notes");
        QDir notesDir(rootDir.filePath("notes"));//TODO: notes в константы

        QDirIterator iter(path);

    }

    bool removeNote(int id)
    {
        return false;
    }

    bool appendNote(const Note& note)
    {
        return false;
    }

    bool updateNote(const Note& note)
    {
        return false;
    }

    QVector<NoteHeader> getHeaders() const
    {
        return {};
    }

    std::optional<Note> getNote(int id) const
    {
        return {};
    }

private:
    QString mPath;
};



NotesProvider::NotesProvider(const QString& path)
    : mImpl(std::make_unique<Impl>(path))
{
}

bool NotesProvider::removeNote(int id)
{
    return mImpl->removeNote(id);
}

bool NotesProvider::appendNote(const Note& note)
{
    return mImpl->appendNote(note);
}

bool NotesProvider::updateNote(const Note& note)
{
    return mImpl->updateNote(note);
}

QVector<NoteHeader> NotesProvider::getHeaders() const
{
    return mImpl->getHeaders();
}

std::optional<Note> NotesProvider::getNote(int id) const
{
    return mImpl->getNote(id);
}

