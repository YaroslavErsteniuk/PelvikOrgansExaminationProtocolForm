#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include "abstractmainapplication.h"
#include "mainwindow.h"

namespace PelvikOrgansExaminationProtocolForm
{
    class MainApplication : public AbstractMainApplication
    {
        Q_OBJECT
    protected:
        MainWindow w;
    public:
        explicit MainApplication(AbstractMainWindow* window, AbstractParser* parser, QObject *parent = nullptr);

    signals:

    public slots:
    };
}

#endif // MAINAPPLICATION_H
