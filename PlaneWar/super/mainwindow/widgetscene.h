#ifndef WIDGETSCENE_H
#define WIDGETSCENE_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include "dptr.h"
#include "config.h"

class WidgetScenePrivate;
class WidgetScene : public QWidget
{
    Q_OBJECT
    DPTR_DECLARE_PRIVATE(WidgetScene)
    public:
        explicit WidgetScene(QWidget *parent = nullptr);
    virtual ~WidgetScene();

protected:
    DPTR_DECLARE(WidgetScene)
    explicit WidgetScene(WidgetScenePrivate &d, QWidget *parent = nullptr);

public:
    //
    void initScene();
    //启动游戏  用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //敌机出场
    void enemyToScene();

    void collisionDetection();

protected:
    //绘图事件
    void paintEvent(QPaintEvent *event);
    //移动事件
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // WIDGETSCENE_H
