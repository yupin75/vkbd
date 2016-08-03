#include "keyboard.h"
#include "ui_keyboard.h"
#include <QDebug>
#include <QSignalMapper>

#include "en_keymap.h"

#if 1
#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

void simulate_key(int fd, int kval)
{
         struct input_event event;
        gettimeofday(&event.time, 0);
       //按下kval鍵
         event.type = EV_KEY;
         event.value = 1;
         event.code = kval;
         write(fd, &event, sizeof(event));
       //同步，也就是把它報告給系統
         event.type = EV_SYN;
         event.value = 0;
         event.code = SYN_REPORT;
         write(fd, &event, sizeof(event));

         memset(&event, 0, sizeof(event));
         gettimeofday(&event.time, 0);
         //鬆開kval鍵
        event.type = EV_KEY;
         event.value = 0;
         event.code = kval;
         write(fd, &event, sizeof(event));
       //同步，也就是把它報告給系統
       event.type = EV_SYN;
       event.value = 0;
       event.code = SYN_REPORT;
       write(fd, &event, sizeof(event));
}
#endif

KeyBoard::KeyBoard(QWidget *parent)
    : QWidget(parent)
{
	m_caps = false;

	m_ui = new Ui::KeyBoard;
	m_ui->setupUi(this);

	QSignalMapper* mapper = new QSignalMapper(this);
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(doButtonClicked(int)));

    m_allKeys = findChildren<QPushButton *>("key");
	int i = 0;
	for (QList<QPushButton *>::const_iterator iter = m_allKeys.begin();
			iter != m_allKeys.end(); iter++, i++) {
		mapper->setMapping((*iter), i);
		connect(*iter, SIGNAL(clicked()), mapper, SLOT(map()));
        //qDebug() << (*iter)->text();;
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

#if 1
    //int fd0 = open("/dev/input/event0", O_RDWR);
    //int fd1 = open("/dev/input/event1", O_RDWR);
    int fd2 = open("/dev/input/event2", O_RDWR);
    //int fd3 = open("/dev/input/event3", O_RDWR);
    //int fd4 = open("/dev/input/event4", O_RDWR);
    //int fd5 = open("/dev/input/event5", O_RDWR);
    //int fd6 = open("/dev/input/event6", O_RDWR);
    //simulate_key(fd0, key);
    //simulate_key(fd1, key);
    simulate_key(fd2, 4);
    simulate_key(fd2, 2);
    simulate_key(fd2, 3);
    //simulate_key(fd3, key);
    //simulate_key(fd4, key);
    //simulate_key(fd5, key);
    //simulate_key(fd6, key);

    //close(fd0);
    //close(fd1);
    ::close(fd2);
    //close(fd3);
    //close(fd4);
    //close(fd5);
    //close(fd6);
#endif

}
