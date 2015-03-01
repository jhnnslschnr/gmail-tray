#include "entryevaluator.h"
#include <QDateTime>
#include <QUrl>
#include <QDebug>

EntryEvaluator::EntryEvaluator(const QXmlNamePool & namePool, const int fullCount) :
    m_state(NoState),
    m_namePool(namePool)
{
    if (fullCount != -1) {
        m_entries.reserve(fullCount);
    }
}

void EntryEvaluator::atomicValue(const QVariant & /*value*/) {

}

void EntryEvaluator::attribute(const QXmlName & name, const QStringRef & value) {
    if (m_state == LinkState && name.localName(m_namePool) == "href") {
        m_entries.last().link = QUrl(value.toString());
    }
}

void EntryEvaluator::characters(const QStringRef & value) {
    switch (m_state) {
    case TitleState:
        m_entries.last().title = value.toString();
        break;
    case SummaryState:
        m_entries.last().summary = value.toString();
        break;
    case ModifiedState:
        m_entries.last().modified = QDateTime::fromString(value.toString(), Qt::ISODate);
        break;
    case IssuedState:
        m_entries.last().issued = QDateTime::fromString(value.toString(), Qt::ISODate);
        break;
    case IdState:
        m_entries.last().id = value.toString();
        break;
    case AuthorNameState:
        m_entries.last().authorName = value.toString();
        break;
    case AuthorMailAddressState:
        m_entries.last().authorMailAddress = value.toString();
        break;
    default:
        break;
    }
}

void EntryEvaluator::comment(const QString & /*value*/) {

}

void EntryEvaluator::endDocument() {

}

void EntryEvaluator::endElement() {

}

void EntryEvaluator::endOfSequence() {

}

void EntryEvaluator::namespaceBinding(const QXmlName & /*name*/) {

}

void EntryEvaluator::processingInstruction(const QXmlName & /*target*/, const QString & /*value*/) {

}

void EntryEvaluator::startDocument() {

}

void EntryEvaluator::startElement(const QXmlName & name) {
    const QString localName = name.localName(m_namePool);
    if (localName == "entry") {
        m_entries.resize(m_entries.size() + 1);
    } else if (localName == "title") {
        m_state = TitleState;
    } else if (localName == "summary") {
        m_state = SummaryState;
    } else if (localName == "link") {
        m_state = LinkState;
    } else if (localName == "modified") {
        m_state = ModifiedState;
    } else if (localName == "issued") {
        m_state = IssuedState;
    } else if (localName == "id") {
        m_state = IdState;
    } else if (localName == "name") {
        m_state = AuthorNameState;
    } else if (localName == "email") {
        m_state = AuthorMailAddressState;
    }
}

void EntryEvaluator::startOfSequence() {

}

const QVector<Entry> & EntryEvaluator::entries() {
    return m_entries;
}
