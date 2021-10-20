//================================================================
//
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//
//================================================================

//****************************************************************
//�C���N���[�h�t�@�C��
//****************************************************************
#include "main.h"		// �w�b�_�t�@�C���̓ǂݍ���
#include "player.h"
#include "bg.h"
#include "input.h"
#include "explosion.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "timer.h"

//****************************************************************
// �}�N����`
//****************************************************************
#define CLASS_NAME "WindowClass"	// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME "����肻"		// �E�C���h�E�̖��O(�L���v�V����)

//****************************************************************
// �v���g�^�C�v�錾
//****************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//****************************************************************
// �O���[�o���ϐ�
//****************************************************************
LPDIRECT3D9 g_pD3D = NULL;					// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3D�f�o�C�X�ւ̃|�C���^(�`��ɕK�v)
MODE g_mode = MODE_TITLE;//���[�h

//****************************************************************
// ���C���֐�
//****************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),			// WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,					// �\������E�C���h�E�̃X�^�C����ݒ�
		WindowProc,					// �E�C���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,							// �ʏ�͎g�p���Ȃ��̂�"0"���w��
		0,							// �ʏ�͎g�p���Ȃ��̂�"0"���w��
		hInstance,					// WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
		LoadIcon(NULL,IDI_APPLICATION),		// �g�p����A�C�R�����w��(Windows�������Ă���A�C�R�����g���Ȃ�NULL)
		LoadCursor(NULL, IDC_ARROW),		// �}�E�X�J�[�\�����w��
		(HBRUSH)(COLOR_WINDOW + 1),			// �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
		NULL,						// Window�ɂ��郁�j���[��ݒ�
		CLASS_NAME,					// �E�C���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION),	// �������A�C�R���̐ݒ肳�ꂽ�ꍇ�̏����L�q
	};
	HWND hWnd;					// �E�C���h�E�n���h���i���ʎq�j
	MSG msg;					// ���b�Z�[�W���i�[����ϐ�
	RECT rect =
	{
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(WINDOW_POS_X + SCREEN_WIDTH),
		(WINDOW_POS_Y + SCREEN_HEIGHT)
	};

	// �ȉ���4�s�̓A�j���[�V����������Ƃ��ɏd�v
	DWORD dwCurrentTime;		// ���ݎ���
	DWORD dwExecLastTime;		// �Ō�ɏ�����������



	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�C���h�E�̍쐬
	hWnd = CreateWindowEx(0,		// �g���E�C���h�E�X�^�C��
		CLASS_NAME,					//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,				// �E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,				// �E�C���h�E�̍���X���W�i�����ɔC�ӂ̒l������Ɓc�j
		CW_USEDEFAULT,				// �E�C���h�E�̍���Y���W�i�����ɔC�ӂ̒l������Ɓc�j
		SCREEN_WIDTH,				// �E�C���h�E�̕�
		SCREEN_HEIGHT,				// �E�C���h�E�̍���
		NULL,						// �e�E�C���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,					// �C���X�^���X�n���h��
		NULL);						// �E�C���h�E�쐬�f�[�^

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();	// ���݂̎����擾

									// ����������(�E�C���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�C���h�E�̕\���i�K���Z�b�g�ŏ����j
	ShowWindow(hWnd, nCmdShow);		// �w�肳�ꂽ�E�C���h�E�̕\����Ԃ��w��(�E�C���h�E��\��)
	UpdateWindow(hWnd);				// �E�C���h�E�̏�Ԃ𒼂��ɔ��f(�E�C���h�E�̃N���C�A���g�̈���X�V

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	// Windows�̏���
			if (msg.message == WM_QUIT)
			{	// WM_QUIT���b�Z�[�W�������烋�[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	// DirectX�̏���	�A�j���[�V�����ɕK�v
			dwCurrentTime = timeGetTime();		// �V�X�e���������擾
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))			// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;		// ��������������ۑ�
				// �X�V����
				Update();
				// �`�揈��
				Draw();
			}
		}
	}
	// �I������
	Uninit();

	// �E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}

//****************************************************************
// �E�C���h�E�v���V�[�W��
//****************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:		// �E�C���h�E�̔j��
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:		// �L�[���������Ƃ��̏���
		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);	// �E�C���h�E�j��

		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);		// �K�菈���̒�
}

//****************************************************************
// ����������
// hInstance : �C���X�^���X�̃n���h��
// hWnd      : �E�C���h�E�̃n���h��
// bWindow   : �E�C���h�E���[�h�ɂ��邩�ǂ���
//****************************************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;		// �v���[���e�[�V�����p�����[�^
										// Direct3D�I�u�W�F�N�g����
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{

				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// �����x���g����
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�^�C�g���̏�����
	SetMode(MODE_TITLE);
	InitTitle();
	InitGame();
	// �L�[�{�[�h�̏�����
	InitKeyboard(hInstance, hWnd);
	//���U���g�̏�����
	InitResult();

	return S_OK;
}

//****************************************************************
// �I������
//****************************************************************
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{	// Direct3D�f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//�^�C�g����ʂ̏I������
	UninitTitle();
	//�`���[�g���A����ʂ̏I������
	UninitTutorial();
	//�Q�[����ʂ̏I������
	UninitGame();
	//���U���g��ʂ̏I������
	UninitResult();
}

//****************************************************************
// �X�V����
//****************************************************************
void Update(void)
{
	// �e��I�u�W�F�N�g�̍X�V����
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g����ʂ̍X�V
		UpdateTitle();
		break;
	case MODE_TUTORIAL: //�`���[�g���A����ʂ̍X�V
		UpdateTutorial();
		break;
	case MODE_GAME:		//�Q�[����ʂ̍X�V
		UpdateGame();
		break;
	case MODE_RESULT:	//���U���g��ʂ̍X�V
		UpdateResult();
		break;
	}
}

//****************************************************************
// �`�揈��
//****************************************************************
void Draw(void)
{
	// �o�b�t�@��Z�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g����ʂ̍X�V
			DrawTitle();
			break;

		case MODE_TUTORIAL: //�`���[�g���A����ʂ̍X�V
			DrawTutorial();
			break;

		case MODE_GAME:		//�Q�[����ʂ̍X�V
			DrawGame();
			break;

		case MODE_RESULT:	//���U���g��ʂ̍X�V
			DrawResult();
			break;
		}
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	// DirectX�ł̕`�揈��
}

//****************************************************************
// �f�o�C�X�̎擾
//****************************************************************
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//****************************************************************
//
//****************************************************************
MODE GetMode(void)
{
	return g_mode;
}

//****************************************************************
//
//****************************************************************
void SetMode(MODE mode)
{
	g_mode = mode;

	switch (g_mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}
}