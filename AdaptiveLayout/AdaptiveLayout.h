#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AdaptiveLayout.h"

class AdaptiveLayout : public QMainWindow
{
	Q_OBJECT

public:
	AdaptiveLayout(QWidget *parent = Q_NULLPTR);

private:
	Ui::AdaptiveLayoutClass ui;

	private slots:
	void on_deleteSelectedImagesButton_clicked();
	void on_fileButton_clicked();
};
