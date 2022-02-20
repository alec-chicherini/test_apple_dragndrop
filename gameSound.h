#include <QSoundEffect>
#include <QCoreApplication>
#include <QUrl>
#include <QMap>

class gameSound : public QObject
{
	gameSound() = delete;
	
public:
	static void init();
	static void play(const QString &);
private:
	static QMap<QString, QSoundEffect*> effects;
};