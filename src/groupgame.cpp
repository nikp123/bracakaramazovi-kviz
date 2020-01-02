#include "include/groupgame.h"
#include "ui_groupgame.h"

GroupGame::GroupGame(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::GroupGame)
{
	ui->setupUi(this);
}

GroupGame::~GroupGame()
{
	delete ui;
}
