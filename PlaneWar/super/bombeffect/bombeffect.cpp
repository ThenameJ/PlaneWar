#include "bombeffect.h"
#include <QPixmap>
#include "config.h"
#include <QRect>

class BombEffectPrivate : public DPtrPrivate<BombEffect>
{
public:
    //放爆炸资源数组
    QVector<QPixmap> pixArr;

    //爆炸位置
    int X;
    int Y;

    //爆炸状态
    bool isFree;

    //爆炸切图的时间间隔
    int recoder;

    //爆炸时加载的图片下标
    int index;


};

BombEffect::BombEffect(QObject *parent)
    :BombEffect(*new BombEffectPrivate, parent)
{

}

BombEffect::~BombEffect()
{

}

BombEffect::BombEffect(BombEffectPrivate &d, QObject *parent)
    :QObject(parent)
    ,DPTR_INIT(&d)
{
    initContent();
}

void BombEffect::updateInfo()
{
    DPTR_D(BombEffect);
    //空闲状态
    if(d.isFree)
    {
        return;
    }

    d.recoder++;
    if(d.recoder < BOMB_INTERVAL)
    {
        //记录爆炸间隔未到，直接return，不需要切图
        return;
    }
    //重置记录
    d.recoder = 0;

    //切换爆炸播放图片
    d.index++;
    //注：数组中的下标从0开始，最大是6
    //如果计算的下标大于6，重置为0
    if(d.index > BOMB_MAX-1)
    {
        d.index = 0;
        d.isFree = true;
    }


}

void BombEffect::initContent()
{
    DPTR_D(BombEffect);
    //初始化爆炸图片数组
    for(int i = 1 ;i <= BOMB_MAX ;i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(BOMB_PATH).arg(i);
        d.pixArr.push_back(QPixmap(str));
    }

    //初始化坐标
    d.X = 0;
    d.Y = 0;

    //初始化空闲状态
    d.isFree = true;

    //当前播放图片下标
    d.index = 0;

    //爆炸间隔记录
    d.recoder = 0;


}

bool BombEffect::getIsFree()
{
    DPTR_D(BombEffect);
    return d.isFree;
}

void BombEffect::setIsFree(bool isFree)
{
    DPTR_D(BombEffect);
    d.isFree = isFree;
}

int BombEffect::getX()
{
    DPTR_D(BombEffect);
    return d.X;
}

void BombEffect::setX(int x)
{
    DPTR_D(BombEffect);
    d.X = x;
}

int BombEffect::getY()
{
    DPTR_D(BombEffect);
    return d.Y;
}

void BombEffect::setY(int y)
{
    DPTR_D(BombEffect);
    d.Y = y;
}

QVector<QPixmap> BombEffect::getArr()
{
    DPTR_D(BombEffect);
    return d.pixArr;
}

int BombEffect::getIndex()
{
    DPTR_D(BombEffect);
    return d.index;
}
