#pragma once

#include <QDialog>
#include <memory>

struct dialogData;

class QMapMaker;

class newSceneDialog :public QDialog
{
	Q_OBJECT
public:
	newSceneDialog(QMapMaker *parent);
	~newSceneDialog();
protected:
	virtual void showEvent(QShowEvent *e) override;
	virtual void closeEvent(QCloseEvent *e) override;
protected:
	std::unique_ptr<dialogData> data;
};

