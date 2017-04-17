#include "triggerSelector.h"

#include "qmapmaker.h"

#include <QButtonGroup>
#include <QVector>
#include <QRadioButton>
#include <QPushButton>

#include <QDebug>

struct selectorData
{
	QVector<QRadioButton *> allTrigger;
	QButtonGroup *group;
	QMapMaker *parent;
};

triggerSelector::triggerSelector(QMapMaker *parent)
{
	data = std::make_unique<selectorData>();
	data->parent = parent;

	auto &trigger = data->parent->getAllTrigger();

	data->group = new QButtonGroup(this);
	for (int i = 0; i < trigger.size(); ++i)
	{
		data->allTrigger.push_back(new QRadioButton(trigger[i].c_str(), this));
		data->group->addButton(data->allTrigger[i]);
		data->allTrigger[i]->setGeometry(10, i * 25, 100, 20);
	}

	QPushButton *submit = new QPushButton(u8"È·¶¨",this);
	submit->setGeometry(60, trigger.size() * 25, 80, 25);

	setMaximumSize(200,trigger.size() * 25 + 50);
	setMinimumSize(200, trigger.size() * 25 + 50);

	connect(submit,&QPushButton::clicked,this,&QDialog::close);
}

triggerSelector::~triggerSelector()
{

}

void triggerSelector::showEvent(QShowEvent * e)
{


}

void triggerSelector::closeEvent(QCloseEvent * e)
{
	for (int i = 0; i < data->allTrigger.size(); ++i)
	{
		if (data->allTrigger[i]->isChecked())
		{
			data->parent->setTriggerIndex(i);
			break;
		}
	}
}
