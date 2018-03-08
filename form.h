#ifndef FORM_H
#define FORM_H

#include <abstractform.h>
#include <QPair>
#include <QVariant>
#include <map>
#include "asktype.h"

namespace PelvikOrgansExaminationProtocolForm
{
    /* Class which represent the template for form
     * and which at the moment save current version of template realisation.
     */
    class Form: public AbstractForm
    {
        Q_OBJECT
    protected:
        //template
        QString formTemplate_;

        //template realisation
        QString form_;
    public:
        Form(QString formTemplate="") noexcept;

        /* Insert answer in current version of template realisation.
         * @inputKey represent the key of question,
         * @inputKey is a pair<Type,Value>.
         * If value is inserted return true;
         * If value can't be converted to QString acording to Type
         * or template haven't @inputKey return false.
         */
        virtual bool insertAnswer(QString inputKey, QPair<AskTypeEnum,QVariant> inputKey) noexcept;

        /* Should be used if question with key @inputKey haven't answer.
         * Delete place for that answer in template.
         * @inputKey - key for question which haven't answer.
         * Return true if deleting was successfull,
         * return false if template haven't @inputKey.
         */
        virtual bool noAnswer(QString inputKey) noexcept;

        /* Setter for template.
         * To update template realisation Form::resetForm should be used explicitly.
         */
        virtual bool setFormTemplate(QString formTemplate) noexcept;
        virtual QString getFormTemplate() const noexcept;

        /* Reset template realisation according to template.
         * All changes would be discarted,
         */
        virtual bool resetForm() noexcept;

        /* Function for getting current version of template realisation.
         * @ok_in is parameter for checking the validity of template realisation.
         * If current version of template realisation is empty retun QString and set value of *(@ok_in) to false.
         * Otherwise return current version of template realisation and set value of *(@ok_in) to true.
         */
        virtual QString getForm(bool* ok_in) const noexcept;

        /* Realisation moved to AbstractForm.
         *
         * Except for getting current version of template realisation,
         * this version insert answers in @answerPairs using the Form::insertAnswer.
         * @answerPairs is a map of answer in form of <Key,<Type,Value>>.
         * @ok_in is parameter for checking the validity of template realisation.
         * If at least one value can't be converted to QString acording to Type
         * or template haven't Key @ok_in is set to false and function return QString().
         * If current version of template realisation is empty retun QString and set value of *(@ok_in) to false.
         * Otherwise return current version of template realisation and set value of *(@ok_in) to true.
         */
        virtual QString getForm(const std::map<QString, QPair<AskTypeEnum, QVariant> > &answerPairs, bool* ok_in) noexcept;
    protected:
        virtual QString toQString(QPair<AskTypeEnum, QVariant> answerPair, bool* ok_in) const noexcept;
        virtual QString qDatetoQString(QDate d) const noexcept;
    public slots:
        /* Slot for creating pdf on template's base.
         * Use QtWebkit and GUI-classes for creating.
         *
         * TODO separate GUI from functional classes.
         */
        virtual void createPDF() const noexcept;

        /* Slot for creating html on template's base.
         * Use GUI-classes for creating.
         *
         * TODO separate GUI from functional classes.
         */
        virtual void createHTML() const noexcept;

        /* Slot for printing on template's base.
         * Use QtWebkit and GUI-classes for printing.
         *
         * TODO separate GUI from functional classes.
         */
        virtual void printInPrinter() const noexcept;
    };
}

#endif // FORM_H
