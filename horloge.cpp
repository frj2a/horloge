// "$Date: 2019-11-15 01:28:07 -0300 (sex, 15 nov 2019) $"
// "$Author: chico $"
// "$Revision: 148 $"

#include "horloge.h"
#include <QtGui>
#include <QRect>
#include <QGraphicsEllipseItem>
#include <QGraphicsBlurEffect>
#include <QDesktopWidget>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QScreen>
#include <QMenu>
#include <QLocale>
#include <QDateTime>
#include <QDate>

#define	INTERVALO_TIMER		1000
#define OPACIDADE_GERAL		0.35
#define OPACIDADE_DIGITOS	0.55

horloge::horloge(int argc, char* argv[], QWidget *parent) : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Dialog  | Qt::Tool /* | Qt::SplashScreen */ ) {
	mArgC = argc;
	mArgV = argv;

	utcTime = false;

	setAttribute(Qt::WA_TranslucentBackground, true);
	// setAttribute(Qt::WA_DeleteOnClose, true);
	setupUi(this);
	mFlags = windowFlags();
	setWindowFlags(mFlags | Qt::WindowTransparentForInput);
	// qApp->setWindowIcon(QIcon(":/ico/ico"));

	setLocale(QLocale::system());

	QFontDatabase::addApplicationFont(":/fontes/Digir___.ttf");
	QFontDatabase::addApplicationFont(":/fontes/Digirc__.ttf");
	QFontDatabase::addApplicationFont(":/fontes/Digircu_.ttf");
	QFontDatabase::addApplicationFont(":/fontes/Digire__.ttf");
	QFontDatabase::addApplicationFont(":/fontes/Digireu_.ttf");
	QFontDatabase::addApplicationFont(":/fontes/Digirtu_.ttf");
	QFontDatabase::addApplicationFont(":/fontes/LEDBDREV.TTF");
	QFontDatabase::addApplicationFont(":/fontes/LEDBOARD.TTF");

	gsPrincipal = new QGraphicsScene(0, 0, 256, 256, this);
	gvPrincipal->setScene(gsPrincipal);
	gvPrincipal->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

	/*
	QGraphicsEllipseItem *backgroundElipse = new QGraphicsEllipseItem(27,27,200,200);
	// backgroundElipse->setSpanAngle(5 * 16);
	// backgroundElipse->setStartAngle(-5 * 8);
	backgroundElipse->setBrush(QBrush(qRgb(191,191,191)));
	backgroundElipse->setGraphicsEffect(new QGraphicsBlurEffect());
	backgroundElipse->setOpacity(OPACIDADE);
	gsPrincipal->addItem(backgroundElipse);
	*/

	QGraphicsPathItem * marca;
	QPainterPath * caminho = new QPainterPath(QPointF(127.0,127.0));
	caminho->lineTo(QPointF(127.0       , 127.0 - 2.0));
	caminho->lineTo(QPointF(127.0 + 12.0, 127.0 - 2.0));
	caminho->lineTo(QPointF(127.0 + 12.0, 127.0 + 2.0));
	caminho->lineTo(QPointF(127.0       , 127.0 + 2.0));
	caminho->lineTo(QPointF(127.0       , 127.0      ));
	for (int iMarca = 0 ; iMarca < 12 ; iMarca++) {
		marca = new QGraphicsPathItem(*caminho);
		marca->setBrush(QBrush(Qt::black));
		marca->setPen(QPen(QBrush(Qt::yellow), 0.75));
		if ( (iMarca % 3) == 0) {
			marca->setScale(1.5);
			marca->moveBy(48.0, 0.0);
			marca->setTransformOriginPoint(127.0 - 48.0 , 127.0);
		} else {
			marca->moveBy(80.0, 0.0);
			marca->setTransformOriginPoint(127.0 - 80.0 , 127.0);
		}
		marca->setRotation(iMarca * 30);
		marca->setOpacity(OPACIDADE_GERAL);
		gsPrincipal->addItem(marca);
	}

	mHoraDigital = new QLabel("00:00:00");
	// mHoraDigital->setFont(QFont("LED BOARD REVERSED", 12));
	mHoraDigital->setFont(QFont("Digital Readout Expanded", 18));
	mHoraDigital->setStyleSheet("color: rgb(31, 31, 31); background-color: rgba(191, 191, 191, 255);");
	mProxyWidgetHora = gsPrincipal->addWidget(mHoraDigital);
	mProxyWidgetHora->setPos(127.0 - mProxyWidgetHora->size().width() / 2 , 127.0 + 14);
	mProxyWidgetHora->setOpacity(OPACIDADE_DIGITOS);

	mDataDigital = new QLabel("00.00.00");
	// mDataDigital->setFont(QFont("LED BOARD REVERSED", 12));
	mDataDigital->setFont(QFont("Digital Readout Expanded", 18));
	mDataDigital->setStyleSheet("color: rgb(31, 31, 31); background-color: rgba(191, 191, 191, 255);");
	mProxyWidgetData = gsPrincipal->addWidget(mDataDigital);
	mProxyWidgetData->setPos(127.0 - mProxyWidgetData->size().width() / 2 , 127.0 + 16 + mProxyWidgetHora->size().height());
	mProxyWidgetData->setOpacity(OPACIDADE_DIGITOS);

	delete caminho;
	caminho = new QPainterPath(QPointF(127.0 +  3.5, 127.0 + 10.0));
	caminho->lineTo(127.0 +   3.5 , 127.0 - 56.0);
	caminho->lineTo(127.0 -   3.5 , 127.0 - 56.0);
	caminho->lineTo(127.0 -   3.5 , 127.0 + 10.0);
	caminho->lineTo(127.0 +   3.5 , 127.0 + 10.0);
	gpiHora = new QGraphicsPathItem(*caminho);
	gpiHora->setBrush(QBrush(Qt::black));
	gpiHora->setPen(QPen(QBrush(Qt::white),OPACIDADE_DIGITOS));
	gpiHora->setTransformOriginPoint(127.0, 127.0);
	gpiHora->setOpacity(OPACIDADE_DIGITOS);
	QGraphicsDropShadowEffect * shadowHora = new QGraphicsDropShadowEffect();
	shadowHora->setBlurRadius(4.0);
	shadowHora->setOffset(4.0);
	shadowHora->setColor(QColor(15, 15, 15, 120));
	gpiHora->setGraphicsEffect(shadowHora);
	gsPrincipal->addItem(gpiHora);

	delete caminho;
	caminho = new QPainterPath(QPointF(127.0 + 2.0, 127.0 + 15.0));
	caminho->lineTo(127.0 +  2.0 , 127.0 - 80.0);
	caminho->lineTo(127.0 -  2.0 , 127.0 - 80.0);
	caminho->lineTo(127.0 -  2.0 , 127.0 + 15.0);
	caminho->lineTo(127.0 +  2.0 , 127.0 + 15.0);
	gpiMinuto = new QGraphicsPathItem(*caminho);
	gpiMinuto->setBrush(QBrush(Qt::black));
	gpiMinuto->setPen(QPen(QBrush(Qt::white),OPACIDADE_DIGITOS));
	gpiMinuto->setTransformOriginPoint(127.0, 127.0);
	gpiMinuto->setOpacity(OPACIDADE_DIGITOS);
	QGraphicsDropShadowEffect * shadowMinuto = new QGraphicsDropShadowEffect();
	shadowMinuto->setBlurRadius(6.0);
	shadowMinuto->setOffset(6.0);
	shadowMinuto->setColor(QColor(15, 15, 15, 120));
	gpiMinuto->setGraphicsEffect(shadowMinuto);
	gsPrincipal->addItem(gpiMinuto);

	delete caminho;
	caminho = new QPainterPath(QPointF(127.0 + 1.0, 127.0 + 20.0));
	caminho->lineTo(127.0 +  1.0 , 127.0 - 100.0);
	caminho->lineTo(127.0 -  1.0 , 127.0 - 100.0);
	caminho->lineTo(127.0 -  1.0 , 127.0 + 20.0);
	caminho->lineTo(127.0 +  1.0 , 127.0 + 20.0);
	gpiSegundo = new QGraphicsPathItem(*caminho);
	gpiSegundo->setBrush(QBrush(Qt::red));
	gpiSegundo->setPen(Qt::NoPen);
	gpiSegundo->setTransformOriginPoint(127.0, 127.0);
	gpiSegundo->setOpacity(OPACIDADE_DIGITOS);
	QGraphicsDropShadowEffect * shadowSegundo = new QGraphicsDropShadowEffect();
	shadowSegundo->setBlurRadius(10.0);
	shadowSegundo->setOffset(8.0);
	shadowSegundo->setColor(QColor(15, 15, 15, 120));
	gpiSegundo->setGraphicsEffect(shadowSegundo);
	gsPrincipal->addItem(gpiSegundo);

	/*
	QGraphicsEllipseItem *secondsElipse = new QGraphicsEllipseItem(120,120,14,14);
	// secondsElipse->setSpanAngle(5 * 16);
	// secondsElipse->setStartAngle(-5 * 8);
	secondsElipse->setBrush(QBrush(Qt::red));
	secondsElipse->setPen(Qt::NoPen);
	secondsElipse->setOpacity(OPACIDADE);
	QGraphicsDropShadowEffect * shadowElipseSegundo = new QGraphicsDropShadowEffect();
	shadowElipseSegundo->setBlurRadius(8.0);
	shadowElipseSegundo->setOffset(8.0);
	shadowElipseSegundo->setColor(QColor(15, 15, 15, 120));
	secondsElipse->setGraphicsEffect(shadowElipseSegundo);
	gsPrincipal->addItem(secondsElipse);
	*/

	QString sToolTip(tr("Use o botão direito para abrir um menu de contexto."));

	mIcone = new QIcon(QPixmap(":/ico/ico"));
	mTrayIcon = new QSystemTrayIcon(*mIcone, this);
	mTrayIcon->setVisible(true);
	mTrayIcon->setToolTip(sToolTip);
	mTrayIcon->show();
	connect(mTrayIcon, &QSystemTrayIcon::activated, this, &horloge::trayAtivado);

	QMenu * trayIconMenu = new QMenu;

	action = new QAction(tr("&Exibir/Ocultar"), mTrayIcon);
	connect(action, &QAction::triggered, this, &horloge::trocaVisibilidade);
	// addAction(action);

	trayIconMenu->addAction(action);

	action = new QAction(tr("&UTC"), mTrayIcon);
	action->setCheckable(true);
	connect(action, &QAction::toggled, this, &horloge::trocaLocalUTC);
	// addAction(action);

	trayIconMenu->addAction(action);


	action = new QAction(tr("&Digitais"), mTrayIcon);
	// addAction(action);
	QMenu * subMenu = new QMenu;
	action->setMenu(subMenu);
	trayIconMenu->addAction(action);

	action = new QAction(tr("&Hora Digital"), action);
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, &QAction::toggled, this, &horloge::trocaVerHoraDigital);
	subMenu->addAction(action);

	action = new QAction(tr("&Data Digital"), action);
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, &QAction::toggled, this, &horloge::trocaVerDataDigital);
	subMenu->addAction(action);

	action = new QAction(tr("&Permite mover"), mTrayIcon);
	action->setCheckable(true);
	connect(action, &QAction::toggled, this, &horloge::trocaSensibMouse);
	// addAction(action);

	trayIconMenu->addAction(action);


	trayIconMenu->addSeparator();

	action = new QAction(tr("&Sair"), this);				//	&Exit
	connect(action, &QAction::triggered, this, &horloge::leave);
	addAction(action);

	trayIconMenu->addAction(action);

	trayIconMenu->setLocale(QLocale::system());
	mTrayIcon->setContextMenu(trayIconMenu);

	mScreen = QGuiApplication::primaryScreen();
	connect (mScreen, &QScreen::geometryChanged, this, &horloge::home );
	reposicionar();



	onTimer();
	mTimer = new QTimer(this);
	connect (mTimer, &QTimer::timeout, this, &horloge::onTimer);
	mTimer->setSingleShot(false);
	mTimer->setInterval(INTERVALO_TIMER);
	mTimer->start();

	retranslateMenus();
}

