#ifndef STAGE_H
#define STAGE_H

#include <QObject>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <qvideowidget.h>
#include <qmultimedia.h>
#include <QMediaPlayer>

#include "ui_rhythm_game.h"

class stage : public QObject
{
	Q_OBJECT

public:
	stage(QObject *parent);
	~stage();

	/*
	Image image;

	typedef struct Data//�׽�Ʈ���� ����Ʈ�� ������ ������ ����
	{
	QUrl    start_music; // ���� ����ȭ�鿡 ������ ª�� ����
	QString game_music;  // ���� ����
	QString music_name;  // ���� ����
	QString music_image; // ���� �ٹ�
	}Data;

	typedef struct _Node
	{
	Data data;
	struct _Node* next;
	struct _Node* before;
	}Node;

	Node *Head = NULL;
	Node *Tail = NULL;
	Node *tempPoint;

	Data music1;
	Data music2;
	Data music3;

	QMediaPlayer* player;

	void add_music(Data data);//��� ����
	void music_info();
	void music_track();
	*/

	QGraphicsVideoItem *item;
	QGraphicsScene *scene;
	QMediaPlayer* player;
	QVideoWidget *video;

	int stage_limit = 1;
	int stage_state = 1;
	void play_video();

private:
	Ui::Rhythm_GameClass ui;
};
#endif // STAGE_H
