#ifndef ABSTRACTMAINAPPLICATION_H
#define ABSTRACTMAINAPPLICATION_H

#include <QObject>
#include "abstractmainwindow.h"
#include "abstractfactoryparser.h"
#include "abstractform.h"

namespace PelvikOrgansExaminationProtocolForm
{
    /* Abstract interface class,
     * whose derived classes will join functional-classes with UI-classes.
     */
    class AbstractMainApplication : public QObject
    {
        Q_OBJECT
    protected:
        // Main UI-class
       AbstractMainWindow* window_;

       /* Main functional-class - read template from some source
        * and on that base can create UI-form and template's object.
        */
       AbstractFactoryParser* parser_;

       AbstractForm* fromPtr;
    public:
       /* Parser_ will create fromPrt.
        * If @window or @parser is nullptr
        * constructor will throw std::invalid_argument
        * with propriate string.
        * If parser_ return nullptr
        * throw std::logic_error
        * with propriate string.
        */
        AbstractMainApplication(AbstractMainWindow* window, AbstractFactoryParser* parser, QObject *parent = nullptr);

        /* Parser_ will create fromPrt.
         * Constructor, which can be used if creation of window_ debend on parser_.
         * If @window or @parser is nullptr
         * constructor will throw std::invalid_argument
         * with propriate string.
         * If parser_ return nullptr
         * throw std::logic_error
         * with propriate string.
         */
        AbstractMainApplication(AbstractFactoryParser* parser, QObject *parent = nullptr);

        virtual ~AbstractMainApplication();
    signals:

    public slots:
        /* This function try to reset template,
         * then read answers from UI and add them to template.
         * If an error occured while doing this return false,
         * on success return true.
         */
        virtual bool setNewDataIntoForm() noexcept =0;

        //Moved to UI
        //Slot for creating pdf on template's base
        //virtual void toPdfForm() noexcept =0;

        //Moved to UI
        //slot for printing form
        //virtual void printForm() noexcept =0;

        //Moved to UI
        //slot for creating html on template's base
        //virtual void toHtmlForm() noexcept=0;

        /* Slot which display UI.
         * In defaul version just invoke window_->show().
         */
        virtual void show() noexcept;

        /* Function for getting current version of template realisation.
         * @ok_in is parameter for checking the validity of template realisation.
         * Default realisation use AbstractForm::getForm.
         */
        virtual QString getForm(bool* ok_in) const noexcept;

        /* Get version of form,
         * in which answers have been inserted.
         * @answerPairs is a map of answer in form of <Key,<Type,Value>>.
         * @ok_in is parameter for checking the validity of template realisation.
         * If at least one value can't be converted or inserted
         * the template is consider to be invalid.
         * Default realisation use AbstractForm::getForm.
         */
        virtual QString getForm(const std::map<QString, QPair<AskTypeEnum, QVariant> > &answerPairs, bool* ok_in) noexcept;
    };
}

#endif // ABSTRACTMAINAPPLICATION_H
