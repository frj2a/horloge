// "$Date: 2019-11-15 01:28:07 -0300 (sex, 15 nov 2019) $"
// "$Author: chico $"
// "$Revision: 148 $"

#ifndef HORLOGE_H
#define HORLOGE_H

#include "ui_horloge.h"
#include <QWidget>
#include <QString>
#include <QFile>
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <QPointer>
#include <QSystemTrayIcon>
#include <QGraphicsPathItem>
#include <QGraphicsProxyWidget>

class horloge : public QWidget, private Ui::horloge {
	Q_OBJECT

public:
	explicit horloge(int argc, char* argv[], QWidget *parent = nullptr);
	~horloge();

	QSize sizeHint() const;

private:
	Qt::WindowFlags			mFlags;
	int						mArgC;							//!< Quantidade de parâmetros de linha de comando.
	char**					mArgV;							//!< Ponteiro para a sequência de parâmetros de linha de comando.
	QIcon					*mIcone;
	QPointer<QSystemTrayIcon> mTrayIcon;
	QString					* mToolTip;
	QTimer					* mTimer;
	QScreen					* mScreen;
	QGraphicsPathItem		* gpiHora;
	QGraphicsPathItem		* gpiMinuto;
	QGraphicsPathItem		* gpiSegundo;
	QLabel					* mHoraDigital;
	QLabel					* mDataDigital;
	QGraphicsProxyWidget	* mProxyWidgetHora;
	QGraphicsProxyWidget	* mProxyWidgetData;
	QAction					*action;
	QString					prov;
	bool					utcTime;

private
slots:
	void onTimer(void);
	void home(const QRect & deskArea);
	void reposicionar(void);
	void trocaVisibilidade(void);
	void trocaLocalUTC(bool estado);
	void trocaVerHoraDigital(bool estado);
	void trocaVerDataDigital(bool estado);
	void trocaSensibMouse(bool estado);
	__attribute__((noreturn)) void leave();
	void trayAtivado(QSystemTrayIcon::ActivationReason reason);

protected:
	void changeEvent(QEvent *e);
	void retranslateMenus();
	void translateAction(QAction * act);

private:
	QGraphicsScene * gsPrincipal;
};

#endif // HORLOGE_H
