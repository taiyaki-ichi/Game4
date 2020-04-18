#pragma once
#include<vector>

namespace Game
{
	class SaveData
	{
	public:
		static bool Load();
		static bool Save();

		static int GetStageData(int stage);
		static void SetStageData(int stage, int score);

	private:
		static std::vector<int> mDatas;

		static void Zero();
	};
}