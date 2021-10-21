//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
#include "manager.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define FADE_MAX	(30)	//�t�F�[�h�A�j���[�V�����̖���

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CStartCount;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CFade :public CScene2D
{
public:
	CFade();
	~CFade();
	static HRESULT Load(void);
	static void Unload(void);
	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE mode);
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE mode);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool GetWrapBack(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[FADE_MAX];	//�e�N�X�`���̃|�C���^�z��
	static CFade *m_pFade;								//�t�F�[�h�̃|�C���^
	static CStartCount *m_pStartCount;					//�X�^�[�g�J�E���g�̃|�C���^
	static CManager::MODE m_mode;						//���[�h�̕ۑ��p
	int m_nCntFade;										//�t�F�[�h�̃X�s�[�h�J�E���g
	int m_nCntTexture;									//�e�N�X�`����؂�ւ���J�E���g
	bool m_bWrapBack;									//�t�F�[�h�̊J����
};

#endif