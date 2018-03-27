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

//In inherited classes should create pool
AbstracMyActionPool::AbstracMyActionPool()
{
    it_=actions.begin();
}

//delete all actions in pool
AbstracMyActionPool::~AbstracMyActionPool()
{
    for (auto obj : actions)
    {
        delete obj;
    }
}

//obtain next action from pool
template <class T> T* AbstracMyActionPool<T>::getNextAction() noexcept
{
    return *(it_++);
}

/* reset internal iterator
 * and start obtaining actions from first.
 */
void AbstracMyActionPool::startFromBegining() noexcept
{
    it_=actions.begin();
}

/* return size of pool,
 * or, as it is the same,
 * count of different actions.
 */
template <class T> auto AbstracMyActionPool<T>::startFromBegining() noexcept ->
    decltype(std::vector<T*>::size())
{
    return actions.size();
}

// return whether it is last action in pool or not.
bool AbstracMyActionPool::nextActionExist() noexcept
{
    return bool(it_);
}
