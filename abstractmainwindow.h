#ifndef ABSTRACTMAINWINDOW_H
#define ABSTRACTMAINWINDOW_H

#include <QMainWindow>
#include <QPair>
#include "asktype.h"


namespace PelvikOrgansExaminationProtocolForm
{
    // Class for abstract input interface
    class AbstractMainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit AbstractMainWindow(QWidget *parent = nullptr);
        virtual ~AbstractMainWindow();

        /* This function return some value from form.
         * @inputKey use to identify question.
         * Type of value returned in first element of returned value.
         * In case of undefined inputKey return
         * QPair(AskTypeEnum::nothingAskType, QVariant())
         */
        virtual QPair<AskTypeEnum,QVariant> getAnswer(QString inputKey)=0;

        /* This function add some question to form.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @askText use for creating text for question.
         * If @askText=="",for creating text for question function use @inputKey/
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QString inputKey, QString askText="")=0;

        /* This function add some question to form to some group of questions.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @group represent group to what question should be added.
         * @askText use for creating text for question.
         * If @askText=="",for creating text for question function use @inputKey/
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QString inputKey, QString group, QString askText="")=0;

        /* This function add some question to form at some position.
         * @place represent rectangle where question should be displayed.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @askText use for creating text for question.
         * If @askText=="",for creating text for question function use @inputKey/
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QRect place, QString inputKey, QString askText="")=0;

        /* This function add some question to form at some position.
         * @place represent rectangle where question should be displayed.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @askText use for creating text for question.
         * If @askText=="",for creating text for question function use @inputKey/
         * Return true if question was created and false if not.
         */
        virtual bool addFormTemplate(QString templ)=0;

    signals:

    public slots:
    };
}

#endif // ABSTRACTMAINWINDOW_H
