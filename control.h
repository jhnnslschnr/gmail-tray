#ifndef CONTROL_H
#define CONTROL_H

#include "watcher.h"
#include "trayicon.h"
#include "trayiconnotificator.h"
#include "configdialog.h"
#include <QObject>
#include <QMenu>

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *pa3rent = 0);

private:
    void buildTrayIconContextMenu();
    void applySettings();

signals:

public slots:

private slots:
    void onNewEntriesNotify();
    void onNoNewMailNotify();
    void onCheckerErrorNotify();
    void onConfigDialogAccepted();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason activationReason);
    void openInbox();

private:
    QUrl m_inboxUrl;
    Watcher m_watcher;
    TrayIcon m_trayIcon;
    TrayIconNotificator m_trayIconNotificator;
    QAction m_quitAction;
    QAction m_configureAction;
    QAction m_checkAction;
    QAction m_openInboxAction;
    QMenu m_trayIconMenu;
    ConfigDialog m_configDialog;
};

#endif // CONTROL_H
