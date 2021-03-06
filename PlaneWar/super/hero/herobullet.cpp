#include "herobullet.h"
#include <QPixmap>
#include "config.h"
#include <QRect>

class HeroBulletPrivate : public DPtrPrivate<HeroBullet>
{
public:
    //子弹资源对象
    QPixmap bullet;
    //子弹坐标
    int X;
    int Y;
    //子弹移动速度
    int bulletSpeed;
    //子弹是否闲置
    bool isFree;
    //子弹的矩形边框（用于碰撞检测）
    QRect bulletRect;
};

HeroBullet::HeroBullet(QObject *parent)
    :HeroBullet(*new HeroBulletPrivate, parent)
{

}

HeroBullet::~HeroBullet()
{

}

HeroBullet::HeroBullet(HeroBulletPrivate &d, QObject *parent)
    :QObject(parent)
    ,DPTR_INIT(&d)
{
    initContent();
}

void HeroBullet::initContent()
{
    DPTR_D(HeroBullet);
    //加载子弹资源
    d.bullet.load(BULLET_PATH);

    //子弹坐标 初始坐标可随意设置，后期会重置
    d.X = GAME_WIDTH * 0.5 - d.bullet.width() * 0.5;
    d.Y = GAME_HEIGHT;

    //子弹状态
    d.isFree = true;

    //子弹速度
    d.bulletSpeed = BULLET_SPEED;

    //子弹矩形框
    d.bulletRect.setWidth(d.bullet.width());
    d.bulletRect.setHeight(d.bullet.height());
    d.bulletRect.moveTo(d.X, d.Y);

}

void HeroBullet::updatePosition()
{
    DPTR_D(HeroBullet);
    //如果子弹是空闲状态，不需要坐标计算
    //玩家飞机可以控制子弹的空闲状态为false
    if(d.isFree)
    {
        return;
    }

    //子弹向上移动
    d.Y -= d.bulletSpeed;
    d.bulletRect.moveTo(d.X, d.Y);

    if(d.Y <= - d.bulletRect.height())
    {
        d.isFree = true;
    }

}

bool HeroBullet::getIsFree()
{
    DPTR_D(HeroBullet);
    return d.isFree;
}

int HeroBullet::getX()
{
    DPTR_D(HeroBullet);
    return d.X;
}

int HeroBullet::getY()
{
    DPTR_D(HeroBullet);
    return d.Y;
}

QRect HeroBullet::getBulletRect()
{
    DPTR_D(HeroBullet);
    return d.bulletRect;
}

void HeroBullet::setX(int x)
{
    DPTR_D(HeroBullet);
    d.X = x;
}

void HeroBullet::setY(int y)
{
    DPTR_D(HeroBullet);
    d.Y = y;
}

void HeroBullet::setIsFree(bool isFree)
{
    DPTR_D(HeroBullet);
    d.isFree = isFree;
}

QPixmap HeroBullet::getBullet()
{
    DPTR_D(HeroBullet);
    return d.bullet;
}
