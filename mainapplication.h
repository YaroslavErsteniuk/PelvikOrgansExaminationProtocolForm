#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QObject>
#include "mainwindow.h"

namespace PelvikOrgansExaminationProtocolForm
{
    class MainApplication : public QObject
    {
        Q_OBJECT
    protected:
        MainWindow w;
    public:
        explicit MainApplication(QObject *parent = nullptr);

    signals:

    public slots:
    };
}

#endif // MAINAPPLICATION_H
