#include "include/leaderboardwindow.h"
#include "ui_leaderboardwindow.h"
#include "include/assetmanager.h"

LeaderboardWindow::LeaderboardWindow(QWidget *parent, uint8 starter) :
	QDialog(parent),
	ui(new Ui::LeaderboardWindow)
{
	ui->setupUi(this);
	parentWin = parent;
	setAttribute(Qt::WA_DeleteOnClose);

	QStringList titles;

	ui->normalTable->setColumnCount(2);
	ui->groupTable->setColumnCount(2);
	ui->countdownTable->setColumnCount(2);

	titles << "Igrač/Igračica" << "Broj osvojenih bodova";
	ui->normalTable->setHorizontalHeaderLabels(titles);
	ui->groupTable->setHorizontalHeaderLabels(titles);
	ui->countdownTable->setHorizontalHeaderLabels(titles);

	// resize so that the rows actually fit
	(ui->normalTable->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
	(ui->groupTable->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
	(ui->countdownTable->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);

	for(uint32 i=0; i<normal.getCount(); i++) {
		ui->normalTable->insertRow(ui->normalTable->rowCount());
		ui->normalTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(normal.getName(i))));
		ui->normalTable->setItem(i, 1, new QTableWidgetItem(QString::number(normal.getScore(i))));
	}
	for(uint32 i=0; i<group.getCount(); i++) {
		ui->groupTable->insertRow(ui->groupTable->rowCount());
		ui->groupTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(group.getName(i))));
		ui->groupTable->setItem(i, 1, new QTableWidgetItem(QString::number(group.getScore(i))));
	}
	for(uint32 i=0; i<countdown.getCount(); i++) {
		ui->countdownTable->insertRow(ui->countdownTable->rowCount());
		ui->countdownTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(countdown.getName(i))));
		ui->countdownTable->setItem(i, 1, new QTableWidgetItem(QString::number(countdown.getScore(i))));
	}

	if(starter) {
		ui->tabWidget->setCurrentIndex(starter-1);
	}
}

LeaderboardWindow::~LeaderboardWindow()
{
	parentWin->show();
	delete ui;
}
