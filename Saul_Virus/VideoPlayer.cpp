#include "VideoPlayer.hpp"
#include <fstream>

VideoPlayer::VideoPlayer(std::string frameFoldername, std::string audioFilename):
	m_frameFoldername(frameFoldername), m_audioFilename(audioFilename)
{
	m_textureLoader = std::thread{ [this]() {
			this->loadTextures();
		}
	};
	loadMusicFile();
	sf::sleep(sf::seconds(0.1f));
	m_timePerFrame = sf::seconds(0.033356f);
	if(m_musicLoaded)
		m_music.play();
}

void VideoPlayer::loadMusicFile()
{
	if (!m_music.openFromFile(m_audioFilename))
	{
		return;
	}
	m_musicLoaded = true;
	m_music.setLoop(true);
}

void VideoPlayer::loadTextures()
{
	std::size_t i = 1;
	while (true)
	{
		std::stringstream filename_ss;
		filename_ss << m_frameFoldername;
		filename_ss << "out-";
		for (std::size_t j = 0; j < 3 - std::to_string(i).length(); j++)
			filename_ss << "0";
		filename_ss << i << ".jpg";
		std::string filename = filename_ss.str();

		if (!fs::exists(filename))
			break;

		sf::Texture temp;
		if (!temp.loadFromFile(filename))
		{
			MessageBoxA(NULL, std::string("Cannot open \"" + filename + "\"").c_str(), "Error!", MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}
		m_textures.push_back(temp);

		i++;
	}
}

void VideoPlayer::update(sf::Time deltaTime)
{
	m_timer += deltaTime;
	while (m_timer >= m_timePerFrame)
	{
		m_timer -= m_timePerFrame;
		m_currentIndex++;
		if (m_currentIndex >= m_textures.size()) m_currentIndex = 0;
	}
}

sf::Texture& VideoPlayer::getCurrentTexture()
{
	return m_textures[m_currentIndex];
}

void VideoPlayer::restart()
{
	if (m_musicLoaded)
	{
		m_music.stop();
		m_music.play();
	}
	m_currentIndex = 0;
}
