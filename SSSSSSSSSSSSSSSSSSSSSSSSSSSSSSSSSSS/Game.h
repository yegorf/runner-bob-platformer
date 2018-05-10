#pragma once


class Game
{
private:
	double mobSpeed = 9;
	double cloudSpeed = 2.5;
	float jumptemp = 9;
	bool jumpCheck = false;

	Hero hero;
	Cloud *clouds;
	Bird *birds;
	Mob *mobs;
	Tree *trees;

	unsigned cloudCol = 10;
	unsigned birdCol = 10;
	unsigned mobCol = 10;
	unsigned score = 0;

public:

	void Faster()
	{
		mobSpeed += 0.2;
		cloudSpeed += 0.02;
	}

	Game()
	{
		clouds = new Cloud[cloudCol];
		birds = new Bird[birdCol];
		mobs = new Mob[mobCol];
		trees = new Tree[mobCol];
	}

	~Game()
	{
		delete[] clouds;
		delete[] birds;
		delete[] mobs;
		delete[] trees;
	}

	void ScoreIteration() { score++; }
	void SetScore(unsigned s) { score = s; }
	unsigned GetScore() { return score; }


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
			if (trees[i].GetUse())
			{
				trees[i].Move(mobSpeed);
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
			if (birds[i].GetX()+birds[i].GetW() <= 0) { birds[i].SetUse(false); }
			if (mobs[i].GetX()+ mobs[i].GetW() <= 0) { mobs[i].SetUse(false); }
			if (trees[i].GetX() + trees[i].GetW() <= 0) { trees[i].SetUse(false); }
			if (clouds[i].GetX()+ clouds[i].GetW() <= 0) { clouds[i].SetUse(false); }
		}
	}

	void DrawAll(Sprite sHead, Sprite sLegs, Sprite s_mob, Sprite sTree, Sprite s_bird, Sprite s_cloud, RenderWindow &window)
	{
		hero.Draw(sHead, sLegs, window);
		for (int i = 0; i < mobCol; i++)
		{
			if(mobs[i].GetUse())
			mobs[i].Draw(s_mob, window);
			if (trees[i].GetUse())
				trees[i].Draw(sTree, window);
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
				if (!trees[i].GetUse())
				{
					trees[i].Null();
					trees[i].SetUse(true);
					break;
				}
			}
			break;
		case 3:
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
			if (!jumpCheck && key == 1 && hero.GetHY() > 12 * Scale)
			{
				hero.MoveHero(jumptemp);
				if (hero.GetHY() <= 12 * Scale) { jumpCheck = true; }
			}

			else if (jumpCheck && hero.GetLY() < (screen.GetM() - 2)*Scale)
			{
				hero.MoveHero(-jumptemp);
				if (hero.GetLY() >= (screen.GetM() - 2)*Scale)
				{
					jumpCheck = false;
					key = 0;
				}
			}
	}

	void HeroDown(int key)
	{
		hero.Down(key);
	}

	bool LooseCheck(int key)
	{
		bool loose = false;
		for (int i = 0; i < mobCol; i++)
		{
			loose = mobs[i].Loose(hero);
			if (loose) { return true; }
			loose = birds[i].Loose(hero, key);
			if (loose) { return true; }
			loose = trees[i].Loose(hero);
			if (loose) { return true; }
		}
		return false;
	}

};