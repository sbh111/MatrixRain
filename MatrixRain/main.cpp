//#include<iostream>
//#include "olcConsoleGameEngineGL.h"
//
//using namespace std;
//
//class matrixRain : public olcConsoleGameEngine
//{
//public:
//	matrixRain()
//	{
//
//	}
//
//private:
//	struct sStream
//	{
//		//stream of chars representing a "drop"
//		int nCol = 0;	//x position
//		float fPos = 0.0f;	//y position
//		wstring sText;
//		float fSpeed;
//
//	};
//	void prepareStream(sStream *s)
//	{
//		s->nCol = rand() % ScreenWidth();
//		s->fPos = 0.0f;
//		s->fSpeed = rand() % 50 + 10;
//		int nStreamLength = rand() % 20 + 5;
//
//		s->sText.clear();
//		for (int i = 0; i < nStreamLength; i++)
//		{
//			s->sText.append(1, randChar());
//		}
//	} 
//
//	wchar_t randChar()
//	{
//		return (wchar_t)(rand() % 93 + 33);
//		//return (wchar_t)(rand() % 0x1EF + 0x00C0); 
//	}
//
//
//	list<sStream> listStream;
//	int MaxStreams = 250;
//
//protected:
//	virtual bool OnUserCreate() override
//	{
//		for (int n = 0; n < MaxStreams; n++)
//		{
//			sStream s;
//			prepareStream(&s);
//			listStream.push_back(s);
//		}
//		return true;
//	}
//
//	virtual bool OnUserUpdate(float fElapsedTime)
//	{
//		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
//
//		for (auto &s : listStream)
//		{
//			s.fPos += s.fSpeed * fElapsedTime;
//
//			for (int i = 0; i < s.sText.size(); i++)
//			{
//				short color = s.fSpeed < 25.0 ? FG_DARK_GREEN : FG_GREEN;
//
//				if (i == 0)
//				{
//					color = FG_WHITE;
//				}
//				else
//				{
//					if (i <= 3)
//					{
//						color = FG_GREY;
//					}
//				}
//
//				int nCharIndex = abs((i - (int)s.fPos)) % s.sText.size();	//this is so chars are in the same place on the screen, and the head writes new rand chars
//				Draw(s.nCol, (int)s.fPos - i, s.sText[nCharIndex], color);
//			}
//
//			if (s.fPos - s.sText.size() >= ScreenHeight())
//			{
//				prepareStream(&s);
//			}
//
//
//		}
//
//		return true;
//	}
//
//
//};
//
//int main()
//{
//
//	matrixRain demo;
//	demo.ConstructConsole(100, 50, 8, 8);
//	demo.Start();
//
//	return 0;
//}