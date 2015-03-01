#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    enum Icon {
        noIcon,
        newMailIcon,
        noNewMailIcon,
        errorIcon
    };

    explicit TrayIcon(QObject *parent = 0);

    ~TrayIcon();

signals:

public slots:
    void updateIcon(Icon icon);

private:
    QIcon m_newMailIcon;
    QIcon m_noNewMailIcon;
    QIcon m_errorIcon;

    Icon m_icon;
};

#endif // TRAYICON_H
