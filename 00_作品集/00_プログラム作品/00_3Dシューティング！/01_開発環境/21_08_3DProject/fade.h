//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "scene2d.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CFade :public CScene2D
{
public:
	//�t�F�[�h��Ԃ̗񋓌^
	enum FADE
	{
		FADE_NONE = 0,
		FADE_IN,		//�t�F�[�h�C��
		FADE_OUT		//�t�F�[�h�A�E�g
	};

	CFade(OBJTYPE Priority = OBJTYPE_FADE);	//�R���X�g���N�^
	~CFade();									//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������	
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void FadeIn(void);	//�t�F�[�h�C������
	void FadeOut(void);	//;�t�F�[�h�A�E�g����

	void SetFade(CManager::MODE mode);	//�t�F�[�h��Ԃ̐ݒ�

	FADE GetFadeStatus(void) { return m_FadeStatus; }	//�t�F�[�h��Ԃ̎擾

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�|�C���^

	static CManager::MODE m_mode;
	static FADE m_FadeStatus;
};
#endif
