#ifndef ABSTRACMYACTIONPOOL_H
#define ABSTRACMYACTIONPOOL_H
#include <QAction>
#include <QString>
#include <vector>

namespace PelvikOrgansExaminationProtocolForm
{
    /* Abstract base class for action.
     * For more comfortable use inherit QAction,
     * which result in creating only one object for each action.
     * MyAction::process() is main method/slot in this class and should do all usefull job.
     * &QAction::triggered connect to this method.
     */
    class MyAction: public QAction
    {
        Q_OBJECT

    public:
        /* create Action with parent qobject.
         * connect &QAction::triggered to MyAction::process().
         */
        MyAction(QObject *parent = nullptr);

        /* create Action with parent qobject and text.
         * connect &QAction::triggered to MyAction::process().
         */
        MyAction(const QString &text, QObject *parent = nullptr);

        virtual ~MyAction();
    public slots:
        /* Main method/slot in this class and should do all usefull job.
         * &QAction::triggered connect to this method.
         */
        virtual void process() noexcept =0;
    };

    /* Abstract base template class for pool of actions.
     * Within this class you can obtain action from pool.
     * They can be obtain one after another
     * and in any moment you can start obtaining from first action in pool.
     */
    template <class T>class AbstracActionPool
    {
    protected:
        std::vector<T*> actions;
        std::vector<T*>::iterator it_;
    public:
        //In inherited classes should create pool
        AbstracMyActionPool();

        //delete all actions in pool
        virtual ~AbstracMyActionPool()=0;

        //obtain next action from pool
        virtual T* getNextAction() noexcept;

        /* reset internal iterator
         * and start obtaining actions from first.
         */
        virtual auto actionCount() noexcept -> decltype(std::vector<T*>::size());

        /* return size of pool,
         * or, as it is the same,
         * count of different actions.
         */
        virtual void startFromBegining() noexcept;

        // return whether it is last action in pool or not.
        virtual bool nextActionExist() noexcept;
    };

    typedef AbstracActionPool<MyAction> AbstracMyActionPool;
}
#endif // ABSTRACMYACTIONFACTORY_H
