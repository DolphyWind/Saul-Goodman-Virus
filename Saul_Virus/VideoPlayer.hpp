#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <filesystem>
#include <thread>
namespace fs = std::filesystem;

class VideoPlayer
{
private:
	std::string m_frameFoldername;
	std::string m_audioFilename;
	sf::Music m_music;
	std::vector<sf::Texture> m_textures;
	sf::Time m_timePerFrame;
	std::size_t m_currentIndex = 0;
	sf::Time m_timer;
	bool m_musicLoaded = false;
	std::thread m_textureLoader;
public:
	VideoPlayer(std::string frameFoldername, std::string audioFilename);
	~VideoPlayer() { m_textureLoader.join(); }

	void loadMusicFile();
	void loadTextures();

	void update(sf::Time deltaTime);
	sf::Texture& getCurrentTexture();
	void restart();
};
