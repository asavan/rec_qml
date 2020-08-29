#include "Examen/Examination.h"
#include "documenthandler.h"

#include <fstream>
#include <QQuickTextDocument>

DocumentHandler::DocumentHandler()
    : m_target(nullptr),
      m_doc(nullptr),
      ex(new Examination()),
      curr(0),
      m_dbloaded(false)
{
    std::ifstream ifs("db.rec", std::ios_base::binary);
    if(ifs)
    {
        bool res = ex->LoadFromFile(ifs);
        if(res)
        {
            ex->MakeAnswerOrder();
        }
    } else {
        error("Не найдена база с вопросами");
        return;
    }
    setDbloaded(true);
    QString title = QString::fromLocal8Bit(ex->getTitle().c_str());

    setDocumentTitle(title);
    QString answer("Ответ");
    QByteArray byteArray = answer.toLocal8Bit();
    std::string str(byteArray.constData(), static_cast<size_t>(byteArray.length()));
    ex->setAnswer_rus(str);

    QString question("Вопрос");
    QByteArray byteArrayQ = question.toLocal8Bit();
    std::string strQ(byteArrayQ.constData(), static_cast<size_t>(byteArrayQ.length()));
    ex->setQuestion_rus(strQ);

}

DocumentHandler::~DocumentHandler() = default;

void DocumentHandler::setTarget(QQuickItem *target)
{
    m_doc = nullptr;
    m_target = target;
    if (!m_target) {
        return;
    }

    QVariant doc = m_target->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc) {
            m_doc = qqdoc->textDocument();
        }
    }
    emit targetChanged();
}

void DocumentHandler::setGo(bool isRight)
{
    saveState();
    if (isRight)
    {
        curr++;
        if( curr == static_cast<int>(ex->size()) )  {
            curr = 0;
        }
    }
    else
    {
        if(curr == 0) {
            curr = static_cast<int>(ex->size()) - 1;
        } else {
            curr--;
        }
    }

    loadState();
    questionNumberChanged();
}


QString DocumentHandler::documentTitle() const
{
    return m_documentTitle;
}


QString DocumentHandler::timeSpent() const
{
    return QString::fromStdString(ex->get_time_differense());
}

int DocumentHandler::size() const
{
    return static_cast<int>(ex->size());
}

void DocumentHandler::setDocumentTitle(QString arg)
{
    if (m_documentTitle != arg) {
        m_documentTitle = arg;
        emit documentTitleChanged();
    }
}

void DocumentHandler::setText(const QString &arg)
{
    m_text = arg;
    emit textChanged();
}

void DocumentHandler::setQuestion(const QString &arg)
{
    if (m_question != arg) {
        m_question = arg;
        emit questionChanged();
    }
}

void DocumentHandler::setUsername(const QString &arg)
{
    if (m_username != arg) {
        m_username = arg;
    }
}


void DocumentHandler::exit()
{
    saveState();
    std::ofstream ofs;
    ofs.open((m_username.toLocal8Bit().toStdString() + "." + ex->get_ext()), std::ios::binary);
    if(ofs)
    {
        ex->SaveToFile( ofs, m_username.toLocal8Bit().data() );
    }
}

void DocumentHandler::startExamen()
{
    ex->startExamen();
    loadState();
}

QString DocumentHandler::text() const
{
    return m_text;
}

QString DocumentHandler::question() const
{
    return m_question;
}

void DocumentHandler::loadState()
{
    setQuestion(QString::fromLocal8Bit(ex->get_question(static_cast<size_t>(curr)).c_str()));
    setText(QString::fromLocal8Bit(ex->get_answer(static_cast<size_t>(curr)).c_str()));
}

void DocumentHandler::saveState()
{
    QByteArray byteArray2 = m_doc->toPlainText().replace("\n", "\r\n").toLocal8Bit();
    std::string str(byteArray2.constData(), static_cast<size_t>(byteArray2.length()));
    ex->set_answer(static_cast<size_t>(curr), str);
}

int DocumentHandler::questionNumber() const
{
    return curr + 1;
}

void DocumentHandler::setQuestionNumber(const int &value)
{
    curr = value - 1;
}

bool DocumentHandler::dbloaded() const
{
    return m_dbloaded;
}

void DocumentHandler::setDbloaded(bool dbloaded)
{
    m_dbloaded = dbloaded;
}
