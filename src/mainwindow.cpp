#include "include/mainwindow.h"
#include "include/assetmanager.h"
#include "ui_mainwindow.h"
#include "include/leaderboardwindow.h"
#include "include/normalgame.h"

static AssetManager *ast;

void MainWindow::closeEvent (QCloseEvent *event) {
	delete ast;
	event->accept();
}

void MainWindow::startAsset() {
	ast = new AssetManager();
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_leaderboards_clicked() {
	hide();

	lbw = new LeaderboardWindow(this);
	lbw->show();
}

void MainWindow::on_startGame_clicked()
{
	if(ui->normalRadio->isChecked()) {
		hide();

		ng = new NormalGame(this, 0);
		ng->show();
	} else if(ui->groupRadio->isChecked()) {
		hide();

		QMessageBox msgBox;
		msgBox.setText("Odaberite težinu!\n");
		QAbstractButton *buttonHard   = msgBox.addButton(tr("Teško"), QMessageBox::NoRole);
		QAbstractButton *buttonMedium = msgBox.addButton(tr("Umjereno"), QMessageBox::ApplyRole);
		QAbstractButton *buttonEasy   = msgBox.addButton(tr("Lako"), QMessageBox::ResetRole);

		msgBox.exec();

		if(msgBox.clickedButton() == buttonEasy) {
			ng = new NormalGame(this, 1);
			ng->show();
		} else if(msgBox.clickedButton() == buttonMedium) {
			ng = new NormalGame(this, 2);
			ng->show();
		} else if(msgBox.clickedButton() == buttonHard) {
			ng = new NormalGame(this, 3);
			ng->show();
		} else show();
	} else if(ui->countdownRadio->isChecked()) {
		hide();

		ng = new NormalGame(this, 5);
		ng->show();
	}
}
