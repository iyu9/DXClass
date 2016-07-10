#define DEBUG
#define APPNAME "DirectX Sample Program"

#include "Graphics.cpp"
#include "Input.cpp"

#include "ObjectManager.cpp"

//window param
int g_width = 800;
int g_height = 680;

HWND                    g_hWnd = nullptr;

/*

//dx11
#include <d3d11.h>
#include <d3dx11.h>

#include <string>
#include <locale.h>
#include <atlstr.h>

//11
ID3D11DepthStencilView* g_pStencilView = nullptr;
ID3D11DepthStencilState* g_pStencilState = nullptr;
ID3D11DeviceContext* g_pDeviceContext = nullptr;

IDXGISwapChain* g_pGISwapChain = nullptr;

//11
ID3D11Device*		g_pDev = nullptr;

//9
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = nullptr;

//11
//ID3D11VertexShader*		g_pVertexBuffer = nullptr;
LPD3DXSPRITE            g_pSprite = nullptr;

LPDIRECTINPUT8 g_pDInput = nullptr;
LPDIRECTINPUTDEVICE8 g_pDIDevice = nullptr;

D3DMATERIAL9            material;
D3DLIGHT9               light;
D3DXVECTOR3             ViewForm(0.0f, 0.0f, -5.0f);
D3DXVECTOR3             ViewFormNext(0.0f, 0.0f, -1.0f);

D3DXVECTOR3             pos;

IDirect3DIndexBuffer9* g_pIndexBuffer;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam);

//頂点インデックス
DWORD index_list[] = {
	0,
	1,
	2,
	3
};

*/

