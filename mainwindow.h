#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <vector>
#include <QMenu>
#include "abstractmainwindow.h"
#include <stdexcept>
#include "abstracmyactionpool.h"

namespace Ui {
    class MainWindow;
}

class QComboBox;
class QDoubleSpinBox;
class QLineEdit;

namespace PelvikOrgansExaminationProtocolForm
{

class InvalidInitialization:  std::runtime_error
{
public:
    explicit InvalidInitialization (const std::string& what_arg):  std::runtime_error(what_arg)
        {}
};

    /* Class for predefined hard-coded input interface.
     * All function for adding template and question
     * return false and doing nothing.
     */
    class MainWindow : public AbstractMainWindow
    {
        Q_OBJECT
    protected:
        QMenu* fileMenu;
    public:
        /*Initialize  predefined hard-coded input interface.
         * GUI created by Qt-design tool.
         * @askKEywords is a list of keywords to reduce number of "magic" constant.
         * Should be getted from object of KeyParser class.
         */
        explicit MainWindow(const QStringList& askKeywords, QWidget *parent = 0);
        ~MainWindow();

        /* Should be not used from this class.
         * Function return false and doing nothing.
         */
        bool addAsk(AskType ask, QString inputKey) noexcept override;

        /* Should be not used from this class.
         * Function return false and doing nothing.
         */
        bool addAsk(AskType ask, QString inputKey, QString askText) noexcept override;

        /* Should be not used from this class.
         * Function return false and doing nothing.
         */
        bool addAsk(AskType ask, QString inputKey, QString group, QString askText) noexcept override;

        /* Should be not used from this class.
         * Function return false and doing nothing.
         */
        bool addAsk(AskType ask, QRect place, QString inputKey) noexcept override;

        /* Should be not used from this class.
         * Function return false and doing nothing.
         */
        bool addAsk(AskType ask, QRect place, QString inputKey, QString askText) noexcept override;

        /* Should be not used from this class.
         * Function return false and doing nothing.
         */
        bool addFormTemplate(QString htmlTempl) noexcept override;

        /* Should be not used from this class.
         * Function return false and doing nothing.
         */
        bool setFormTemplate(QString htmlTempl) noexcept override;
    protected:
        /* Function for registering @action in UI.
         * If registering is impossible return false
         * else return true.
         */
        virtual bool registerAction(MyAction* action) noexcept override;

        /* Function for ending registration of actions in UI.
         * If all ok return true, otherwise return false.
         * Used for adding a menu to main window.
         */
        virtual bool allActionsRegistered() noexcept override;

        /* One-time-used function for structuring code.
         * Initialise all comboboxes and set the dependencies.
         * On error will return false, otherwise return true.
         */
        bool initializeComboBox() noexcept;

        /* One-time-used function for structuring code.
         * Initialise uterus-dedicated-comboboxes and set the dependencies.
         * On error will return false, otherwise return true.
         */
        bool initializeUterus() noexcept;

        /* Function for structuring code.
         * Initialise ovary-dedicated-comboboxes and set the dependencies.
         * On error will return false, otherwise return true.
         */
        bool initializeOvary(QComboBox* vizualizationOvaryComboBox, QComboBox*  conturOvaryComboBox,
                                         QComboBox*  bordersOvaryComboBox, QComboBox* formationOvaryComboBox,
                                         QComboBox* contentsOvaryComboBox, QDoubleSpinBox* sizeOvaryDoubleSpinBox1,
                                         QDoubleSpinBox* sizeOvaryDoubleSpinBox2, QDoubleSpinBox* sizeOvaryDoubleSpinBox3,
                                         QDoubleSpinBox* volumeOvaryDoubleSpinBox,
                                         QLineEdit* foliculusOvaryEdit, QDoubleSpinBox* diametrOvaryDoubleSpinBox) noexcept;

        /* One-time-used function for structuring code.
         * Bind keywords with widgets.
         * Keywords should be ranged in corresponding to the widgets order.
         * On error will return false, otherwise return true.
         */
        bool initializeWidgets(const QStringList& askKeywords) noexcept;
    public slots:
    private:
        Ui::MainWindow *ui;
    };
}
#endif // MAINWINDOW_H
