#include "abstractmainapplication.h"
#include <stdexcept>

using namespace PelvikOrgansExaminationProtocolForm;

AbstractMainApplication::AbstractMainApplication(AbstractMainWindow* window, AbstractParser* parser,
    QObject *parent) : window_(window), parser_(parser),QObject(parent)
{
    if (!window)
        throw std::invalid_argument("Nullptr main window");
    if (!parser)
        throw std::invalid_argument("Nullptr parser");
}

void AbstractMainApplication::show() noexcept
{
    window_->show();
}

AbstractMainApplication::~AbstractMainApplication()
{
    delete window_;
    delete parser_;
}
