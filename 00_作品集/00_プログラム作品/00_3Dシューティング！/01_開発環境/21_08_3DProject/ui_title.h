//=============================================================================
//
// �^�C�g��UI���� [ui_title.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_TITLE_H_
#define _UI_TITLE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CUiTitle :public CUi
{
public:
	CUiTitle(OBJTYPE nPriority = CScene::OBJTYPE_UI_TITLE);	//�R���X�g���N�^
	~CUiTitle();											//�f�X�g���N�^

	static CUiTitle *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
};

#endif