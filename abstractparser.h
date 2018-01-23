#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QString>
#include <QRect>
#include <QStringList>
#include <QPair>
#include <QVariant>
#include <map>
#include "asktype.h"

namespace PelvikOrgansExaminationProtocolForm {
    /* Class for parsing file or some another input stream
     * and on this base create variaty of questions
     * and may create form template
     */
    class AbstractParser
    {
    protected:
        QString inputName_;
    public:
        AbstractParser(QString inputName);
        virtual ~AbstractParser();

        //Sometimes it may need to do some more speculation while setting inputName_
        virtual bool setInputName(QString inputName) noexcept;
        QString inputName() const noexcept;

        /* Get new ask from input stream.
         * Return is there a new question,
         * and AskType of that ask in @askType_in,
         * and key in @inputKey_in.
         * Optionally, if passed and if was declared in stream,
         * can set name of question in @askText_in,
         * group of question in @group_in,
         * and place of question in @place_in.
         * If parameter passed but not used in stream
         * the pointer is set to nullptr.
         * The default realization return false,
         * @askType_in=AskType(),@inputKey_in=QString(),
         * and nullptr for other arguments.
         */
        virtual bool ask(AskType& askType_in, QString& inputKey_in, QString** askText_in, QString** group_in,
            QRect** place_in) noexcept =0;

        /* Get new full form template from input stream.
         * Return new template and
         * optionally in @ok_in if it was created or not.
         * If not the returned value is QString().
         * The default realization return QString,
         * and @ok_in=false()
         */
        virtual QString fullFormTemplate(bool* ok_in) noexcept =0;

        /* Get new particular form template from input stream.
         * Return new template and
         * optionally in @ok_in if it was created or not.
         * If not the returned value is QString().
         * The default realization return QString,
         * and @ok_in=false()
         */
        virtual QString particularFormTemplate(bool* ok_in) noexcept =0;

        /* Get asks' keys for all question
         * that was taken from stream.
         * If there wasn't taken any keys,
         * returned QStringList().
         * The default realization return QStringList().
         */
        virtual QStringList mentionedAsksKeys() const noexcept =0;

        virtual bool insertAnswer(QString inputKey, QPair<AskTypeEnum,QVariant> answerPair) noexcept =0;
        virtual QString getForm(bool* ok_in) const noexcept =0;
        virtual QString getForm(std::map<QString,QPair<AskTypeEnum,QVariant> > answerPairs, bool* ok_in) noexcept =0;

    };
}


#endif // ABSTRACTPARSER_H