void horloge::changeEvent(QEvent *e) {
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			retranslateUi(this);
			retranslateMenus();
		break;
		default:
		break;
	}
}

inline void horloge::translateAction(QAction * act) {
	// prov = QApplication::translate("horloge", act->text().toStdString().c_str(), nullptr);
	act->setText(QApplication::translate("horloge", act->text().toStdString().c_str(), nullptr));
}

void horloge::retranslateMenus() {
	QString prov;
	// prov = QApplication::translate("horloge", mTrayIcon->toolTip().toStdString().c_str(), nullptr);
	mTrayIcon->setToolTip(QApplication::translate("horloge", mTrayIcon->toolTip().toStdString().c_str(), nullptr));
	foreach(QAction* act, mTrayIcon->contextMenu()->actions()) {
		if (act->menu() != nullptr) {
			foreach (QAction * acti, act->menu()->actions()) {
				translateAction(acti);
			}
		}
		translateAction(act);
	}
}

horloge::~horloge() {
	mTimer->stop();
	disconnect (mTimer, &QTimer::timeout, this, &horloge::onTimer);
	delete mTimer;

	disconnect (mScreen, &QScreen::geometryChanged, this, &horloge::home);
	delete mScreen;

	disconnect(mTrayIcon, &QSystemTrayIcon::activated, this, &horloge::trayAtivado);
	foreach (QAction * act, mTrayIcon->contextMenu()->actions()) {
		if (act->menu() != nullptr) {
			foreach (QAction * acti, act->menu()->actions()) {
				act->menu()->removeAction(acti);
				delete acti;
			}
			delete act->menu();
		}
		mTrayIcon->contextMenu()->removeAction(act);
		delete act;
	}
	QMenu *trayMenu = mTrayIcon->contextMenu();
	mTrayIcon->setContextMenu(nullptr);
	delete trayMenu;
	delete mTrayIcon;

	foreach (QGraphicsItem * giItem , gsPrincipal->items()) {
		gsPrincipal->removeItem(giItem);
		delete giItem;
	}
	gvPrincipal->setScene(nullptr);

	delete mHoraDigital;

	delete gsPrincipal;
}

