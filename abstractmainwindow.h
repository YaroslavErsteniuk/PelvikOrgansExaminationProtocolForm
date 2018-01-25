#ifndef ABSTRACTMAINWINDOW_H
#define ABSTRACTMAINWINDOW_H

#include <QMainWindow>
#include <QPair>
#include <map>
#include "asktype.h"

namespace PelvikOrgansExaminationProtocolForm
{
    /* Class for abstract input interface.
     * All function in the default realization
     * return false and doing nothing.
     */
    class AbstractMainWindow : public QMainWindow
    {
        Q_OBJECT
    protected:
        std::map<QString, QPair<AskTypeEnum,const QWidget*>> widgets;
    public:
        explicit AbstractMainWindow(QWidget *parent = nullptr);
        virtual ~AbstractMainWindow();

        /* This function return some value from form.
         * @inputKey use to identify question.
         * Type of value returned in first element of returned value.
         * In case of undefined inputKey return
         * QPair(AskTypeEnum::nothingAskType, QVariant())
         */
        virtual QPair<AskType,QVariant> getAnswer(QString inputKey) const noexcept;

        /* This function add some question to form.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QString inputKey) noexcept =0 ;

        /* This function add some question to form.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @askText use for creating text for question.
         * If @askText=="",for creating text for question function use @inputKey.
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QString inputKey, QString askText)noexcept =0 ;

        /* This function add some question to form to some group of questions.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @group represent group to what question should be added.
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QString inputKey, QString group) noexcept =0;

        /* This function add some question to form to some group of questions.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @group represent group to what question should be added.
         * @askText use for creating text for question.
         * If @askText=="",for creating text for question function use @inputKey.
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QString inputKey, QString group, QString askText) noexcept =0;

        /* This function add some question to form at some position.
         * @place represent rectangle where question should be displayed.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QRect place, QString inputKey) noexcept =0;

        /* This function add some question to form at some position.
         * @place represent rectangle where question should be displayed.
         * @inputKey use to identify question.
         * Type of question's answer depend on @ask.
         * @askText use for creating text for question.
         * If @askText=="",for creating text for question function use @inputKey.
         * Return true if question was created and false if not.
         */
        virtual bool addAsk(AskType ask, QRect place, QString inputKey, QString askText) noexcept =0;

        /* This function add text template to and of form.
         * @htmlTempl is template test in html format.
         * Return true if adding was succesfull and false if not.
         */
        virtual bool addFormTemplate(QString htmlTempl) noexcept =0;

        /* This function set text template to form.
         * @htmlTempl is template test in html format.
         * Return true if setting was succesfull and false if not.
         */
        virtual bool setFormTemplate(QString htmlTempl) noexcept =0;
    signals:
        /* signal is emmited when
         * user is thinking all answers is right
         * and they can be processed.
         */
        void applyAnswers();

        void toPdfForm();
        void printForm();
    public slots:

    };
}

#endif // ABSTRACTMAINWINDOW_H
