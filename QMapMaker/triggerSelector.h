#pragma once

#include <QDialog>
#include <memory>

struct selectorData;

class QMapMaker;

class triggerSelector :public QDialog
{
public:
	triggerSelector(QMapMaker *parent);
	~triggerSelector();
protected:
	virtual void showEvent(QShowEvent *e) override;
	virtual void closeEvent(QCloseEvent *e) override;
protected:
	std::unique_ptr<selectorData> data;
};

