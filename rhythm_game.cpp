#include "rhythm_game.h"

using namespace cv;

Rhythm_Game::Rhythm_Game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stacked_widget->setCurrentWidget(ui.intro_video_widget);
	emit intro_video();


	ui.stacked_widget->setCurrentWidget(ui.main_widget);

	camera_timer = new QTimer(this);
	camera_timer->start(1);
	connect(camera_timer, SIGNAL(timeout()), this, SLOT(update_camera()));
}

void Rhythm_Game::intro_video(){
	video_play = new QMediaPlayer();
	item = new QGraphicsVideoItem;
	scene = new QGraphicsScene();
	video = new QVideoWidget();
	timer = new QTimer(this);

	video_play->setVideoOutput(item);
	video_play->setMedia(QUrl::fromLocalFile("C:/music/intro_(2).mp4"));
	video_play->setVolume(50);

	ui.intro_video->setViewport(video);
	video_play->setVideoOutput(video);
	ui.intro_video->show();

	video_play->play();
	connect(timer, SIGNAL(timeout()), ui.next_button, SLOT(show));
}

Rhythm_Game::~Rhythm_Game(){

}

// webcam 에서 영상을 capture
void Rhythm_Game::update_camera(){
	cv::Mat* img;
	img = cap.ReadCam();
	QImage qimg((uchar*)img->data, img->cols, img->rows, QImage::Format_RGB888);
	ui.camera->setPixmap(QPixmap::fromImage(qimg));
	ui.camera_2->setPixmap(QPixmap::fromImage(qimg));
	ui.camera_3->setPixmap(QPixmap::fromImage(qimg));
	ui.camera_4->setPixmap(QPixmap::fromImage(qimg));
	ui.camera_5->setPixmap(QPixmap::fromImage(qimg));
	ui.camera_6->setPixmap(QPixmap::fromImage(qimg));
	ui.camera_7->setPixmap(QPixmap::fromImage(qimg));
	ui.camera_8->setPixmap(QPixmap::fromImage(qimg));
}


// exit_button evetn : 종료
void Rhythm_Game::exit_game(){
	this->close();
}

// start_button event : 게임 시작
void Rhythm_Game::enter_stage(){	

	if (limit_stage == 1)
	{
		ui.stacked_widget->setCurrentWidget(ui.stage_1_widget);
	}
	else if (limit_stage == 2)
	{
		ui.stacked_widget->setCurrentWidget(ui.stage_2_widget);
	}
	else if (limit_stage == 3)
	{
		ui.stacked_widget->setCurrentWidget(ui.stage_3_widget);
	}

	answer_correct = 0;

	//ui.stacked_widget->setCurrentWidget(ui.stage_3_widget);
}

void Rhythm_Game::play_video(){
	ui.stacked_widget->setCurrentWidget(ui.video_widget);
	emit video_function();
}

void Rhythm_Game::play_game(){

	if (limit_stage == 1)
	{
		ui.stacked_widget->setCurrentWidget(ui.play_1_widget);
	}
	else if (limit_stage == 2)
	{
		ui.stacked_widget->setCurrentWidget(ui.play_2_widget);
	}
	else if (limit_stage == 3)
	{
		ui.stacked_widget->setCurrentWidget(ui.play_1_widget);
	}
	emit play_function();
}

void Rhythm_Game::video_function(){
	video_timer = new QTimer();
	//video_timer->start(VIDEO_TIMER);

	ui.stacked_widget->setCurrentWidget(ui.video_widget);
	//ui.next_button->hide();
	video_player();

	connect(video_timer, SIGNAL(timeout()), ui.next_button, SLOT(show()));
}

void Rhythm_Game::play_function(){
	video_play->stop();


	music_play = new QMediaPlayer;
	if (limit_stage == 1)
	{
		music_play->setMedia(QUrl::fromLocalFile("C:/music/video_1.mp3"));
	}
	else if (limit_stage == 2)
	{
		music_play->setMedia(QUrl::fromLocalFile("C:/music/video_2.mp3"));
	}
	else if (limit_stage == 3)
	{
		music_play->setMedia(QUrl::fromLocalFile("C:/music/video_1.mp3"));
	}
	music_play->setVolume(50);
	music_play->play();

	intro_timer = new QTimer();	
	intro_timer->start(INTRO_TIMER);

	connect(intro_timer, SIGNAL(timeout()), this, SLOT(apple()));

}

