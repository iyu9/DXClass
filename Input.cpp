#include <d3d9.h>
#include <d3dx9.h>

#include <dinput.h>

#pragma comment(lib,"dinput8.lib")

class Input {

private:
	LPDIRECTINPUT8 m_pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 m_pDIDevice = nullptr;

public:
	HRESULT Init(HWND hWnd) 
	{
		if (FAILED(DirectInput8Create(NULL, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL)))
		{
			return E_FAIL;
		}

		if (FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL)))
		{
			return E_FAIL;
		}

		m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
		m_pDIDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		m_pDIDevice->Acquire();

		return S_OK;
	}

	void GetKeyDown()
	{
		HRESULT hr;
		BYTE diKeyState[256];

		hr = m_pDIDevice->GetDeviceState(256, diKeyState);

		if (SUCCEEDED(hr))
		{
			if (diKeyState[DIK_W] & 0x80)
			{

			}

			if (diKeyState[DIK_A] & 0x80)
			{

			}

			if (diKeyState[DIK_S] & 0x80)
			{

			}

			if (diKeyState[DIK_D] & 0x80)
			{

			}

			if (diKeyState[DIK_LEFT] & 0x80)
			{

			}

			if (diKeyState[DIK_RIGHT] & 0x80)
			{

			}

			if (diKeyState[DIK_UP] & 0x80)
			{

			}

			if (diKeyState[DIK_DOWN] & 0x80)
			{

			}

			if (diKeyState[DIK_LSHIFT] & 0x80)
			{

			}

			if (diKeyState[DIK_Z] & 0x80)
			{

			}

			if (diKeyState[DIK_X] & 0x80)
			{

			}

			if (diKeyState[DIK_C] & 0x80)
			{

			}

			if (diKeyState[DIK_RETURN] & 0x80)
			{

			}

		}
		else {
			m_pDIDevice->Acquire();
		}
	}

};