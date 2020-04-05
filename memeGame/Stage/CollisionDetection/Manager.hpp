#pragma once
#include<vector>

namespace Game
{
	namespace Stage
	{
		class Body;

		class Cell;
		class LinerObject;

		class Liner4Tree
		{
		public:

			Liner4Tree(unsigned int level, float left, float top, float right, float bottom);
			~Liner4Tree();

			bool Regist(LinerObject* obj);
			void SearchCellArray();
			void CheckDelete(unsigned int elem);

		private:
			//SearchCellArrayで再帰的に使用
			void SearchCellArraySub(std::vector<LinerObject*>& colStac, unsigned int Elem);

			bool CreateNewCell(unsigned int Elem);

			//モートン番号関係
			//座標からCellArryの添え字を検出
			unsigned int GetMortonNumber(float left, float top, float right, float bottom);
			//ビット分割関数
			unsigned int BitSeparate32(unsigned int n);
			//2Dモートン空間番号算出関数
			unsigned short Get2DMortonNumber(unsigned short x, unsigned short y);
			//座標からモートン番号
			unsigned int GetPointElem(float pos_x, float pos_y);


			Cell** mCellArray;

			float mWidth;
			float mHeight;
			float mLeft;
			float mTop;
			float mUnitW;
			float mUnitH;
			unsigned int mCellNum;
			unsigned int mLevel;
		};



		class Cell
		{
		public:
			Cell(Liner4Tree* tree, unsigned int elem);
			~Cell();

			bool Push(LinerObject* obj);

			LinerObject* GetFirstObject() const { return mFirstObject; }
			void SetFirstObject(LinerObject* obj) { mFirstObject = obj; }

			unsigned int GetElm() const { return mElem; }
			Liner4Tree* GetTree() const { return mTree; }

		private:
			Liner4Tree* mTree;
			LinerObject* mFirstObject;
			unsigned int mElem;
		};

		class LinerObject
		{
		public:
			LinerObject(Body* body);
			~LinerObject();

			void RemoveFromList();

			LinerObject* mPre;
			LinerObject* mNext;

			//所属空間
			Cell* mCell;

			Body* GetBody() const { return mBody; }

		private:
			Body* mBody;

		};
	}
}