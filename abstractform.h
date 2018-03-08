#ifndef ABSTRACTFORM_H
#define ABSTRACTFORM_H

#include <QObject>

namespace PelvikOrgansExaminationProtocolForm
{
    // Class which represent the template for form
    class AbstractForm: public QObject
    {
    public:
        virtual ~AbstractForm();

        /* Insert answer in template.
         * @inputKey represent the key of question,
         * @inputKey is a pair<Type,Value>.
         * If value is inserted return true;
         * return false otherwise.
         */
        virtual bool insertAnswer(QString inputKey, QPair<AskTypeEnum,QVariant> inputKey) noexcept=0;

        /* Should be used if question with key @inputKey haven't answer.
         * Delete place for that answer in template.
         * @inputKey - key for question which haven't answer.
         * Return true if deleting was successfull,
         * return false otherwise.
         */
        virtual bool noAnswer(QString inputKey) noexcept=0;

        /* Function for getting current version of template realisation.
         * @ok_in is parameter for checking the validity of template realisation.
         */
        virtual QString getForm(bool* ok_in) const noexcept=0;

        /* Except for getting current version of template realisation,
         * this version insert answers in @answerPairs using the AbstractForm::insertAnswer.
         * @answerPairs is a map of answer in form of <Key,<Type,Value>>.
         * @ok_in is parameter for checking the validity of template realisation.
         * If at least one value can't be converted or inserted
         * the template is consider to be invalid.
         */
        QString getForm(const std::map<QString, QPair<AskTypeEnum, QVariant> > &answerPairs, bool* ok_in) noexcept;
    };
}

#endif // ABSTRACTFORM_H
