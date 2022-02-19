#ifndef BOMBEFFECT_H
#define BOMBEFFECT_H

#include <QObject>
#include "dptr.h"

class BombEffectPrivate;
class BombEffect : public QObject
{
    Q_OBJECT
    DPTR_DECLARE_PRIVATE(BombEffect)
    public:
        explicit BombEffect(QObject *parent = nullptr);
    virtual ~BombEffect();

protected:
    DPTR_DECLARE(BombEffect)
    explicit BombEffect(BombEffectPrivate &d, QObject *parent = nullptr);

public:
    //更新信息（播放图片下标、播放间隔）
    void updateInfo();

    void initContent();

    bool getIsFree();

    void setIsFree(bool isFree);

    int getX();

    void setX(int x);

    int getY();

    void setY(int y);

    QVector<QPixmap> getArr();

    int getIndex();

signals:

public slots:

};

#endif // BOMBEFFECT_H
