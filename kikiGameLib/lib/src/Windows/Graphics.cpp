#include"Graphics.hpp"
#include"lib/include/Scene.hpp"
#include"lib/src/SpritesManager.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/Draw/SpriteComponent.hpp"
#include"lib/include/Math.hpp"
#include"Window.hpp"
#include"lib/include/Draw/TextComponent.hpp"

#include<Windows.h>
#include<d3d9.h>
#include"lib/DirectX/d3dx9.h"

#include<dsound.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include<iostream>

namespace GameLib
{

	static LPDIRECT3D9 g_D3DInterface;						
	static LPDIRECT3DDEVICE9 g_D3DDevice;

	GraphicsManager::GraphicsManager()
	{
	}

	GraphicsManager::~GraphicsManager()
	{
		if (g_D3DInterface)
			g_D3DInterface->Release();
		if (g_D3DDevice)
			g_D3DDevice->Release();
			
	}

	bool GraphicsManager::Init()
	{
		D3DPRESENT_PARAMETERS present_param;
		ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

		// インターフェース作成
		g_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
		if (g_D3DInterface == NULL)
		{
			// 作成失敗
			std::cout << "Direct3DCreate9 is failed\n";
			return false;
		}

		// バックバッファの数 => 1
		present_param.BackBufferCount = 1;
		// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
		present_param.BackBufferFormat = D3DFMT_UNKNOWN;
		// ウィンドウモード設定 => 定数で切り替え
		present_param.Windowed = true;

		// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
		present_param.SwapEffect = D3DSWAPEFFECT_DISCARD;

		// DirectDeviceの作成
		if (FAILED(g_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			FindWindowA(WINDOW_CLASS_NAME, nullptr),
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
			&present_param,
			&g_D3DDevice)))
		{
			std::cout << "CreateDevice is failed\n";
			return false;
		}

		g_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		
		// ビューポートパラメータ
		D3DVIEWPORT9 view_port;

		// ビューポートの左上座標
		view_port.X = 0;
		view_port.Y = 0;
		// ビューポートの幅
		view_port.Width = present_param.BackBufferWidth;
		// ビューポートの高さ
		view_port.Height = present_param.BackBufferHeight;
		// ビューポート深度設定
		view_port.MinZ = 0.0f;
		view_port.MaxZ = 1.0f;

		// ビューポート設定
		if (FAILED(g_D3DDevice->SetViewport(&view_port)))
		{
			std::cout << "SetViewport is failed\n";
			return false;
		}

