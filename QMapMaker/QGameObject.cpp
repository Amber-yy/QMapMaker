#include "QGameObject.h"

#include <QPixmap>
#include <QPainter>

#include <QDebug>

/*
0:ио
1:об
2:вС
3:ср
*/

struct gameObjectData
{
	QVector<QPixmap> allPicture;
	int level;
};

QGameObject::QGameObject(QObject *parent):QObject(parent)
{
	data = std::make_unique<gameObjectData>();
	data->allPicture.resize(1);
	data->allPicture[0] = QPixmap(16, 16);
	data->allPicture[0].fill(Qt::black);
}

QGameObject::~QGameObject()
{

}

void QGameObject::paint(QPoint target, QSize size,QPixmap *canvas)
{
	int x = target.x()*size.width();
	int r = size.width()/data->allPicture[0].width();
	int y = target.y()*size.width()-(size.height()-16);

	QPainter painter(canvas);

	painter.drawPixmap(x, y, size.width(), size.height(), data->allPicture[0]);
}

void QGameObject::setData(QStringList & pics, QVector<int>&& canMoveTo,int level)
{
	data->allPicture.resize(pics.size());

	for (int i = 0; i < pics.size(); ++i)
	{
		data->allPicture[i].load(pics[i]);
	}

	data->level = level;
}

int QGameObject::getLevel()
{
	return data->level;
}
