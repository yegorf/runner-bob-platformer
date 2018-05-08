#pragma once

class Cell
{
private:
	float x;
	float y;

public:
	Cell()
	{
		x = 50;
		y = 50;
	}

	void SetX(float X) { x = X; }
	void SetY(float Y) { y = Y; }
	float GetX() { return x; }
	float GetY() { return y; }

};


