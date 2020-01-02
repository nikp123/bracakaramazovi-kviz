#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QMessageBox>

#include "leaderboardwindow.h"
#include "normalgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
		void startAsset();

	private slots:
		void on_leaderboards_clicked();
		void closeEvent(QCloseEvent *event);
		void on_startGame_clicked();

	private:
		Ui::MainWindow *ui;
		LeaderboardWindow *lbw;
		NormalGame *ng;
};
#endif // MAINWINDOW_H
