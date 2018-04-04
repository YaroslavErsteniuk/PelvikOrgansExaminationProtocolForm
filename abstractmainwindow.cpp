#include "abstractmainwindow.h"
#include <stdexcept>

#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QComboBox>

using namespace PelvikOrgansExaminationProtocolForm;

AbstractMainWindow::AbstractMainWindow(QWidget *parent) : QMainWindow(parent)
    {}

AbstractMainWindow::~AbstractMainWindow()
    {}

/* get actions from @pool and register them.
 * In this realisation if at least one action is nullptr
 * or don't registered return false,
 * in success return true.
 * If there isn't any action return false too.
 */
bool AbstractMainWindow::createActions(AbstracMyActionPool* pool) noexcept
{
    if (pool->actionCount()==0)
        return false;
    pool->startFromBegining();
    while( pool->nextActionExist())
    {
        auto ac=pool->getNextAction();
        if (!ac)
            return false;
        if (!registerAction(ac))
            return false;
    }
    return allActionsRegistered();
}

/* This function return whether some not-empty value
 * can be taken from form.
 * If form isn't enabled or visible or value is empty it return false,
 * otherwise return true.
 * @inputKey use to identify question.
 */
bool AbstractMainWindow::isAnswer(QString inputKey) const noexcept
try{
    auto v=widgets.at(inputKey);
    if (!v.second->isEnabled() || !v.second->isVisible())
            return false;
    return true;
}
catch (std::out_of_range)
{
    return false;
}

/* This function return some value from form.
 * @inputKey use to identify question.
 * Type of value returned in first element of returned value.
 * In case of undefined inputKey return
 * QPair(AskTypeEnum::nothingAskType, QVariant())
 * In default realization
 * return false and doing nothing.
 */
QPair<AskTypeEnum, QVariant> AbstractMainWindow::getAnswer(QString inputKey) const noexcept
try{
    auto v=widgets.at(inputKey);

    const char errorString[]="Type mismatch"; //error string if qobject_cast return nullptr

    /* depending on value type (v.first)
     * function cast ptr to QWidget(v.second)
     * to input-widget type and get value from that widget
     */
    switch (v.first)
    {
        case stringAskType:
        {
            const QLineEdit* lineEditWidget=qobject_cast<const QLineEdit*>(v.second);
            if (!lineEditWidget)
                throw std::logic_error(errorString);
            return QPair<AskTypeEnum, QVariant>(v.first, QVariant(lineEditWidget->text()));
        }
            break;
        case numberAskType:
        {
            const QSpinBox* spinBoxWidget=qobject_cast<const QSpinBox*>(v.second);
            if (!spinBoxWidget)
                throw std::logic_error(errorString);
            return QPair<AskTypeEnum, QVariant>(v.first, QVariant(spinBoxWidget->value()));
        }
            break;
        case floatAskType:
        {
            const QDoubleSpinBox* doubleSpinBoxWidget=qobject_cast<const QDoubleSpinBox*>(v.second);
            if (!doubleSpinBoxWidget)
                throw std::logic_error(errorString);
            return QPair<AskTypeEnum, QVariant>(v.first, QVariant(doubleSpinBoxWidget->value()));
        }
            break;
        case enumAskType: //input type for list of variants
        {
            const QComboBox* comboBoxWidget=qobject_cast<const QComboBox*>(v.second);
            if (!comboBoxWidget)
                throw std::logic_error(errorString);
            return QPair<AskTypeEnum, QVariant>(v.first, QVariant(comboBoxWidget->currentText()));
        }
            break;
        case dateAskType:
        {
            const QDateEdit * dateEditWidget=qobject_cast<const QDateEdit*>(v.second);
            if (!dateEditWidget)
                throw std::logic_error(errorString);
            return QPair<AskTypeEnum, QVariant>(v.first, QVariant(dateEditWidget->date()));
        }
            break;
        default:
            return QPair<AskTypeEnum, QVariant>(nothingAskType, QVariant());
    }

}
catch (std::out_of_range)
{
    return QPair<AskTypeEnum, QVariant>(nothingAskType, QVariant());
}
catch (std::invalid_argument)
{
    return QPair<AskTypeEnum, QVariant>(nothingAskType, QVariant());
}
catch (std::logic_error)
{
    return QPair<AskTypeEnum, QVariant>(nothingAskType, QVariant());
}
catch (...)
{
    return QPair<AskTypeEnum, QVariant>(nothingAskType, QVariant());
}

/* This function add some question to form.
 * @inputKey use to identify question.
 * Type of question's answer depend on @ask.
 * Return true if question was created and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addAsk(AskType, QString) noexcept
{
    return false;
}

/* This function add some question to form.
 * @inputKey use to identify question.
 * Type of question's answer depend on @ask.
 * @askText use for creating text for question.
 * If @askText=="",for creating text for question function use @inputKey.
 * Return true if question was created and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addAsk(AskType, QString, QString) noexcept
{
    return false;
}

/* This function add some question to form to some group of questions.
 * @inputKey use to identify question.
 * Type of question's answer depend on @ask.
 * @group represent group to what question should be added.
 * @askText use for creating text for question.
 * If @askText=="",for creating text for question function use @inputKey.
 * Return true if question was created and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addAsk(AskType, QString, QString, QString) noexcept
{
    return false;
}

/* This function add some question to form at some position.
 * @place represent rectangle where question should be displayed.
 * @inputKey use to identify question.
 * Type of question's answer depend on @ask.
 * Return true if question was created and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addAsk(AskType, QRect, QString) noexcept
{
    return false;
}

/* This function add some question to form at some position.
 * @place represent rectangle where question should be displayed.
 * @inputKey use to identify question.
 * Type of question's answer depend on @ask.
 * @askText use for creating text for question.
 * If @askText=="",for creating text for question function use @inputKey.
 * Return true if question was created and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addAsk(AskType, QRect, QString, QString) noexcept
{
    return false;
}

/* This function add text template to and of form.
 * @htmlTempl is template test in html format.
 * Return true if adding was succesfull and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addFormTemplate(QString) noexcept
{
    return false;
}

/* This function set text template to form.
 * @htmlTempl is template test in html format.
 * Return true if setting was succesfull and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::setFormTemplate(QString) noexcept
{
    return false;
}

/* slot  is processing dependent widgets from the std::list<QWidget*> (*iterator)
 * in way setting up their visibility to isVisible_
 * @iterator is an iterator to list of widgets visibility neeeded to change
 * @isVisible_ is new value of widgets' visibility
 */
void AbstractMainWindow::setDependentWidgetsVisibility(std::list<std::list<QWidget*> >::iterator it, bool isVisible_) noexcept
{
    for (auto widget_: (*it))
    {
        widget_->setVisible(isVisible_);
        emit widgetVisible(widget_,isVisible_);
    }
}

/* slot  is processing dependent widgets from the std::list<QWidget*> (*iterator)
 * in way setting up their enabling to isEnabled_
 * @iterator is an iterator to list of widgets enabling neeeded to change
 * @isEnabled_ is new value of widgets' enabling
 */
void AbstractMainWindow::setDependentWidgetsEnabling(std::list<std::list<QWidget*> >::iterator it, bool isEnabled_) noexcept
{
    for (auto widget_: (*it))
    {
        widget_->setEnabled(isEnabled_);
        emit widgetEnable(widget_,isEnabled_);
    }
}
