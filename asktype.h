#ifndef ASKTYPE_H
#define ASKTYPE_H

#include <QString>
#include <QStringList>
#include <stdexcept>

namespace PelvikOrgansExaminationProtocolForm
{
    // input data typesd
    enum AskTypeEnum
    {
        nothingAskType,  //use if shouldn't be answer or answer can't be readen
        stringAskType,
        numberAskType,
        floatAskType,
        enumAskType, //input type for list of variants
        dateAskType
    };

    // input data definition
    struct  AskType
    {
       public:
        AskTypeEnum askTypeValue;

        /* list of variants(in form of strings)
         * for askType-value "enumAskType"
         */
        QStringList enumVariantsList;

        AskType() noexcept: askTypeValue(nothingAskType)
            {}
        AskType(AskTypeEnum askTypeValue_): askTypeValue(askTypeValue_)
            {}
        AskType(AskTypeEnum askTypeValue_,const QStringList& enumVariantsList_): askTypeValue(nothingAskType),
                                                                                 enumVariantsList(enumVariantsList_)
        {
            if ((askTypeValue_!=enumAskType) && (enumVariantsList_.isEmpty()))
                throw std::invalid_argument("enumVariantsList can be not empty only for enumAskType");

        }
    };
}

#endif // ASKTYPE_H
