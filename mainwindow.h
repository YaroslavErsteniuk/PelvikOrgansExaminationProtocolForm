#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <vector>
#include "abstractmainwindow.h"
#include <stdexcept>

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
    explicit InvalidInitialization (const string& what_arg):  std::runtime_error(what_arg)
        {}
};

    /* Class for predefined input interface.
     * All function for adding template and question
     * return false and doing nothing.
     */
    class MainWindow : public AbstractMainWindow
    {
        Q_OBJECT
    private:
    public:
        explicit MainWindow(const QStringList& askKeywords, QWidget *parent = 0);
        ~MainWindow();

        bool addAsk(AskType ask, QString inputKey) noexcept override;
        bool addAsk(AskType ask, QString inputKey, QString askText) noexcept override;
        bool addAsk(AskType ask, QString inputKey, QString group) noexcept override;
        bool addAsk(AskType ask, QString inputKey, QString group, QString askText) noexcept override;
        bool addAsk(AskType ask, QRect place, QString inputKey) noexcept override;
        bool addAsk(AskType ask, QRect place, QString inputKey, QString askText) noexcept override;
        bool addFormTemplate(QString htmlTempl) noexcept override;
        bool setFormTemplate(QString htmlTempl) noexcept override;
    protected:
        bool initializeComboBox() noexcept;
        bool initializeUterus() noexcept;
        bool initializeOvary(QComboBox* vizualizationOvaryComboBox, QComboBox*  conturOvaryComboBox,
                                         QComboBox*  bordersOvaryComboBox, QComboBox* formationOvaryComboBox,
                                         QComboBox* contentsOvaryComboBox, QDoubleSpinBox* sizeOvaryDoubleSpinBox1,
                                         QDoubleSpinBox* sizeOvaryDoubleSpinBox2, QDoubleSpinBox* sizeOvaryDoubleSpinBox3,
                                         QLineEdit* foliculusOvaryEdit, QDoubleSpinBox* diametrOvaryDoubleSpinBox) noexcept;
        bool initializeWidgets(const QStringList& askKeywords) noexcept;
    private:
        Ui::MainWindow *ui;
    };
}
#endif // MAINWINDOW_H
