#include"lib/include/Draw/SpriteComponent.hpp"
#include"lib/include/Actor.hpp"
#include"lib/include/Scene.hpp"
#include"lib/src/SpritesManager.hpp"
#include"lib/src/Windows/Graphics.hpp"

namespace GameLib
{


	SpriteComponent::SpriteComponent(Actor* owner, int drawOrder, int updateOrder)
		:Component(owner,updateOrder)
		,mDrawOrder(drawOrder)
	{
		owner->GetScene()->GetSpritesManagerPtr()->Add(this);
	}

	SpriteComponent::~SpriteComponent()
	{
		GetOwner()->GetScene()->GetSpritesManagerPtr()->Remove(this);
	}

	void SpriteComponent::SetDrawOrder(int d)
	{
		if (d != mDrawOrder)
		{
			GetOwner()->GetScene()->GetSpritesManagerPtr()->Remove(this);
			mDrawOrder = d;
			GetOwner()->GetScene()->GetSpritesManagerPtr()->Add(this);
		}
	}

	void DrawTexture(Texture* texture, const Vector2& pos, float rot, float scale, const TextureFlip& flip)
	{
		Graphics::DrawTexture(texture, pos, rot, scale, flip);
	}

	void DrawLine(const Vector2& point1, const Vector2& point2, const Vector3& color, float alpha)
	{
		Graphics::DrawLine(point1, point2, color,alpha);
	}

	void DrawTriangle(const Vector2& point1, const Vector2& point2, const Vector2& point3, const Vector3& color, float alpha)
	{
		Graphics::DrawTriangle(point1, point2, point3, color, alpha);
	}

}