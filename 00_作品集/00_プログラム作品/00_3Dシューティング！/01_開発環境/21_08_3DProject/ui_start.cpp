//=============================================================================
//
// �X�^�[�gUI���� [ui_start.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui_start.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define INIT_GAME_BGM_COUNT (60)	//�Q�[���X�^�[�g���Ă���Q�[��BGM��������܂ł̃J�E���g��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CUiStart::CUiStart(OBJTYPE nPriority) :CUi(nPriority)
{
	m_nCntUi = 0;
	m_nCntGameBGM = 0;
	m_bFirstUpdate = false;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CUiStart::~CUiStart()
{
}

//*****************************************************************************
//�X�^�[�gUI�̐���
//*****************************************************************************
CUiStart* CUiStart::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//�X�^�[�gUI�̃������m��
	CUiStart *pUiStart = new CUiStart;

	if (pUiStart != nullptr)
	{
		//�X�^�[�gUI���̐ݒ�
		pUiStart->SetPos(pos);
		pUiStart->SetSize(size);

		//UI�̏���������
		pUiStart->Init();

		return pUiStart;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CUiStart::Init(void)
{
	//�e�N�X�`���̐ݒ�
	BindTexture(GetTexture(TYPE_START));

	//�F�̐ݒ�
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//UI�̏�����
	CUi::Init();

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CUiStart::Uninit(void)
{
	//�w�肵��OBJTYPE�݂̂��X�V����
	SetUpdateType(OBJTYPE_MAX, NULL);

	//UI�̏I������
	CUi::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CUiStart::Update(void)
{
	if (m_bFirstUpdate == false)
	{ //�X�V������1�t���[���ڂ̂Ƃ�
		//�����true�ɂ���
		m_bFirstUpdate = true;

		//�T�E���h�̐���
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_START);
	}

	if (m_nCntUi < 120 && m_nCntGameBGM < INIT_GAME_BGM_COUNT)
	{ //�J�E���g���K��l��菬�����Ƃ�
		//�J�E���g��i�߂�
		m_nCntUi++;
	}

	if (m_nCntUi == 60)
	{ //�J�E���g���K��l�𒴂����Ƃ�
		//�F�̐ݒ�
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (m_nCntUi == 120)
	{ //�J�E���g���K��l��菬�����Ƃ�
		//�F�̐ݒ�
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (m_nCntGameBGM < INIT_GAME_BGM_COUNT && m_nCntUi > 60)
	{ //�J�E���g���K��l��菬�����Ƃ�
		//�J�E���g��i�߂�
		m_nCntGameBGM++;
	}

	if (m_nCntGameBGM >= INIT_GAME_BGM_COUNT)
	{ //�J�E���g���K��l�𒴂����Ƃ�
		//�T�E���h�̐���
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_GAME);
	}

	if (m_nCntUi >= 120 && m_nCntGameBGM >= INIT_GAME_BGM_COUNT)
	{ //�ǂ���̃J�E���g���K��l�𒴂����Ƃ�
		//�I������
		Uninit();
		return;
	}

	//UI�̍X�V����
	CUi::Update();
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CUiStart::Draw(void)
{
	//UI�̕`�揈��
	CUi::Draw();
}