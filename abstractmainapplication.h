#ifndef ABSTRACTMAINAPPLICATION_H
#define ABSTRACTMAINAPPLICATION_H

#include <QObject>
#include "abstractmainwindow.h"
#include "abstractparser.h"

namespace PelvikOrgansExaminationProtocolForm
{
    class AbstractMainApplication : public QObject
    {
        Q_OBJECT
    protected:
       AbstractMainWindow* window_;
       AbstractParser* parser_;
    public:
        AbstractMainApplication(AbstractMainWindow* window, AbstractParser* parser, QObject *parent = nullptr);
        AbstractMainApplication(AbstractParser* parser, QObject *parent = nullptr);

        virtual ~AbstractMainApplication();
    signals:

    public slots:
        virtual void toPdfForm() noexcept =0;
        virtual void printForm() noexcept =0;

        virtual void show() noexcept;
    };
}

#endif // ABSTRACTMAINAPPLICATION_H
