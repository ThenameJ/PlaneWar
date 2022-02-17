#include "widgetscene.h"
#include "gamemap.h"
#include <QIcon>
#include <QTimer>
#include <QPainter>

class WidgetScenePrivate : public DPtrPrivate<WidgetScene>
{
public:
    QTimer      timer;
    GameMap     gameMap;
};

WidgetScene::WidgetScene(QWidget *parent)
    :WidgetScene(*new WidgetScenePrivate(), parent)
{

}

WidgetScene::~WidgetScene()
{

}

WidgetScene::WidgetScene(WidgetScenePrivate &d, QWidget *parent)
    :QWidget(parent)
    ,DPTR_INIT(&d)
{
    initScene();
}

void WidgetScene::initScene()
{
    DPTR_D(WidgetScene);
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置图标资源
    setWindowIcon(QIcon( GAME_ICON));

    d.timer.setInterval(GAME_RATE);

    playGame();
}

void WidgetScene::playGame()
{
    DPTR_D(WidgetScene);
    d.timer.start();

    //监听定时器
    connect(&d.timer,&QTimer::timeout,[=](){
        //更新游戏中元素的坐标
        updatePosition();
        //重新绘制图片
        update();
    });
}

void WidgetScene::updatePosition()
{
    DPTR_D(WidgetScene);
    d.gameMap.mapPosition();
}

void WidgetScene::paintEvent(QPaintEvent *event)
{
    DPTR_D(WidgetScene);
    Q_UNUSED(event)
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0, d.gameMap.getMap1PosY(), d.gameMap.getMap1());
    painter.drawPixmap(0, d.gameMap.getMap2PosY(), d.gameMap.getMap2());
}

