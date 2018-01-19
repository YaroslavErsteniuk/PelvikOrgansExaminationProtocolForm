#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <set>

namespace MainWindowNs
{
    struct OneAsk
    {

    };
}

namespace Ui {
    class MainWindow;
}

namespace PelvikOrgansExaminationProtocolForm
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
    };
}
#endif // MAINWINDOW_H
