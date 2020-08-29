#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <memory>
#include <QObject>

class Examination;

QT_BEGIN_NAMESPACE
class QTextDocument;
class QQuickItem;
QT_END_NAMESPACE

class DocumentHandler : public QObject
{
    Q_OBJECT

    Q_ENUMS(HAlignment)

    Q_PROPERTY(QQuickItem *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString documentTitle READ documentTitle WRITE setDocumentTitle NOTIFY documentTitleChanged)

    Q_PROPERTY(int questionNumber READ questionNumber WRITE setQuestionNumber NOTIFY questionNumberChanged)
    Q_PROPERTY(QString timeSpent READ timeSpent)

    Q_PROPERTY(bool dbloaded READ dbloaded CONSTANT)
    Q_PROPERTY(int size READ size CONSTANT)

public:
    DocumentHandler();
    ~DocumentHandler();

    QQuickItem *target() { return m_target; }

    void setTarget(QQuickItem *target);

    QString text() const;
    QString question() const;


    Q_INVOKABLE void go(bool isRight);
    Q_INVOKABLE void setUsername(const QString &arg);

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
    QString m_text;
    QString m_documentTitle;
    QString m_username;
    QString m_question;

    std::unique_ptr<Examination> ex;
    int curr;
    bool m_dbloaded;
};

#endif
