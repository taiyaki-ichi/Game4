#include"Input.hpp"
#include"Window.hpp"
#include<Windows.h>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace GameLib
{

	static LPDIRECTINPUT8 g_pInputInterface;
	static LPDIRECTINPUTDEVICE8 g_pKeyDevice;
	static LPDIRECTINPUTDEVICE8 g_MouseDevice;

	bool InitDirectInput();
	void ShutdownDirectInput();
	bool CreateInputInterface();
	bool CreateKeyboardDevice();
	bool CreateMouseDevice();
	//!< �������x���̐ݒ�
	BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device);
	//!< �}�E�X�̐���N��
	BOOL StartMouseControl();
	

	bool InitDirectInput()
	{
		if (!CreateInputInterface())
			return false;

		if (!CreateKeyboardDevice())
			return false;

		if (!CreateMouseDevice())
			return false;

		return true;
		
	}

	bool CreateInputInterface()
	{
		// IDirectInput8�C���^�[�t�F�C�X�̎擾
		HRESULT hr = DirectInput8Create(
			GetModuleHandle(nullptr),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&g_pInputInterface,
			NULL);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}

	bool CreateKeyboardDevice()
	{
		HRESULT hr;
		// IDirectInputDevice8�C���^�[�t�F�C�X�̎擾
		hr = g_pInputInterface->CreateDevice(GUID_SysKeyboard, &g_pKeyDevice, NULL);
		if (FAILED(hr))
		{
			return false;
		}

		// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
		hr = g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr))
		{
			return false;
		}

		HWND window_handle = FindWindowA(WINDOW_CLASS_NAME, nullptr);
		// �������[�h�̐ݒ�
		hr = g_pKeyDevice->SetCooperativeLevel(window_handle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hr))
		{
			return false;
		}

		// �f�o�C�X�̎擾�J�n
		g_pKeyDevice->Acquire();

		return true;
	}

	bool CreateMouseDevice()
	{
		g_MouseDevice = nullptr;

		// �f�o�C�X����
		HRESULT hr = g_pInputInterface->CreateDevice(
			GUID_SysMouse,
			&g_MouseDevice,
			NULL);

		if (FAILED(hr))
		{
			return false;
		}

		// ���̓t�H�[�}�b�g�̎w��
		hr = g_MouseDevice->SetDataFormat(&c_dfDIMouse);
		if (FAILED(hr))
		{
			return false;
		}

		// �������x���̐ݒ�
		if (SetUpCooperativeLevel(g_MouseDevice) == false)
		{
			return false;
		}

		int count = 0;
		// ����J�n
		while (StartMouseControl() == false)
		{
			Sleep(100);
			count++;
			if (count >= 5)
			{
				break;
			}
		}

		return true;
	}

	void ShutdownDirectInput()
	{
		g_pKeyDevice->Unacquire();
		g_pKeyDevice->Release();
		g_pInputInterface->Release();
	}


	BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device)
	{
		// �������[�h�̐ݒ�
		if (FAILED(device->SetCooperativeLevel(
			FindWindow(WINDOW_CLASS_NAME, nullptr),
			DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
		))
		{
			return false;
		}

		return true;
	}


	BOOL StartMouseControl()
	{
		// �f�o�C�X����������ĂȂ�
		if (g_MouseDevice == nullptr)
		{
			return false;
		}
		// ����J�n
		if (FAILED(g_MouseDevice->Acquire()))
		{
			return false;
		}

		DIDEVCAPS cap;
		g_MouseDevice->GetCapabilities(&cap);
		// �|�[�����O����
		if (cap.dwFlags & DIDC_POLLEDDATAFORMAT)
		{
			DWORD error = GetLastError();
			// �|�[�����O�J�n
			if (FAILED(g_MouseDevice->Poll()))
			{
				return false;
			}
		}

		return true;
	}

	Keyboard::Keyboard()
	{
		memset(mCurrState, 0, 256);
		memset(mPrevState, 0, 256);
	}

	Keyboard::~Keyboard()
	{
	}

	void Keyboard::Update()
	{
		memcpy(mPrevState, mCurrState, 256);
		if (g_pKeyDevice)
			g_pKeyDevice->GetDeviceState(256, mCurrState);
	}

	bool Keyboard::GetKeyValue(const Key& key ) const
	{
		auto k = static_cast<unsigned char>(key);

		if (mCurrState[k] & 0x80)
			return true;
		else
			return false;
		
	}

	ButtonState Keyboard::GetKeyState(const Key& key) const
	{
		auto k = static_cast<unsigned char>(key);
	
		if (mPrevState[k] & 0x80)
		{
			if (mCurrState[k] & 0x80)
				return ButtonState::Held;
			else
				return ButtonState::Released;
		}
		else
		{
			if (mCurrState[k] & 0x80)
				return ButtonState::Pressed;
			else
				return ButtonState::None;
		}
		
	}

	Mouse::Mouse()
		:mMousePos()
		,mRelativeMousePos()
	{
		ZeroMemory(&mCurrState, sizeof(DIMOUSESTATE));
		ZeroMemory(&mPrevState, sizeof(DIMOUSESTATE));
	}

	Mouse::~Mouse()
	{
	}

	void Mouse::Update()
	{
		if (g_MouseDevice == nullptr)
		{
			return;
		}

		// �X�V�O�ɍŐV�}�E�X����ۑ�����
		mPrevState = mCurrState;

		// �}�E�X�̏�Ԃ��擾���܂�
		HRESULT	hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mCurrState);
		if (FAILED(hr))
		{
			g_MouseDevice->Acquire();
			hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mCurrState);
		}

		POINT p;
		// �}�E�X���W(�X�N���[�����W)���擾����
		GetCursorPos(&p);

		// �X�N���[�����W�ɃN���C�A���g���W�ɕϊ�����
		ScreenToClient(FindWindowA(WINDOW_CLASS_NAME, nullptr), &p);

		Vector2 pos(static_cast<float>(p.x), static_cast<float>(p.y));
		mRelativeMousePos = pos - mMousePos;
		mMousePos = pos;
		
	}

	bool Mouse::GetMouseButtonValue(MouseButton mouseButton) const
	{
		if (mCurrState.rgbButtons[static_cast<int>(mouseButton)] & 0x80)
			return true;
		else
			return false;
	}

	ButtonState Mouse::GetMouseButtonState(MouseButton mouseButton) const
	{
		int k = static_cast<int>(mouseButton);
		if (mPrevState.rgbButtons[k] & 0x80)
		{
			if (mCurrState.rgbButtons[k] & 0x80)
				return ButtonState::Held;
			else
				return ButtonState::Released;
		}
		else
		{
			if (mCurrState.rgbButtons[k] & 0x80)
				return ButtonState::Pressed;
			else
				return ButtonState::None;
		}
	}

	InputStateImpl::InputStateImpl()
	{
		mKeyboard = new Keyboard();
		mMouse = new Mouse();
	}

	InputStateImpl::~InputStateImpl()
	{
		delete mKeyboard;
		delete mMouse;
		ShutdownDirectInput();
	}

	bool InputStateImpl::Init()
	{
		return InitDirectInput();
	}

	void InputStateImpl::Update()
	{
		mKeyboard->Update();
		mMouse->Update();
	}

	bool InputStateImpl::GetValue(const Key& key) const
	{
		return mKeyboard->GetKeyValue(key);
	}

	bool InputStateImpl::GetValue(const MouseButton& mouseButton) const
	{
		return mMouse->GetMouseButtonValue(mouseButton);
	}

	ButtonState InputStateImpl::GetState(const Key& key) const
	{
		return mKeyboard->GetKeyState(key);
	}

	ButtonState InputStateImpl::GetState(const MouseButton& mouseButton) const
	{
		return mMouse->GetMouseButtonState(mouseButton);
	}

	const Vector2& InputStateImpl::GetMousePos() const
	{
		return mMouse->GetPosition();
	}

	const Vector2& InputStateImpl::GetRelativeMousePos() const
	{
		return mMouse->GetRelativePos();
	}

}