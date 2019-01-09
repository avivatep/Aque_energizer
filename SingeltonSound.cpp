#include "SingeltonSound.h"

SingeltonSound *SingeltonSound::m_instance = nullptr;

SingeltonSound::SingeltonSound()
{
	if (!m_backgroundStageB.loadFromFile("Resources/Sounds/backgroundStage.wav")||
		!m_nemoGoB.loadFromFile("Resources/Sounds/nemoWalk.wav") ||
		!m_backgroundMusicB.loadFromFile("Resources/Sounds/backgroundMusic.wav") ||
		!m_goodbyeB.loadFromFile("Resources/Sounds/byebye.wav") ||
		!m_clappingB.loadFromFile("Resources/Sounds/clapping.wav") ||
		!m_countdownB.loadFromFile("Resources/Sounds/countdown.wav") ||
		!m_explosionB.loadFromFile("Resources/Sounds/explosion.wav") ||
		!m_gameOverB.loadFromFile("Resources/Sounds/gameOver.wav") ||
		!m_instuctionsSoundB.loadFromFile("Resources/Sounds/instuctions_sound.wav") ||
		!m_nemoEnergizerB.loadFromFile("Resources/Sounds/nemoEnergizer.wav") ||
		!m_openEnergizerB.loadFromFile("Resources/Sounds/openEnergizer.wav") ||
		!m_openGateB.loadFromFile("Resources/Sounds/openGate.wav")||
		!m_startStageB.loadFromFile("Resources/Sounds/startStage.wav"))
		exit(EXIT_FAILURE);
	
	m_nemoGo.setBuffer(m_nemoGoB);
	m_backgroundMusic.setBuffer(m_backgroundMusicB);
	m_goodbye.setBuffer(m_goodbyeB);
	m_clapping.setBuffer(m_clappingB);
	m_countdown.setBuffer(m_countdownB);
	m_explosion.setBuffer(m_explosionB);
	m_gameOver.setBuffer(m_gameOverB);
	m_instuctionsSound.setBuffer(m_instuctionsSoundB);
	m_nemoEnergizer.setBuffer(m_nemoEnergizerB);
	m_openEnergizer.setBuffer(m_openEnergizerB);
	m_openGate.setBuffer(m_openGateB);
	m_startStage.setBuffer(m_startStageB);
	m_backgroundStage.setBuffer(m_backgroundStageB);
}

SingeltonSound *SingeltonSound::instance()
{
	if (m_instance == nullptr)
		m_instance = new SingeltonSound;
	return m_instance;
}

void SingeltonSound::stopAllSounds()
{
	m_nemoGo.stop();
	m_backgroundMusic.stop();
	m_clapping.stop();
	m_countdown.stop();
	m_explosion.stop();
	m_gameOver.stop();
	m_instuctionsSound.stop();
	m_nemoEnergizer.stop();
	m_openEnergizer.stop();
	m_openGate.stop();
	m_startStage.stop();
	m_backgroundStage.stop();
}

