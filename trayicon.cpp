#include "trayicon.h"
#include <QDebug>

TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent),
    m_newMailIcon(":/icons/newmail.png"),
    m_noNewMailIcon(":/icons/nonewmail.png"),
    m_icon(noIcon)
{
    m_errorIcon = QIcon::fromTheme("dialog-error");
}

TrayIcon::~TrayIcon() {
}

void TrayIcon::updateIcon(const Icon icon) {
    if (icon == m_icon) return;
    m_icon = icon;
    const QIcon *iconToBeSet = 0;
    switch (m_icon) {
    case newMailIcon:
        iconToBeSet = &m_newMailIcon;
        break;
    case noNewMailIcon:
        iconToBeSet = &m_noNewMailIcon;
        break;
    case errorIcon:
        iconToBeSet = &m_errorIcon;
        break;
    default:
        break;
    }
    if (iconToBeSet != 0) {
        setIcon(*iconToBeSet);
        show();
    } else {
        hide();
    }
}
