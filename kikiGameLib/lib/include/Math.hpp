#pragma once
#include<cmath>
#include<limits>

namespace GameLib
{
	namespace Math
	{
		const float Pi = 3.1415926535f;
		const float TwoPi = Pi * 2.0f;
		const float PiOver2 = Pi / 2.0f;
		const float Infinity = std::numeric_limits<float>::infinity();
		const float NegInfinity = -std::numeric_limits<float>::infinity();


		inline float ToRadians(float degrees)
		{
			return degrees * Pi / 180.0f;
		}

		inline float ToDegrees(float radians)
		{
			return radians * 180.0f / Pi;
		}

		inline bool NearZero(float val, float epsilon = 0.001f)
		{
			if (fabs(val) <= epsilon)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		template <typename T>
		T Max(const T& a, const T& b)
		{
			return (a < b ? b : a);
		}

		template <typename T>
		T Min(const T& a, const T& b)
		{
			return (a < b ? a : b);
		}

		inline float Abs(float value)
		{
			return fabs(value);
		}

		inline float Cos(float angle)
		{
			return cosf(angle);
		}

		inline float Sin(float angle)
		{
			return sinf(angle);
		}

		inline float Tan(float angle)
		{
			return tanf(angle);
		}

		inline float Acos(float value)
		{
			return acosf(value);
		}

		inline float Atan2(float y, float x)
		{
			return atan2f(y, x);
		}

		inline float Cot(float angle)
		{
			return 1.0f / Tan(angle);
		}

		inline float Lerp(float a, float b, float f)
		{
			return a + f * (b - a);
		}

		inline float Sqrt(float value)
		{
			return sqrtf(value);
		}

		inline float Fmod(float numer, float denom)
		{
			return fmod(numer, denom);
		}

		inline float Pow(float num, float index)
		{
			return powf(num, index);
		}

	}


	class Vector2
	{
	public:
		float x;
		float y;

		//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
		//ˆø”‚È‚µ‚Å‚OƒxƒNƒgƒ‹
		Vector2() :
			x(0.f),
			y(0.f)
		{}
		//ˆÃ–Ù‚ÌŒ^•ÏŠ·‚Ì‹ÖŽ~‚Ìexplicit
		explicit Vector2(float inX, float inY) :
			x(inX),
			y(inY)
		{}

		//x,y‚ð‚¢‚Á‚Ø‚ñ‚É•Ï‚¦‚½‚¢
		void Set(float inX, float inY)
		{
			x = inX;
			y = inY;
		}


		//‘«‚µŽZ
		friend Vector2 operator+(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.x + b.x, a.y + b.y);
		}

		//ˆø‚«ŽZ
		friend Vector2 operator-(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.x - b.x, a.y - b.y);
		}

