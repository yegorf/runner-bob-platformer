#pragma once


class Game
{
private:
	double mobSpeed = 3;
	double cloudSpeed = 1;
	float jumptemp = 3;
	bool jumpCheck = false;

	Cloud *clouds;
	Bird *birds;
	Mob *mobs;

	unsigned cloudCol = 10;
	unsigned birdCol = 10;
	unsigned mobCol = 10;

public:

	Game()
	{
		clouds = new Cloud[cloudCol];
		birds = new Bird[birdCol];
		mobs = new Mob[mobCol];
	}

	void MoveAll()
	{
		for (int i = 0; i < birdCol; i++)
		{
			if (birds[i].GetUse())
			{
				birds[i].Move(mobSpeed);
			}
			if (mobs[i].GetUse())
			{
				mobs[i].Move(mobSpeed);
			}
		}

		for (int i = 0; i < cloudCol; i++)
		{
			if (clouds[i].GetUse())
			{
				clouds[i].Move(cloudSpeed);
			}
		}
	}

	void CheckEnd()
	{
		for (int i = 0; i < birdCol; i++)
		{
			if (birds[i].GetX() <= 0) { birds[i].SetUse(false); }
			if (mobs[i].GetX() <= 0) { mobs[i].SetUse(false); }
			if (clouds[i].GetX() <= 0) { clouds[i].SetUse(false); }
		}
	}

	void DrawAll(Sprite s_mob, Sprite s_bird, Sprite s_cloud, RenderWindow &window)
	{
		for (int i = 0; i < mobCol; i++)
		{
			if(mobs[i].GetUse())
			mobs[i].Draw(s_mob, window);
			if (birds[i].GetUse())
			birds[i].Draw(s_bird, window);
			if (clouds[i].GetUse())
			clouds[i].Draw(s_cloud, window);
		}
	}

	void AddBarrier(int var)
	{
		switch (var)
		{
		case 0:
			for (int i = 0; i < mobCol; i++)
			{
				if (!mobs[i].GetUse()) 
				{ 
					mobs[i].Null();
					mobs[i].SetUse(true);
					break;
				}
			}
			break;
		case 1:
			for (int i = 0; i < mobCol; i++)
			{
				if (!birds[i].GetUse())
				{
					birds[i].Null();
					birds[i].SetUse(true);
					break;
				}
			}
			break;
		case 2:
			for (int i = 0; i < mobCol; i++)
			{
				if (!clouds[i].GetUse())
				{
					clouds[i].Null();
					clouds[i].SetUse(true);
					break;
				}
			}
			break;
		}
	}

	void HeroJump(int &key)
	{

		if (!jumpCheck && key == 1 && hero.GetHeadY() > 13 * Scale)
		{
			hero.MoveHero(jumptemp);
			if (hero.GetHeadY() <= 13 * Scale) { jumpCheck = true;}
		}

		else if (jumpCheck && hero.GetLegsY() < (screen.GetM()-2)*Scale)
		{
			hero.MoveHero(-jumptemp);
			if (hero.GetLegsY() >= (screen.GetM() - 2)*Scale)
			{
				jumpCheck = false;
				key = 0;
			}
		}
	}



};