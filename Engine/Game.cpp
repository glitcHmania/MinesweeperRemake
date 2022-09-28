/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	minefield(1)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	minefield.CountNearbyMines();
	if (minefield.CheckWinStatus() == Minefield::GameStatus::Started)
	{
		while (!wnd.mouse.IsEmpty())
		{
			const Mouse::Event e = wnd.mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				minefield.RevealOnClick(e.GetPos(), gfx);
				//minefield.RevealSafeCells();
			}
			else if (e.GetType() == Mouse::Event::Type::RPress)
			{
				minefield.ToggleFlagOnClick(e.GetPos(), gfx);
			}
		}
	}
}

void Game::ComposeFrame()
{
	minefield.Draw(gfx);
	if (minefield.CheckWinStatus() == Minefield::GameStatus::Win)
	{
		SpriteCodex::DrawWinTitle({ gfx.ScreenWidth/2 - 25, gfx.ScreenHeight/2 - 19 }, gfx);
	}
	else if (minefield.CheckWinStatus() == Minefield::GameStatus::Lost)
	{
		SpriteCodex::DrawLooseTitle({ gfx.ScreenWidth / 2 - 30, gfx.ScreenHeight / 2 - 19 }, gfx);
	}
}
