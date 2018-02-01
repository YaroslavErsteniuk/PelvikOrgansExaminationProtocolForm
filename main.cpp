#include "mainapplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PelvikOrgansExaminationProtocolForm::MainApplication ma;
    ma.show();
    return a.exec();
}
