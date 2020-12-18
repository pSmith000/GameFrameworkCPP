#pragma once
class Game
{
public:
	void run();

private:
	void start();
	void update();
	void draw();
	void end();

private:
	bool m_gameOver = false;
};