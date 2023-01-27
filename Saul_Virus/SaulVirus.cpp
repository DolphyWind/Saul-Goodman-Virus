#include "SaulVirus.hpp"

SaulVirus::SaulVirus():
	m_videoPlayer("./frames/", "./saul_audio.wav")
{
	//m_window.create(sf::VideoMode(800, 600), "Demo Window");
	m_textureSize = m_videoPlayer.getCurrentTexture().getSize();
	
	sf::Vector2f textureSizeAsV2f;
	textureSizeAsV2f.x = m_textureSize.x;
	textureSizeAsV2f.y = m_textureSize.y;

	sf::Vector2f halfTexture;
	halfTexture.x = textureSizeAsV2f.x / 2;
	halfTexture.y = textureSizeAsV2f.y / 2;

	m_mainView = sf::View(halfTexture, textureSizeAsV2f);
	m_window.setView(m_mainView);
}

void SaulVirus::mainLoop()
{
	while (!m_isClosed)
	{
		checkWindows();
		if (!m_window.isOpen()) continue;
		updateWindow();
		drawWindow();
		sf::sleep(deltaTime);
	}
}

void SaulVirus::createWindow()
{
	m_window.create(m_activeWindowHandle);
	m_window.setView(m_mainView);
	m_videoPlayer.restart();
}

void SaulVirus::checkWindows()
{
	HWND currentHandle = GetForegroundWindow();
	if (currentHandle != m_activeWindowHandle)
	{
		m_activeWindowHandle = currentHandle;
		createWindow();
	}
}

void SaulVirus::updateWindow()
{
	sf::Time deltaTime = m_timer.restart();
	m_videoPlayer.update(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_isClosed = true;
}

void SaulVirus::drawWindow()
{
	m_window.clear();

	m_window.draw(sf::Sprite(m_videoPlayer.getCurrentTexture()));

	m_window.display();
}
