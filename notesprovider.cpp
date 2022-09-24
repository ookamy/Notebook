#include "notesprovider.h"

#include <QDirIterator>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


const char* jsonNoteTitle = "title";
const char* jsonNoteContent = "content";

class NotesProvider::Impl
{
public:
    Impl(const QString& notesDirPath)
        : mPath(notesDirPath)
    {
        QDir notesDir;
        if (!notesDir.mkpath(mPath))
        {
            //TODO: ошибка
        }

        QDirIterator it(mPath, {"*.json"});
        while(it.hasNext())
        {
            const QString filePath = it.next();
            auto optHeader = loadNoteHeaderFromFile(filePath);
            if (!optHeader.has_value())
            {
                //TODO: ошибка
                continue;
            }

            NoteHeader& header = optHeader.value();
            header.id = getNextId();
            mHeaders[header.id] = header;
            mFiles[header.id] = filePath;
        }
    }

    bool removeNote(int id)
    {
        if (!mFiles.contains(id))
        {
            //TODO: ошибка
            return false;
        }

        if (!QFile::remove(mFiles[id]))
        {
            //TODO: warning
        }

        mFiles.remove(id);
        mHeaders.remove(id);

        return true;
    }

    bool appendNote(const Note& note)
    {
        QUuid uuid(note.header.title);
        QDir notesDir(mPath);
        QString filePath = notesDir.absoluteFilePath(uuid.toString(QUuid::Id128));

        //TODO: already exists?

        if (!writeNoteToFile(note, filePath))
        {
            //TODO: ошибка
            return false;
        }

        NoteHeader header = note.header;
        header.id = getNextId();
        header.createdDateTime = QDateTime::currentDateTimeUtc();
        mHeaders[header.id] = header;
        mFiles[header.id] = filePath;

        return true;
    }

    bool updateNote(const Note& note)
    {
        auto optNote = getNote(note.header.id);
        if (!optNote.has_value())
        {
            //TODO: ошибка
            return false;
        }

        mHeaders[note.header.id] = note.header;
        return writeNoteToFile(note, mFiles[note.header.id]);
    }

    QVector<NoteHeader> getHeaders() const
    {
        QVector<NoteHeader> allHeaders;
        for (const auto& header: mHeaders)
            allHeaders << header;
        return allHeaders;
    }

    std::optional<Note> getNote(int id) const
    {
        auto it = mHeaders.find(id);
        if (it == mHeaders.end())
            return std::nullopt;

        NoteHeader header = it.value();
        auto optContent = loadNoteContentFromFile(mFiles[id]);
        if (!optContent.has_value())
        {
            //TODO: ошибка
            return std::nullopt;
        }

        return Note{header, optContent.value()};
    }

private:
    bool writeNoteToFile(const Note& note, QString filePath) const
    {
        QJsonObject mainObject;
        mainObject[jsonNoteTitle] = note.header.title;
        //TODO: date
        mainObject[jsonNoteContent] = note.content.text;

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly))
        {
            //TODO: ошибка
            return false;
        }

        QJsonDocument doc(mainObject);
        if (file.write(doc.toJson(QJsonDocument::Compact)) < 0)
        {
            //TODO: ошибка
            return false;
        }

        return true;
    }

    std::optional<NoteHeader> loadNoteHeaderFromFile(QString filePath) const
    {
        QJsonDocument doc = loadJsonDocument(filePath);
        if (doc.isNull())
        {
            //TODO: ошибка
            return std::nullopt;
        }

        QJsonValue jsonValue = doc[jsonNoteTitle];
        if (!jsonValue.isString())
        {
            //TODO: ошибка
            return std::nullopt;
        }


        NoteHeader header;
        header.id = 0;
        header.title = jsonValue.toString();
        //TODO: дата создания

        return header;
    }

    std::optional<NoteContent> loadNoteContentFromFile(QString filePath) const
    {
        QJsonDocument doc = loadJsonDocument(filePath);
        if (doc.isNull())
        {
            //TODO: ошибка
            return std::nullopt;
        }

        QJsonValue jsonValue = doc[jsonNoteContent];
        if (!jsonValue.isString())
        {
            //TODO: ошибка
            return std::nullopt;
        }

        NoteContent content;
        content.text = jsonValue.toString();

        return content;
    }

    QJsonDocument loadJsonDocument(QString filePath) const
    {
        QFile noteFile(filePath);
        if (!noteFile.open(QIODevice::ReadOnly))
        {
            //TODO: ошибка
            return QJsonDocument();
        }

        QJsonDocument doc = QJsonDocument::fromJson(noteFile.readAll());
        if (!doc.isObject())
        {
            //TODO: ошибка
            return QJsonDocument();
        }

        return doc;
    }

    int getNextId()
    {
        static int lastId = 0;
        return ++lastId;
    }

    QString mPath;
    QHash<int, QString> mFiles;
    QHash<int, NoteHeader> mHeaders;
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

