#include "enemyplane.h"
#include <QPixmap>
#include "config.h"
#include <QRect>

class EnemyPlanePrivate : public DPtrPrivate<EnemyPlane>
{
public:
    //敌机资源对象
    QPixmap enemy;

    //位置
    int X;
    int Y;

    //敌机的矩形边框（碰撞检测）
    QRect enemyRect;

    //状态
    bool isFree;

    //速度
    int enemySpeed;

};

EnemyPlane::EnemyPlane(QObject *parent)
    :EnemyPlane(*new EnemyPlanePrivate, parent)
{

}

EnemyPlane::~EnemyPlane()
{

}

EnemyPlane::EnemyPlane(EnemyPlanePrivate &d, QObject *parent)
    :QObject(parent)
    ,DPTR_INIT(&d)
{
    initContent();
}

void EnemyPlane::updatePosition()
{
    DPTR_D(EnemyPlane);
    //空闲状态，不计算坐标
    if(d.isFree)
    {
        return;
    }

    d.Y += d.enemySpeed;
    d.enemyRect.moveTo(d.X,d.Y);

    if(d.Y >= GAME_HEIGHT + d.enemyRect.height())
    {
        d.isFree = true;
    }

}

void EnemyPlane::initContent()
{
    DPTR_D(EnemyPlane);
    //敌机资源加载
    d.enemy.load(ENEMY_PATH);

    //敌机位置
    d.X = 0;
    d.Y = 0;

    //敌机状态
    d.isFree = true;

    //敌机速度
    d.enemySpeed = ENEMY_SPEED;

    //敌机矩形
    d.enemyRect.setWidth(d.enemy.width());
    d.enemyRect.setHeight(d.enemy.height());
    d.enemyRect.moveTo(d.X, d.Y);

}

bool EnemyPlane::getIsFree()
{
    DPTR_D(EnemyPlane);
    return d.isFree;
}

void EnemyPlane::setIsFree(bool isFree)
{
    DPTR_D(EnemyPlane);
    d.isFree = isFree;
}

void EnemyPlane::setX(int x)
{
    DPTR_D(EnemyPlane);
    d.X = x;
}

int EnemyPlane::getX()
{
    DPTR_D(EnemyPlane);
    return d.X;
}

void EnemyPlane::setY(int y)
{
    DPTR_D(EnemyPlane);
    d.Y = y;
}

int EnemyPlane::getY()
{
    DPTR_D(EnemyPlane);
    return d.Y;
}

QRect EnemyPlane::getRect()
{
    DPTR_D(EnemyPlane);
    return d.enemyRect;
}

QPixmap EnemyPlane::getEnemy()
{
    DPTR_D(EnemyPlane);
    return d.enemy;
}
