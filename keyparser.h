#ifndef KEYPARSER_H
#define KEYPARSER_H

#include <QStringList>
#include "abstractfactoryparser.h"

namespace PelvikOrgansExaminationProtocolForm {

    /* Simpiest realisation of AbstractParser,
     * which just use predefined hard-coded questions
     * and cooperate with predefined hard-coded GUI.
     * The only function which return correct result is mentionedAsksKeys
     * for redusing number of "magic" constants.
     */
    class KeyParser : public AbstractParser
    {
    protected:

    public:
        KeyParser();

        //Should be not used from this class
        virtual bool ask(AskType& askType_in, QString& inputKey_in, QString** askText_in, QString** group_in,
                    QRect** place_in) noexcept override;

        //Should be not used from this class
        virtual QString fullFormTemplate(bool* ok_in) noexcept override;

        //Should be not used from this class
        virtual QString particularFormTemplate(bool* ok_in) noexcept override;

        /* The only function which return correct result is mentionedAsksKeys
        * for redusing number of "magic" constants.
        */
        virtual QStringList mentionedAsksKeys() const noexcept override;

    };
}

#endif // KEYPARSER_H
