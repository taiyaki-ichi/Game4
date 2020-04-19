#include"SaveData.hpp"
#include"StageSelect/StageSelectScene.hpp"
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

		file.close();

		if (mDatas.size() < StageSelect::StageNum + 1)
			Zero();

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

	void SaveData::Zero()
	{
		mDatas.clear();
		while (mDatas.size() < StageSelect::StageNum+1)
			mDatas.push_back(0);
	}

	int SaveData::GetStageData(int stage)
	{
		if (0 <= stage && stage <= mDatas.size())
			return mDatas[stage];
		else
			return 0;
	
	}

	void SaveData::SetStageData(int stage, int score)
	{
		
		if (0 <= stage && stage <= mDatas.size())
			mDatas[stage] = score;

	}

}