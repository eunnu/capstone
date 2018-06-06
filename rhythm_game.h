#ifndef RHYTHM_GAME_H
#define RHYTHM_GAME_H

#define WIDTH  1280
#define HEIGHT 720

#define VIDEO_TIMER  45000 // 40段
#define INTRO_TIMER  14000 // 14段
#define GAME_TIMER   4000  // 4段
#define FINISH_TIMER 9000  // 9段

#define TRUE  1
#define FALSE 0

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMultimedia>
#include <QMouseEvent>
#include <QTimer>

#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\core.hpp"

#include "ui_rhythm_game.h"

#include "includes.h"
#include "hand.hpp"
class Rhythm_Game : public QMainWindow
{
	Q_OBJECT

public:
	Rhythm_Game(QWidget *parent = 0);
	~Rhythm_Game();

	Cap cap;

	Point m_point;

	void get_mouse_state( QPoint &hand_point, int &finger);	
	void click_evet(QMouseEvent *e);
	void video_player();
	void get_mouse_state(bool &flag);

	int select_stage = 1;
	int limit_stage  = 1;
	int timer_count = 0;
	int answer_correct = 0;
	int click_flag   = FALSE;
	int finger_count = 0;
	int m_point_x = 0;
	int m_point_y = 0;

private:
	Ui::Rhythm_GameClass ui;
	QGraphicsVideoItem *item;
	QGraphicsScene *scene;
	QMediaPlayer* video_play;
	QMediaPlayer* music_play;
	QVideoWidget *video;
	QMouseEvent *click;
	QTimer *camera_timer;
	QTimer *video_timer;
	QTimer *intro_timer;
	QTimer *apple_timer;
	QTimer *bus_timer;
	QTimer *cat_timer;
	QTimer *duck_timer;
	QTimer *timer_finish;
	QTimer *timer;

private slots:
	void update_camera();
	void enter_stage();
	void exit_game();
	void change_next_stage();
	void change_before_stage();
	void play_video();
	void play_game();
	void result();

	void video_function();
	void play_function();
	void answer_function();
	void intro_video();

	void apple();
	void bus();
	void cat();
	void duck();
	void finish_game();
	//void click_event();


};

#endif // RHYTHM_GAME_H
