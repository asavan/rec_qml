/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "documenthandler.h"

#include <QtGui/QTextDocument>
#include <QtGui/QTextCursor>
#include <QtGui/QFontDatabase>
#include <QtCore/QFileInfo>

#include <QException>

#include <fstream>


DocumentHandler::DocumentHandler()
    : m_target(0),
      m_doc(0),
      curr(0),
      m_dbloaded(false)
{
    std::istream* ifs = 0;
    ifs = new std::ifstream("db.rec", std::ios_base::binary);
    if( *ifs)
    {
        bool res = ex.LoadFromFile( *ifs );
        if(res)
        {
            ex.MakeAnswerOrder();
        }
        delete ifs;
    } else {
        error("Не найдена база с вопросами");
        return;
    }
    setDbloaded(true);
    QString title = QString::fromLocal8Bit(ex.get_set().get_name().c_str());

    setDocumentTitle(title);
    QString answer("Ответ");
    QByteArray byteArray = answer.toLocal8Bit();
    std::string str(byteArray.constData(), byteArray.length());
    ex.setAnswer_rus(str);

    QString question("Вопрос");
    QByteArray byteArrayQ = question.toLocal8Bit();
    std::string strQ(byteArrayQ.constData(), byteArrayQ.length());
    ex.setQuestion_rus(strQ);

}

void DocumentHandler::setTarget(QQuickItem *target)
{
    m_doc = 0;
    m_target = target;
    if (!m_target)
        return;

    QVariant doc = m_target->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc)
            m_doc = qqdoc->textDocument();
    }
    emit targetChanged();
}

void DocumentHandler::setGo(bool isRight)
{
    saveState();
    if (isRight)
    {
        curr++;
        if( curr==ex.size() ) curr=0;
    }
    else
    {
        if( curr==0 ) curr=ex.size()-1;
        else curr--;
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
    return QString::fromStdString(ex.get_time_differense());
}

int DocumentHandler::size() const
{
    return ex.size();
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
    {
        m_text = arg;
        emit textChanged();
    }
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
    ofs.open((m_username.toLocal8Bit().toStdString()+"."+ex.get_set().get_ext()).c_str(), std::ios::binary);
    if( ofs.is_open() )
    {
        ex.SaveToFile( ofs, m_username.toLocal8Bit().data() );
        ofs.close();
    }
}

void DocumentHandler::startExamen()
{
    ex.startExamen();
    loadState();
}

QUrl DocumentHandler::fileUrl() const
{
    return m_fileUrl;
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
    setQuestion(QString::fromLocal8Bit(ex.get_question(curr).c_str()));
    setText(QString::fromLocal8Bit(ex.get_answer(curr).c_str()));
}

void DocumentHandler::saveState()
{
    QByteArray byteArray2 = m_doc->toPlainText().replace("\n", "\r\n").toLocal8Bit();
    // qDebug() << byteArray2;
    std::string str(byteArray2.constData(), byteArray2.length());
    ex.set_answer( curr, str );
}

int DocumentHandler::questionNumber() const
{
    return curr+1;
}

void DocumentHandler::setQuestionNumber(const int &value)
{
    curr = value-1;
}

bool DocumentHandler::dbloaded() const
{
    return m_dbloaded;
}

void DocumentHandler::setDbloaded(bool dbloaded)
{
    m_dbloaded = dbloaded;
}


