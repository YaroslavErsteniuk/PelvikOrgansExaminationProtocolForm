#include "abstractmainapplication.h"
#include <stdexcept>

using namespace PelvikOrgansExaminationProtocolForm;

/* If @window or @parser is nullptr
 * constructor will throw std::invalid_argument
 * with propriate string.
 */
AbstractMainApplication::AbstractMainApplication(AbstractMainWindow* window, AbstractParser* parser,
    QObject *parent) : QObject(parent), window_(window), parser_(parser)
{
    if (!window)
        throw std::invalid_argument("Nullptr main window");
    if (!parser)
        throw std::invalid_argument("Nullptr parser");
}

/* Constructor, which can be used if creation of window_ debend on parser_.
 * If @window or @parser is nullptr
 * constructor will throw std::invalid_argument
 * with propriate string.
 */
AbstractMainApplication::AbstractMainApplication(AbstractParser* parser, QObject *parent):
    QObject(parent), window_(nullptr), parser_(parser)
{
    if (!parser)
        throw std::invalid_argument("Nullptr parser");
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
}
