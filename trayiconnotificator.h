#ifndef TRAYICONNOTIFICATOR_H
#define TRAYICONNOTIFICATOR_H

#include <QObject>

class Watcher;
class TrayIcon;

class TrayIconNotificator : public QObject
{
    Q_OBJECT
public:
    explicit TrayIconNotificator(Watcher *watcher, TrayIcon *trayIcon, QObject *parent = 0);

signals:

public slots:
    void notificate();

private:
    Watcher *m_watcher;
    TrayIcon *m_trayIcon;
};

#endif // TRAYICONNOTIFICATOR_H
