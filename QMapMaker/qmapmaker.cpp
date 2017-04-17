#include "qmapmaker.h"
#include "MapLua.h"
#include "QGameObject.h"
#include "newSceneDialog.h"
#include "triggerDialog.h"
#include "triggerSelector.h"

#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>

#include <QDebug>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

struct MapMakerData
{
	QVector<QGameObject *> allObjects;
	QVector <QPixmap> mapCanvas;
	QVector<std::string> allTriggers;
	QVector<QVector<mapObject>> mapData;
	QPoint currentItem;
	QPoint currentMapObject;
	QPixmap itemCanvas;
	QScrollArea *map;
	QScrollArea *item;
	QWidget *mapWidget;
	QWidget *itemWidget;
	QLabel *stepLa;
	QLabel *timeLa;
	QLabel *checkLa;
	QLabel *touchLa;
	QLineEdit *stepEd;
	QLineEdit *checkEd;
	QLineEdit *timeEd;
	QLineEdit *touchEd;
	QPushButton *stepBt;
	QPushButton *checkBt;
	QPushButton *timeBt;
	QPushButton *touchBt;
	QPushButton *newMap;
	QPushButton *openMap;
	QPushButton *addTrigger;
	newSceneDialog *sceneDialog;
	triggerDialog *trigger;
	triggerSelector *selector;
	int currentIndex;
};

QMapMaker::QMapMaker(QWidget *parent): QWidget(parent)
{
	try
	{
		registerToLua();
		createSubCom();
		setGeometry();
		connectSignal();
		auto temp = new QGameObject(this);
		data->allObjects.push_back(temp);
		setMaximumSize(980, 620);
		setMinimumSize(980, 620);

	}
	catch (std::bad_alloc &)
	{
		abort();
	}
	catch (std::exception &e)
	{
		QMessageBox::warning(this, u8"Lua解析错误", e.what());
		exit(1);
	}
}

QMapMaker::~QMapMaker()
{

}

void QMapMaker::addObect(QStringList & pics, QVector<int>&& canMoveTo, int level)
{
	QGameObject *obj = new QGameObject(this);
	obj->setData(pics, std::move(canMoveTo), level);
	data->allObjects.push_back(obj);
}

void QMapMaker::newMap(int w, int h, int f)
{
	data->mapData = QVector<QVector<mapObject>>(h, QVector<mapObject>(w,f));
	data->mapWidget->setGeometry(0, 0, w * 16 + 20, h * 16 + 20);
	data->mapCanvas[0] = QPixmap(w * 16 + 20, h * 16 + 20);
	data->mapCanvas[1] = QPixmap(w * 16 + 20, h * 16 + 20);
	data->mapCanvas[2] = QPixmap(w * 16 + 20, h * 16 + 20);
}

void QMapMaker::openMap()
{
	QString route=QFileDialog::getOpenFileName(this, u8"请选择地图文件",QDir::currentPath(),"*.lua");
	if (route.isEmpty())
	{
		return;
	}
	MapLua::getLua()->doFile(route.toStdString().c_str());
	MapLua::getLua()->getGlobal("start");
	MapLua::getLua()->pushUserData(this, "QMapMaker");
	MapLua::getLua()->pushUserData(this, "QMapMaker");
	MapLua::getLua()->protectedCall(2, 0, 0);
}

void QMapMaker::addTrigger(QString &trigger)
{
	data->allTriggers.push_back(trigger.toStdString());
}

void QMapMaker::setAllTrigger(QVector<std::string>&& triggers)
{
	data->allTriggers = triggers;
}

QVector<std::string>& QMapMaker::getAllTrigger()
{
	return data->allTriggers;
}

void QMapMaker::setMap(QVector<QVector<mapObject>>&& objects)
{
	data->mapData = objects;
	int h = data->mapData.size();
	int w = data->mapData[0].size();
	data->mapWidget->setGeometry(0, 0, w * 16 + 20, h * 16 + 20);
	data->mapCanvas[0] = QPixmap(w * 16 + 20, h * 16 + 20);
	data->mapCanvas[1] = QPixmap(w * 16 + 20, h * 16 + 20);
	data->mapCanvas[2] = QPixmap(w * 16 + 20, h * 16 + 20);
}

