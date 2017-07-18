#pragma once

namespace App
{
	static constexpr int FRAMERATE = 60;
	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = WINDOW_WIDTH / 12 * 9;

	void Init();
	void Close();
	void Cycle();
}