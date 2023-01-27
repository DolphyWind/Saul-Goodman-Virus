#pragma once
#include <SFML/Graphics.hpp>
#include "VideoPlayer.hpp"
#include <iostream>
#include <Windows.h>


class SaulVirus
{
private:
	HWND m_activeWindowHandle = NULL;
	sf::RenderWindow m_window;
	bool m_isClosed = false;
	const sf::Time deltaTime = sf::seconds(1.f / 60.f);
	sf::Clock m_timer;
	VideoPlayer m_videoPlayer;
	sf::Vector2u m_textureSize;
	sf::View m_mainView;
public:
	SaulVirus();
	~SaulVirus() {}

	void mainLoop();
	void createWindow();
	void checkWindows();
	void updateWindow();
	void drawWindow();
};
