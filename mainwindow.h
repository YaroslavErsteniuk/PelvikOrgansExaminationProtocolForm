#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include "abstractmainwindow.h"

namespace Ui {
    class MainWindow;
}

namespace PelvikOrgansExaminationProtocolForm
{
    /* Class for predefined input interface.
     * All function for adding template and question
     * return false and doing nothing.
     */
    class MainWindow : public AbstractMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
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
    private:
        Ui::MainWindow *ui;
    };
}
#endif // MAINWINDOW_H
