#include "MapLua.h"
#include "qmapmaker.h"

int MapLua::addObject(lua_State *)
{
	QMapMaker **data = static_cast<QMapMaker **>(uniqueState->toUserData(1));

	if (data == nullptr)
	{
		return 0;
	}

	QMapMaker *game = *data;

	int len = uniqueState->length(2);

	if (len < 6)
	{
		return 0;
	}

	uniqueState->getRow(2, 1);
	int level = uniqueState->toInteger(-1);
	uniqueState->pop(1);
	QVector<int> canMoveTo(4);
	for (int i = 0; i < 4; ++i)
	{
		uniqueState->getRow(2, i + 2);
		canMoveTo[i] = uniqueState->toInteger(-1);
		uniqueState->pop(1);
	}

	QStringList list;

	for (int i = 6; i <= len; ++i)
	{
		uniqueState->getRow(2, i);
		list.push_back(uniqueState->toString(-1));
		uniqueState->pop(1);
	}

	game->addObect(list, std::move(canMoveTo), level);
	return 0;
}

int MapLua::setMap(lua_State *)
{
	QMapMaker **data = static_cast<QMapMaker **>(uniqueState->toUserData(1));

	if (data == nullptr)
	{
		return 0;
	}

	QMapMaker *scene = *data;

	int maxY = uniqueState->length(2);

	if (maxY < 1)
	{
		return 0;
	}

	uniqueState->getRow(-1, 1);
	int maxX = uniqueState->length(-1);
	uniqueState->pop(1);

	QVector<QVector<mapObject>> map(maxY, QVector<mapObject>(maxX));

	mapObject temp;

	for (int i = 1; i <= maxY; i++)
	{
		uniqueState->getRow(-1, i);
		for (int j = 1; j <= maxX; j++)
		{
			uniqueState->getRow(-1, j);

			uniqueState->getRow(-1, 1);
			temp.groundIndex = uniqueState->toInteger(-1);
			uniqueState->pop(1);

			uniqueState->getRow(-1, 2);
			temp.objectIndex = uniqueState->toInteger(-1);
			uniqueState->pop(1);

			uniqueState->getRow(-1, 3);
			temp.buildingIndex = uniqueState->toInteger(-1);
			uniqueState->pop(1);

			uniqueState->getRow(-1, 4);
			temp.onStep = uniqueState->toInteger(-1);
			uniqueState->pop(1);

			uniqueState->getRow(-1, 5);
			temp.onCheck = uniqueState->toInteger(-1);
			uniqueState->pop(1);

			uniqueState->getRow(-1, 6);
			temp.onTime = uniqueState->toInteger(-1);
			uniqueState->pop(1);

			uniqueState->getRow(-1, 7);
			temp.onTouch = uniqueState->toInteger(-1);

			map[i - 1][j - 1] = temp;

			uniqueState->pop(2);

		}

		uniqueState->pop(1);
	}

	scene->setMap(std::move(map));

	return 0;
}

int MapLua::setAllTrigger(lua_State *)
{
	QMapMaker **data = static_cast<QMapMaker **>(uniqueState->toUserData(1));

	if (data == nullptr)
	{
		return 0;
	}

	QMapMaker *scene = *data;

	int len = uniqueState->length(2);
	QVector<std::string> triggers(len);

	for (int i = 1; i <= len; i++)
	{
		uniqueState->getRow(2, i);
		triggers[i - 1] = uniqueState->toString(-1);
		uniqueState->pop(1);
	}
	scene->setAllTrigger(std::move(triggers));

	return 0;
}
