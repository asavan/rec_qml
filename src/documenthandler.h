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

#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QQuickTextDocument>

#include <qqmlfile.h>

#include "Examen/Examination.h"

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class DocumentHandler : public QObject
{
    Q_OBJECT

    Q_ENUMS(HAlignment)

    Q_PROPERTY(QQuickItem *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString documentTitle READ documentTitle WRITE setDocumentTitle NOTIFY documentTitleChanged)
    Q_PROPERTY(bool go WRITE setGo)
    Q_PROPERTY(QString username WRITE setUsername)

    Q_PROPERTY(bool dbloaded READ dbloaded WRITE setDbloaded)

    Q_PROPERTY(int questionNumber READ questionNumber WRITE setQuestionNumber NOTIFY questionNumberChanged)
    Q_PROPERTY(QString timeSpent READ timeSpent)
    Q_PROPERTY(int size READ size)

public:
    DocumentHandler();

    QQuickItem *target() { return m_target; }

    void setTarget(QQuickItem *target);

    QUrl fileUrl() const;
    QString text() const;
    QString question() const;


    void setGo(bool isRight);
    void setUsername(const QString &arg);

    QString documentTitle() const;

    QString timeSpent() const;

    int size() const;

    bool dbloaded() const;
    void setDbloaded(bool dbloaded);

    int questionNumber() const;
    void setQuestionNumber(const int &value);

public Q_SLOTS:

    void setText(const QString &arg);
    void setQuestion(const QString &arg);

    void setDocumentTitle(QString arg);

    void exit();
    void startExamen();

Q_SIGNALS:
    void targetChanged();

    void textChanged();
    void questionChanged();
    void questionNumberChanged();
    void documentTitleChanged();
    void error(QString message);

private:

    void loadState();
    void saveState();


    QQuickItem *m_target;
    QTextDocument *m_doc;

    QUrl m_fileUrl;
    QString m_text;
    QString m_documentTitle;
    QString m_username;
    QString m_question;

    Examination ex;
    size_t curr;
    bool m_dbloaded;
};

#endif
