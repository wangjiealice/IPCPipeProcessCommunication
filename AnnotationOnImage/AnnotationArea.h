#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPainter>
#include <QMenu>

class AnnotationArea : public QGraphicsView
{
	Q_OBJECT

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

public:
	AnnotationArea(QWidget *parent = 0);

signals:
	void mouseMovePoint(QPoint point);
	void mouseClicked(QPoint point);
};
