#include <d3d9.h>
#include <d3dx9.h>

#pragma once
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")

#pragma comment(lib,"winmm.lib")

#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = nullptr; } }
#define EMSG(x)         MessageBox(nullptr, x, "DirectX D3D", MB_OK);

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	DWORD color;
	FLOAT tu, tv;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Graphics {

private:
	LPDIRECT3D9             m_pD3D = nullptr;
	LPDIRECT3DDEVICE9       m_pDev = nullptr;

	LPD3DXSPRITE			m_pSprite = nullptr;
	LPDIRECT3DTEXTURE9      m_pTexture = nullptr;
	LPD3DXFONT				m_pFont = nullptr;

	void TextureDraw(LPD3DXSPRITE &pSprite, LPDIRECT3DTEXTURE9 &pTexture, int SrcX, int SrcY, int SrcW, int SrcH, int DstX, int DstY)
	{
		RECT rect = { SrcX, SrcY, SrcW, SrcH };
		D3DXVECTOR3 Center(0, 0, 0);
		D3DXVECTOR3 Pos((float)DstX, (float)DstY, 0);

		pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		pSprite->Draw(pTexture, &rect, &Center, &Pos, 0xffffffff);
		pSprite->End();
	}

	void TextDraw(LPD3DXFONT pFont, const char* text, int X, int Y)
	{
		RECT rect = { X, Y, 0, 0 };
		pFont->DrawText(nullptr, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

public:

	HRESULT Init(HWND hWnd)
	{
		D3DPRESENT_PARAMETERS   d3dpp;
		D3DDISPLAYMODE          dmode;

		m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

		if (m_pD3D == nullptr)
		{
			return E_FAIL;
		}

		if (FAILED((m_pD3D)->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode)))
		{
			return E_FAIL;
		}

		ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = dmode.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDev))) {

			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pDev))) {

				if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pDev))) {
					return E_FAIL;
				}
			}
		}

		if (FAILED(D3DXCreateTextureFromFile(m_pDev, "test.bmp", &m_pTexture)))
		{
			return E_FAIL;
		}

		if (FAILED(D3DXCreateSprite(m_pDev, &m_pSprite)))
		{
			return E_FAIL;
		}

		if (FAILED(D3DXCreateFont(m_pDev, 32, 0, FW_HEAVY, 1, false, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
			ANTIALIASED_QUALITY, FF_DONTCARE, "‚l‚r ƒSƒVƒbƒN", &m_pFont)))
		{
			return E_FAIL;
		}

		return S_OK;
	}

	void Release()
	{
		SAFE_RELEASE(m_pD3D);
		SAFE_RELEASE(m_pDev);

		SAFE_RELEASE(m_pSprite);
		SAFE_RELEASE(m_pTexture);
		SAFE_RELEASE(m_pFont);
	}

	void Render() 
	{
		m_pDev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		m_pDev->BeginScene();

		TextureDraw(m_pSprite, m_pTexture, 0, 0, 1024, 768, 0, 0);
		TextDraw(m_pFont, "TEST", 100, 100);

		m_pDev->EndScene();
		m_pDev->Present(NULL, NULL, NULL, NULL);
	}
};