		return true;
	}



	Texture::Texture(LPDIRECT3DTEXTURE9 ptr, float w, float h)
		:mPtr(ptr)
		,mWidth(w)
		,mHeight(h)
	{
	}

	Texture::~Texture()
	{
		if (mPtr)
			mPtr->Release();
	}

	Texture* LoadTexture(const std::string& fileName)
	{
		
		LPDIRECT3DTEXTURE9 tex;
		D3DXIMAGE_INFO info;

		// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
		D3DXGetImageInfoFromFileA(fileName.c_str(), &info);

		if (FAILED(D3DXCreateTextureFromFileExA(g_D3DDevice,
			fileName.c_str(),
			info.Width,
			info.Height,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0x0000ff00,
			nullptr,
			nullptr,
			&tex)
		))
		{
			std::cout << "CreateTexture is failed : " << fileName << "\n";
			return nullptr;
		}
		else
		{
			// テクスチャサイズの取得
			D3DSURFACE_DESC desc;

			if (FAILED(tex->GetLevelDesc(0, &desc)))
			{
				std::cout << "GetLevelDesc is failed : " << fileName << "\n";
				return nullptr;
			}

			return new Texture(tex, static_cast<float>(desc.Width), static_cast<float>(desc.Height));
		}

	}

	void Graphics::DrawTexture(Texture* texture, const Vector2& pos, float rot, float scale, const TextureFlip& flip)
	{
		
		if (texture)
		{
			float width = texture->GetWidth() * scale;
			float height = texture->GetHeight() * scale;
			float wi = width / 2.f;
			float hei = height / 2.f;
			
			Vector2 point[] = {
				Vector2(-wi,-hei)+pos,
				Vector2(wi,-hei)+pos,
				Vector2(wi,hei)+pos,
				Vector2(-wi,hei)+pos,
			};

			GetRotatedRect(point, pos, rot);

			bool h = (flip == TextureFlip::Horizontal);
			bool v = (flip == TextureFlip::Vertical);
			CUSTOM_VERTEX TriangleFan[] = {
				{ point[0].x, point[0].y,0.f, 1.f ,(h ? 1.f : 0.f),(v ? 1.f : 0.f)},
				{ point[1].x, point[1].y,0.f, 1.f ,(h ? 0.f : 1.f),(v ? 1.f : 0.f)},
				{ point[2].x, point[2].y,0.f, 1.f ,(h ? 0.f : 1.f),(v ? 0.f : 1.f)},
				{ point[3].x, point[3].y,0.f, 1.f ,(h ? 1.f : 0.f),(v ? 0.f : 1.f)},
			};

			// 頂点構造の指定
			g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1 );
			g_D3DDevice->SetTexture(0, texture->GetPtr());
			g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TriangleFan, sizeof(CUSTOM_VERTEX));
			

		}
	}

	void Graphics::DrawLine(const Vector2& point1, const Vector2& point2, const Vector3& color, float alpha)
	{
		auto c = D3DCOLOR_ARGB(static_cast<int>(alpha), static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));

		CUSTOM_VERTEX2 p[] = {
			{point1.x,point1.y,0.f,1,c},
			{point2.x,point2.y,0.f,1,c},
		};

		g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		g_D3DDevice->SetTexture(0, nullptr);
		g_D3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, p, sizeof(CUSTOM_VERTEX2));

	}

	void Graphics::DrawTriangle(const Vector2& point1, const Vector2& point2, const Vector2& point3, const Vector3& color,float alpha)
	{
		auto c = D3DCOLOR_ARGB(static_cast<int>(alpha), static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
		
		CUSTOM_VERTEX2 p[] = {
			{point1.x,point1.y,0.f,1,c},
			{point2.x,point2.y,0.f,1,c},
			{point3.x,point3.y,0.f,1,c}
		};

		g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		g_D3DDevice->SetTexture(0, nullptr);
		g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, p, sizeof(CUSTOM_VERTEX2));

	}




	void DrawStart()
	{
		g_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0);

		if (D3D_OK != g_D3DDevice->BeginScene())
			std::cout << "BeginScene is failed\n";

	}

	void DrawEnd()
	{
		g_D3DDevice->EndScene();
		g_D3DDevice->Present(NULL, NULL, NULL, NULL);

	}

	Font::Font(LPD3DXFONT font[Font::SizeNum])
		:mPtr()
	{
		for (int i = 0; i < Font::SizeNum; i++)
			mPtr[i] = font[i];
	}

	Font::~Font()
	{
		for (int i = 0; i < Font::SizeNum; i++)
			if (mPtr[i])
				mPtr[i]->Release();
	}


	Font* LoadFont(const std::string& fileName)
	{

		LPD3DXFONT font[Font::SizeNum];
		int size;
		for (int i = 0; i < Font::SizeNum; i++)
		{
			if (i == 0)
				size = 16;
			else if (i == 1)
				size = 32;
			else
				size += 32;

			if (FAILED(D3DXCreateFont(
				g_D3DDevice,                /* デバイス */
				size,                            /* 文字の高さ */
				0,                            /* 文字幅 */
				FW_NORMAL,                    /* フォントの太さ */
				1,                            /* MIPMAPのレベル */
				FALSE,                        /* イタリックか？ */
				DEFAULT_CHARSET,            /* 文字セット */
				OUT_DEFAULT_PRECIS,            /* 出力精度 */
				DEFAULT_QUALITY,            /* 出力品質 */
				DEFAULT_PITCH | FF_SWISS,    /* フォントピッチとファミリ */
				fileName.c_str(),                    /* フォント名 */
				&font[i]))) {        /* Direct3Dフォントへのポインタへのアドレス */

				std::cout << "CreateFont " << i << " is failed\n";
			}
		}

		return new Font(font);
	}


	void Graphics::DrawMyText(Font* font, const std::string& text, const Vector2& center, const FontSize& size , const Vector3& color, float alpha)
	{
		int i = static_cast<int>(size);
		if (font->GetPtr(i))
		{
			float width = static_cast<float>(text.size() * i);
			float wi = width / 2.f;
			int size;
			if (i == 0)
				size = 16;
			else
				size = 32 * i;
			
			float hei = size / 2.f;

			RECT rect = {
				static_cast<LONG>(center.x - wi),
				static_cast<LONG>(center.y - hei),
				static_cast<LONG>(center.x + wi),
				static_cast<LONG>(center.y + hei)
			};
			D3DCOLOR c = D3DCOLOR_ARGB(static_cast<int>(alpha), static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
			font->GetPtr(i)->DrawTextA(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_NOCLIP, c);

		}

	}

}