void QMapMaker::setTriggerIndex(int index)
{
	if (data->currentMapObject.x() == -1)
	{
		return;
	}


	if (data->currentIndex == 0)
	{
		data->mapData[data->currentMapObject.y()][data->currentMapObject.x()].onStep = index;
	}
	else if (data->currentIndex == 1)
	{
		data->mapData[data->currentMapObject.y()][data->currentMapObject.x()].onCheck = index;
	}
	else if (data->currentIndex == 2)
	{
		data->mapData[data->currentMapObject.y()][data->currentMapObject.x()].onTime = index;
	}
	else if (data->currentIndex == 3)
	{
		data->mapData[data->currentMapObject.y()][data->currentMapObject.x()].onTouch = index;
	}

}

void QMapMaker::saveMap()
{
	QString str = QFileDialog::getOpenFileName(this,u8"请选择保存路径",QDir::currentPath(),"*.lua");
	if (str.isEmpty())
	{
		return;
	}

	auto list = str.split('/');
	QString temp = list[list.size() - 1];
	list = temp.split('.');
	QString sceneName = temp[0];

	QFile outFile(str);

	outFile.open(QIODevice::WriteOnly);

	

	outFile.write();







}

int QMapMaker::getObjectNum()
{
	return data->allObjects.size()-1;
}

bool QMapMaker::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == data->itemWidget)
	{
		if (event->type() == QEvent::Paint)
		{
			data->itemCanvas.fill(Qt::transparent);
			for (int i = 0; i < data->allObjects.size(); ++i)
			{
				data->allObjects[i]->paint(QPoint(i % 15, i / 15), QSize(16, 16), &data->itemCanvas);
			}
			QPainter painter(data->itemWidget);
			painter.drawPixmap(data->itemWidget->rect(), data->itemCanvas);
			painter.setPen(Qt::red);
			if (data->currentItem.x() != -1)
			{
				painter.drawRect(data->currentItem.x() * 16, data->currentItem.y() * 16, 16, 16);
			}

			return true;
		}
		else if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *e = dynamic_cast<QMouseEvent *>(event);
			int x = e->x() / 16;
			int y = e->y() / 16;

			data->itemWidget->update();
			if (x >= 15)
			{
				data->currentItem.setX(-1);
				return false;
			}

			if ((y * 15 + x + 1) > data->allObjects.size())
			{
				data->currentItem.setX(-1);
				return false;
			}

			data->currentItem = QPoint(x, y);

			return true;
		}
	}

	if (obj == data->mapWidget)
	{

		if (event->type() == QEvent::Paint)
		{
			data->mapCanvas[0].fill(Qt::black);
			data->mapCanvas[1].fill(Qt::transparent);
			data->mapCanvas[2].fill(Qt::transparent);

			for (int i = 0; i < data->mapData.size(); ++i)
			{
				for (int j = 0; j <  data->mapData[0].size(); ++j)
				{
					if (data->mapData[i][j].groundIndex != -1)
					{
						data->allObjects[data->mapData[i][j].groundIndex]->paint(QPoint(j, i), QSize(16, 16), &data->mapCanvas[0]);
					}
					if (data->mapData[i][j].objectIndex != -1)
					{
						data->allObjects[data->mapData[i][j].objectIndex]->paint(QPoint(j, i), QSize(16, 22), &data->mapCanvas[1]);
					}
					if (data->mapData[i][j].buildingIndex != -1)
					{
						data->allObjects[data->mapData[i][j].buildingIndex]->paint(QPoint(j, i), QSize(16, 16), &data->mapCanvas[2]);
					}

					if (data->mapData[i][j].onCheck != -1|| data->mapData[i][j].onStep != -1|| data->mapData[i][j].onTime != -1|| data->mapData[i][j].onTouch != -1)
					{
						QPainter rectPainter(&data->mapCanvas[2]);
						rectPainter.setPen(Qt::red);
						rectPainter.drawRect(j* 16, i * 16, 16, 16);
					}

				}
			}

			QPainter rectPainter(&data->mapCanvas[2]);
			rectPainter.setPen(Qt::blue);
			rectPainter.drawRect(data->currentMapObject.x() * 16, data->currentMapObject.y() * 16, 16, 16);

			QPainter painter(data->mapWidget);
			painter.drawPixmap(data->mapWidget->rect(), data->mapCanvas[0]);
			painter.drawPixmap(data->mapWidget->rect(), data->mapCanvas[1]);
			painter.drawPixmap(data->mapWidget->rect(), data->mapCanvas[2]);

			return true;
		}
		else if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *e = dynamic_cast<QMouseEvent *>(event);
			int x = e->x() / 16;
			int y = e->y() / 16;

			if (x < 0 || y < 0)
			{
				return false;
			}

			if (y >=data->mapData.size() || x >=data->mapData[0].size())
			{
				return false;
			}

			if (data->currentItem.x() == -1)
			{
				data->currentMapObject.setX(x);
				data->currentMapObject.setY(y);

				data->stepEd->clear();
				data->checkEd->clear();
				data->timeEd->clear();
				data->touchEd->clear();

				if (data->mapData[y][x].onStep != -1)
				{
					data->stepEd->setText(QString(data->allTriggers[data->mapData[y][x].onStep].c_str()));
				}
				if (data->mapData[y][x].onCheck != -1)
				{
					data->checkEd->setText(QString(data->allTriggers[data->mapData[y][x].onCheck].c_str()));
				}
				if (data->mapData[y][x].onTime != -1)
				{
					data->timeEd->setText(QString(data->allTriggers[data->mapData[y][x].onTime].c_str()));
				}
				if (data->mapData[y][x].onTouch != -1)
				{
					data->touchEd->setText(QString(data->allTriggers[data->mapData[y][x].onTouch].c_str()));
				}

				data->mapWidget->update();
				return false;
			}

			int item = data->currentItem.y() * 15 + data->currentItem.x();
			int level = data->allObjects[item]->getLevel();

			if (item == data->allObjects.size() - 1)
			{
				data->mapData[y][x].objectIndex = data->mapData[y][x].buildingIndex = -1;
				data->mapWidget->update();
				return false;
			}

			if (level == 0)
			{
				if (data->mapData[y][x].groundIndex != item)
				{
					data->mapData[y][x].groundIndex = item;
					data->mapWidget->update();
				}
			}
			else if (level == 1)
			{
				if (data->mapData[y][x].objectIndex != item)
				{
					data->mapData[y][x].objectIndex = item;
					data->mapWidget->update();
				}
			}
			else
			{
				if (data->mapData[y][x].buildingIndex != item)
				{
					data->mapData[y][x].buildingIndex = item;
					data->mapWidget->update();
				}
			}

			return true;
		}
		else if (event->type() == QEvent::MouseMove)
		{
			QMouseEvent *e = dynamic_cast<QMouseEvent *>(event);
			int x = e->x() / 16;
			int y = e->y() / 16;

			if (x < 0 || y < 0)
			{
				return false;
			}

			if (y >= data->mapData.size() || x >= data->mapData[0].size())
			{
				return false;
			}

			if (data->currentItem.x() == -1)
			{
				return false;
			}

			int item = data->currentItem.y() * 15 + data->currentItem.x();
			int level = data->allObjects[item]->getLevel();

			if (item ==data->allObjects.size()-1)
			{
				data->mapData[y][x].objectIndex = data->mapData[y][x].buildingIndex = -1;
				data->mapWidget->update();
				return false;
			}

			if (level == 0)
			{
				if (data->mapData[y][x].groundIndex != item)
				{
					data->mapData[y][x].groundIndex = item;
					data->mapWidget->update();
				}
			}
			else if (level == 1)
			{
				if (data->mapData[y][x].objectIndex != item)
				{
					data->mapData[y][x].objectIndex = item;
					data->mapWidget->update();
				}
			}
			else
			{
				if (data->mapData[y][x].buildingIndex != item)
				{
					data->mapData[y][x].buildingIndex = item;
					data->mapWidget->update();
				}
			}

			return true;
		}
	}

	return false;
}

