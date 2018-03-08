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
        //Slot for creating pdf on template's base
        virtual void toPdfForm() noexcept =0;

        //slot for printing form
        virtual void printForm() noexcept =0;

        //slot for creating html on template's base
        virtual void toHtmlForm() noexcept=0;

        /* Slot which display UI.
         * In defaul version just invoke window_->show().
         */
        virtual void show() noexcept;
    };
}

#endif // ABSTRACTMAINAPPLICATION_H
