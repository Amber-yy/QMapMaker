#include "newSceneDialog.h"
#include "qmapmaker.h"

#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

struct dialogData
{
	QPushButton *submit;
	QLabel *lengthLa;
	QLabel *widthLa;
	QLabel *fillLa;
	QSpinBox *lengthBox;
	QSpinBox *widthBox;
	QSpinBox *fillBox;
	QMapMaker *parent;
	bool ok;
};

newSceneDialog::newSceneDialog(QMapMaker *parent)
{
	try
	{
		data = std::make_unique<dialogData>();
		data->submit=new QPushButton(u8"确定",this);
		data->lengthLa = new QLabel(u8"长度",this);
		data->widthLa = new QLabel(u8"宽度", this);
		data->fillLa = new QLabel(u8"填充物体", this);
		data->lengthBox = new QSpinBox(this);
		data->widthBox= new QSpinBox(this);
		data->fillBox = new QSpinBox(this);

		data->lengthBox->setRange(0,1000);
		data->widthBox->setRange(0, 1000);

		data->lengthLa->setGeometry(20,10,60,20);
		data->widthLa->setGeometry(20,40,60,20);
		data->fillLa->setGeometry(20,70,60,20);
		data->lengthBox->setGeometry(100,10,50,20);
		data->widthBox->setGeometry(100,40,50,20);
		data->fillBox->setGeometry(100,70,50,20);

		data->submit->setGeometry(45, 100, 60, 25);

		setMaximumSize(150, 140);
		setMinimumSize(150, 140);

		data->parent = parent;
		connect(data->submit, &QPushButton::clicked, [this]()
		{
			data->ok = true;
			close();
		}
		);
	}
	catch(std::bad_alloc &e)
	{ 
		abort();
	}
}

newSceneDialog::~newSceneDialog()
{

}

void newSceneDialog::showEvent(QShowEvent * e)
{
	data->fillBox->setRange(0,data->parent->getObjectNum());
	data->fillBox->setValue(0);
	data->lengthBox->setValue(0);
	data->widthBox->setValue(0);
	data->ok = false;
	setWindowTitle("");
}

void newSceneDialog::closeEvent(QCloseEvent * e)
{
	if (data->ok)
	{
		data->parent->newMap(data->widthBox->value(), data->lengthBox->value(), data->fillBox->value());
	}
}
