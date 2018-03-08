#include "abstractform.h"

using namespace PelvikOrgansExaminationProtocolForm;

virtual AbstractForm::~AbstractForm()
{

}

/* Except for getting current version of template realisation,
 * this version insert answers in @answerPairs using the AbstractForm::insertAnswer.
 * @answerPairs is a map of answer in form of <Key,<Type,Value>>.
 * @ok_in is parameter for checking the validity of template realisation.
 * If at least one value can't be converted or inserted
 * the template is consider to be invalid.
 */
QString AbstractForm::getForm(const std::map<QString, QPair<AskTypeEnum, QVariant> > &answerPairs, bool* ok_in) noexcept
{
    bool ok_in=true;
    for (auto it=answerPairs.cbegin(); it!=answerPairs.cend() && ok_in; ++it)
        ok_in=insertAnswer(it->first,it->second);
    if (!ok_in)
    {
        return QString();
    }
    return getForm(ok_in);
}