void horloge::trocaVisibilidade() {
	if (isVisible()) {
		hide();
	} else {
		show();
		reposicionar();
	}
}

void horloge::trocaLocalUTC(bool estado) {
	utcTime = estado;
	onTimer();
}

void horloge::trocaVerHoraDigital(bool estado) {
	mHoraDigital->setVisible(estado);
}

void horloge::trocaVerDataDigital(bool estado) {
	mDataDigital->setVisible(estado);
}

void horloge::trocaSensibMouse(bool estado) {
	if (estado) {
		setWindowFlags(mFlags);
	} else {
		setWindowFlags(mFlags | Qt::WindowTransparentForInput);
	}
	show();
}

void horloge::leave() {
	exit(0);
}

void horloge::trayAtivado(QSystemTrayIcon::ActivationReason reason) {
	if (reason == QSystemTrayIcon::Trigger) {
		trocaVisibilidade();
	}
}

QSize horloge::sizeHint(void) const {
	return QSize(256,256);
}

void horloge::reposicionar() {
	const QRect rect = mScreen->geometry();
	home(rect);
}

void horloge::home(const QRect &deskArea) {
	int x, y, w, h;
	w = geometry().width();
	h = geometry().height();
	x = deskArea.width() * 125 / 128 - w;
	y = deskArea.height() * 122 / 128 - h;
	setGeometry(x, y, w, h);
}

