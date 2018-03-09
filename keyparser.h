#ifndef KEYPARSER_H
#define KEYPARSER_H

#include <QStringList>
#include "abstractfactoryparser.h"
#include "form.h"

namespace PelvikOrgansExaminationProtocolForm {

    /* Simpiest realisation of AbstractParser,
     * which just use predefined hard-coded questions
     * and cooperate with predefined hard-coded GUI.
     * The only function which return correct result is mentionedAsksKeys
     * for redusing number of "magic" constants.
     */
    class KeyParser : public AbstractFactoryParser
    {
    protected:

    public:
        KeyParser();

        /* The only function which return correct result is mentionedAsksKeys
        * for redusing number of "magic" constants.
        */
        virtual QStringList mentionedAsksKeys() const noexcept override;

        /* Main part of realisation of abstract factory pattern.
         * This function try
         * to open and read file "template.htm".
         * If it can't be done return nullptr,
         * else return pointer to new Form object.
         */
        virtual Form* createForm() noexcept override;
protected:
        //Should be not used from this class
        virtual bool ask(AskType& askType_in, QString& inputKey_in, QString** askText_in, QString** group_in,
                    QRect** place_in) noexcept override;

        //Should be not used from this class
        virtual QString fullFormTemplate(bool* ok_in) noexcept override;

        //Should be not used from this class
        virtual QString particularFormTemplate(bool* ok_in) noexcept override;



    };
}

#endif // KEYPARSER_H
