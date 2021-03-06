#include "heroplane.h"
#include <QPixmap>
#include "config.h"
#include <QRect>

class HeroPlanePrivate : public DPtrPrivate<HeroPlane>
{
public:
    //飞机资源 对象
    QPixmap plane;

    //飞机坐标
    int X;
    int Y;

    //飞机的矩形边框
    QRect rect;

    HeroBullet  bullets[BULLET_NUM];
    int         recorder;

};

HeroPlane::HeroPlane(QObject *parent)
    :HeroPlane(*new HeroPlanePrivate, parent)
{

}

HeroPlane::~HeroPlane()
{

}

HeroPlane::HeroPlane(HeroPlanePrivate &d, QObject *parent)
    :QObject(parent)
    ,DPTR_INIT(&d)
{
    initContent();
}

void HeroPlane::shoot()
{
    DPTR_D(HeroPlane);
    //累加时间间隔记录变量
    d.recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if (d.recorder < BULLET_INTERVAL)
    {
        return;
    }
    //到达发射时间处理
    //重置发射时间间隔记录
    d.recorder = 0;

    //发射子弹
    for (int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲的子弹进行发射
        if (d.bullets[i].getIsFree())
        {
            //将改子弹空闲状态改为假
            d.bullets[i].setIsFree(false);
            //设置发射的子弹坐标
            d.bullets[i].setX(d.X + d.rect.width() * 0.5 - 10);
            d.bullets[i].setY(d.Y - 25);
            break;
        }
    }

}

void HeroPlane::setPosition(int x, int y)
{
    DPTR_D(HeroPlane);
    d.X = x;
    d.Y = y;
    d.rect.moveTo(d.X,d.Y);
}

void HeroPlane::initContent()
{
    DPTR_D(HeroPlane);
    d.plane.load(HERO_PATH);

    d.X = GAME_WIDTH * 0.5 - d.plane.width() * 0.5;
    d.Y = GAME_HEIGHT - d.plane.height();

    //初始化矩形框
    d.rect.setWidth(d.plane.width());
    d.rect.setHeight(d.plane.height());
    d.rect.moveTo(d.X,d.Y);

    d.recorder = 0;

}

QPixmap HeroPlane::getHero()
{
    DPTR_D(HeroPlane);
    return d.plane;
}

int HeroPlane::getX()
{
    DPTR_D(HeroPlane);
    return d.X;
}

int HeroPlane::getY()
{
    DPTR_D(HeroPlane);
    return d.Y;
}

QRect HeroPlane::getRect()
{
    DPTR_D(HeroPlane);
    return d.rect;
}

HeroBullet& HeroPlane::getHeroBullet(int i)
{
    DPTR_D(HeroPlane);
    return d.bullets[i];
}
