#ifndef HEROBULLET_H
#define HEROBULLET_H

#include <QObject>
#include "dptr.h"

class HeroBulletPrivate;
class HeroBullet : public QObject
{
    Q_OBJECT
    DPTR_DECLARE_PRIVATE(HeroBullet)
    public:
        explicit HeroBullet(QObject *parent = nullptr);
    virtual ~HeroBullet();

protected:
    DPTR_DECLARE(HeroBullet)
    explicit HeroBullet(HeroBulletPrivate &d, QObject *parent = nullptr);

public:
    //
    void initContent();
    //更新子弹坐标
    void updatePosition();

    bool getIsFree();

    int getX();

    int getY();

    QRect getBulletRect();

    void setX(int x);

    void setY(int y);

    void setIsFree(bool isFree);

    QPixmap getBullet();

signals:

public slots:

};

#endif // HEROBULLET_H
