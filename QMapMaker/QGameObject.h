#pragma once

#include <QObject>
#include <memory>

class QPoint;
struct gameObjectData;

class QGameObject :public QObject
{
public:
	QGameObject(QObject *parent);
	~QGameObject();
	void paint(QPoint target,QSize size, QPixmap *canvas);
	void setData(QStringList &pics, QVector<int>&& canMoveTo, int level);
	int getLevel();
protected:
	std::unique_ptr<gameObjectData> data;
};

