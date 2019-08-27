#include "AnnotationOnImage.h"
#include "AnnotationArea.h"
#include    <QGraphicsEllipseItem>

void AnnotationOnImage::iniGraphicsSystem()
{ //构造Graphics View的各项
	//QRectF rect(-200, -100, 400, 200);
	QRectF rect(-100, -100, 200, 200);
	scene = new QGraphicsScene(rect); //scene逻辑coordinate系定义
	ui.View->setScene(scene);

	//画一个矩形框,大小等于scene
	QGraphicsRectItem *item = new QGraphicsRectItem(rect); //矩形框正好等于scene的大小
	item->setFlags(QGraphicsItem::ItemIsSelectable     //可选,可以有焦点,但是不能移动
		| QGraphicsItem::ItemIsFocusable);
	QPen pen;
	pen.setWidth(2);
	item->setPen(pen);
	//    item->setPos(500,0);//缺省位置在scene的（0,0）
	scene->addItem(item);

	//一个位于scene中心的椭圆,测试局部coordinate
	QGraphicsEllipseItem   *item2 = new QGraphicsEllipseItem(-100, -50, 200, 100); //矩形框内创建椭圆,绘图项的局部coordinate,左上角(-100,-50),宽200,高100
	//item2->setPos(200, 200);
	item2->setBrush(QBrush(Qt::blue));
	item2->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	scene->addItem(item2);

	//一个圆,中心位于scene的边缘
	QGraphicsEllipseItem   *item3 = new QGraphicsEllipseItem(-150, -150, 100, 100); //矩形框内创建圆,绘图项的局部coordinate,左上角(-100,-50),直径100
	//item3->setPos(rect.right(), rect.bottom());
	item3->setBrush(QBrush(Qt::red));
	item3->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	scene->addItem(item3);

	scene->clearSelection();
	//    item->setSelected(true);
	//    ui.View->setDragMode(QGraphicsView::RubberBandDrag);

	currentTool = ToolTypes::Line;
}

AnnotationOnImage::~AnnotationOnImage()
{
	if (pItem != NULL)
	{
		delete(pItem);
		pItem = NULL;
	}
}

bool isLine1 = true;
void AnnotationOnImage::on_changeLinePositionButton_clicked()
{
	if (isLine1)
	{
		pItem->setLine(100, -100, -100, 100);
	}
	else
	{
		pItem->setLine(-100, -100, 100, 100);
	}
	isLine1 = !isLine1;
}


void AnnotationOnImage::resizeEvent(QResizeEvent *event)
{ //窗口变化大小时的事件
	Q_UNUSED(event);
	//Graphics Viewcoordinate,left top is always（0,0）,width=,长度=
	ui.labViewSize->setText(QString::asprintf("Graphics Viewcoordinate,left top is always(0,0),width=%d,height=%d",
		ui.View->width(), ui.View->height()));

	QRectF  rectF = ui.View->sceneRect(); //Scene的矩形区
	ui.LabSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect=(Left,Top,Width,Height)=%.0f,%.0f,%.0f,%.0f",
		rectF.left(), rectF.top(), rectF.width(), rectF.height()));
}

AnnotationOnImage::AnnotationOnImage(QWidget *parent) :QMainWindow(parent)
{
	ui.setupUi(this);

	labViewCord = new QLabel("View coordinate：");
	labViewCord->setMinimumWidth(150);
	ui.statusBar->addWidget(labViewCord);

	labSceneCord = new QLabel("Scene coordinate：");
	labSceneCord->setMinimumWidth(150);
	ui.statusBar->addWidget(labSceneCord);

	labItemCord = new QLabel("Item coordinate：");
	labItemCord->setMinimumWidth(150);
	ui.statusBar->addWidget(labItemCord);

	ui.View->setCursor(Qt::CrossCursor);
	ui.View->setMouseTracking(true);
	ui.View->setDragMode(QGraphicsView::RubberBandDrag);

	//接收到mouseMovePoint信号，传递给on_mouseMovePoint函数
	QObject::connect(ui.View, SIGNAL(mouseMovePoint(QPoint)),
		this, SLOT(on_mouseMovePoint(QPoint)));

	QObject::connect(ui.View, SIGNAL(mouseClicked(QPoint)),
		this, SLOT(on_mouseClicked(QPoint)));

	iniGraphicsSystem();
}

int clickTimes = 0;
void AnnotationOnImage::on_mouseMovePoint(QPoint point)
{//鼠标移动事件,point是 GraphicsView的coordinate,物理coordinate
	labViewCord->setText(QString::asprintf("View coordinate:%d,%d", point.x(), point.y()));
	QPointF pointScene = ui.View->mapToScene(point); //转换到Scenecoordinate
	labSceneCord->setText(QString::asprintf("Scene coordinate:%.0f,%.0f", pointScene.x(), pointScene.y()));

	switch (currentTool)
	{
	case ToolTypes::Line:
		if (clickTimes == 1)
		{
			pItem->setLine(firstPoint.x(), firstPoint.y(), pointScene.x(), pointScene.y());
		}
		break;
	default:
	break;
	}
}

void AnnotationOnImage::on_mouseClicked(QPoint point)
{
	QPointF pointScene = ui.View->mapToScene(point); //转换到Scenecoordinate
	clickTimes = (++clickTimes) > 1 ? 0 : clickTimes;

	switch (currentTool)
	{
	case ToolTypes::Line:
		if (clickTimes == 1)
		{
			firstPoint = pointScene;
			pItem = new QGraphicsLineItem(firstPoint.x(), firstPoint.y(), firstPoint.x(), firstPoint.y());
			pItem->setPen(QColor(Qt::black));
			scene->addItem(pItem);
		}
		break;
	default:
		break;
	}

	
}
