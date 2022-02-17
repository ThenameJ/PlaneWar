#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <QPixmap>

#include "dptr.h"

class GameMapPrivate;
class GameMap : public QObject
{
    Q_OBJECT
    DPTR_DECLARE_PRIVATE(GameMap)
public:
    explicit GameMap(QObject *parent = nullptr);
    virtual ~GameMap();

protected:
    DPTR_DECLARE(GameMap)
    explicit GameMap(GameMapPrivate &d, QObject *parent = nullptr);

public:
    //地图滚动坐标计算
    void mapPosition();

    QPixmap getMap1();

    QPixmap getMap2();

    int getMap1PosY();

    int getMap2PosY();

private:
    void initContent();

signals:

public slots:

};

#endif // GAMEMAP_H
