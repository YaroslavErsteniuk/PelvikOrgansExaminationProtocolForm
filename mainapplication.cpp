#include "mainapplication.h"
#include <QFile>
#include "mainwindow.h"
#include "keyparser.h"

using namespace PelvikOrgansExaminationProtocolForm;

MainApplication::MainApplication(QObject *parent) :AbstractMainApplication(nullptr,new KeyParser()), fromPtr(nullptr)
{
    fromPtr=createForm();
    window_=new MainWindow(parser_->mentionedAsksKeys());

}

Form* MainApplication::createForm() noexcept
{
    QFile templateFile("template.html");
    if (!templateFile.open())
        return nullptr;
    auto templateInHtml=QString(templateFile.readAll(QIODevice::ReadOnly | QIODevice::Text));
    return new Form(templateInHtml);
}
