#include "keyparser.h"

using namespace PelvikOrgansExaminationProtocolForm;

KeyParser::KeyParser():AbstractParser("")
{
}

bool KeyParser::ask(AskType& askType_in, QString& inputKey_in, QString** askText_in, QString** group_in,
    QRect** place_in) noexcept
{
    askType_in=AskType();
    inputKey_in=QString();
    if (askText_in)
        *askText_in=nullptr;
    if (group_in)
        *group_in=nullptr;
    if (place_in)
        *place_in=nullptr;
    return false;
}

/* Get new full form template from input stream.
 * Return new template and
 * optionally in @ok_in if it was created or not.
 * If not the returned value is QString().
 * The default realization return QString,
 * and @ok_in=false()
 */
QString KeyParser::fullFormTemplate(bool* ok_in) noexcept
{
    if (ok_in)
        *ok_in=false;
    return QString();
}

/* Get new particular form template from input stream.
 * Return new template and
 * optionally in @ok_in if it was created or not.
 * If not the returned value is QString().
 * The default realization return QString,
 * and @ok_in=false()
 */
QString KeyParser::particularFormTemplate(bool* ok_in) noexcept
{
    if (ok_in)
        *ok_in=false;
    return QString();
}

/* Get asks' keys for all question
 * that was taken from stream.
 * If there wasn't taken any keys,
 * returned QStringList().
 * The default realization return QStringList().
 */
QStringList KeyParser::mentionedAsksKeys() const noexcept
{
    return QStringList({
                           "nsf","typeObservation","yearObservation","oM",
                        "uterusDisposition","uterusForm","uterusContur",
                           "uterusSize1", "uterusSize2", "uterusSize3",
                           "uterusVolume", "endometriusThikness",
                           "endometriusVizualization","endometriusLayers",
                           "uterusCervixSize1","uterusCervixSize2",
                           "uterusCervixVolume","canalVizualization",
                           "echostructure","echostructureOn",
                           "rightOvaryVizualization","rightOvaryContur",
                           "rightOvaryBorder","rightOvarySize1",
                           "rightOvarySize2","rightOvarySize3",
                           "rightOvaryFoliculus","rightOvaryFormation",
                           "rightOvaryFormationDiametre","rightOvaryFormationContent",
                           "leftOvaryVizualization","leftOvaryContur",
                           "leftOvaryBorder","leftOvarySize1",
                           "leftOvarySize2","leftOvarySize3",
                           "leftOvaryFoliculus","leftOvaryFormation",
                           "leftOvaryFormationDiametre","leftOvaryFormationContent",
                           "fallopianTubes","freeLiquid","recomendation",
                           "data","doctor"
                       });
}
