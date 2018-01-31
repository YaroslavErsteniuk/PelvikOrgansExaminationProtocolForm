#include <QDate>
#include "form.h"

#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QPrintDialog>

using namespace PelvikOrgansExaminationProtocolForm;

Form::Form(QString formTemplate="") noexcept: formTemplate_(formTemplate), form_(formTemplate)
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
    const QString valueToInsert=toQString(answerPair,ok);
    if (!ok)
        return false;
    auto iot=form_.indexOf(templateAll,0,Qt::CaseInsensitive);
    if (iot==-1)
        return false;
    form_.replace(iot,templateAll.size(),valueToInsert);
    return true;
}

QString Form::getForm(bool* ok_in) const noexcept
{
    if (form_.isEmpty())
    {
        if (ok_in)
            ok_in=false;
        return QString();
    }
    if (ok_in)
        ok_in=true;
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
            ok_in=false;
        return QString();
    }
    if (ok_in)
        ok_in=true;
    return form_;
}

QString Form::toQString(QPair<AskType, QVariant> answerPair, bool* ok_in) const noexcept
{
    if (!(answerPair.second.isValid()))
    {
        if (ok_in)
            ok_in=false;
        return QString();
    }
    bool ok=true;
    QString result;

    switch (answerPair.first.askTypeValue)
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
            result=QString::number(answerPair.second.toDouble(),'f',answerPair.first.floatPrecision);
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
        return QString();
    }
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

void Form::printInPrinter() const noexcept
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);
    dialog.setOption(QAbstractPrintDialog::PrintPageRange,false);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QTextDocument textDoc;
    textDoc.setHtml(form_);
    textDoc.setPageSize(printer.pageRect(QPrinter::Millimeter).size()); // to hide the page number
    textDoc.print(&printer);
}