void QMapMaker::createSubCom()
{
	data = std::make_unique<MapMakerData>();

	data->map = new QScrollArea(this);
	data->item = new QScrollArea(this);
	data->mapWidget = new QWidget(data->map);
	data->itemWidget = new QWidget(data->item);
	data->stepLa = new QLabel(u8"踩踏触发",this);
	data->checkLa = new QLabel(u8"检查触发", this);
	data->timeLa = new QLabel(u8"定时触发", this);
	data->touchLa = new QLabel(u8"触碰触发", this);
	data->stepEd = new QLineEdit(this);
	data->checkEd = new QLineEdit(this);
	data->timeEd = new QLineEdit(this);
	data->touchEd = new QLineEdit(this);
	data->stepBt = new QPushButton(u8"修改", this);
	data->checkBt = new QPushButton(u8"修改", this);
	data->timeBt = new QPushButton(u8"修改", this);
	data->touchBt = new QPushButton(u8"修改", this);
	data->newMap = new QPushButton(u8"新建场景", this);
	data->openMap = new QPushButton(u8"打开场景", this);
	data->addTrigger = new QPushButton(u8"新建触发", this);
	data->sceneDialog = new newSceneDialog(this);
	data->trigger = new triggerDialog(this);

	data->map->setWidget(data->mapWidget);
	data->item->setWidget(data->itemWidget);

	data->mapWidget->installEventFilter(this);
	data->itemWidget->installEventFilter(this);
	
	data->mapCanvas.resize(3);

	data->stepEd->setEnabled(false);
	data->checkEd->setEnabled(false);
	data->timeEd->setEnabled(false);
	data->touchEd->setEnabled(false);

	data->currentItem = QPoint(0, 0);
	data->currentMapObject = QPoint(-1, -1);

	MapLua::getLua()->doFile("objects/objects.lua");
	MapLua::getLua()->getGlobal("objects");
	MapLua::getLua()->pushUserData(this, "QMapMaker");
	MapLua::getLua()->protectedCall(1, 0, 0);

}

