#ifndef ONEKEYHIDE_H
#define ONEKEYHIDE_H

#include <QtWidgets/QDialog>
#include "ui_onekeyhide.h"

#include <QVBoxLayout>
#include <QMenu>

#include "core/hider.h"

#include "base-ui/supportframess.h"
#include "ui/newdialog.h"

class OneKeyHide : public SupportFrameless<QDialog>, public Hider::Delegate {
	Q_OBJECT

public:
	OneKeyHide(QWidget *parent = 0);
	~OneKeyHide();

	virtual void OnEnumStart() override;
	virtual void OnEnumFinish(const WindowHash&) override;
	virtual void OnNewRuleAdd(const Rule&  rule) override;
	virtual void OnNewRuleUpdate(const Rule& rule) override;
	virtual void OnWindowVisibleChanged(HWND hwnd, bool visible) override;
public slots:
	void on_pushButtonHome_clicked();
	void on_pushButtonNewHide_clicked();
	void on_pushButtonSettings_clicked();
	void on_pushButtonHelp_clicked();

	void on_pushButtonClose_clicked();
	void on_pushButtonMax_clicked();
	void on_pushButtonMin_clicked();

	void SlotVisibleActivated();
	void SlotOnekeyActivated();

	void SlotDelete();
private:
	void Init();

	void SetWidgetToWidget(QWidget* parent, QWidget* child);

	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

	void InitTable(QTableWidget* table);

	void AddRow(QTableWidget* table, bool is_hide, const Rule& list);

	void AddHelp(const QString& title, const QString& gif_path);

	bool eventFilter(QObject* obj, QEvent* e);
private:
	Ui::OneKeyHideClass ui;

	Hider* hider_;

	NewDialog* new_dialog_;

	QVBoxLayout* help_layout_;

	QMenu menu_;
};

#endif // ONEKEYHIDE_H
