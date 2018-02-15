#include <QDate>
#include "form.h"

#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QPrintDialog>

using namespace PelvikOrgansExaminationProtocolForm;

Form::Form(QString formTemplate) noexcept: formTemplate_(formTemplate), form_(formTemplate)
{
}

Form::~Form() noexcept
{
}

bool Form::setFormTemplate(QString formTemplate) noexcept//not use "resetForm"
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

bool Form::resetForm() noexcept
{
    if (formTemplate_.isEmpty())
        return false;
    form_=formTemplate_;
    return true;
}

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

void Form::createPDF() const noexcept
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (fileName.isEmpty() || (!fileName.compare(".pdf",Qt::CaseInsensitive)))
        return;
    if (!fileName.endsWith(".pdf",Qt::CaseInsensitive))
        fileName.append(".pdf");
    QTextDocument textDoc;
    textDoc.setHtml(form_);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    textDoc.setPageSize(printer.pageRect(QPrinter::Millimeter).size()); // to hide the page number
    textDoc.print(&printer);
}

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

void Form::printInPrinter() const noexcept
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer);
    dialog.setOption(QAbstractPrintDialog::PrintPageRange,false);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QTextDocument textDoc;
    textDoc.setHtml(form_);
    textDoc.setPageSize(printer.pageRect(QPrinter::Millimeter).size()); // to hide the page number
    textDoc.print(&printer);
}
