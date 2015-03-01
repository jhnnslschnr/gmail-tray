#include "watcher.h"

Watcher::Watcher(QObject *parent) :
    QObject(parent),
    m_firstCheck(true),
    m_previousSuccess(false)
{
    connect(&m_timer, SIGNAL(timeout()), &m_checker, SLOT(check()));
    connect(&m_checker, SIGNAL(finished(bool)), this, SLOT(checkerFinished(bool)));
    m_timer.setInterval(5000);
}

void Watcher::setUsername(const QString & username) {
    m_checker.setUsername(username);
}

void Watcher::setPassword(const QString & password) {
    m_checker.setPassword(password);
}

void Watcher::setCheckInterval(const int msec) {
    m_timer.setInterval(msec);
}

QList<Entry> Watcher::newEntries() const {
    return m_newEntries;
}

void Watcher::check() {
    m_checker.check();
}

void Watcher::startChecking() {
    m_checker.check();
    m_timer.start();
}

void Watcher::stopChecking() {
    m_timer.stop();
}

void Watcher::checkerFinished(bool success) {
    if (success) {
        const QVector<Entry> & entries = m_checker.entries();
        m_newEntries.clear();
        for (int i = 0; i < entries.size(); ++i) {
            if (!m_previousEntryIds.contains(entries[i].id)) {
                m_newEntries.append(entries[i]);
            }
        }
        if (entries.isEmpty() && (!m_previousEntryIds.isEmpty() || !m_previousSuccess)) {
            emit noNewMailNotify();
        } else if (!m_newEntries.isEmpty()) {
            emit newEntriesNotify();
        }
        m_previousEntryIds.clear();
        for (int i = 0; i < entries.size(); ++i) {
            m_previousEntryIds.append(entries[i].id);
        }
    } else {
        if (m_previousSuccess || m_firstCheck) {
            emit checkerErrorNotify();
        }
    }
    m_firstCheck = false;
    m_previousSuccess = success;
}
