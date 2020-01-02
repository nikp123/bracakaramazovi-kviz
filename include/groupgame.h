#ifndef GROUPGAME_H
#define GROUPGAME_H

#include <QDialog>

namespace Ui {
	class GroupGame;
}

class GroupGame : public QDialog
{
		Q_OBJECT

	public:
		explicit GroupGame(QWidget *parent = nullptr);
		~GroupGame();

	private:
		Ui::GroupGame *ui;
};

#endif // GROUPGAME_H
