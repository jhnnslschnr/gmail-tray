#include "control.h"
#include <QApplication>
#include <QSettings>
#include <QDesktopServices>

Control::Control(QObject *parent) :
    QObject(parent),
    m_inboxUrl("https://mail.google.com/mail/u/0/#inbox"),
    m_trayIconNotificator(&m_watcher, &m_trayIcon),
    m_quitAction(QIcon::fromTheme("application-exit"), "Quit", this),
    m_configureAction(QIcon::fromTheme("configure"), "Configure", this),
    m_checkAction(QIcon::fromTheme("view-refresh"), "Check", this),
    m_openInboxAction(QIcon::fromTheme("internet-web-browser"), "Open inbox", this)
{
    connect(&m_watcher, SIGNAL(newEntriesNotify()), this, SLOT(onNewEntriesNotify()));
    connect(&m_watcher, SIGNAL(noNewMailNotify()), this, SLOT(onNoNewMailNotify()));
    connect(&m_watcher, SIGNAL(checkerErrorNotify()), this, SLOT(onCheckerErrorNotify()));
    connect(&m_configDialog, SIGNAL(accepted()), this, SLOT(onConfigDialogAccepted()));
    connect(&m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    connect(&m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(&m_configureAction, SIGNAL(triggered()), &m_configDialog, SLOT(show()));
    connect(&m_checkAction, SIGNAL(triggered()), &m_watcher, SLOT(check()));
    connect(&m_openInboxAction, SIGNAL(triggered()), this, SLOT(openInbox()));

    buildTrayIconContextMenu();
    m_trayIcon.setContextMenu(&m_trayIconMenu);

    QSettings settings;
    QVariant firststart = settings.value("firststart");
    if (!firststart.isValid() || firststart.toBool()) { // first start
        m_configDialog.show();
        settings.setValue("firststart", false);
    } else { // not first start
        applySettings();
        m_watcher.startChecking();
    }
}

void Control::buildTrayIconContextMenu() {
    m_trayIconMenu.addAction(&m_openInboxAction);
    m_trayIconMenu.addAction(&m_checkAction);
    m_trayIconMenu.addAction(&m_configureAction);
    m_trayIconMenu.addAction(&m_quitAction);
}

void Control::applySettings() {
    QSettings settings;
    m_watcher.setUsername(settings.value("username").toString());
    m_watcher.setPassword(settings.value("password").toString());
    m_watcher.setCheckInterval(settings.value("interval").toInt());
}

void Control::onNewEntriesNotify() {
    m_trayIcon.updateIcon(TrayIcon::newMailIcon);
    m_trayIconNotificator.notificate();
}

void Control::onNoNewMailNotify() {
    m_trayIcon.updateIcon(TrayIcon::noNewMailIcon);
}

void Control::onCheckerErrorNotify() {
    m_trayIcon.updateIcon(TrayIcon::errorIcon);
}

void Control::onConfigDialogAccepted() {
    applySettings();
    m_watcher.check();
}

void Control::openInbox() {
    QDesktopServices::openUrl(m_inboxUrl);
}

void Control::onTrayIconActivated(QSystemTrayIcon::ActivationReason activationReason) {
    switch (activationReason) {
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::MiddleClick:
        openInbox();
        break;
    default:
        break;
    }
}
