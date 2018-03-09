#include "keyparser.h"
#include <QFile>

using namespace PelvikOrgansExaminationProtocolForm;

KeyParser::KeyParser():AbstractFactoryParser("")
{
}

/* Main part of realisation of abstract factory pattern.
 * This function try
 * to open and read file "template.htm".
 * If it can't be done return nullptr,
 * else return pointer to new Form object.
 */
Form* KeyParser::createForm() noexcept
{
    QFile templateFile("template.htm");
    if (!templateFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;
    auto templateInHtml=QString(templateFile.readAll());
    return new Form(templateInHtml);
}

// Should be not used from this class
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
 * and @ok_in=false().
 *
 * Should be not used from this class
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
 *
 * Should be not used from this class
 */
QString KeyParser::particularFormTemplate(bool* ok_in) noexcept
{
    if (ok_in)
        *ok_in=false;
    return QString();
}

/* Get asks' keys for all question
 * that was used.
 * It is the only function which return correct result.
 * It used for redusing number of "magic" constants.
 */
QStringList KeyParser::mentionedAsksKeys() const noexcept
{
    return QStringList({
                           "nsf","typeObservation","yearPatient","yearObservation","oM",
                        "uterusDisposition","uterusForm","uterusContur",
                           "uterusSize1", "uterusSize2", "uterusSize3",
                           "uterusVolume", "endometriusThikness",
                           "endometriusVizualization","endometriusLayers",
                           "uterusCervixSize1","uterusCervixSize2",
                           "uterusCervixVolume","canalVizualization",
                           "echostructure","echostructureOn",
                           "rightOvaryVizualization","rightOvaryContur",
                           "rightOvaryBorder","rightOvarySize1",
                           "rightOvarySize2","rightOvarySize3","rightOvaryVolume",
                           "rightOvaryFoliculus","rightOvaryFormation",
                           "rightOvaryFormationDiametre","rightOvaryFormationContent",
                           "leftOvaryVizualization","leftOvaryContur",
                           "leftOvaryBorder","leftOvarySize1",
                           "leftOvarySize2","leftOvarySize3","leftOvaryVolume",
                           "leftOvaryFoliculus","leftOvaryFormation",
                           "leftOvaryFormationDiametre","leftOvaryFormationContent",
                           "fallopianTubes","freeLiquid","recomendation",
                           "data","doctor"
                       });
}
