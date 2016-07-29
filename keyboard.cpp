#include "keyboard.h"
#include "ui_keyboard.h"
#include <QDebug>
#include <QSignalMapper>

#include "en_keymap.h"



KeyBoard::KeyBoard(QWidget *parent)
    : QWidget(parent)
{
	m_caps = false;

	m_ui = new Ui::KeyBoard;
	m_ui->setupUi(this);

	QSignalMapper* mapper = new QSignalMapper(this);
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(doButtonClicked(int)));

	m_allKeys = findChildren<QPushButton *>();
	int i = 0;
	for (QList<QPushButton *>::const_iterator iter = m_allKeys.begin();
			iter != m_allKeys.end(); iter++, i++) {
		mapper->setMapping((*iter), i);
		connect(*iter, SIGNAL(clicked()), mapper, SLOT(map()));
		//qDebug() << (*iter)->text();
	}
    setKeyMap(en_lower_keymap);


    //setFocusPolicy(Qt::NoFocus);
    //setAttribute(Qt::WA_ShowWithoutActivating);
    //setParent(0);
    //setWindowFlags(Qt::Tool | Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowTransparentForInput | Qt::WindowDoesNotAcceptFocus | Qt::Tool );
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::Tool );

}

KeyBoard::~KeyBoard()
{
	delete m_ui;
}

void KeyBoard::setKeyMap(const char **keymap)
{
	int i = 0;


	for (QList<QPushButton *>::const_iterator iter = m_allKeys.begin();
			iter != m_allKeys.end(); iter++, i++) {
		(*iter)->setText(keymap[i]);
        (*iter)->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON));
        //(*iter)->setFocusPolicy(Qt::NoFocus);
	}
	
}

void KeyBoard::doButtonClicked(int idx)
{
	qDebug() << m_allKeys.at(idx)->text();

	if (m_allKeys.at(idx)->text() == "Caps") {
		m_caps = !m_caps;
		if (m_caps) {
			setKeyMap(en_upper_keymap);
		} else {
			setKeyMap(en_lower_keymap);
		}
	} else if (m_allKeys.at(idx)->text() == "123") {
		setKeyMap(en_number_keymap);
	} else if (m_allKeys.at(idx)->text() == "en/cn") {
		setKeyMap(en_lower_keymap);
	}


}
