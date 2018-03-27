#include "abstractmainapplication.h"
#include <stdexcept>

using namespace PelvikOrgansExaminationProtocolForm;

/* Parser_ will create fromPrt.
 * If @window or @parser is nullptr
 * constructor will throw std::invalid_argument
 * with propriate string.
 * If parser_ return nullptr
 * throw std::logic_error
 * with propriate string.
 */
AbstractMainApplication::AbstractMainApplication(AbstractMainWindow* window, AbstractFactoryParser* parser,
    QObject *parent) : QObject(parent), window_(window), parser_(parser)
{
    if (!window)
        throw std::invalid_argument("Nullptr main window");
    if (!parser)
        throw std::invalid_argument("Nullptr parser");
    fromPtr=parser_->createForm();
    if (!fromPtr)
        throw std::logic_error("Nullptr form");
}

/* Parser_ will create fromPrt.
 * Constructor, which can be used if creation of window_ debend on parser_.
 * If @window or @parser is nullptr
 * constructor will throw std::invalid_argument
 * with propriate string.
 * If parser_ return nullptr
 * throw std::logic_error
 * with propriate string.
 */
AbstractMainApplication::AbstractMainApplication(AbstractFactoryParser* parser, QObject *parent):
    QObject(parent), window_(nullptr), parser_(parser)
{
    if (!parser)
        throw std::invalid_argument("Nullptr parser");
    fromPtr=parser_->createForm();
    if (!fromPtr)
        throw std::logic_error("Nullptr form");
}

/* Slot which display UI.
 * In defaul version just invoke window_->show().
 */
void AbstractMainApplication::show() noexcept
{
    window_->show();
}

AbstractMainApplication::~AbstractMainApplication()
{
    delete window_;
    delete parser_;
    delete fromPtr;
}

/* Get version of form,
 * in which answers have been inserted.
 * @answerPairs is a map of answer in form of <Key,<Type,Value>>.
 * @ok_in is parameter for checking the validity of template realisation.
 * If at least one value can't be converted or inserted
 * the template is consider to be invalid.
 * Default realisation use AbstractForm::getForm.
 */
QString AbstractMainApplication::getForm(const std::map<QString, QPair<AskTypeEnum, QVariant> >
                                         &answerPairs, bool* ok_in) noexcept
{
    return fromPtr->getForm(answerPairs,ok_in);
}
