#include "VideoPlayer.hpp"

VideoPlayer::VideoPlayer(std::string frameFoldername, std::string audioFilename):
	m_frameFoldername(frameFoldername), m_audioFilename(audioFilename)
{
	loadMusicFile();
	loadTextures();
	m_timePerFrame = sf::seconds(m_music.getDuration().asSeconds() / double(m_textures.size()));
	m_music.play();
}

void VideoPlayer::loadMusicFile()
{
	if (!m_music.openFromFile(m_audioFilename))
	{
		MessageBoxA(NULL, std::string("Cannot open \"" + m_audioFilename + "\"").c_str(), "Error!", MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}
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
	m_music.stop();
	m_music.play();
	m_currentIndex = 0;
}
