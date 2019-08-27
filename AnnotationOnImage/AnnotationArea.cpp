#include "AnnotationArea.h"
#include    <QMouseEvent>
#include    <QPoint>

void AnnotationArea::mouseMoveEvent(QMouseEvent *event)
{//����ƶ��¼�
	QPoint point = event->pos(); //QGraphicsView������
	emit mouseMovePoint(point); //�ͷ��ź�
	QGraphicsView::mouseMoveEvent(event);
}

void AnnotationArea::mousePressEvent(QMouseEvent *event)
{ //�����������¼�
	if (event->button() == Qt::LeftButton)
	{
		QPoint point = event->pos(); //QGraphicsView������
		emit mouseClicked(point);//�ͷ��ź�
	}
	QGraphicsView::mousePressEvent(event);
}

AnnotationArea::AnnotationArea(QWidget *parent) :QGraphicsView(parent)
{

}
