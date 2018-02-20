#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include "abstractmainapplication.h"
#include "mainwindow.h"
#include "form.h"
#include <memory>

namespace PelvikOrgansExaminationProtocolForm
{
    class MainApplication : public AbstractMainApplication
    {
        Q_OBJECT
    protected:
        Form* fromPtr;
    public:
        explicit MainApplication(QObject *parent = nullptr);
        ~MainApplication() override;
    protected:
        Form* createForm() noexcept;
        bool setNewDataIntoForm() noexcept;
    signals:

    public slots:
        virtual void toPdfForm() noexcept override;
        virtual void printForm() noexcept override;
        virtual void toHtmlForm() noexcept override;
    };
}

#endif // MAINAPPLICATION_H
