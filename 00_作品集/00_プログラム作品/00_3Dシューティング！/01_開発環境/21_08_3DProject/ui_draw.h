//=============================================================================
//
// ��������UI���� [ui_draw.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_DRAW_H_
#define _UI_DRAW_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CUiDraw :public CUi
{
public:
	CUiDraw(OBJTYPE nPriority = CScene::OBJTYPE_UI_DRAW);	//�R���X�g���N�^
	~CUiDraw();												//�f�X�g���N�^

	static CUiDraw *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:
	int m_nCntUi;	//UI�̍X�V�p�J�E���g
};

#endif