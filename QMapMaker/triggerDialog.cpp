#include "triggerDialog.h"
#include "qmapmaker.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

struct triggerData
{
	QMapMaker *parent;
	QLineEdit *editor;
	QPushButton *submit;
	QLabel *prompt;
};

triggerDialog::triggerDialog(QMapMaker *parent)
{
	try
	{
		data = std::make_unique<triggerData>();
		data->editor = new QLineEdit(this);
		data->submit = new QPushButton(u8"确定",this);
		data->prompt = new QLabel(u8"触发名",this);

		data->prompt->setGeometry(10, 30, 40, 20);
		data->editor->setGeometry(60, 30, 100, 20);
		data->submit->setGeometry(55, 60, 60, 20);

		setMaximumSize(170,90);
		setMinimumSize(170, 90);

		data->parent = parent;
	}
	catch (std::bad_alloc &)
	{
		abort();
	}
}

triggerDialog::~triggerDialog()
{

}

void triggerDialog::showEvent(QShowEvent * e)
{
	data->editor->clear();
}

void triggerDialog::closeEvent(QCloseEvent * e)
{
	if (!data->editor->text().isEmpty())
	{
		data->parent->addTrigger(data->editor->text());
	}
}