		//—v‘f“¯Žm‚ÌŠ|‚¯ŽZ
		friend Vector2 operator*(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.x * b.x, a.y * b.y);
		}

		//ƒxƒNƒgƒ‹‚ÌƒXƒJƒ‰[”{
		friend Vector2 operator*(const Vector2& vec, float scalar)
		{
			return Vector2(vec.x * scalar, vec.y * scalar);
		}
		friend Vector2 operator*(float scalar, const Vector2& vec)
		{
			return Vector2(vec.x * scalar, vec.y * scalar);
		}

		friend Vector2 operator/(const Vector2& vec, float s)
		{
			return Vector2(vec.x / s, vec.y / s);
		}
		friend Vector2 operator/(float s, const Vector2& vec)
		{
			return Vector2(vec.x / s, vec.y / s);
		}


		//ƒXƒJƒ‰[”{‚Ì‘ã“ü‰‰ŽZŽq
		Vector2& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		//‘«‚µŽZ‚Ì‘ã“ü‰‰ŽZŽq
		Vector2& operator+=(const Vector2& right)
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		//ˆø‚«ŽZ‚Ì‘ã“ü‰‰ŽZŽq
		Vector2& operator-=(const Vector2& right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		//ƒxƒNƒgƒ‹‚Ì’·‚³‚Ì“ñæ
		float LengthSq() const
		{
			return (x * x + y * y);
		}

		//ƒxƒNƒgƒ‹‚Ì’·‚³
		float Length() const
		{
			return (Math::Sqrt(LengthSq()));
		}

		//ƒxƒNƒgƒ‹‚Ì³‹K‰»
		void Normalize()
		{
			float length = Length();
			x /= length;
			y /= length;
		}

		//ŽÀ‘Ì‚ª‚È‚­‚Ä‚àŒÄ‚×‚éstatic
		static Vector2  Normalize(const Vector2& vec)
		{
			Vector2 temp = vec;
			temp.Normalize();
			return temp;
		}

		//ƒxƒNƒgƒ‹‚Ì“àÏ
		static float Dot(const Vector2& a, const Vector2& b)
		{
			return (a.x * b.x + a.y * b.y);
		}

		//ƒxƒNƒgƒ‹‚ÌŠOÏ‚Ì‚š
		static float Cross(const Vector2& a, const Vector2& b)
		{
			return (a.x * b.y - a.y * b.x);
		}

		//Œ´“_‚©‚ç‚ÌƒxƒNƒgƒ‹‚Ì‰ñ“]
		//SDL‚Í”½ŽžŒv‰ñ‚è‚ª³‚Ì‚½‚ß-rot
		static Vector2 Rotation(const Vector2& a, float rot)
		{
			if (rot == 0.f)
				return Vector2(a);
			if (a.x == 0.f && a.y == 0.f)
				return Vector2(a);
			float x = a.x * Math::Cos(-rot) - a.y * Math::Sin(-rot);
			float y = a.x * Math::Sin(-rot) + a.y * Math::Cos(-rot);
			return Vector2(x, y);
		}

	};

	//‰ñ“]‚³‚ê‚½Žl“_‚ÌÀ•W
	static void GetRotatedRect(Vector2 point[], const Vector2& center, float rot)
	{
		if (rot != 0.f)
		{
			for (int i = 0; i < 4; i++)
				point[i] = Vector2::Rotation(point[i] - center, rot) + center;
		}
	}
	static void GetRotatedRect(Vector2 point[], const Vector2& center, float width, float height, float rot)
	{
		float wi = width / 2.f;
		float hei = height / 2.f;
		point[0] = Vector2(wi, hei) + center;
		point[1] = Vector2(wi, -hei) + center;
		point[2] = Vector2(-wi, -hei) + center;
		point[3] = Vector2(-wi, hei) + center;
		GetRotatedRect(point, center, rot);
	}

	// 3D Vector
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3()
			:x(0.0f)
			, y(0.0f)
			, z(0.0f)
		{}

		explicit Vector3(float inX, float inY, float inZ)
			:x(inX)
			, y(inY)
			, z(inZ)
		{}

		void Set(float inX, float inY, float inZ)
		{
			x = inX;
			y = inY;
			z = inZ;
		}

		//‘«‚µŽZ
		friend Vector3 operator+(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
		}

		//ˆø‚«ŽZ
		friend Vector3 operator-(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
		}

		//—v‘f“¯Žm‚ÌŠ|‚¯ŽZ
		friend Vector3 operator*(const Vector3& left, const Vector3& right)
		{
			return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
		}

		//ƒXƒJƒ‰[”{
		friend Vector3 operator*(const Vector3& vec, float scalar)
		{
			return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
		}
		friend Vector3 operator*(float scalar, const Vector3& vec)
		{
			return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
		}

		//ƒXƒJƒ‰[”{‚Ì‘ã“ü‰‰ŽZŽq
		Vector3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		//‘«‚µŽZ‚Ì‘ã“ü‰‰ŽZŽq
		Vector3& operator+=(const Vector3& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			return *this;
		}

		//ˆø‚«ŽZ‚Ì‘ã“ü‰‰ŽZŽq
		Vector3& operator-=(const Vector3& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			return *this;
		}

		//ƒxƒNƒgƒ‹‚Ì’·‚³‚Ì“ñæ
		float LengthSq() const
		{
			return (x * x + y * y + z * z);
		}

		//ƒxƒNƒgƒ‹‚Ì’·‚³
		float Length() const
		{
			return (Math::Sqrt(LengthSq()));
		}

		//ƒxƒNƒgƒ‹‚Ì³‹K‰»
		void Normalize()
		{
			float length = Length();
			x /= length;
			y /= length;
			z /= length;
		}

		//³‹K‰»‚ÌÃ“Iƒƒ“ƒoŠÖ”
		static Vector3 Normalize(const Vector3& vec)
		{
			Vector3 temp = vec;
			temp.Normalize();
			return temp;
		}

		//“àÏ
		static float Dot(const Vector3& a, const Vector3& b)
		{
			return (a.x * b.x + a.y * b.y + a.z * b.z);
		}

		//ŠOÏ
		static Vector3 Cross(const Vector3& a, const Vector3& b)
		{
			Vector3 temp;
			temp.x = a.y * b.z - a.z * b.y;
			temp.y = a.z * b.x - a.x * b.z;
			temp.z = a.x * b.y - a.y * b.x;
			return temp;
		}


	};




	//FARGB‚Ì‚»‚ê‚¼‚ê‚ÌŠ„‡‚Å•\Œ»(0.f-1.f)
	namespace Color
	{
		static const Vector3 Black(0.0f * 255, 0.0f * 255, 0.0f * 255);
		static const Vector3 White(1.0f * 255, 1.0f * 255, 1.0f * 255);
		static const Vector3 Red(1.0f * 255, 0.0f * 255, 0.0f * 255);
		static const Vector3 Green(0.0f * 255, 1.0f * 255, 0.0f * 255);
		static const Vector3 Blue(0.0f * 255, 0.0f * 255, 1.0f * 255);
		static const Vector3 Yellow(1.0f * 255, 1.0f * 255, 0.0f * 255);
		static const Vector3 LightYellow(1.0f * 255, 1.0f * 255, 0.88f * 255);
		static const Vector3 LightBlue(0.68f * 255, 0.85f * 255, 0.9f * 255);
		static const Vector3 LightPink(1.0f * 255, 0.71f * 255, 0.76f * 255);
		static const Vector3 LightGreen(0.56f * 255, 0.93f * 255, 0.56f * 255);
	}

}