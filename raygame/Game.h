#pragma once
class Game
{
private:
	bool _gameOver;

public:
	void start();
	void update();
	void draw();
	void end();
	void run();
};