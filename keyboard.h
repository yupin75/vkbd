#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <QtWidgets/QWidget>
#include <QList>
#include "ui_keyboard.h"

class KeyBoard: public QWidget
{
#define DEFAULT_BACKGROUND_BUTTON       "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #8C8F8C, stop: 1 #000000);"
#define CHANGED_BACKGROUND_BUTTON       "background:lightgray;color:darkred;"
//#define DEFAULT_BACKGROUND_BUTTON     "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);"
//#define CHANGED_BACKGROUND_BUTTON     "background:lightblue;"

#define DEFAULT_STYLE_BUTTON            "color:white;border: 1px solid #000000;border-radius:6px;"
//#define DEFAULT_STYLE_BUTTON          "border: 1px solid #8f8f91;border-radius:5px;"
#define STYLE_FOCUS_TEXT                "border: 1px solid red"

//#define DEFAULT_STYLE_BUTTON		"color:white;border: 2px solid black;border-radius:5px;font-weight: bold;font-size:17px;"
//#define DEFAULT_BACKGROUND_BUTTON	"background:gray;"
//#define CHANGED_BACKGROUND_BUTTON	"background:red;"

#define EMBEDDED_KEYBOARD               "font-size:9px"
#define WIDTH_ZOOM_KEY                  20
#define HEIGHT_ZOOM_KEY                 WIDTH_ZOOM_KEY


	Q_OBJECT
public:
    KeyBoard(QWidget *parent = 0);
	~KeyBoard();

public Q_SLOTS:
	void doButtonClicked(int idx);

private:
	void setKeyMap(const char **keymap);
	Ui::KeyBoard *m_ui;
	QList<QPushButton *> m_allKeys;

	bool m_caps;
};

#endif

