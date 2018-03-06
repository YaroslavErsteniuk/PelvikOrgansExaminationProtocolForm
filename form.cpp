#include <QDate>
#include "form.h"

#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QPrintDialog>

#include <QtWebKitWidgets/QWebView>

using namespace PelvikOrgansExaminationProtocolForm;

Form::Form(QString formTemplate) noexcept: formTemplate_(formTemplate), form_(formTemplate)
{
}

Form::~Form() noexcept
{
}

/* Setter for template.
 * To update template realisation Form::resetForm should be used explicitly.
 */
bool Form::setFormTemplate(QString formTemplate) noexcept
{
    if (formTemplate.isEmpty())
        return false;
    formTemplate_=formTemplate;
    return true;
}

QString Form::getFormTemplate() const noexcept
{
    return formTemplate_;
}

/* Reset template realisation according to template.
 * All changes would be discarted,
 */
bool Form::resetForm() noexcept
{
    if (formTemplate_.isEmpty())
        return false;
    form_=formTemplate_;
    return true;
}

/* Insert answer in current version of template realisation.
 * @inputKey represent the key of question,
 * @inputKey is a pair<Type,Value>.
 * If value is inserted return true;
 * If value can't be converted to QString acording to Type
 * or template haven't @inputKey return false.
 */
bool Form::insertAnswer(QString inputKey, QPair<AskTypeEnum,QVariant> answerPair) noexcept
{
    if (form_.isEmpty())
            return false;
    static const QString templateBegin="<ASK key=\"";
    static const QString templateEnd="\">";
    const QString templateAll=templateBegin+inputKey+templateEnd;
    bool ok=false;
    const QString valueToInsert=toQString(answerPair,&ok);
    if (!ok)
        return false;
    auto iot=form_.indexOf(templateAll,0,Qt::CaseInsensitive);
    if (iot==-1)
        return false;
    static const QString inputTemplateBegin="<ANS key=\"";
    static const QString inputTemplateEnd="\"/>";
    const QString inputTemplateAll=inputTemplateBegin+inputKey+inputTemplateEnd;
    auto iotInput=form_.indexOf(inputTemplateAll,iot,Qt::CaseInsensitive);
    if (iotInput==-1)
        return false;
    static const QString templateEndAll="</ASK>";
    auto iotEnd=form_.indexOf(templateEndAll,iotInput,Qt::CaseInsensitive);
    if (iotEnd==-1)
        return false;
    form_.remove(iotEnd,templateEndAll.size());
    form_.replace(iotInput,inputTemplateAll.size(),valueToInsert);
    form_.remove(iot,templateAll.size());
    return true;
}

/* Should be used if question with key @inputKey haven't answer.
 * Delete place for that answer in template.
 * @inputKey - key for question which haven't answer.
 * Return true if deleting was successfull,
 * return false if template haven't @inputKey.
 */
bool Form::noAnswer(QString inputKey) noexcept
{
    if (form_.isEmpty())
            return false;
    static const QString templateBegin="<ASK key=\"";
    static const QString templateEnd="\">";
    const QString templateAll=templateBegin+inputKey+templateEnd;
    auto iot=form_.indexOf(templateAll,0,Qt::CaseInsensitive);
    if (iot==-1)
        return false;
    static const QString templateEndAll="</ASK>";
    auto iotEnd=form_.indexOf(templateEndAll,iot,Qt::CaseInsensitive);
    if (iotEnd==-1)
        return false;
    form_.remove(iot,iotEnd-iot+1);
    return true;
}

/* Function for getting current version of template realisation.
 * @ok_in) is parameter for checking the validity of template realisation.
 * If current version of template realisation is empty retun QString and set value of *(@ok_in) to false.
 * Otherwise return current version of template realisation and set value of *(@ok_in) to true.
 */
QString Form::getForm(bool* ok_in) const noexcept
{
    if (form_.isEmpty())
    {
        if (ok_in)
            *ok_in=false;
        return QString();
    }
    if (ok_in)
        *ok_in=true;
    return form_;

}

