#include "abstracmyactionpool.h"

using namespace PelvikOrgansExaminationProtocolForm;

/* create Action with parent qobject.
 * connect &QAction::triggered to MyAction::process().
 */
MyAction::MyAction(QObject *parent): QAction(parent)
{
    connect(this,&MyAction::triggered,this,&MyAction::process);
}

/* create Action with parent qobject and text.
 * connect &QAction::triggered to MyAction::process().
 */
MyAction::MyAction(const QString &text, QObject *parent): QAction(text, parent)
{
    connect(this,&MyAction::triggered,this,&MyAction::process);
}

MyAction::~MyAction()
    {}
