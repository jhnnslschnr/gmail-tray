#include "trayiconnotificator.h"
#include "watcher.h"
#include "trayicon.h"

TrayIconNotificator::TrayIconNotificator(Watcher *const watcher, TrayIcon *const trayIcon, QObject *parent) :
    QObject(parent),
    m_watcher(watcher),
    m_trayIcon(trayIcon)
{
}

void TrayIconNotificator::notificate() {
    const QList<Entry> & newEntries = m_watcher->newEntries();
    if (!newEntries.isEmpty()) {
        QString title = QString::number(newEntries.size()) + QString(" new mails");
        QString message;
        for (int i = 0; i < newEntries.size(); ++i) {
            message += newEntries[i].authorName + " (" + newEntries[i].authorMailAddress + "): " + newEntries[i].title;
            if (i != newEntries.size() - 1) {
                message += '\n';
            }
        }
        m_trayIcon->showMessage(title, message);
    }
}
