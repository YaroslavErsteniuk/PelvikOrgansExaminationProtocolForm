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

/* This function return some value from form.
 * @inputKey use to identify question.
 * Type of value returned in first element of returned value.
 * In case of undefined inputKey return
 * QPair(AskTypeEnum::nothingAskType, QVariant())
 * In default realization
 * return false and doing nothing.
 */
QPair<AskType, QVariant> AbstractMainWindow::getAnswer(QString inputKey) const
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
            const QLineEdit* lineEditWidget=qobject_cast<const QLineEdit*>(v.second);
            if (!lineEditWidget)
                throw std::logic_error(errorString);
            return QPair(v.first, QVariant(lineEditWidget->text()));
            break;
        case numberAskType:
            const QSpinBox* spinBoxWidget=qobject_cast<const QSpinBox*>(v.second);
            if (!spinBoxWidget)
                throw std::logic_error(errorString);
            return QPair(v.first, QVariant(spinBoxWidget->value()));
            break;
        case floatAskType:
            const QDoubleSpinBox* doubleSpinBoxWidget=qobject_cast<const QDoubleSpinBox*>(v.second);
            if (!doubleSpinBoxWidget)
                throw std::logic_error(errorString);
            return QPair(AskType(doubleSpinBoxWidget->decimals()), QVariant(doubleSpinBoxWidget->value()));
            break;
        case enumAskType: //input type for list of variants
            const QComboBox* comboBoxWidget=qobject_cast<const QComboBox*>(v.second);
            if (!comboBoxWidget)
                throw std::logic_error(errorString);
            return QPair(v.first, QVariant(comboBoxWidget->currentText()));
            break;
        case dateAskType:
            const QDateEdit * dateEditWidget=qobject_cast<const QDateEdit*>(v.second);
            if (!dateEditWidget)
                throw std::logic_error(errorString);
            return QPair(v.first, QVariant(dateEditWidget->date()));
            break;
        default:
            return QPair(nothingAskType, QVariant());
    }

}
catch (std::out_of_range)
{
    return QPair(nothingAskType, QVariant());
}
catch (std::invalid_argument)
{
    return QPair(nothingAskType, QVariant());
}
catch (std::logic_error)
{
    return QPair(nothingAskType, QVariant());
}
catch (...)
{
    return QPair(nothingAskType, QVariant());
}

/* This function add some question to form.
 * @inputKey use to identify question.
 * Type of question's answer depend on @ask.
 * Return true if question was created and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addAsk(AskType ask, QString inputKey)
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
bool AbstractMainWindow::addAsk(AskType ask, QString inputKey, QString askText)
{
    return false;
}

/* This function add some question to form to some group of questions.
 * @inputKey use to identify question.
 * Type of question's answer depend on @ask.
 * @group represent group to what question should be added.
 * Return true if question was created and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addAsk(AskType ask, QString inputKey, QString group)
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
bool AbstractMainWindow::addAsk(AskType ask, QString inputKey, QString group, QString askText)
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
bool AbstractMainWindow::addAsk(AskType ask, QRect place, QString inputKey)
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
bool AbstractMainWindow::addAsk(AskType ask, QRect place, QString inputKey, QString askText)
{
    return false;
}

/* This function add text template to and of form.
 * @htmlTempl is template test in html format.
 * Return true if adding was succesfull and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::addFormTemplate(QString htmlTempl)
{
    return false;
}

/* This function set text template to form.
 * @htmlTempl is template test in html format.
 * Return true if setting was succesfull and false if not.
 * In default realization
 * return false and doing nothing.
 */
bool AbstractMainWindow::setFormTemplate(QString htmlTempl)
{
    return false;
}
