// "$Date: 2019-11-20 00:59:23 -0300 (qua, 20 nov 2019) $"
// "$Author: chico $"
// "$Revision: 158 $"

#include "CApplication.h"
#include <QApplication>
#include <QLocale>
#include <QDesktopWidget>

QTranslator* CApplication::current = nullptr;
QHash<QString, QTranslator*> CApplication::mTranslators;

CApplication::CApplication(int &argc, char **argv) : QApplication(argc, argv ) {
	// note a forma de acesso ao "argc", por referência e não por cópia; ver documentação!
	// http://qt-project.org/doc/qt-4.8/qapplication.html#QApplication
}

void CApplication::setSession(QWidget * sessao)	{
	mSessao = sessao;
}

void CApplication::commitData(QSessionManager& manager )	{
	manager.release();
}

void CApplication::loadTranslations(const QString& dir)	{
	loadTranslations(QDir(dir));
}

void CApplication::loadTranslations(const QDir& dir)	{
	// formato do nome do arquivo: <código do idioma>_<codigo do país>.qm
	QString filter = "*_*.qm";
	QDir::Filters filters = QDir::Files | QDir::Readable;
	QDir::SortFlags sort = QDir::Name;
	QFileInfoList entries = dir.entryInfoList(QStringList() << filter, filters, sort);
	foreach (QFileInfo file, entries)		{
		// pick country and language out of the file name
		QStringList parts = file.baseName().split("_");
		QString language = parts.at(parts.count() - 2).toLower();
		QString country  = parts.at(parts.count() - 1).toUpper();

		// construct and load translator
		QTranslator* translator = new QTranslator(instance());
		if (translator->load(file.absoluteFilePath())) {
			QString locale = language + "_" + country;
			mTranslators.insert(locale, translator);
		}
	}
}

const QStringList CApplication::availableLanguages()	{
	// the content won't get copied thanks to implicit sharing and constness
	return QStringList(mTranslators.keys());
}

void CApplication::setLanguage(const QString& locale)	{
	if (current) {										// remove previous
		removeTranslator(current);
	}
	current = mTranslators.value(locale, nullptr);
	if (current) {										// install new
		installTranslator(current);
	}
	qApp->desktop()->setLocale(QLocale(locale));
}
