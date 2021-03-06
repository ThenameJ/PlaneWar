#include "widgetscene.h"
#include <QApplication>
#include <QResource>
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QResource::registerResource(GAME_RES_PATH);

    WidgetScene w;
    w.show();

    return a.exec();
}
