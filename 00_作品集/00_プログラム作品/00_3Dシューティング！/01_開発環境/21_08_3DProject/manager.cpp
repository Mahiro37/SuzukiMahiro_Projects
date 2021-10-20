//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "playerData.h"
#include "bulletData.h"
#include "wallData.h"
#include "blockData.h"
#include "floorData.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "scene.h"
#include "scene2d.h"
#include "scene3d.h"
#include "camera.h"
#include "light.h"
#include "title.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "movie.h"
#include "player.h"
#include "billboard.h"
#include "bullet.h"
#include "ui.h"
#include "wall.h"
#include "collision.h"
#include "bullet.h"
#include "block.h"
#include "effect.h"
#include "floor.h"

//=============================================================================
//���I�����o�ϐ��錾
//=============================================================================
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputMouse *CManager::m_pInputMouse = nullptr;
CInputJoystick *CManager::m_pInputJoystick = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CLight *CManager::m_pLight = nullptr;
CSound *CManager::m_pSound = nullptr;
CFade *CManager::m_pFade = nullptr;
CDebugProc *CManager::m_pDebugProc = nullptr;
CMode *CManager::m_pMode = nullptr;
CManager::MODE CManager::m_mode = CManager::MODE_NONE;
CPlayerData* CManager::m_pPlayerData = nullptr;
CBulletData* CManager::m_pBulletData = nullptr;
CWallData* CManager::m_pWallData = nullptr;
CBlockData* CManager::m_pBlockData = nullptr;
CFloorData* CManager::m_pFloorData = nullptr;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�X�V����I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetUpdateType(CScene::OBJTYPE_MAX, nullptr);

	//--------------------
	//�N���X����,������
	//--------------------
	if (m_pRenderer == nullptr)
	{ //�����_���[
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, TRUE);
	}
	if (m_pInputKeyboard == nullptr)
	{ //�L�[�{�[�h
		m_pInputKeyboard = new CInputKeyboard;
		m_pInputKeyboard->Init(hInstance, hWnd);
	}
	if (m_pInputMouse == nullptr)
	{ //�}�E�X�̐���
		m_pInputMouse = new CInputMouse;
		m_pInputMouse->Init(hInstance, hWnd);
	}
	if (m_pInputJoystick == nullptr)
	{ //�Q�[���p�b�h
		m_pInputJoystick = new CInputJoystick;
		m_pInputJoystick->Init(hInstance, hWnd);
	}
	if (m_pSound == nullptr)
	{ //�T�E���h
		m_pSound = new CSound;
		// ����������
		if (FAILED(m_pSound->Init(hWnd)))
		{
			return -1;
		}
	}
	if (m_pFade == nullptr)
	{ //�t�F�[�h
		m_pFade = new CFade(CScene::OBJTYPE_FADE);
		m_pFade->Init();
	}
	if (m_pPlayerData == nullptr)
	{ //�v���C���[�f�[�^
		m_pPlayerData = new CPlayerData;
		m_pPlayerData->Init();
	}
	if (m_pBulletData == nullptr)
	{ //�e�f�[�^
		m_pBulletData = new CBulletData;
		m_pBulletData->Init();
	}
	if (m_pWallData == nullptr)
	{ //�ǃf�[�^
		m_pWallData = new CWallData;
		m_pWallData->Init();
	}
	if (m_pBlockData == nullptr)
	{ //��Q���f�[�^
		m_pBlockData = new CBlockData;
		m_pBlockData->Init();
	}
	if (m_pFloorData == nullptr)
	{ //���f�[�^
		m_pFloorData = new CFloorData;
		m_pFloorData->Init();
	}

	//�e�N�X�`���̓ǂݍ���
	LoadAll();

	//���[�h�̐ݒ�
	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//�e�N�X�`���̔j��
	UnloadAll();
	
	if (m_pLight != nullptr)
	{
		//���C�g�̏I��
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	
	if (m_pCamera != nullptr)
	{
		//�J�����̏I��
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	
	if (m_pInputJoystick != nullptr)
	{
		//�Q�[���p�b�h�̏I��
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = nullptr;
	}
	
	if (m_pInputKeyboard != nullptr)
	{
		//�L�[�{�[�h�̏I��
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	
	if (m_pInputMouse != nullptr)
	{
		//�}�E�X�̏I��
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	if (m_pMode != nullptr)
	{
		//���̎��̃��[�h�̏I��
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	if (m_pSound != nullptr)
	{
		//�T�E���h�I��
		m_pSound->CSound::StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}
	if (m_pPlayerData != nullptr)
	{
		//�v���C���[�f�[�^�̏I��
		m_pPlayerData->Uninit();
		delete m_pPlayerData;
		m_pPlayerData = nullptr;
	}
	if (m_pPlayerData != nullptr)
	{
		//�e�f�[�^�̏I��
		m_pBulletData->Uninit();
		delete m_pBulletData;
		m_pBulletData = nullptr;
	}
	if (m_pWallData != nullptr)
	{
		//�ǃf�[�^�̏I��
		m_pWallData->Uninit();
		delete m_pWallData;
		m_pWallData = nullptr;
	}
	if (m_pBlockData != nullptr)
	{
		//��Q���f�[�^�̏I��
		m_pBlockData->Uninit();
		delete m_pBlockData;
		m_pBlockData = nullptr;
	}
	if (m_pFloorData != nullptr)
	{
		//���f�[�^�̏I��
		m_pFloorData->Uninit();
		delete m_pFloorData;
		m_pFloorData = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		//�����_���[�̏I��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInputJoystick != nullptr)
	{
		//�L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	if (m_pInputJoystick != nullptr)
	{
		//�W���C�X�e�B�b�N�̍X�V����
		m_pInputJoystick->Update();
	}

	if (m_pRenderer != nullptr)
	{
#ifdef _DEBUG
		// FPS�̃Z�b�g
		m_pRenderer->SetNumFPS(m_nCountFPS);
#endif
		//�����_���[�̍X�V����
		m_pRenderer->Update();
	}

	if (m_pCamera != nullptr)
	{
		//�J�����̂̍X�V����
		m_pCamera->Update();
	}

	if (m_pMode != nullptr)
	{
		//���̎��̃��[�h�̍X�V����
		m_pMode->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pCamera != nullptr)
	{
		//�J�����̐ݒ�
		m_pCamera->SetCamera();
	}

	if (m_pRenderer != nullptr)
	{
		//�`�揈��
		m_pRenderer->Draw();
	}
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
//=============================================================================
void CManager::LoadAll(void)
{
	//�v���C���[
	CPlayer::Load();

	//�r���{�[�h
	CBillboard::Load();

	//�G�t�F�N�g
	CEffect::Load();

	//UI
	CUi::Load();

	//��
	CWall::Load();

	//�����蔻��
	CCollision::Load();

	//�e
	CBullet::Load();

	//��Q��
	CBlock::Load();

	//��
	CFloor::Load();
}

//=============================================================================
//�e�N�X�`���̔j���܂Ƃ�
//=============================================================================
void CManager::UnloadAll(void)
{	
	//�v���C���[
	CPlayer::Unload();

	//�r���{�[�h
	CBillboard::Unload();

	//�G�t�F�N�g
	CEffect::Unload();

	//UI
	CUi::Unload();

	//��
	CWall::Unload();

	//�����蔻��
	CCollision::Unload();

	//�e
	CBullet::Unload();

	//��Q��
	CBlock::Unload();

	//��
	CFloor::Unload();
}

//=============================================================================
//���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		//���̎��̃��[�h�̏I������
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	if (m_pMode == nullptr)
	{
		m_mode = mode;

		CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);

		switch (m_mode)
		{
		case MODE_TITLE:

			//�^�C�g���̐���
			m_pMode = new CTitle;

			//�^�C�g���̏���������
			m_pMode->Init();

			break;

		case MODE_GAME:

			//�Q�[���̐���
			m_pMode = new CGame;

			//�Q�[���̏���������
			m_pMode->Init();

			break;
		}
	}
}

//=============================================================================
//�J�����̐���
//=============================================================================
void CManager::CreateCamera(void)
{
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;
		if (m_pCamera != nullptr)
		{
			m_pCamera->Init();
		}
	}
}

//=============================================================================
//���C�g�̐���
//=============================================================================
void CManager::CreateLight(void)
{
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight;
		if (m_pLight != nullptr)
		{
			m_pLight->Init();
		}
	}
}

//=============================================================================
//�t�F�[�h�̐���
//=============================================================================
void CManager::CreateFade(MODE mode)
{
	if (m_pFade != nullptr)
	{
		m_pFade->SetFade(mode);
	}
}