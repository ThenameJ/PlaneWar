#ifndef HEROPLANE_H
#define HEROPLANE_H

#include <QObject>
#include "dptr.h"
#include "herobullet.h"

class HeroPlanePrivate;
class HeroPlane : public QObject
{
    Q_OBJECT
    DPTR_DECLARE_PRIVATE(HeroPlane)
    public:
        explicit HeroPlane(QObject *parent = nullptr);
    virtual ~HeroPlane();

protected:
    DPTR_DECLARE(HeroPlane)
    explicit HeroPlane(HeroPlanePrivate &d, QObject *parent = nullptr);

public:
    //发射子弹
    void shoot();
    //设置飞机位置
    void setPosition(int x, int y);
    //
    void initContent();
    //
    QPixmap getHero();
    //
    int getX();
    //
    int getY();
    //
    QRect getRect();

    HeroBullet &getHeroBullet(int i);

signals:

public slots:

};

#endif // HEROPLANE_H