/* Except for getting current version of template realisation,
 * this version insert answers in @answerPairs using the Form::insertAnswer.
 * @answerPairs is a map of answer in form of <Key,<Type,Value>>.
 * @ok_in is parameter for checking the validity of template realisation.
 * If at least one value can't be converted to QString acording to Type
 * or template haven't Key @ok_in is set to false and function return QString().
 * If current version of template realisation is empty retun QString and set value of *(@ok_in) to false.
 * Otherwise return current version of template realisation and set value of *(@ok_in) to true.
 */
QString Form::getForm(const std::map<QString,QPair<AskTypeEnum,QVariant> >& answerPairs, bool* ok_in) noexcept
{
    bool ok=true;
    for (auto it=answerPairs.cbegin(); it!=answerPairs.cend() && ok; ++it)
        ok=insertAnswer(it->first,it->second);
    if (form_.isEmpty() || !ok)
    {
        if (ok_in)
            *ok_in=false;
        return QString();
    }
    if (ok_in)
        *ok_in=true;
    return form_;
}

QString Form::toQString(QPair<AskTypeEnum, QVariant> answerPair, bool* ok_in) const noexcept
{
    if (!(answerPair.second.isValid()))
    {
        if (ok_in)
            *ok_in=false;
        return QString();
    }
    bool ok=true;
    QString result;

    switch (answerPair.first)
    {
    case stringAskType:
    case enumAskType: //input type for list of variants
        //stringAskType and enumAskType both use QString
        if (answerPair.second.userType()==QMetaType::QString)
            result=answerPair.second.toString();
        else
            ok=false;
        break;
    case numberAskType:
        if (answerPair.second.userType()==QMetaType::Int)
            result=answerPair.second.toString();
        else
            ok=false;
        break;
    case floatAskType:
        if (answerPair.second.userType()==QMetaType::Double)
            result=QString::number(answerPair.second.toDouble(),'f',2);
        else
            ok=false;
        break;
    case dateAskType:
        if (answerPair.second.userType()==QMetaType::QDate)
            result=qDatetoQString(answerPair.second.toDate());
        else
            ok=false;
        break;
    default:
        ok=false;
    }
    *ok_in=ok;
    return result;
}

QString Form::qDatetoQString(QDate d) const noexcept
{
    return d.toString(Qt::ISODate);
}

/* Slot for creating pdf on template's base.
 * Use QtWebkit and GUI for creating.
 *
 * TODO separate GUI-classes from functional classes.
 */
void Form::createPDF() const noexcept
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (fileName.isEmpty() || (!fileName.compare(".pdf",Qt::CaseInsensitive)))
        return;
    if (!fileName.endsWith(".pdf",Qt::CaseInsensitive))
        fileName.append(".pdf");
    //QTextDocument textDoc;
    //textDoc.setHtml(form_);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    //textDoc.setPageSize(printer.pageRect(QPrinter::Millimeter).size()); // to hide the page number
    //textDoc.print(&printer);
    QWebView *view = new QWebView();
    view->setHtml(form_);
    view->print(&printer);
    view->deleteLater();
}

/* Slot for creating html on template's base.
 * Use GUI-classes for creating.
 *
 * TODO separate GUI from functional classes.
 */
void Form::createHTML() const noexcept
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export Html", QString(), "*.htm");
    if (fileName.isEmpty() || (!fileName.compare(".htm",Qt::CaseInsensitive)))
        return;
    if (!fileName.endsWith(".htm",Qt::CaseInsensitive))
        fileName.append(".htm");
    QFile htmlRes(fileName);
    if (!htmlRes.open(QFile::WriteOnly | QFile::Text))
        return;
    if (-1==htmlRes.write(form_.toLocal8Bit()))
        return;
}

/* Slot for printing on template's base.
 * Use QtWebkit and GUI-classes for printing.
 *
 * TODO separate GUI from functional classes.
 */
void Form::printInPrinter() const noexcept
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer);
    dialog.setOption(QAbstractPrintDialog::PrintPageRange,false);
    if (dialog.exec() != QDialog::Accepted)
        return;
    //QTextDocument textDoc;
    //textDoc.setHtml(form_);
    //textDoc.setPageSize(printer.pageRect(QPrinter::Millimeter).size()); // to hide the page number
    //textDoc.print(&printer);

    QWebView *view = new QWebView();
    view->setHtml(form_);
    view->print(&printer);
    view->deleteLater();
}
