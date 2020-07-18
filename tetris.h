#ifndef __TETRIS_H__
#define __TETRIS_H__
/*
	OneLoneCoder.com - Command Line Tetris
	"Put Your Money Where Your Mouth Is" - @Javidx9

	License
	~~~~~~~
	Copyright (C) 2018  Javidx9
	This program comes with ABSOLUTELY NO WARRANTY.
	This is free software, and you are welcome to redistribute it
	under certain conditions; See license for details.
	Original works located at:
	https://www.github.com/onelonecoder
	https://www.onelonecoder.com
	https://www.youtube.com/javidx9

	GNU GPLv3
	https://github.com/OneLoneCoder/videos/blob/master/LICENSE

	From Javidx9 :)
	~~~~~~~~~~~~~~~
	Hello! Ultimately I don't care what you use this for. It's intended to be
	educational, and perhaps to the oddly minded - a little bit of fun.
	Please hack this, change it and use it in any way you see fit. You acknowledge
	that I am not responsible for anything bad that happens as a result of
	your actions. However this code is protected by GNU GPLv3, see the license in the
	github repo. This means you must attribute me if you use it. You can view this
	license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE
	Cheers!

	Background
	~~~~~~~~~~
	I made a video "8-Bits of advice for new programmers" (https://youtu.be/vVRCJ52g5m4)
	and suggested that building a tetris clone instead of Dark Sould IV might be a better
	approach to learning to code. Tetris is nice as it makes you think about algorithms.

	Controls are Arrow keys Left, Right & Down. Use Z to rotate the piece.
	You score 25pts per tetronimo, and 2^(number of lines)*100 when you get lines.

	Future Modifications
	~~~~~~~~~~~~~~~~~~~~
	1) Show next block and line counter

	Author
	~~~~~~
	Twitter: @javidx9
	Blog: www.onelonecoder.com

	Video:
	~~~~~~
	https://youtu.be/8OK8_tHeCIA

	Last Updated: 30/03/2017
*/
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
using namespace std;

#include <stdio.h>
#include <Windows.h>



class Tetris
{
	//int nScreenWidth = 80;			// Console Screen Size X (columns)
	//int nScreenHeight = 30;			// Console Screen Size Y (rows)

	const int nFieldWidth = 12;
	const int nFieldHeight = 18;
	unsigned char* pField = nullptr;
	wstring tetromino[7] = { {L"..X...X...X...X."}, {L"..X..XX...X....."},{L".....XX..XX....."},{L"..X..XX..X......"},{L".X...XX...X....."},{L".X...X...XX....."},{L"..X...X..XX....."} };
	//tetromino[0] = { L"..X...X...X...X." }; // Tetronimos 4x4
	//tetromino[1].append(L"..X..XX...X.....");
	//tetromino[2].append(L".....XX..XX.....");
	//tetromino[3].append(L"..X..XX..X......");
	//tetromino[4].append(L".X...XX...X.....");
	//tetromino[5].append(L".X...X...XX.....");
	//tetromino[6].append(L"..X...X..XX.....");

	// Game Logic
	bool bKey[4];
	int nNextPiece = rand() % 7;
	//int nNextNextPiece = 0;	// maybe I don't need
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;
	int nSpeed = 250;
	int nSpeedCount = 0;
	bool bForceDown = false;
	bool bRotateHold = true;
	int nPieceCount = 0;
	int nScore = 0;
	vector<int> vLines;
	bool bGameOver = false;

	wchar_t* screen;
	//comment later===============
	HANDLE hConsole;
	DWORD dwBytesWritten;
public:
	Tetris();
	~Tetris();
	int Rotate(int px, int py, int r);

	bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY);
	//void start();
	bool update(float fElapsedTime, bool up, bool down, bool left, bool right);
	void close()
	{
		// Oh Dear
		/*CloseHandle(hConsole);*/
		/*cout << "Game Over!! Score:" << nScore << endl;
		system("pause");
		return 0;*/
	}
};

#endif // !__tetris_H__
