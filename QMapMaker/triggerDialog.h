#pragma once
#include <QDialog>
#include <memory>

struct triggerData;

class QMapMaker;

class triggerDialog :public QDialog
{
public:
	triggerDialog(QMapMaker *parent);
	~triggerDialog();
protected:
	virtual void showEvent(QShowEvent *e) override;
	virtual void closeEvent(QCloseEvent *e) override;
protected:
	std::unique_ptr<triggerData> data;
};

