//
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <list>
//#include <windows.h>
//
//
//struct sStream
//{
//	//stream of chars representing a "drop"
//
//	int nCol = 0;	//x position
//	float fPos = 0.0f;	//y position
//
//	std::wstring sText;
//	float fSpeed;
//};
//
//wchar_t randChar()
//{
//	return (wchar_t)(rand() % 93 + 33);
//	//return (wchar_t)(rand() % 0x1EF + 0x00C0); 
//}
//
//void prepareStream(sStream *s, int nWidth, int nSpriteSize)
//{
//	s->nCol = (rand() % (nWidth / nSpriteSize))*nSpriteSize;
//	s->fPos = 0.0f;
//	s->fSpeed = rand() % 50 + 10;
//	int nStreamLength = rand() % 20 + 5;
//
//	s->sText.clear();
//	for (int i = 0; i < nStreamLength; i++)
//	{
//		s->sText.append(1, randChar());
//	}
//}
//
//float elapsedTime(LARGE_INTEGER *timeNew, LARGE_INTEGER *timeOld, LARGE_INTEGER *timeFreq)
//{
//	std::cout << "In Elapsed Time\n";
//	float fElapsedTime;
//	QueryPerformanceCounter(timeNew);
//	fElapsedTime = (float)((timeNew->QuadPart - timeOld->QuadPart) / (double)timeFreq->QuadPart);
//	timeOld = timeNew;
//
//	return fElapsedTime;
//}
//
//
//int main()
//{
//	int nWidth = 1000;
//	int nHeight = 1000;
//	int nSpriteSize = 10;
//	std::list<sStream> listStream;
//	int MaxStreams = 250;
//
//	LARGE_INTEGER timeFreq, timeNew, timeOld;
//	QueryPerformanceFrequency(&timeFreq);
//	QueryPerformanceCounter(&timeOld);
//	QueryPerformanceCounter(&timeNew);
//
//	//prepare streams
//	for (int n = 0; n < MaxStreams; n++)
//	{
//		sStream s;
//		prepareStream(&s, nWidth, nSpriteSize);
//		listStream.push_back(s);
//	}
//
//	sf::RenderWindow window(sf::VideoMode(nWidth, nHeight), "SFML works!");
//
//	while (window.isOpen())
//	{
//		sf::Event evnt;
//		while (window.pollEvent(evnt))
//		{
//
//			switch (evnt.type)
//			{
//			case sf::Event::Closed:
//				window.close();
//				break;
//			case sf::Event::Resized:
//				std::cout << "width: " << evnt.size.width << " , height: " << evnt.size.height << std::endl;
//				nWidth = evnt.size.width;
//				nHeight = evnt.size.height;
//				break;
//
//			}//end case
//		}//end while pollEvent
//
//
//
//		window.clear(sf::Color::Black);
//		//window.draw(shape);
//
//		for (auto &s : listStream)
//		{
//
//			s.fPos += s.fSpeed * elapsedTime(&timeNew, &timeOld, &timeFreq);
//			std::cout << "Elapsed time: " << elapsedTime(&timeNew, &timeOld, &timeFreq) << std::endl;
//			
//						for (int i = 0; i < s.sText.size(); i++)
//						{
//							sf::Color color = s.fSpeed < 25.0 ? sf::Color(0, 100, 0)/*dark green*/ : sf::Color(0, 128, 0)/*green*/;
//			
//							if (i == 0)
//							{
//								//white
//								color = sf::Color::White;
//							}
//							else if (i <= 3)
//							{
//								//grey
//								color = sf::Color(128, 128, 128);
//							}
//			
//							
//							int nCharIndex = abs((i - (int)s.fPos)) % s.sText.size();	//this is so chars are in the same place on the screen, and the head writes new rand chars
//							//s.nCol, (int)s.fPos - i, s.sText[nCharIndex], color
//							sf::Text c;
//							c.setString(s.sText[nCharIndex]);
//							c.setCharacterSize(nSpriteSize);
//							c.setFillColor(color);
//							c.setPosition(s.nCol, (int)s.fPos - i);
//
//							window.draw(c);
//						}
//			
//						if (s.fPos - s.sText.size() >= nHeight/nSpriteSize)
//						{
//							prepareStream(&s, nWidth, nSpriteSize);
//						}
//		}
//
//		window.display();
//
//	}//end while windowOpen
//
//	return 0;
//} 
//
//
//
//
//
//
//