void horloge::onTimer(void)	{
	QTime timeNow = QTime::currentTime();
	QDate dateNow = QDate::currentDate();
	if (utcTime) {
		QDateTime * dateTimeNow = new QDateTime(dateNow, timeNow);
		timeNow = dateTimeNow->toUTC().time();
		dateNow = dateTimeNow->toUTC().date();
		delete dateTimeNow;
	}
	gpiHora->setRotation(timeNow.hour() * 30.0 + timeNow.minute() / 2.0);
	gpiMinuto->setRotation(timeNow.minute() * 6.0 + timeNow.second() / 10.0);
#if INTERVALO_TIMER < 600
	gpiSegundo->setRotation( ( timeNow.second() + timeNow.msec() / 1000.0 ) * 6.0 );
#else
	gpiSegundo->setRotation( timeNow.second() * 6.0 );
#endif
	mHoraDigital->setText(timeNow.toString("hh:mm:ss"));
	mDataDigital->setText(dateNow.toString("dd.MM.yy"));
}

/*
void horloge::slotMudouIdioma(qint32 codIdioma) {
	switch (codIdioma) {
		case 0:
			pbIdioma->setIcon(QIcon(":/imagens/BRA"));
			CApplication::setLanguage("pt_BR");
			break;
		case 1:
			pbIdioma->setIcon(QIcon(":/imagens/USA"));
			CApplication::setLanguage("en_US");
			break;
		case 2:
			pbIdioma->setIcon(QIcon(":/imagens/ESP"));
			CApplication::setLanguage("es_ES");
			break;
		default:
			pbIdioma->setIcon(QIcon(":/imagens/BRA"));
			CApplication::setLanguage("pt_BR");
	}
}
*/