void Rhythm_Game::apple() {
	intro_timer->stop();

	apple_timer = new QTimer();
	apple_timer->start(GAME_TIMER);

	if (limit_stage == 1)
	{
		connect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	else if (limit_stage == 2)
	{
		connect(ui.elephant, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.frog, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.gorilla, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.horse, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	else if (limit_stage == 3)
	{
		connect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
	}

	connect(apple_timer, SIGNAL(timeout()), this, SLOT(bus()));
}

void Rhythm_Game::bus(){
	apple_timer->stop();

	bus_timer = new QTimer();
	bus_timer->start(GAME_TIMER);

	if (limit_stage == 1)
	{
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	else if (limit_stage == 2)
	{
		disconnect(ui.elephant, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.frog, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.gorilla, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.horse, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	if (limit_stage == 3)
	{
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
	}

	connect(bus_timer, SIGNAL(timeout()), this, SLOT(cat()));
}

void Rhythm_Game::cat(){
	bus_timer->stop();

	cat_timer = new QTimer();
	cat_timer->start(GAME_TIMER);

	if (limit_stage == 1)
	{
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	else if (limit_stage == 2)
	{
		disconnect(ui.elephant, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.frog, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.gorilla, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.horse, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	if (limit_stage == 3)
	{
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
	}


	connect(cat_timer, SIGNAL(timeout()), this, SLOT(duck()));
}

void Rhythm_Game::duck(){
	cat_timer->stop();

	duck_timer = new QTimer();
	duck_timer->start(GAME_TIMER);

	if (limit_stage == 1)
	{
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	else if (limit_stage == 2)
	{
		disconnect(ui.elephant, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.frog, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.gorilla, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.horse, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	if (limit_stage == 3)
	{
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
		connect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
	}


	connect(duck_timer, SIGNAL(timeout()), this, SLOT(finish_game()));
}

void Rhythm_Game::finish_game(){
	duck_timer->stop();

	timer_finish = new QTimer();
	timer_finish->start(FINISH_TIMER);
	if (limit_stage == 1)
	{
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	else if (limit_stage == 2)
	{
		disconnect(ui.elephant, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.frog, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.gorilla, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.horse, SIGNAL(clicked()), this, SLOT(answer_function()));
	}
	if (limit_stage == 3)
	{
		disconnect(ui.cat, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.apple, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.bus, SIGNAL(clicked()), this, SLOT(answer_function()));
		disconnect(ui.duck, SIGNAL(clicked()), this, SLOT(answer_function()));
	}

	connect(timer_finish, SIGNAL(timeout()), this, SLOT(result()));
}

void Rhythm_Game::answer_function(){
	answer_correct += 1;
}

void Rhythm_Game::result(){
	timer_finish->stop();

	if (answer_correct == 4){
		ui.stacked_widget->setCurrentWidget(ui.result_great_widget);
		ui.great->show();
		//ui.fail->hide();

		if (limit_stage < 3){
			limit_stage += 1;
		}
	}

	else {
		ui.stacked_widget->setCurrentWidget(ui.result_fail_widget);
		//ui.great->hide();
		ui.fail->show();
	}
}

void Rhythm_Game::video_player(){
	video_play = new QMediaPlayer();
	item       = new QGraphicsVideoItem;
	scene      = new QGraphicsScene();
	video      = new QVideoWidget();

	video_play->setVideoOutput(item);

	if (select_stage == 1)	{
		video_play->setMedia(QUrl::fromLocalFile("C:/music/stage_1.mp4"));
	}

	else if (select_stage == 2)	{
		video_play->setMedia(QUrl::fromLocalFile("C:/music/stage_2.mp4"));
	}

	else if (select_stage == 3)	{
		video_play->setMedia(QUrl::fromLocalFile("C:/music/stage_1.mp4"));
	}

	video_play->setVolume(50);

	ui.video->setViewport(video);
	video_play->setVideoOutput(video);
	ui.video->show();

	video_play->play();
}

void Rhythm_Game::change_next_stage() {

	if (limit_stage == 2) {

		if (select_stage == 1) {
			ui.stage_6->show();
			ui.stage_5->hide();
			select_stage = 2;

		}
		else if (select_stage == 2) {
			ui.stage_6->hide();
			ui.stage_5->show();
			select_stage = 1;
		}
	}

	else if (limit_stage == 3) {
		switch (select_stage){
		case 1:
			ui.stage_1->hide();
			ui.stage_2->show();
			ui.stage_3->hide();

			select_stage = 2;
			break;

		case 2:
			ui.stage_1->hide();
			ui.stage_2->hide();
			ui.stage_3->show();

			select_stage = 3;
			break;

		case 3:
			ui.stage_1->show();
			ui.stage_2->hide();
			ui.stage_3->hide();

			select_stage = 1;
			break;

		default:
			select_stage = 1;
			break;
		}
	}
}

void Rhythm_Game::change_before_stage() {
	if (limit_stage == 2) {
		if (select_stage == 1) {
			ui.stage_6->show();
			ui.stage_5->hide();

			select_stage = 2;
		}
		else if (select_stage == 2) {
			ui.stage_6->hide();
			ui.stage_5->show();
			select_stage = 1;
		}
	}
	else if (limit_stage == 3) {

		switch (select_stage){
		case 1:
			ui.stage_1->hide();
			ui.stage_2->hide();
			ui.stage_3->show();

			select_stage = 3;
			break;

		case 2:
			ui.stage_1->show();
			ui.stage_2->hide();
			ui.stage_3->hide();

			select_stage = 1;
			break;

		case 3:
			ui.stage_1->hide();
			ui.stage_2->show();
			ui.stage_3->hide();

			select_stage = 2;
			break;

		default:
			select_stage = 1;
			break;
		}
	}
}


void Rhythm_Game::get_mouse_state(bool &flag){
	if (flag == true){
		m_point = cap.GetPoint();
		//emit click_event();
	}
}

//void Rhythm_Game::click_evet(QMouseEvent *e)
//{
	
//}
