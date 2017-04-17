#ifndef QMAPMAKER_H
#define QMAPMAKER_H

#include <QWidget>
#include <memory>

struct MapMakerData;

struct mapObject
{
	mapObject()
	{
		objectIndex = buildingIndex = onStep = onCheck = onTime = onTouch = -1;
		groundIndex = 1;
	}
	mapObject(int f)
	{
		objectIndex = buildingIndex = onStep = onCheck = onTime = onTouch = -1;
		groundIndex = f;
	}
	int groundIndex;
	int objectIndex;
	int buildingIndex;
	int onStep;
	int onCheck;
	int onTime;
	int onTouch;
};

class QMapMaker : public QWidget
{
	Q_OBJECT
public:
	QMapMaker(QWidget *parent = 0);
	~QMapMaker();
	void addObect(QStringList &pics, QVector<int> &&canMoveTo, int level);
	void newMap(int w,int h,int f);
	void openMap();
	void addTrigger(QString &trigger);
	void setAllTrigger(QVector<std::string> &&triggers);
	QVector<std::string>& getAllTrigger();
	void setMap(QVector<QVector<mapObject>> &&objects);
	void setTriggerIndex(int index);
	void saveMap();
	int getObjectNum();
protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
protected:	
	void newScence();
	void registerToLua();
	void createSubCom();
	void connectSignal();
	void setGeometry();
protected:
	std::unique_ptr<MapMakerData> data;
};

#endif // QMAPMAKER_H
