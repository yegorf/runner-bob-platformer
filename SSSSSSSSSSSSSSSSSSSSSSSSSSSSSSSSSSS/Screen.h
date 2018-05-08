#pragma once


class Screen
{
private:
	int scale = 35;
	int n;
	int m;
	int w;
	int h;


public:

	Screen()
	{
		n = 30;
		m = 20;
		w = scale * n;
		h = scale * m;
	}


	int GetW() { return w; }
	int GetH() { return h; }
	int GetN() { return n; }
	int GetM() { return m; }
	int GetScale() { return scale; }

}screen;