#include "mainapplication.h"
#include <QFile>
#include "mainwindow.h"
#include "keyparser.h"

using namespace PelvikOrgansExaminationProtocolForm;

/* Connect signals from GUI-class to slots,
 * create GUI-class, parser-class and form-class.
 * constructor will throw std::invalid_argument
 * with propriate string if form can't be created:
 * when it's impossible to open or to read file "template.htm".
 */
MainApplication::MainApplication(QObject *parent) :AbstractMainApplication(new KeyParser(), parent), fromPtr(nullptr)
{
    /*   Now this is realised in AbstractMainApplication
    fromPtr=createForm();
    if (!fromPtr)
        throw std::invalid_argument("Nullptr form");
    */
    window_=new MainWindow(parser_->mentionedAsksKeys());

    connect(window_,&MainWindow::printForm,this,&MainApplication::printForm);
    connect(window_,&MainWindow::toPdfForm,this,&MainApplication::toPdfForm);
    connect(window_,&MainWindow::toHtmlForm,this,&MainApplication::toHtmlForm);
}

/* Replaced by Abstract Factory template.
 *
 * Realisation of factory method pattern.
 * In this class this function try
 * to open and read file "template.htm".
 * If it can't be done return nullptr,
 * else return pointer to new Form object.
 */
/*Form* MainApplication::createForm() noexcept
{
    QFile templateFile("template.htm");
    if (!templateFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;
    auto templateInHtml=QString(templateFile.readAll());
    return new Form(templateInHtml);
}*/

/* Slot for creating pdf on template's base.
 * Before creating function try to update template according to
 * data, inputed to GUI.
 * If updating is impossible, creating canceled.
 */
void MainApplication::toPdfForm() noexcept
{
    if (!setNewDataIntoForm())
        return;
    fromPtr->createPDF();
}

/* Slot for printing form.
 * Before printing function try to update template according to
 * data, inputed to GUI.
 * If updating is impossible, printing canceled.
 */
void MainApplication::printForm() noexcept
{
    if (!setNewDataIntoForm())
        return;
    fromPtr->printInPrinter();
}

/* Slot for creating html on template's base.
 * Before creating function try to update template according to
 * data, inputed to GUI.
 * If updating is impossible, creating canceled.
 */
void MainApplication::toHtmlForm() noexcept
{
    if (!setNewDataIntoForm())
        return;
    fromPtr->createHTML();
}

/* This function try to reset template,
 * then take from parser all keys,
 * read from GUI answers and add them to template.
 * If an error occured while doing this return false,
 * on success return true.
 */
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
