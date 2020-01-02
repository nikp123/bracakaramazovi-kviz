#include "include/normalgame.h"
#include "ui_normalgame.h"
#include "include/assetmanager.h"
#include "include/leaderboardwindow.h"

#include <QTimer>
#include <QDateTime>
#include <QInputDialog>
#include <cmath>

static double modifier = 1.0;

void NormalGame::timeEvent() {
	modifier=pow(modifier, 0.99);
	QString time_text = QString::number(points)+" bodova - "+QString::number(timer->remainingTime()/1000) + "s (x" + QString::number(modifier, 'g', 3) + ")";
	ui->timeText->setText(time_text);
}

static QuestionBank *lol[3] = {&easy, &medium, &hard};
static Leaderboard *lmao[3] = {&normal, &group, &countdown};

uint8 NormalGame::convert() {
	switch(gm) {
		case 0:
			return 0;
		case 1:
		case 2:
		case 3:
		case 4:
			return 1;
		case 5:
			return 2;
	}
	return 255;
}

void NormalGame::questionHandler(uint8 result) {
	answerCount++;

	if(result == (lol[mode]->getQuestion(q))->correct) {
		switch(mode) {
			case 0:
				points+=modifier*5;
				break;
			case 1:
				points+=modifier*10;
				break;
			case 2:
				points+=modifier*15;
				break;
		}
		modifier*=1.25;

		if(convert() == 2) {
			int32 remaining = timer->remainingTime();
			timer->stop();
			disconnect(timer);
			if(answerCount<10)
				timer->start(remaining+5000);
			else if(answerCount<25)
				timer->start(remaining+4000);
			else if(answerCount<50)
				timer->start(remaining+3000);
			else if(answerCount<100)
				timer->start(remaining+2000);
			else timer->start(remaining+1000);
			connect(timer, SIGNAL(timeout()), this, SLOT(endGame()));
		}
	} else {
		points-=10;
		modifier=1.0;
	}

	// you'll never notice this anyway
	switch(convert()) {
		case 0:
		case 2:
			if(timer->remainingTime()<60)
				mode = 1;
			else if(timer->remainingTime()<30)
				mode = 2;
			tryAgain:
			q = lol[mode]->getRandomQuestion();
			if(q == UINT_MAX) {
				mode++;
				if(mode > 2) {
					mode = 0;
					lol[0]->initQuestionList();
					lol[1]->initQuestionList();
					lol[2]->initQuestionList();
				}
				goto tryAgain;
			}
			break;
		case 1:
			tryAgain2:
			q = lol[mode]->getRandomQuestion();
			if(q == UINT_MAX) {
				lol[mode]->initQuestionList();
				goto tryAgain2;
			}
			break;
	}

	ui->questionText->setText(QString::fromStdString((lol[mode]->getQuestion(q))->text));
	ui->answer0->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[0]));
	ui->answer1->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[1]));
	ui->answer2->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[2]));
	ui->answer3->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[3]));
}

NormalGame::NormalGame(QWidget *parent, uint8 gameMode) :
	QDialog(parent),
	ui(new Ui::NormalGame)
{
	modifier = 1.0;
	parentWin = parent;
	setAttribute(Qt::WA_DeleteOnClose);

	gm = gameMode;
	ui->setupUi(this);

	moreTime = TIME;
	ui->timeText->setAlignment(Qt::AlignCenter);

	points = 0;
	answerCount = 0;

	switch(convert()) {
		case 0:
		case 2:
			mode = 0;
			easy.initQuestionList();
			medium.initQuestionList();
			hard.initQuestionList();

			q = easy.getRandomQuestion();
			ui->timeText->setText(QString::number(moreTime));
			ui->questionText->setText(QString::fromStdString((easy.getQuestion(q))->text));
			ui->answer0->setText(QString::fromStdString((easy.getQuestion(q))->answer[0]));
			ui->answer1->setText(QString::fromStdString((easy.getQuestion(q))->answer[1]));
			ui->answer2->setText(QString::fromStdString((easy.getQuestion(q))->answer[2]));
			ui->answer3->setText(QString::fromStdString((easy.getQuestion(q))->answer[3]));
			break;
		case 1:
			mode = gm-1;
			lol[mode]->initQuestionList();
			q = lol[mode]->getRandomQuestion();
			ui->timeText->setText(QString::number(moreTime));
			ui->questionText->setText(QString::fromStdString((lol[mode]->getQuestion(q))->text));
			ui->answer0->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[0]));
			ui->answer1->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[1]));
			ui->answer2->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[2]));
			ui->answer3->setText(QString::fromStdString((lol[mode]->getQuestion(q))->answer[3]));
			break;
	}


	// one for keeping time
	timer = new QTimer(this);
	timer->setSingleShot(true);
	timer->start(moreTime*1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(endGame()));

	// and one for updating the counter
	clock = new QTimer(this);
	clock->start(100);
	connect(clock, SIGNAL(timeout()), this, SLOT(timeEvent()));
}

void NormalGame::endGame() {
	disconnect(clock);
	clock->stop();
	delete clock;
	delete timer;
	std::string text = QInputDialog::getText(this, "Kraj igre", "Molimo vas da upišete vaše ime:").toUtf8().constData();
	if(text == "") text = "Neimenovani";
	lmao[convert()]->append(text, points);
	LeaderboardWindow *lb = new LeaderboardWindow(parentWin, convert()+1);
	lb->show();
	this->deleteLater();
}

NormalGame::~NormalGame() {
	delete ui;
}

void NormalGame::on_answer0_clicked() {
    questionHandler(0);
}

void NormalGame::on_answer1_clicked() {
    questionHandler(1);
}

void NormalGame::on_answer2_clicked() {
    questionHandler(2);
}

void NormalGame::on_answer3_clicked() {
    questionHandler(3);
}
