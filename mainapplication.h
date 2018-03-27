#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include "abstractmainapplication.h"
#include "mainwindow.h"
#include "form.h"
#include <memory>

namespace PelvikOrgansExaminationProtocolForm
{
    /* Simple realisation of AbstractMainApplication
     * with predefined hardcoded GUI and Form.
     * This class use mainwindow as GUI-class,
     * Form as class for representing template
     * and KeyParser as parserClass.
     */
    class MainApplication : public AbstractMainApplication
    {
        Q_OBJECT
    protected:
        //Form* fromPtr;
    public:
        /* Connect signals from GUI-class to slots,
         * create GUI-class, parser-class and form-class.
         * constructor will throw std::invalid_argument
         * with propriate string if form can't be created:
         * when it's impossible to open or to read file "template.htm".
         */
        explicit MainApplication(QObject *parent = nullptr);
    protected:
        /* Replaced by Abstract Factory template.
         *
         * Realisation of factory method pattern.
         * In this class this function try
         * to open and read file "template.htm".
         * If it can't be done return nullptr,
         * else return pointer to new Form object.
         */
        //Form* createForm() noexcept;
    signals:

    public slots:
        /* This function try to reset template,
         * then take from parser all keys,
         * read from GUI answers and add them to template.
         * If an error occured while doing this return false,
         * on success return true.
         */
        virtual bool setNewDataIntoForm() noexcept override;

        /* Moved to GUI.
         *
         * Slot for creating pdf on template's base.
         * Before creating function try to update template according to
         * data, inputed to GUI.
         * If updating is impossible, creating canceled.
         */
        //virtual void toPdfForm() noexcept override;

        /* Moved to GUI.
         *
         * Slot for printing form.
         * Before printing function try to update template according to
         * data, inputed to GUI.
         * If updating is impossible, printing canceled.
         */
        //virtual void printForm() noexcept override;

        /* Moved to GUI.
         *
         * Slot for creating html on template's base.
         * Before creating function try to update template according to
         * data, inputed to GUI.
         * If updating is impossible, creating canceled.
         */
        //virtual void toHtmlForm() noexcept override;
    };
}

#endif // MAINAPPLICATION_H
