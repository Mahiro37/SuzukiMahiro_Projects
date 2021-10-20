//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "score.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define NUMBER_INTERVAL		(40.0f)		//�����̊Ԋu

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
int CScore::m_nScore = 0;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CScore::CScore()
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CScore::~CScore()
{
}

//*****************************************************************************
//�X�R�A�̐���
//*****************************************************************************
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fInterval, int nScore, CNumber::TYPE type)
{
	//�X�R�A�̃������m��
	CScore *pScore = new CScore;

	if (pScore != NULL)
	{
		//�X�R�A�̏���������
		pScore->Init(pos, size, fInterval, nScore, type);
	}

	return pScore;
}

HRESULT CScore::Init(void)
{
	return S_OK;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fInterval, int nScore, CNumber::TYPE type)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		//�����̃������m��
		m_apNumber[nCount] = CNumber::Create(pos, size, 0, type);

		//�����̐ݒ�
		int nNum = (nScore / (int)(pow(10, nCount))) % 10;
		m_apNumber[nCount]->SetNumber(nNum);

		//�I�u�W�F�N�g�̎�ނ̐ݒ�
		SetObjType(OBJTYPE_SCORE);

		//�����̊Ԋu��������
		pos.x -= fInterval;
	}

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//�����̏I������
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CScore::Update(void)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//�����̍X�V����
			m_apNumber[nCount]->Update();
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//�����̕`�揈��
			m_apNumber[nCount]->Draw();
		}
	}
}

//*****************************************************************************
//�X�R�A�̉��Z����
//*****************************************************************************
void CScore::AddScore(int nScore)
{
	//�X�R�A�̉��Z
	m_nScore += nScore;

	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		int nNum = (m_nScore / (int)(pow(10, nCount))) % 10;

		//�����̐ݒ�
		m_apNumber[nCount]->SetNumber(nNum);
	}
}

//*****************************************************************************
//�X�R�A�̐ݒ菈��
//*****************************************************************************
void CScore::SetScore(int nScore)
{
	//�X�R�A�̐ݒ�
	m_nScore = nScore;

	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		int nNum = (m_nScore / (int)(pow(10, nCount))) % 10;

		if (m_apNumber[nCount] != NULL)
		{
			//�����̐ݒ�
			m_apNumber[nCount]->SetNumber(nNum);
		}
	}
}

//*****************************************************************************
//�X�R�A�̎擾
//*****************************************************************************
int CScore::GetScore(void)
{
	return m_nScore;
}

//*****************************************************************************
//�����̎擾
//*****************************************************************************
CNumber *CScore::GetNumber(int nNum)
{
	return m_apNumber[nNum];
}