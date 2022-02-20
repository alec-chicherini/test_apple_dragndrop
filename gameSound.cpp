#include "gameSound.h"

QMap<QString, QSoundEffect*>  gameSound::effects = {};

void gameSound::init()
{
	QString crunch_name = "apple-crunch.wav";
	
	if (!effects.contains(crunch_name))
	{
		QUrl crunch_url = QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/sounds/apple-crunch.wav");
		QSoundEffect* effect = new QSoundEffect(qApp);
		effect->setSource(crunch_url);
		effect->setVolume(0.5f);
		effects[crunch_name] = effect;
	}
}

void gameSound::play(const QString & name)
{
	effects[name]->play();
}