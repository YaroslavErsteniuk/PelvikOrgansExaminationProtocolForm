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
        std::unique_ptr<Form*> fromPtr;
    public:
        explicit MainApplication(QObject *parent = nullptr);
    protected:
        Form* createForm() noexcept;
    signals:

    public slots:
    };
}

#endif // MAINAPPLICATION_H
