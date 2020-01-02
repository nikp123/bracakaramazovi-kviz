#ifndef NORMALGAME_H
#define NORMALGAME_H

#include <QDialog>
#include "shared.h"

namespace Ui {
	class NormalGame;
}

class NormalGame : public QDialog
{
		Q_OBJECT

	public:
		explicit NormalGame(QWidget *parent = nullptr, uint8 gameMode = 0);
		~NormalGame();

	private slots:
		void timeEvent();
		void endGame();

		void on_answer0_clicked();

		void on_answer1_clicked();

		void on_answer2_clicked();

		void on_answer3_clicked();

	private:
		uint8 convert();
		void questionHandler(uint8 result);

		uint32 q;
		uint8 gm;
		uint8 mode;
		int32 points;
		uint32 answerCount;
		uint32 moreTime;
		QTimer *timer, *clock;
		Ui::NormalGame *ui;
		QWidget *parentWin;
};

#endif // NORMALGAME_H
