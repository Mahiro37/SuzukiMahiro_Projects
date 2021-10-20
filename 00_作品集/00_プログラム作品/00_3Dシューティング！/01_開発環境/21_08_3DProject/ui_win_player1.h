//=============================================================================
//
// �v���C���[�P�̏���UI���� [ui_win_player1.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_WIN_PLAYER1_H_
#define _UI_WIN_PLAYER1_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CUiWinPlayer1 :public CUi
{
public:
	CUiWinPlayer1(OBJTYPE nPriority = CScene::OBJTYPE_UI_WIN_PLAYER_1);	//�R���X�g���N�^
	~CUiWinPlayer1();													//�f�X�g���N�^

	static CUiWinPlayer1 *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:
	int m_nCntUi;	//UI�̍X�V�p�J�E���g
};

#endif