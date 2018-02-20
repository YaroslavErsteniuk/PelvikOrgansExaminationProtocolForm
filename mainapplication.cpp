#include "mainapplication.h"
#include <QFile>
#include "mainwindow.h"
#include "keyparser.h"

using namespace PelvikOrgansExaminationProtocolForm;

MainApplication::MainApplication(QObject *parent) :AbstractMainApplication(new KeyParser(), parent), fromPtr(nullptr)
{
    fromPtr=createForm();
    if (!fromPtr)
        return;
    window_=new MainWindow(parser_->mentionedAsksKeys());

    connect(window_,&MainWindow::printForm,this,&MainApplication::printForm);
    connect(window_,&MainWindow::toPdfForm,this,&MainApplication::toPdfForm);
    connect(window_,&MainWindow::toHtmlForm,this,&MainApplication::toHtmlForm);
}

MainApplication::~MainApplication()
{
    delete fromPtr;
}

Form* MainApplication::createForm() noexcept
{
    QFile templateFile("template.htm");
    if (!templateFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;
    auto templateInHtml=QString(templateFile.readAll());
    return new Form(templateInHtml);
}

void MainApplication::toPdfForm() noexcept
{
    if (!setNewDataIntoForm())
        return;
    fromPtr->createPDF();
}

void MainApplication::printForm() noexcept
{
    if (!setNewDataIntoForm())
        return;
    fromPtr->printInPrinter();
}


void MainApplication::toHtmlForm() noexcept
{
    if (!setNewDataIntoForm())
        return;
    fromPtr->createHTML();
}

bool MainApplication::setNewDataIntoForm() noexcept
{
    if (!fromPtr->resetForm())
        return false;
    for (const auto& askKey: parser_->mentionedAsksKeys())
    {
        if (!window_->isAnswer(askKey))
            fromPtr->noAnswer(askKey);
        else
            fromPtr->insertAnswer(askKey,window_->getAnswer(askKey));
    }
    return true;
}
