#include "gamemap.h"
#include "config.h"

class GameMapPrivate : public DPtrPrivate<GameMap>
{
public:
    //地图图片对象
    QPixmap map1;
    QPixmap map2;

    //地图Y轴坐标
    int map1_posY;
    int map2_posY;

    //地图滚动幅度
    int scroll_speed;

};

GameMap::GameMap(QObject *parent)
    :GameMap(*new GameMapPrivate, parent)
{

}

GameMap::~GameMap()
{

}

GameMap::GameMap(GameMapPrivate &d, QObject *parent)
    :QObject(parent)
    ,DPTR_INIT(&d)
{
    initContent();
}

void GameMap::mapPosition()
{
    DPTR_D(GameMap);
    //处理第一张图片滚动
    d.map1_posY += MAP_SCROLL_SPEED;
    if(d.map1_posY >= 0)
    {
        d.map1_posY =-GAME_HEIGHT;
    }

    //处理第二张图片滚动
    d.map2_posY += MAP_SCROLL_SPEED;
    if(d.map2_posY >= GAME_HEIGHT )
    {
        d.map2_posY =0;
    }

}

QPixmap GameMap::getMap1()
{
    DPTR_D(GameMap);
    return d.map1;
}

QPixmap GameMap::getMap2()
{
    DPTR_D(GameMap);
    return d.map2;
}

int GameMap::getMap1PosY()
{
    DPTR_D(GameMap);
    return d.map1_posY;
}

int GameMap::getMap2PosY()
{
    DPTR_D(GameMap);
    return d.map2_posY;
}

void GameMap::initContent()
{
    DPTR_D(GameMap);
    //初始化加载地图对象
    d.map1.load(MAP_PATH);
    d.map2.load(MAP_PATH);

    //设置地图其实y轴坐标
    d.map1_posY = -GAME_HEIGHT;
    d.map2_posY = 0;

    //设置地图滚动速度
    d.scroll_speed = MAP_SCROLL_SPEED;

}
