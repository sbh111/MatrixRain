

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>


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
	//return (wchar_t)(rand() % 0x1EF + 0x00C0); 
}

void prepareStream(sStream *s, int nWidth)
{
	s->fYPos = 0.0f;
	s->nXPos = rand() % nWidth;

	s->fSpeed = rand() % 1000 + 200;	//TODO: replace this with binomial distribution generator
	s->fSize = rand() % 100 + 10;		//TODO: map speed bw 10 and 100 and assign to size


	s->sText.clear();
	int nStreamLength = rand() % 20 + 5;
	for (int i = 0; i < nStreamLength; i++)
	{
		s->sText.append(1, randChar());
	}
}

void updateStream(sStream *s)
{
	if (rand() >= (float)RAND_MAX*.75)	//there's got to be a better way to do this
	{
		int randIndex = rand() % s->sText.size();
		s->sText[randIndex] = randChar();
	}
}




int main()
{
	sf::Font font;
	if (!font.loadFromFile("sansation.ttf"))
	{
		return EXIT_FAILURE;
	}

	int nWidth = 1000;
	int nHeight = 1000;
	float fSpriteSize = 50.f;
	int nMaxStreams = 10;
	std::list<sStream> listStream;
	sf::RenderWindow window(sf::VideoMode(nWidth, nHeight), "Testing Text");
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;

	//populate listStream
	for (int i = 0; i < nMaxStreams; i++)
	{
		sStream s;
		prepareStream(&s, nWidth);
		listStream.push_back(s);
	}
	listStream.sort([](const sStream &lhs, const sStream &rhs) {return lhs.fSize < rhs.fSize; });


	while (window.isOpen())
	{
		sf::Event evnt;
		sf::Time elapsedTime = clock.restart();
		float fps = 1.f / (elapsedTime.asSeconds());
		window.setTitle("FPS: " + std::to_string(fps));

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



		window.clear(sf::Color::Black);

		//for each string stream
		for (auto &s : listStream)
		{
			s.fYPos += s.fSpeed * elapsedTime.asSeconds();

			//for each char
			for (int i = 0; i < s.sText.size(); i++)
			{

				//TODO: map color to size and maybe speed
				sf::Color color = s.fSpeed < 120.0 ? sf::Color(0, 100, 0)/*dark green*/ : sf::Color(0, 128, 0)/*green*/;
				if (i == 0)
				{
					//white
					color = sf::Color::White;
				}
				else if (i <= 3)
				{
					//grey
					color = sf::Color(128, 128, 128);
				}


				//int nCharIndex = abs(i - (int)s.fYPos / nSpriteSize ) % s.sText.size();	//this is so chars are in the same place on the screen, and the head writes new rand chars
				int nCharIndex = i;	//FOR TESTING, DELETE

				sf::Text c;
				c.setFont(font);
				c.setOrigin(0, c.getLocalBounds().height);
				c.setString(s.sText[nCharIndex]);
				c.setCharacterSize(s.fSize);

				c.setPosition((float)s.nXPos, s.fYPos - (float)(i*s.fSize));
				c.setFillColor(color);
				window.draw(c);
			}

			updateStream(&s);

			if (s.fYPos - s.sText.size()*s.fSize  >= nHeight)
			{
				prepareStream(&s, nWidth);
				listStream.sort([](const sStream &lhs, const sStream &rhs) {return lhs.fSize < rhs.fSize; });
			}

		}
		window.display();

	}//end gameLoop

	return 0;
}