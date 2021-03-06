#include "widgetscene.h"
#include "gamemap.h"
#include <QIcon>
#include <QTimer>
#include <QPainter>
#include <ctime>
#include <QSound>
#include "heroplane.h"
#include "enemyplane.h"
#include "bombeffect.h"

class WidgetScenePrivate : public DPtrPrivate<WidgetScene>
{
public:
    QTimer      timer;
    GameMap     gameMap;
    HeroPlane   hero;
    //敌机数组
    EnemyPlane  enemys[ENEMY_NUM];
    //敌机出场间隔记录
    int         recorder;
    BombEffect  bombs[BOMB_NUM];
};

WidgetScene::WidgetScene(QWidget *parent)
    :WidgetScene(*new WidgetScenePrivate(), parent)
{

}

WidgetScene::~WidgetScene()
{

}

WidgetScene::WidgetScene(WidgetScenePrivate &d, QWidget *parent)
    :QWidget(parent)
    ,DPTR_INIT(&d)
{
    initScene();
}

void WidgetScene::initScene()
{
    DPTR_D(WidgetScene);
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置图标资源
    setWindowIcon(QIcon( GAME_ICON));

    d.timer.setInterval(GAME_RATE);

    playGame();

    d.recorder = 0;

    srand((unsigned int)time(NULL));


}

void WidgetScene::playGame()
{
    DPTR_D(WidgetScene);
    d.timer.start();

    QSound::play(SOUND_BACKGROUND);

    //监听定时器
    connect(&d.timer,&QTimer::timeout,[=](){
        enemyToScene();
        //更新游戏中元素的坐标
        updatePosition();
        //重新绘制图片
        update();
        //碰撞检测
        collisionDetection();
    });


}

void WidgetScene::updatePosition()
{
    DPTR_D(WidgetScene);
    d.gameMap.mapPosition();

    //发射子弹
    d.hero.shoot();
    //计算子弹坐标
    for (int i = 0 ;i < BULLET_NUM; i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if (!d.hero.getHeroBullet(i).getIsFree())
        {
            d.hero.getHeroBullet(i).updatePosition();
        }
    }

    //敌机坐标计算
    for (int i = 0 ; i < ENEMY_NUM; i++)
    {
        //非空闲敌机 更新坐标
        if (d.enemys[i].getIsFree() == false)
        {
            d.enemys[i].updatePosition();
        }
    }

    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM; i++)
    {
        if(d.bombs[i].getIsFree() == false)
        {
            d.bombs[i].updateInfo();
        }
    }

}

void WidgetScene::enemyToScene()
{
    DPTR_D(WidgetScene);
    d.recorder++;
    if (d.recorder < ENEMY_INTERVAL)
    {
        return;
    }

    d.recorder = 0;

    for (int i = 0 ; i < ENEMY_NUM ; i++)
    {
        if (d.enemys[i].getIsFree())
        {
            //敌机空闲状态改为false
            d.enemys[i].setIsFree(false);
            //设置坐标
            d.enemys[i].setX(rand() % (GAME_WIDTH - d.enemys[i].getRect().width()));
            d.enemys[i].setY(- d.enemys[i].getRect().height());
            break;
        }
    }

}

void WidgetScene::collisionDetection()
{
    DPTR_D(WidgetScene);
    //遍历所有非空闲的敌机
    for (int i = 0 ;i < ENEMY_NUM; i++)
    {
        if (d.enemys[i].getIsFree())
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //遍历所有 非空闲的子弹
        for (int j = 0 ; j < BULLET_NUM; j++)
        {
            if (d.hero.getHeroBullet(j).getIsFree())
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if (d.enemys[i].getRect().intersects(d.hero.getHeroBullet(j).getBulletRect()))
            {
                d.enemys[i].setIsFree(true);
                d.hero.getHeroBullet(j).setIsFree(true);
                //播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM; k++)
                {
                    if(d.bombs[k].getIsFree())
                    {
                        //爆炸状态设置为非空闲
                        d.bombs[k].setIsFree(false);
                        //更新坐标

                        d.bombs[k].setX(d.enemys[i].getX());
                        d.bombs[k].setY(d.enemys[i].getY());
                        break;
                    }
                }
                //播放音效
                QSound::play(SOUND_BOMB);
            }
        }
    }

}

void WidgetScene::paintEvent(QPaintEvent *event)
{
    DPTR_D(WidgetScene);
    Q_UNUSED(event)
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0, d.gameMap.getMap1PosY(), d.gameMap.getMap1());
    painter.drawPixmap(0, d.gameMap.getMap2PosY(), d.gameMap.getMap2());

    //绘制英雄
    painter.drawPixmap(d.hero.getX(), d.hero.getY(), d.hero.getHero());

    //绘制子弹
    for (int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if (!d.hero.getHeroBullet(i).getIsFree())
        {
            painter.drawPixmap(d.hero.getHeroBullet(i).getX(), d.hero.getHeroBullet(i).getY(), d.hero.getHeroBullet(i).getBullet());
        }
    }

    //绘制敌机
    for (int i = 0 ; i< ENEMY_NUM; i++)
    {
        if (d.enemys[i].getIsFree() == false)
        {
            painter.drawPixmap(d.enemys[i].getX(), d.enemys[i].getY(), d.enemys[i].getEnemy());
        }
    }

    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(d.bombs[i].getIsFree() == false)
        {
            painter.drawPixmap(d.bombs[i].getX(), d.bombs[i].getY(), d.bombs[i].getArr()[d.bombs[i].getIndex()]);
        }
    }

}

void WidgetScene::mouseMoveEvent(QMouseEvent *event)
{
    DPTR_D(WidgetScene);
    int x = event->x() - d.hero.getRect().width()*0.5; //鼠标位置 - 飞机矩形的一半
    int y = event->y() - d.hero.getRect().height()*0.5;

    //边界检测
    if (x <= 0 )
    {
        x = 0;
    }
    if (x >= GAME_WIDTH - d.hero.getRect().width())
    {
        x = GAME_WIDTH - d.hero.getRect().width();
    }
    if (y <= 0)
    {
        y = 0;
    }
    if (y >= GAME_HEIGHT - d.hero.getRect().height())
    {
        y = GAME_HEIGHT - d.hero.getRect().height();
    }
    d.hero.setPosition(x,y);

}
