#include "abstractfactoryparser.h"

using namespace PelvikOrgansExaminationProtocolForm;

AbstractFactoryParser::AbstractFactoryParser(QString inputName): inputName_(inputName)
    {}

AbstractFactoryParser::~AbstractFactoryParser()
    {}

bool AbstractFactoryParser::setInputName(QString inputName) noexcept
    { inputName_=inputName; return true; }

QString AbstractFactoryParser::inputName() const noexcept
    { return inputName_; }

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
bool AbstractFactoryParser::ask(AskType& askType_in, QString& inputKey_in, QString** askText_in, QString** group_in,
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
QString AbstractFactoryParser::fullFormTemplate(bool* ok_in) noexcept
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
QString AbstractFactoryParser::particularFormTemplate(bool* ok_in) noexcept
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
QStringList AbstractFactoryParser::mentionedAsksKeys() const noexcept
{
    return QStringList();
}
