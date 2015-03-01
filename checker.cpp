#include "checker.h"
#include "entryevaluator.h"
#include <QNetworkReply>
#include <QAuthenticator>
#include <QXmlQuery>
#include <QBuffer>

Checker::Checker(QObject *parent) :
    QObject(parent),
    m_url("https://mail.google.com/mail/feed/atom"),
    m_networkRequest(m_url),
    m_defaultXmlNS("http://purl.org/atom/ns#"),
    m_networkReply(0),
    m_authenticationAlreadyRequested(false)
{
    connect(&m_networkAccessManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*,QAuthenticator*)), Qt::DirectConnection);
    connect(&m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(evaluate(QNetworkReply*)));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    m_timer.setSingleShot(true);
    m_timer.setInterval(6000);
}

void Checker::setUsername(const QString & username) {
    m_username = username;
}

void Checker::setPassword(const QString & password) {
    m_password = password;
}

void Checker::setTimeout(const int msec) {
    m_timer.setInterval(msec);
}

QVector<Entry> Checker::entries() const {
    return m_entries;
}

void Checker::check() {
    m_networkReply = m_networkAccessManager.get(m_networkRequest);
    m_authenticationAlreadyRequested = false;
    m_timer.start();
}

void Checker::authenticate(QNetworkReply *reply, QAuthenticator *authenticator) {
    if (reply == m_networkReply && !m_authenticationAlreadyRequested) {
        authenticator->setUser(m_username);
        authenticator->setPassword(m_password);
        m_authenticationAlreadyRequested = true;
    }
}

void Checker::evaluate(QNetworkReply *reply) {
    m_timer.stop();
    if (reply->error() == QNetworkReply::NoError) {
        QBuffer buffer;
        buffer.setData(reply->readAll());
        buffer.open(QIODevice::ReadOnly);
        QXmlQuery xmlQuery;
        EntryEvaluator entryEvaluator(xmlQuery.namePool());
        xmlQuery.bindVariable("atomfeed", &buffer);
        xmlQuery.setQuery("declare default element namespace \""+m_defaultXmlNS+"\"; doc($atomfeed)/feed/entry");
        xmlQuery.evaluateTo(&entryEvaluator);
        m_entries = entryEvaluator.entries();
        emit finished(true);
    } else {
        emit finished(false);
    }
    reply->deleteLater();
}

void Checker::timeout() {
    if (m_networkReply != 0) {
        m_networkReply->close();
        emit finished(false);
    }
}
