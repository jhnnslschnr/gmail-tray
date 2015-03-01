#ifndef ENTRYEVALUATOR_H
#define ENTRYEVALUATOR_H

#include "entry.h"
#include <QAbstractXmlReceiver>
#include <QXmlNamePool>
#include <QVector>

class EntryEvaluator : public QAbstractXmlReceiver
{
public:
    EntryEvaluator(const QXmlNamePool & m_namePool, int fullCount = -1);

    void atomicValue(const QVariant & value);
    void attribute(const QXmlName & name, const QStringRef & value);
    void characters(const QStringRef & value);
    void comment(const QString & value);
    void endDocument();
    void endElement();
    void endOfSequence();
    void namespaceBinding(const QXmlName & name);
    void processingInstruction(const QXmlName & target, const QString & value);
    void startDocument();
    void startElement(const QXmlName & name);
    void startOfSequence();

    const QVector<Entry> & entries();

private:
    enum State {
        NoState,
        TitleState,
        SummaryState,
        LinkState,
        ModifiedState,
        IssuedState,
        IdState,
        AuthorNameState,
        AuthorMailAddressState
    };

    State m_state;
    QXmlNamePool m_namePool;
    QVector<Entry> m_entries;
};

#endif // ENTRYEVALUATOR_H
