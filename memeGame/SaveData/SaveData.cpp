#include"SaveData.hpp"
#include<fstream>
#include<iostream>

namespace Game
{

	std::vector<int> SaveData::mDatas;

	bool SaveData::Load()
	{
		std::ifstream file;
		file.open("../memeGame/SaveData/SaveData.bin", std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "SaveData.bin load failed\n";
			return false;
		}

		int num;
		while (!file.eof())
		{
			file.read((char*)&num, sizeof(int));
			mDatas.push_back(num);
		}

		mDatas.pop_back();

		std::cout << "DataNum :" << mDatas.size() << "\n";

		file.close();

		for (int i = 0; i < mDatas.size(); i++)
			std::cout << i << " : " << mDatas[i] << "\n";

		return true;

	}

	bool SaveData::Save()
	{
		std::ofstream file;
		file.open("../memeGame/SaveData/SaveData.bin", std::ios::out | std::ios::binary | std::ios::trunc);
		if (!file)
		{
			std::cout << "SaveData.bin save failed\n";
			return false;
		}

		for (int i = 0; i < mDatas.size(); i++)
		{
			file.write((char*)&mDatas[i], sizeof(int));
		}

		file.close();

		return true;
	}

	int SaveData::GetStageData(int stage)
	{
		if (stage == 0 && mDatas.size() == 0)
			return 0;
		else if (0 <= stage && stage <= mDatas.size())
			return mDatas[stage];
		else
			return 0;
	}

	void SaveData::SetStageData(int stage, int score)
	{
		if (0 <= stage && stage <= mDatas.size())
			mDatas[stage] = score;
		else if (mDatas.size() + 1 == stage)
			mDatas.push_back(score);

	}

}