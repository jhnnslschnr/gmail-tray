#ifndef CHECKER_H
#define CHECKER_H

#include "entry.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QTimer>

class Checker : public QObject
{
    Q_OBJECT
public:
    explicit Checker(QObject *parent = 0);

    void setUsername(const QString & username);
    void setPassword(const QString & password);
    void setTimeout(int msec);
    QVector<Entry> entries() const;

signals:
    void finished(bool);

public slots:
    void check();

private slots:
    void authenticate(QNetworkReply *reply, QAuthenticator *authenticator);
    void evaluate(QNetworkReply *reply);
    void timeout();

private:
    QNetworkAccessManager m_networkAccessManager;
    QUrl m_url;
    QNetworkRequest m_networkRequest;
    QString m_defaultXmlNS;
    QString m_username;
    QString m_password;
    QNetworkReply *m_networkReply;
    bool m_authenticationAlreadyRequested;
    QTimer m_timer;
    QVector<Entry> m_entries;
};

#endif // CHECKER_H
