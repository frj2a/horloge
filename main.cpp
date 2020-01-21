// "$Date: 2019-11-15 01:28:07 -0300 (sex, 15 nov 2019) $"
// "$Author: chico $"
// "$Revision: 148 $"

#include "horloge.h"
#include "CApplication.h"
#include <QApplication>
#include <QTextCodec>

#ifdef _WIN32
#	ifndef QT_DLL
#	include <QtPlugin>
//	Q_IMPORT_PLUGIN(qsvg)
//	Q_IMPORT_PLUGIN(qico)
#	endif
#endif


#include <QStringList>
#include <QTextCodec>

int main(int argc, char **argv) {
	CApplication a(argc, argv);
	Q_INIT_RESOURCE(horloge);
	a.loadTranslations(":/traducoes");
#if QT_VERSION > 0x050000
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
#else
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
#endif
	horloge w(argc - 1, &argv[1]);
	a.setLanguage(QLocale::system().name());
	a.setSession(static_cast<QWidget*>(&w));
	a.setStyle ("Cleanlooks");
	w.show();
	return a.exec();
}
