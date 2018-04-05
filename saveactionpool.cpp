#include "saveactionpool.h"
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QPrintDialog>

#include <QtWebKitWidgets/QWebView>
using namespace PelvikOrgansExaminationProtocolForm;

// Set and get methods for application
void CreatePDFAction::setAplication(AbstractMainApplication* apl) noexcept
    { apl_=apl; }
const AbstractMainApplication* CreatePDFAction::getApplication() const noexcept
    { return apl_; }

/* In this class create pdf on template's base.
 * Use QtWebkit and GUI-classes for creating
 * and selecting a name for a file.
 *
 * Main method/slot in this class and should do all usefull job.
 * &QAction::triggered connect to this method.
 */
void CreatePDFAction::process() noexcept
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (fileName.isEmpty() || (!fileName.compare(".pdf",Qt::CaseInsensitive)))
        return;
    if (!fileName.endsWith(".pdf",Qt::CaseInsensitive))
        fileName.append(".pdf");

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QWebView *view = new QWebView();
    apl_->setNewDataIntoForm();
    view->setHtml(apl_->getForm());
    view->print(&printer);
    view->deleteLater();
}

// Set and get methods for application
void CreateHTMLAction::setAplication(AbstractMainApplication* apl) noexcept
    { apl_=apl; }
const AbstractMainApplication* CreateHTMLAction::getApplication() const noexcept
    { return apl_; }

/* In this class create pdf on template's base.
 * Use QtWebkit and GUI-classes for creating
 * and selecting a name for a file.
 *
 * Main method/slot in this class and should do all usefull job.
 * &QAction::triggered connect to this method.
 */
void CreateHTMLAction::process() noexcept
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export Html", QString(), "*.htm");
    if (fileName.isEmpty() || (!fileName.compare(".htm",Qt::CaseInsensitive)))
        return;
    if (!fileName.endsWith(".htm",Qt::CaseInsensitive))
        fileName.append(".htm");
    QFile htmlRes(fileName);
    if (!htmlRes.open(QFile::WriteOnly | QFile::Text))
        return;
    apl_->setNewDataIntoForm();
    if (-1==htmlRes.write(apl_->getForm().toLocal8Bit()))
        return;
}

// Set and get methods for application
void printInPrinter::setAplication(AbstractMainApplication* apl) noexcept
    { apl_=apl; }
const AbstractMainApplication* printInPrinter::getApplication() const noexcept
    { return apl_; }

/* In this class create pdf on template's base.
 * Use QtWebkit and GUI-classes for creating
 * and selecting a name for a file.
 *
 * Main method/slot in this class and should do all usefull job.
 * &QAction::triggered connect to this method.
 */
void printInPrinter::process() noexcept
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer);
    dialog.setOption(QAbstractPrintDialog::PrintPageRange,false);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QWebView *view = new QWebView();
    apl_->setNewDataIntoForm();
    view->setHtml(apl_->getForm());
    view->print(&printer);
    view->deleteLater();
}

/* Create pool, which includes
 * printInPrinter, CreateHTMLAction and CreatePDFAction.
 * AbstractMainApplication object is needed be actions objects
 */
SaveActionPool::SaveActionPool(AbstractMainApplication* apl): AbstracActionPool<MyAction>()
{
    auto actionPDF=new CreatePDFAction(QObject::tr("Import to pdf..."));
    actionPDF->setShortcuts(QKeySequence::Save);
    actionPDF->setAplication(apl);
    actions.push_back(actionPDF);

    auto actionHTML=new CreateHTMLAction(QObject::tr("Import to html..."));
    actionHTML->setShortcuts(QList<QKeySequence>({QKeySequence(QObject::tr("Ctrl+h"))}));
    actionHTML->setAplication(apl);
    actions.push_back(actionHTML);

    auto actionPrint=new printInPrinter(QObject::tr("Print..."));
    actionPrint->setShortcuts(QKeySequence::Print);
    actionPrint->setAplication(apl);
    actions.push_back(actionPrint);

    it_=actions.begin();
}

//delete all actions in pool
//all delation is done in base class
SaveActionPool::~SaveActionPool()
{
    /*for (auto ac : actions)
    {
        delete ac;
    }*/
}
