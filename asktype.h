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

        int floatPrecision;

        AskType() noexcept: askTypeValue(nothingAskType),floatPrecision(0)
            {}
        AskType(AskTypeEnum askTypeValue_) noexcept: askTypeValue(askTypeValue_),floatPrecision(0)
            {}
        explicit AskType(int floatPrecision_) noexcept: askTypeValue(floatAskType),floatPrecision(floatPrecision_)
            {}

        explicit AskType(const QStringList& enumVariantsList_) noexcept: askTypeValue(enumAskType),
                                                     enumVariantsList(enumVariantsList_),floatPrecision(0)
            {}
    };
}

#endif // ASKTYPE_H
