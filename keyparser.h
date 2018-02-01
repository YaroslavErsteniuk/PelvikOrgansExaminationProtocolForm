#ifndef KEYPARSER_H
#define KEYPARSER_H

#include <QStringList>
#include "abstractparser.h"

namespace PelvikOrgansExaminationProtocolForm {
    class KeyParser : public AbstractParser
    {
    protected:

    public:
        KeyParser();

        virtual bool ask(AskType& askType_in, QString& inputKey_in, QString** askText_in, QString** group_in,
                    QRect** place_in) noexcept override;
        virtual QString fullFormTemplate(bool* ok_in) noexcept override;
        virtual QString particularFormTemplate(bool* ok_in) noexcept override;
        virtual QStringList mentionedAsksKeys() const noexcept override;

    };
}

#endif // KEYPARSER_H
