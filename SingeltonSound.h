#pragma once
#include <SFML/Audio.hpp>
// Singleton for sound

class SingeltonSound
{
private:
	SingeltonSound();
	static SingeltonSound *m_instance;
	sf::SoundBuffer m_nemoGoB;
	sf::SoundBuffer m_backgroundMusicB;
	sf::SoundBuffer m_goodbyeB;
	sf::SoundBuffer m_clappingB;
	sf::SoundBuffer m_countdownB;
	sf::SoundBuffer m_explosionB;
	sf::SoundBuffer m_gameOverB;
	sf::SoundBuffer m_instuctionsSoundB;
	sf::SoundBuffer m_nemoEnergizerB;
	sf::SoundBuffer m_openEnergizerB;
	sf::SoundBuffer m_openGateB;
	sf::SoundBuffer m_startStageB;
	sf::SoundBuffer m_backgroundStageB;

	sf::Sound m_nemoGo;
	sf::Sound m_backgroundMusic;
	sf::Sound m_goodbye;
	sf::Sound m_clapping;
	sf::Sound m_countdown;
	sf::Sound m_explosion;
	sf::Sound m_gameOver;
	sf::Sound m_instuctionsSound;
	sf::Sound m_nemoEnergizer;
	sf::Sound m_openEnergizer;
	sf::Sound m_openGate;
	sf::Sound m_startStage;
	sf::Sound m_backgroundStage;

public:
	static SingeltonSound *instance();
	void stopAllSounds();
	void playNemoGo() { m_nemoGo.play(); }
	void playBackgroundMusic() { m_backgroundMusic.play(); }
	void playGoodbye() { m_goodbye.play(); }
	void playClapping() { m_clapping.play(); }
	void playCountdown() {m_countdown.play(); }
	void playExplosion() { m_explosion.play(); }
	void playGameOver(){ m_gameOver.play(); }
	void playInstuctionsSound() { m_instuctionsSound.play(); }
	void playNemoEnergizer() { m_nemoEnergizer.setVolume(100); m_nemoEnergizer.play(); }
	void playOpenEnergizer() { m_openEnergizer.setVolume(100); m_openEnergizer.play(); }
	void playOpenGate() { m_openGate.play(); }
	void playStartStage() { m_startStage.play(); }
	void playBackgroundStage() { m_backgroundStage.play(); }
};

