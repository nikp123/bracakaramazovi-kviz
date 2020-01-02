#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QDialog>
#include "shared.h"

namespace Ui {
	class LeaderboardWindow;
}

class LeaderboardWindow : public QDialog
{
		Q_OBJECT

	public:
		explicit LeaderboardWindow(QWidget *parent = nullptr, uint8 starter = 0);
		~LeaderboardWindow();
		//virtual void closeEvent( QCloseEvent *event );

	private:
		Ui::LeaderboardWindow *ui;
		QWidget *parentWin;
};

#endif // LEADERBOARDWINDOW_H
