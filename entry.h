#ifndef ENTRY_H
#define ENTRY_H

#include <QString>
#include <QUrl>
#include <QDateTime>

struct Entry
{
public:
    Entry();
    QString title;
    QString summary;
    QUrl link;
    QDateTime modified;
    QDateTime issued;
    QString id;
    QString authorName;
    QString authorMailAddress;
};

#endif // ENTRY_H
