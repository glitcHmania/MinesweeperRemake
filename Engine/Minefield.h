#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Mouse.h"
#include <random>

class Minefield
{
public:
	enum class GameStatus {
		Started,
		Win,
		Lost
	};
private:
	class Cell {
	public:
		enum class Status {
			Hidden,
			Revealed,
			Flagged
		};
		void Reveal();
		void ToggleFlag();
		bool IsRevealed();
		bool IsFlagged();
		void SpawnMine();
		bool HasMine();
		Status& GetStatus();
		void SetNearbyMines(int in_nearbyMines);
		int GetNearbyMines();
	private:
		Status status = Status::Hidden;
		bool hasMine = false;
		int nearbyMines = -1;
	};
public:
	Minefield(int in_nMines);
	Cell& CellAt(const Vei2 gridPos);
	void Draw(Graphics& gfx);
	Vei2 ScreenToGrid(const Vei2& screenPos, Graphics& gfx);
	void RevealOnClick(const Vei2& screenPos, Graphics& gfx);
	void ToggleFlagOnClick(const Vei2& screenPos, Graphics& gfx);
	void CountNearbyMines();
	void DrawCellByNumber(int number, Graphics& gfx, const Vei2& screenPos);
	void RevealSafeCells();
	GameStatus CheckWinStatus();
private:
	static constexpr int width = 5;
	static constexpr int height = 5;
	Cell field[width * height];
	int nMines;
	Vei2 pos;
	bool isDead = false;
};

