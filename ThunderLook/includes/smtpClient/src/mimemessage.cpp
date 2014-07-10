#include "mimemessage.h"

#include <QDateTime>
#include "quotedprintable.h"
#include <typeinfo>

/* [1] Constructors and Destructors */
MimeMessage::MimeMessage(bool createAutoMimeContent) :
    hEncoding(MimePart::_8Bit)
{
    if (createAutoMimeContent)
        this->content = new MimeMultiPart();
    
    autoMimeContentCreated = createAutoMimeContent;
}

MimeMessage::~MimeMessage()
{
    if (this->autoMimeContentCreated)
    {
      this->autoMimeContentCreated = false;
      delete (this->content);
    }
}

QList<MimeAttachment *> MimeMessage::getAttachment()
{
    return attachment;
}

void MimeMessage::addAttachment(MimeAttachment * mimeAttachment)
{
    this->attachment.push_back(mimeAttachment);
}

/* [2] Getters and Setters */
MimePart& MimeMessage::getContent() {
    return *content;
}

void MimeMessage::setContent(MimePart *content) {
    if (this->autoMimeContentCreated)
    {
      this->autoMimeContentCreated = false;
      delete (this->content);
    }
    this->content = content;
}

void MimeMessage::setSender(EmailAddress* e)
{
    this->sender = e;
}

void MimeMessage::addRecipient(EmailAddress* rcpt, RecipientType type)
{
    switch (type)
    {
    case To:
        recipientsTo << rcpt;
        break;
    case Cc:
        recipientsCc << rcpt;
        break;
    case Bcc:
        recipientsBcc << rcpt;
        break;
    }
}

void MimeMessage::addTo(EmailAddress* rcpt) {
    this->recipientsTo << rcpt;
}

void MimeMessage::addCc(EmailAddress* rcpt) {
    this->recipientsCc << rcpt;
}

void MimeMessage::addBcc(EmailAddress* rcpt) {
    this->recipientsBcc << rcpt;
}

void MimeMessage::setSubject(const QString & subject)
{
    this->subject = subject;
}

const QString & MimeMessage::getText() const
{
    return this->textMail;
}

void MimeMessage::setText(const QString & text)
{
    this->textMail = text;
}

const QString & MimeMessage::getHtml() const
{
    return this->html;
}
void MimeMessage::setHtml(const QString & html)
{
    this->html = html;
}

const QString & MimeMessage::getSubject() const
{
    return subject;
}

const QString & MimeMessage::getIndice() const
{
    return this->indice;
}

void MimeMessage::setIndice(const QString & indice)
{
    this->indice = indice;
}

const QString & MimeMessage::getDate() const
{
    return this->date;
}

void MimeMessage::setDate(const QString & date)
{
    this->date = date;
}

void MimeMessage::addPart(MimePart *part)
{
    if (typeid(*content) == typeid(MimeMultiPart))
    {
        // qDebug() << "Ok addPart" << part->getContent() << endl;
        ((MimeMultiPart*) content)->addPart(part);
    };
}

void MimeMessage::setHeaderEncoding(MimePart::Encoding hEnc)
{
    this->hEncoding = hEnc;
}

const EmailAddress & MimeMessage::getSender() const
{
    return *sender;
}

const QList<EmailAddress*> & MimeMessage::getRecipients(RecipientType type) const
{
    switch (type)
    {
    default:
    case To:
        return recipientsTo;
    case Cc:
        return recipientsCc;
    case Bcc:
        return recipientsBcc;
    }
}

const QList<MimePart*> & MimeMessage::getParts() const
{
    if (typeid(*content) == typeid(MimeMultiPart)) {
        return ((MimeMultiPart*) content)->getParts();
    }
    else {
        QList<MimePart*> *res = new QList<MimePart*>();
        res->append(content);
        return *res;
    }
}

/* [2] --- */


/* [3] Public Methods */

QString MimeMessage::toString()
{
    QString mime;


    /* =========== MIME HEADER ============ */

    /* ---------- Sender / From ----------- */
    mime = "From:";
    if (sender->getName() != "")
    {
        switch (hEncoding)
        {
        case MimePart::Base64:
            mime += " =?utf-8?B?" + QByteArray().append(sender->getName()).toBase64() + "?=";
            break;
        case MimePart::QuotedPrintable:
            mime += " =?utf-8?Q?" + QuotedPrintable::encode(QByteArray().append(sender->getName())).replace(' ', "_").replace(':',"=3A") + "?=";
            break;
        default:
            mime += " " + sender->getName();
        }
    }



    mime += " <" + sender->getAddress() + ">\r\n";
    /* ---------------------------------- */


    /* ------- Recipients / To ---------- */    
    mime += "To:";
    QList<EmailAddress*>::iterator it;  int i;
    for (i = 0, it = recipientsTo.begin(); it != recipientsTo.end(); ++it, ++i)
    {
        if (i != 0) { mime += ","; }

        if ((*it)->getName() != "")
        {
            switch (hEncoding)
            {
            case MimePart::Base64:
                mime += " =?utf-8?B?" + QByteArray().append((*it)->getName()).toBase64() + "?=";
                break;
            case MimePart::QuotedPrintable:
                mime += " =?utf-8?Q?" + QuotedPrintable::encode(QByteArray().append((*it)->getName())).replace(' ', "_").replace(':',"=3A") + "?=";
                break;
            default:
                mime += " " + (*it)->getName();
            }
        }
        mime += " <" + (*it)->getAddress() + ">";
    }

    mime += "\r\n";
    /* ---------------------------------- */

    /* ------- Recipients / Cc ---------- */
    if (recipientsCc.size() != 0) {
        mime += "Cc:";
    }
    for (i = 0, it = recipientsCc.begin(); it != recipientsCc.end(); ++it, ++i)
    {
        if (i != 0) { mime += ","; }

        if ((*it)->getName() != "")
        {
            switch (hEncoding)
            {
            case MimePart::Base64:
                mime += " =?utf-8?B?" + QByteArray().append((*it)->getName()).toBase64() + "?=";
                break;
            case MimePart::QuotedPrintable:
                mime += " =?utf-8?Q?" + QuotedPrintable::encode(QByteArray().append((*it)->getName())).replace(' ', "_").replace(':',"=3A") + "?=";
                break;
            default:
                mime += " " + (*it)->getName();
            }
        }
        mime += " <" + (*it)->getAddress() + ">";
                qDebug() << "After getCC" << endl;
    }
    if (recipientsCc.size() != 0) {
        mime += "\r\n";
    }


    /* ---------------------------------- */

    /* ------------ Subject ------------- */
    mime += "Subject: ";

    switch (hEncoding)
    {
    case MimePart::Base64:
        mime += "=?utf-8?B?" + QByteArray().append(subject).toBase64() + "?=";
        break;
    case MimePart::QuotedPrintable:
        mime += "=?utf-8?Q?" + QuotedPrintable::encode(QByteArray().append(subject)).replace(' ', "_").replace(':',"=3A") + "?=";
        break;
    default:
        mime += subject;
    }
    /* ---------------------------------- */

    mime += "\r\n";
    mime += "MIME-Version: 1.0\r\n";

    mime += content->toString();
    return mime;
}

/* [3] --- */
