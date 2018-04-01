#ifndef SAVEACTIONPOOL_H
#define SAVEACTIONPOOL_H

#include "abstracmyactionpool.h"
#include "abstractmainapplication.h"

namespace PelvikOrgansExaminationProtocolForm
{
    //Action for creating pdf from form
    class CreatePDFAction:MyAction
    {
        Q_OBJECT
    protected:
       AbstractMainApplication* apl_=nullptr;
    public:
        /* Use constructors of base class
         * for creating action with parent qobject or
         * parent object and text.
         */
        using MyAction::MyAction;

        // Set and get methods for application
        void setAplication(AbstractMainApplication* apl) noexcept;
        const AbstractMainApplication *getApplication() const noexcept;
    public slots:
        /* In this class create pdf on template's base.
         * Use QtWebkit and GUI-classes for creating
         * and selecting a name for a file.
         *
         * Main method/slot in this class and should do all usefull job.
         * &QAction::triggered connect to this method.
         */
        virtual void process() noexcept override;
    };

    //Action for creating html from form
    class CreateHTMLAction:MyAction
    {
        Q_OBJECT
    protected:
       AbstractMainApplication* apl_=nullptr;
    public:
        /* Use constructors of base class
         * for creating action with parent qobject or
         * parent object and text.
         */
        using MyAction::MyAction;

        // Set and get methods for application
        void setAplication(AbstractMainApplication* apl) noexcept;
        const AbstractMainApplication *getApplication() const noexcept;
    public slots:
        /* In this class creating html on template's base.
         * Use GUI-classes for creating
         * and selecting a name for a file.
         *
         * Main method/slot in this class and should do all usefull job.
         * &QAction::triggered connect to this method.
         */
        virtual void process() noexcept override;
    };


    //Action for printing from form
    class printInPrinter:MyAction
    {
        Q_OBJECT
    protected:
       AbstractMainApplication* apl_=nullptr;
    public:
        /* Use constructors of base class
         * for creating action with parent qobject or
         * parent object and text.
         */
        using MyAction::MyAction;

        // Set and get methods for application
        void setAplication(AbstractMainApplication* apl) noexcept;
        const AbstractMainApplication *getApplication() const noexcept;
    public slots:
        /* In this class printing on template's base.
         * Use QtWebkit and GUI-classes for printing.
         * and getting print information.
         *
         * Main method/slot in this class and should do all usefull job.
         * &QAction::triggered connect to this method.
         */
        virtual void process() noexcept override;
    };

    class SaveActionPool : public AbstracMyActionPool
    {
    public:
        /* Create pool, which includes
         * printInPrinter, CreateHTMLAction and CreatePDFAction.
         * AbstractMainApplication object is needed be actions objects
         */
        SaveActionPool(AbstractMainApplication* apl);

        //delete all actions in pool
        virtual ~SaveActionPool() override;
    };
}

#endif // SAVEACTIONPOOL_H
