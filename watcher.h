#ifndef WATCHER_H
#define WATCHER_H

#include "checker.h"
#include <QObject>
#include <QTimer>
#include <QList>
#include <QStringList>

class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = 0);

    void setUsername(const QString & username);
    void setPassword(const QString & password);
    void setCheckInterval(int msec);
    QList<Entry> newEntries() const;

signals:
    void newEntriesNotify();
    void noNewMailNotify();
    void checkerErrorNotify();

public slots:
    void check();
    void startChecking();
    void stopChecking();

private slots:
    void checkerFinished(bool success);

private:
    Checker m_checker;
    QTimer m_timer;
    QList<Entry> m_newEntries;
    QStringList m_previousEntryIds;
    bool m_firstCheck;
    bool m_previousSuccess;
};

#endif // WATCHER_H
