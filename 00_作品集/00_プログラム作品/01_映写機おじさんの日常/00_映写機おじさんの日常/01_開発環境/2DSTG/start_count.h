//=============================================================================
//
// �X�^�[�g���̃J�E���g���� [start_count.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _START_COUNT_H_
#define _START_COUNT_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CNumber;
class CUi;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CStartCount :public CScene
{
public:
	CStartCount();
	~CStartCount();
	static CStartCount *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CNumber *m_pNumber;	//�����̃|�C���^
	CUi *m_pUi;			//UI�̃|�C���^
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_size;	//�T�C�Y
	int m_nStartNumber;	//�J�n�̐���
	int m_nCounter;		//�J�E���g�̃J�E���g
	int m_nCntStageNum;	//�X�e�[�W�ԍ�
};

#endif