/*
HRESULT CreateShaderFile(char* filename) {
	HRESULT hr;
	ID3DBlob *pBlob;

	UINT nCompileFlag = D3D10_SHADER_DEBUG |
	D3D10_SHADER_SKIP_OPTIMIZATION |
	D3D10_SHADER_ENABLE_STRICTNESS |
	D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR;

	hr = D3DX11CompileFromFile(
	filename,
	0,
	0,
	"VS",
	"vs_4_0",
	nCompileFlag,
	0,
	0L,
	&pBlob,
	0,
	0);

	if (FAILED(hr))
	{
	return E_FAIL;
	}

	hr = g_pDev->CreateVertexShader(
	pBlob->GetBufferPointer(),
	pBlob->GetBufferSize(),
	0,
	&m_lpVertexShader);

	if (FAILED(hr))
	{
	return E_FAIL;
	}

	hr = m_lpDirect3DDevice->CreateInputLayout(
	m_lpInputElementDesc,
	m_nInputElementDescCountSize,
	pBlob->GetBufferPointer(),
	pBlob->GetBufferSize(),
	&m_lpInputLayout);

	if (FAILED(hr)) {
	return E_FAIL;
	}
	pBlob->Release();
	pBlob = 0;

	return S_OK;
}

HRESULT Init3DDev(HWND hwnd, LPDIRECT3D9 *d3d, LPDIRECT3DDEVICE9 *d3Device)
{
	D3DPRESENT_PARAMETERS   d3dpp;
	D3DDISPLAYMODE          dmode;

	*d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (*d3d == nullptr)
	{
		return E_FAIL;
	}

	if (FAILED((*d3d)->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode)))
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

	if (FAILED((*d3d)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, d3Device))) {

		if (FAILED((*d3d)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, d3Device))) {

			if (FAILED((*d3d)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hwnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, d3Device))) {
				EMSG("Create Device Error");
				return E_FAIL;
			}
		}
	}

	if (FAILED(DirectInput8Create(NULL, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL)))
	{
	return E_FAIL;
	}

	if (FAILED(g_pDInput->CreateDevice(GUID_SysKeyboard, NULL, NULL)))
	{
	return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pDev, g_imgfile, &g_pTexture)))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(g_pDev, &g_pSprite)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//3Dポリゴン表示用の頂点バッファを設定する
//頂点定義->頂点バッファ作成->頂点情報の保持？
HRESULT SetVertexBuffer()
{
	const int W = 400;
	const int H = 400;

	CUSTOMVERTEX Vertices[] =
	{
		//primitive - triangle strip
		{ g_width / 2, 0.0f, 0.0f, 1.0f, 0xFFF00FFF, 0.0f, 0.0f },	//top
		{ g_width, 0.5 * g_height, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },		//right
		{ g_width / 2, g_height, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },	//bottom -- 2
		{ 0.0f, 0.5 * g_height, 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },			//left -- 1
	};

	//頂点バッファ
	if (FAILED(g_pDev->CreateVertexBuffer(sizeof(Vertices), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVertexBuffer, nullptr)))
	{
		return E_FAIL;
	}

	void* pVertices;
	if (FAILED(g_pVertexBuffer->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}
	memcpy(pVertices, Vertices, sizeof(Vertices));
	g_pVertexBuffer->Unlock();

	//インデックスバッファ: test

	DWORD Indices[] = {
		0, 1, 2, 3
	};

	if (FAILED(g_pDev->CreateIndexBuffer(4 * sizeof(DWORD), 0, D3DFMT_INDEX32,
		D3DPOOL_MANAGED, &g_pIndexBuffer, nullptr)))
	{
		return E_FAIL;
	}

	void* pIndices;
	if (FAILED(g_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0)))
	{
		return E_FAIL;
	}
	memcpy(pIndices, index_list, sizeof(index_list) * 3);
	g_pIndexBuffer->Unlock();

	return S_OK;
}

HRESULT Init3DDevices(void)
{
	if (FAILED(Init3DDev(g_hWnd, &g_pD3D, &g_pDev)))
	{
		return E_FAIL;
	}

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = material.Diffuse.g = 1.0f;
	material.Diffuse.b = 0.0f;
	material.Ambient.r = material.Ambient.g = material.Ambient.b = 0.5f;
	material.Specular.r = material.Specular.g = material.Specular.b = 0.0f;
	material.Emissive.r = material.Emissive.g = material.Emissive.b = 0.0f;
	material.Power = 0;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = 1.0f;
	light.Specular.r = light.Specular.g = light.Specular.b = 0.2f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = 0.5f;
	light.Direction = D3DXVECTOR3(1, -2, 1);

	return S_OK;
}

void SetupMatrices()
{
	RECT            rect;
	D3DXMATRIX      matWorld;
	D3DXMATRIX      matView;
	D3DXMATRIX      matProj;

	GetClientRect(g_hWnd, &rect);

#ifndef DEBUG
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	g_pDev->SetTransform(D3DTS_WORLD, &matWorld);
#endif

	D3DXMatrixLookAtLH(&matView, &ViewForm,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	g_pDev->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f), (float)rect.right / (float)rect.bottom, 1, 50);
	g_pDev->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pDev->SetRenderState(D3DRS_AMBIENT, 0x00080808);

	g_pDev->SetLight(0, &light);
	g_pDev->LightEnable(0, FALSE);
	g_pDev->SetMaterial(&material);
}

void Render(void)
{
	g_pDev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(g_pDev->BeginScene()))
	{
		time += 0.001f * timeGetTime() - CurrentTime;
		CurrentTime = 0.001f * timeGetTime();

		/*
		g_message = std::to_string(time);

		//文字送りテスト
		for (int i = 0; i < g_const_message.length(); i++) {
		if (i <= time && time < i+1) {

		//マルチバイト判定
		
		if (mblen(&g_message[message_index], MB_CUR_MAX) == 2) {
		message_index += 2;
		}
		else {
		message_index++;
		}

		message_index = i;
		g_message = g_const_message.substr(0, i+1);  //マルチバイト送り必要
		}
		}

		//for (int i = 0; i < (int)g_message.size(); ++i) {
		//	char ch = str[i];
		//}

		TextDraw(g_pFont, g_message.c_str(), 0, 0);

		//TextureDraw(g_pSprite, g_pTexture, 0 + pos.x, 0 - pos.y, 1280 + pos.x, 720 + pos.y, 50, 50);
		//TextureDraw(g_pSprite, g_pTexture, 0, 0, 1280, 720, 50, 50);


		///////
		g_pDev->SetIndices(g_pIndexBuffer);
		////

		g_pDev->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));


		SetupMatrices();

		//set texture
		g_pDev->SetTexture(0, g_pTexture);

		//g_pMesh->DrawSubset(0);
		g_pDev->SetFVF(D3DFVF_CUSTOMVERTEX);
		//g_pDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
		g_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, 3, 0, 2);

		//mode
		if (mode_index == TITLE)
		{
			if (title_index == START)
			{
				TextDraw(g_pFont, "はじめから", 320, 400, 255, 255, 255, 0);
			}
			else
			{
				TextDraw(g_pFont, "はじめから", 320, 400, 255, 255, 255, 255);
			}

			if (title_index == LOAD)
			{
				TextDraw(g_pFont, "つづきから", 320, 460, 255, 255, 255, 0);
			}
			else
			{
				TextDraw(g_pFont, "つづきから", 320, 460, 255, 255, 255, 255);
			}
			if (title_index == OPTION)
			{
				TextDraw(g_pFont, "設定", 320, 520, 255, 255, 255, 0);
			}
			else
			{
				TextDraw(g_pFont, "設定", 320, 520, 255, 255, 255, 255);
			}
		}

		if (mode_index == GAME) {

		}


		g_pDev->EndScene();
	}

	g_pDev->Present(nullptr, nullptr, nullptr, nullptr);
}

void Release(void)
{
	SAFE_RELEASE(g_pSprite);
	SAFE_RELEASE(g_pFont);
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pMesh);
	SAFE_RELEASE(g_pDev);
	SAFE_RELEASE(g_pD3D);
}

*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0L;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{

	Graphics* graphics = new Graphics();
	Input* input = new Input();

	ObjectManager objManager;
	Object cube;
	objManager.add_object(cube);

	MSG msg;

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInst,
		nullptr, nullptr, nullptr, nullptr, APPNAME, nullptr };

	if (RegisterClassEx(&wc) == 0)
	{
		return FALSE;
	}

	RECT rect;
	SetRect(&rect, 0, 0, g_width, g_height);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	rect.right = g_width;
	rect.bottom = g_height;
	rect.top = 0;
	rect.left = 0;

	g_hWnd = CreateWindowEx(0, APPNAME, APPNAME, WS_OVERLAPPEDWINDOW,
		0, 0, g_width, g_height,
		nullptr, nullptr, hInst, nullptr);

	graphics->Init(g_hWnd);
	//input->Init(g_hWnd);

	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			graphics->Render();
			//input->GetKeyDown();
		}
	}

	graphics->Release();
	delete(graphics);
	delete(input);

	UnregisterClass(APPNAME, wc.hInstance);
	return 0;
}
