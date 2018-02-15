#ifndef FORM_H
#define FORM_H

#include <QObject>
#include <QPair>
#include <QVariant>
#include <map>
#include "asktype.h"

namespace PelvikOrgansExaminationProtocolForm
{
    class Form: public QObject
    {
        Q_OBJECT
    protected:
        QString formTemplate_;
        QString form_;
    public:
        Form(QString formTemplate="") noexcept;
        virtual ~Form() noexcept;

        virtual bool insertAnswer(QString inputKey, QPair<AskTypeEnum,QVariant> answerPair) noexcept;
        virtual bool noAnswer(QString inputKey) noexcept;

        virtual bool setFormTemplate(QString formTemplate) noexcept; //not use "resetForm"
        virtual QString getFormTemplate() const noexcept;

        virtual bool resetForm() noexcept;
        virtual QString getForm(bool* ok_in) const noexcept;
        virtual QString getForm(const std::map<QString, QPair<AskTypeEnum, QVariant> > &answerPairs, bool* ok_in) noexcept;
    protected:
        virtual QString toQString(QPair<AskTypeEnum, QVariant> answerPair, bool* ok_in) const noexcept;
        virtual QString qDatetoQString(QDate d) const noexcept;
    public slots:
        virtual void createPDF() const noexcept;
        virtual void createHTML() const noexcept;
        virtual void printInPrinter() const noexcept;
    };
}

#endif // FORM_H
