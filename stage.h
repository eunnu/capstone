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

	typedef struct Data//테스트에서 리스트에 보관할 데이터 형식
	{
	QUrl    start_music; // 음악 선택화면에 나오는 짧은 음악
	QString game_music;  // 게임 음악
	QString music_name;  // 음악 제목
	QString music_image; // 음악 앨범
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

	void add_music(Data data);//노드 생성
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
