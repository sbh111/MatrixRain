

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <random>
#include <chrono>



struct sStream
{
	//stream of chars representing a "drop"

	int nXPos = 0;	//x position
	float fYPos = 0.0f;	//y position
	std::wstring sText;
	float fSpeed = 0.f;
	int fSize = 10.f;
};

wchar_t randChar()
{
	return (wchar_t)(rand() % 93 + 33);
}

void prepareStream(sStream *s, int nWidth)
{
	s->fYPos = 0.0f;
	s->nXPos = (rand() % nWidth/s->fSize) * s->fSize;


	//IDK why these are not working
	/*std::default_random_engine generator;	
	std::normal_distribution<float> d1(500.f, 100.f);
	std::normal_distribution<float> d2(35.f, 15.f);
	s->fSpeed = d1(generator);
	s->fSize = d2(generator);*/


	s->fSpeed = rand() % 800 + 100;
	s->fSize = rand() % 70 + 10;

	s->sText.clear();
	int nStreamLength = rand() % 6 + 1;
	for (int i = 0; i < nStreamLength; i++)
	{
		s->sText.append(1, randChar());
	}
}

void updateStream(sStream *str)
{
	if (rand() >= (float)RAND_MAX*.75)	//there's got to be a better way to do this
	{
		int randIndex = rand() % str->sText.size();
		str->sText[randIndex] = randChar();
	}
}

int affineMap(int a, int b, int c, int d, int x)
{
	//transform x from range [a, b] to y in range [c, d]
	int y = ((x - a) * (d - c) / (b - a)) + c;
	return y;


}




int main()
{
	sf::Font font;
	sf::Music music;
	if (!(font.loadFromFile("matrixFont.ttf") && music.openFromFile("8-Bit-Mayhem.ogg")))
	{
		return EXIT_FAILURE;
	}

	int nWidth = 1500;
	int nHeight = 1000;
	int nMaxStreams = 150;
	std::list<sStream> listStream;
	sf::RenderWindow window(sf::VideoMode(nWidth, nHeight), " SFML Matrix Rain");
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(30);

	sf::Clock clock;
	sf::Clock totalClock;



	//populate listStream
	for (int i = 0; i < nMaxStreams; i++)
	{
		sStream s;
		prepareStream(&s, nWidth);
		listStream.push_back(s);
	}
	listStream.sort([](const sStream &lhs, const sStream &rhs) {return lhs.fSize < rhs.fSize; });

	music.play();
	music.setLoop(true);
	while (window.isOpen())
	{
		sf::Event evnt;
		sf::Time totalTime = totalClock.getElapsedTime();
		sf::Time elapsedTime = clock.restart();
		float fps = 1.f / (elapsedTime.asSeconds());
		window.setTitle("FPS: " + std::to_string((int)fps) + ", Elapsed Time: " + std::to_string(totalTime.asSeconds()));

		while (window.pollEvent(evnt))
		{

			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "width: " << evnt.size.width << " , height: " << evnt.size.height << std::endl;
				nWidth = evnt.size.width;
				nHeight = evnt.size.height;
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::T)
				{
					std::cout << "Elapsed Time: " << elapsedTime.asSeconds() << std::endl;
				}
				break;


			}//end case
		}//end while pollEvent


		window.clear(sf::Color(0, 20, 0));

		//for each string stream
		for (auto &s : listStream)
		{
			s.fYPos += s.fSpeed * elapsedTime.asSeconds();




			//for each char
			for (int i = 0; i < s.sText.size(); i++)
			{

				//TODO: map color to size and maybe speed
				sf::Color color;
				if (i == 0)
				{
					color = sf::Color::White;
				}
				else if(s.fSpeed >= 750 && s.fSpeed < 880)
				{
					color = sf::Color::Red;
				}
				else if (s.fSpeed >= 880)
				{
					color = sf::Color::Blue;

				}
				else
				{
					color = sf::Color::Green;
				}

				color.a = affineMap(10, 80, 1, 255, s.fSize);	//Streams that are 

				int nCharIndex = abs(i - (int)s.fYPos / s.fSize ) % s.sText.size();	//this is so chars are in the same place on the screen, and the head writes new rand chars

				sf::Text c;
				c.setFont(font);
				c.setOrigin(0, c.getLocalBounds().height);
				c.setString(s.sText[nCharIndex]);
				c.setCharacterSize(s.fSize);

				int row = (s.fYPos - (float)i*s.fSize)/ s.fSize;
				float pos = row * s.fSize;
				c.setPosition((float)s.nXPos, pos);

				c.setFillColor(color);
				
				window.draw(c);
			}

			updateStream(&s);

			if (s.fYPos - s.sText.size()*s.fSize  >= nHeight)
			{
				prepareStream(&s, nWidth);

				//apparently this sorting routine is to slow, and causes flickering
				//i probably dont need it anyway
				//listStream.sort([](const sStream &lhs, const sStream &rhs) {return lhs.fSize < rhs.fSize; });
			}

		}
		window.display();

	}//end gameLoop, window is closed

	music.stop();
	std::cout << "Exiting..." << std::endl;



	return 0;
}