void QMapMaker::connectSignal()
{
	connect(data->newMap, &QPushButton::clicked, this, &QMapMaker::newScence);
	connect(data->openMap, &QPushButton::clicked, this, &QMapMaker::openMap);
	connect(data->addTrigger, &QPushButton::clicked, [this]()
	{
		data->trigger->exec();
	}
	);

	connect(data->stepBt, &QPushButton::clicked, [this]()
	{
		if (data->allTriggers.size() > 0)
		{
			data->currentIndex = 0;
			data->selector = new triggerSelector(this);
			data->selector->exec();
			delete data->selector;
		}
		else
		{
			QMessageBox::warning(this, u8"错误", u8"当前场景无触发");
		}
	}
	);

	connect(data->checkBt, &QPushButton::clicked, [this]()
	{
		if (data->allTriggers.size() > 0)
		{
			data->currentIndex = 1;
			data->selector = new triggerSelector(this);
			data->selector->exec();
			delete data->selector;
		}
		else
		{
			QMessageBox::warning(this, u8"错误", u8"当前场景无触发");
		}
	}
	);

	connect(data->timeBt, &QPushButton::clicked, [this]()
	{
		if (data->allTriggers.size() > 0)
		{
			data->currentIndex = 2;
			data->selector = new triggerSelector(this);
			data->selector->exec();
			delete data->selector;
		}
		else
		{
			QMessageBox::warning(this, u8"错误", u8"当前场景无触发");
		}
	}
	);

	connect(data->touchBt, &QPushButton::clicked, [this]()
	{
		if (data->allTriggers.size() > 0)
		{
			data->currentIndex = 3;
			data->selector = new triggerSelector(this);
			data->selector->exec();
			delete data->selector;
		}
		else
		{
			QMessageBox::warning(this, u8"错误", u8"当前场景无触发");
		}
	}
	);

}

void QMapMaker::setGeometry()
{
	data->map->setGeometry(0, 0, 700, 620);
	data->item->setGeometry(705, 5, 270, 350);

	data->itemWidget->setGeometry(0, 0, 250, 350);

	data->stepLa->setGeometry(705, 370, 54, 20);
	data->checkLa->setGeometry(705,420,54,20);
	data->timeLa->setGeometry(705, 470, 54, 20);
	data->touchLa->setGeometry(705, 520, 54, 20);
	data->stepEd->setGeometry(770,370,150,20);
	data->checkEd->setGeometry(770, 420, 150, 20);
	data->timeEd->setGeometry(770, 470, 150, 20);
	data->touchEd->setGeometry(770, 520, 150, 20);
	data->stepBt->setGeometry(925,370,50,20);
	data->checkBt->setGeometry(925, 420, 50, 20);
	data->timeBt->setGeometry(925, 470, 50, 20);
	data->touchBt->setGeometry(925, 520, 50, 20);

	data->newMap->setGeometry(710,575,75,25);
	data->openMap->setGeometry(800, 575, 75, 25);
	data->addTrigger->setGeometry(890, 575, 75, 25);

	data->itemCanvas = QPixmap(250, 350);

	newMap(0, 0, 1);
}

void QMapMaker::newScence()
{
	data->sceneDialog->exec();
}

void QMapMaker::registerToLua()
{
	LuaOperator *op = MapLua::getLua();
	luaL_Reg reg[] =
	{
		{ "addObject",MapLua::addObject},
		{ "setMap",MapLua::setMap },
		{ "setAllTrigger",MapLua::setAllTrigger },
		{ nullptr,nullptr }
	};
	op->registerClass("QMapMaker", reg);
}
