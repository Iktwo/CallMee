#include <QtGui/QApplication>
#include "autoanswer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AutoAnswer aa;

    return app.exec();
}
