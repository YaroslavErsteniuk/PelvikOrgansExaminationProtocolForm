#ifndef ASKTYPE_H
#define ASKTYPE_H

#include <QString>
#include <list>

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
        AskTypeEnum askType;

        /* list of variants(in form of strings)
         * for askType-value "enumAskType"
         */
        std::list<QString> enumVariantsList;
    };
}

#endif // ASKTYPE_H
