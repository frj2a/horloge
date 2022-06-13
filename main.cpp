// "$Date: 2019-11-22 19:44:01 -0300 (sex, 22 nov 2019) $"
// "$Author: chico $"
// "$Revision: 159 $"

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
#include "runguard.h"

/*|
#include <chrono>
#include <iomanip>
#include <sstream>
#include <sys/time.h>
*/

int main(int argc, char **argv) {

/*
    int64_t timestamp;

    timestamp = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count();

    std::chrono::system_clock::time_point now;
    now +=  std::chrono::milliseconds(timestamp);

    std::time_t epoch_seconds = std::chrono::system_clock::to_time_t(now); // std::chrono::system_clock::now());
    std::ostringstream ss;
    ss << std::put_time(gmtime(&epoch_seconds), "%FT%TZ");
    auto truncated = std::chrono::system_clock::from_time_t(epoch_seconds);
    auto delta_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - truncated).count();
    ss << "." << std::fixed << std::setw(3) << std::setfill('0') << delta_ms;
    std::string sTimeDate = ss.str();


    timeval curTime;
    gettimeofday(&curTime, NULL);
    int milli = curTime.tv_usec / 1000;

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    char currentTime[84] = "";
    sprintf(currentTime, "%s:%d", buffer, milli);
    printf("current time: %s \n", currentTime);

*/
    RunGuard guard( "some_random_key" );
    if ( !guard.tryToRun() ) {
        return 0;
    }

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
