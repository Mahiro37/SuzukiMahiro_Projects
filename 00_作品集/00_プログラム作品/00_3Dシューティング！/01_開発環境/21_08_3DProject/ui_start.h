//=============================================================================
//
// �X�^�[�gUI���� [ui_start.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_START_H_
#define _UI_START_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CUiStart :public CUi
{
public:
	CUiStart(OBJTYPE nPriority = CScene::OBJTYPE_UI_START);	//�R���X�g���N�^
	~CUiStart();											//�f�X�g���N�^

	static CUiStart *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:
	int m_nCntUi;			//UI�̍X�V�p�J�E���g
	int m_nCntGameBGM;		//�Q�[��BGM�������n�߂�܂ł̃J�E���g
	bool m_bFirstUpdate;	//1�t���[���ڂ̍X�V�����p
};

#endif