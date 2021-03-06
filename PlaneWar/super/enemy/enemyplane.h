#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include <QObject>
#include "dptr.h"

class EnemyPlanePrivate;
class EnemyPlane : public QObject
{
    Q_OBJECT
    DPTR_DECLARE_PRIVATE(EnemyPlane)
    public:
        explicit EnemyPlane(QObject *parent = nullptr);
    virtual ~EnemyPlane();

protected:
    DPTR_DECLARE(EnemyPlane)
    explicit EnemyPlane(EnemyPlanePrivate &d, QObject *parent = nullptr);

public:
    //更新坐标
    void updatePosition();

    void initContent();

    bool getIsFree();

    void setIsFree(bool isFree);

    void setX(int x);

    int getX();

    void setY(int y);

    int getY();

    QRect getRect();

    QPixmap getEnemy();

signals:

public slots:

};

#endif // ENEMYPLANE_H
