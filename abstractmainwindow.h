#ifndef ABSTRACTMAINWINDOW_H
#define ABSTRACTMAINWINDOW_H

#include <QMainWindow>
#include <QPair>
#include <map>
#include <list>
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
        std::map<QString, QPair<AskTypeEnum,QWidget*>> widgets;
        std::list<std::list<QWidget*> > dependentWidgets;
    public:
        explicit AbstractMainWindow(QWidget *parent = nullptr);
        virtual ~AbstractMainWindow();

        /* This function return some value from form.
         * @inputKey use to identify question.
         * Type of value returned in first element of returned value.
         * In case of undefined inputKey return
         * QPair(AskTypeEnum::nothingAskType, QVariant())
         */
        virtual QPair<AskTypeEnum,QVariant> getAnswer(QString inputKey) const noexcept;

        /* This function return whether some not-empty value
         * can be taken from form.
         * If form isn't enabled or visible or value is empty it return false,
         * otherwise return true.
         * @inputKey use to identify question.
         */
        virtual bool isAnswer(QString inputKey) const noexcept;

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

    protected:
        virtual bool createActions() noexcept =0;
    signals:
        /* signal is emmited when
         * user is thinking all answers is right
         * and they can be processed.
         */
        void applyAnswers();

        /*Not used
         *
         *  signal is emmited when
         * user is trying create form's pdf-file
         */
        //void toPdfForm();

        /* Not used
         *
         *  signal is emmited when
         * user is trying print form
         */
        //void printForm();

        /* Not used
         *
         * signal is emmited when
         * user is trying create form's html-file
         */
        //void toHtmlForm();

        /* signal is emmited when
         * visibility of widget_ is change
         */
        void widgetVisible(QWidget* widget_, bool isVisible_);

        /* signal is emmited when
         * enabling of widget_ is change
         */
        void widgetEnable(QWidget* widget_, bool isEnabled_);
    protected slots:

        /* slot  is processing dependent widgets from the std::list<QWidget*> (*iterator)
         * in way setting up their visibility to isVisible_
         * @iterator is an iterator to list of widgets visibility neeeded to change
         * @isVisible_ is new value of widgets' visibility
         */
        virtual void setDependentWidgetsVisibility(std::list<std::list<QWidget*> >::iterator it, bool isVisible_) noexcept;

        /* slot  is processing dependent widgets from the std::list<QWidget*> (*iterator)
         * in way setting up their enabling to isEnabled_
         * @iterator is an iterator to list of widgets enabling neeeded to change
         * @isEnabled_ is new value of widgets' enabling
         */
        virtual void setDependentWidgetsEnabling(std::list<std::list<QWidget*> >::iterator it, bool isEnabled_) noexcept;
    };
}

#endif // ABSTRACTMAINWINDOW_H
