#ifndef HIDER_H
#define HIDER_H

#include "windowinfo.h"

#include <QHash>
#include <QObject>
#include <Windows.h>

#include "3rd/qxtglobalshortcut/qxtglobalshortcut.h"
#include "3rd/volume/volume.h"

class Hider : public QObject {
	Q_OBJECT

public:
	class Delegate {
	public:
		virtual void OnEnumStart() {}
		virtual void OnEnumFinish(const WindowHash&) {}

		virtual void OnNewRuleAdd(const Rule&  rule) {}
		virtual void OnNewRuleUpdate(const Rule& rule) {}

		virtual void OnWindowVisibleChanged(HWND hwnd, bool visible) {}
	};

	Hider(Delegate* delegate);
	~Hider();

	static WindowHash WindowsInfo() { return windows_info_; }

	static Window FindByHwnd(HWND);

	void EnableEnum(bool enable) { enable_enum_window_ = enable; }

	void AddRule(const QKeySequence& key_seq, const Rule& rule);

	void OneKeyAllHide();

	void OneKeyShowHide(WindowList& list);

	void OneKeySwitch(WindowList& list);

	void SetVisible(HWND, bool visible);

	void SetUnsetted(HWND);
public slots :
	void StartEnumWindows();

	void SlotShortCutActivated();
private:
	static bool CALLBACK MyEnumWindowsProc(HWND hwnd, LPARAM lParam);

private:
	static WindowHash windows_info_;

	QHash<QxtGlobalShortcut*, Rule> actions_;

	Delegate* delegate_;

	Volumer volumer_;

	bool enable_enum_window_;
};

#endif // HIDER_H
