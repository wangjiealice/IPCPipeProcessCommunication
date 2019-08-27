#pragma once

#include <QtWidgets/QMainWindow>
#include<QLabel>
#include<QPainterPath>
#include<QStyleOptionGraphicsItem>

#include "ui_AnnotationOnImage.h"

enum class ToolTypes
{
	Select,
	Pen,
	MarkerPen,
	MarkerRect,
	MarkerEllipse,
	Line,
	Arrow,
	DoubleArrow,
	Rect,
	Ellipse,
	Number,
	Text,
	Blur
};

class AnnotationOnImage : public QMainWindow
{
	Q_OBJECT

private:
	QGraphicsScene  *scene;

	QLabel  *labViewCord;
	QLabel  *labSceneCord;
	QLabel  *labItemCord;
	QGraphicsLineItem *pItem;
	QPointF firstPoint;
	ToolTypes currentTool;

	void iniGraphicsSystem(); //创建Graphics View的各项
protected:
	void resizeEvent(QResizeEvent *event);

public:
	AnnotationOnImage(QWidget *parent = Q_NULLPTR);
	~AnnotationOnImage();

protected:
	//void paintEvent(QPaintEvent* painter);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QPainterPath *mShape = NULL;
	bool inDrwaing = false;

	QPoint point1;

private:
	Ui::AnnotationOnImageClass ui;

	private slots:
	void on_changeLinePositionButton_clicked();
	void on_mouseMovePoint(QPoint point);
	void on_mouseClicked(QPoint point);

};
