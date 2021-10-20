//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "animation.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CEffect :public CAnimation
{
public:
	//�G�t�F�N�g�̎�ނ̗񋓌^
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_EXPLOSION,			//�v���C���[�̔���
		TYPE_EXPLOSION_BULLET,	//�e�̔���
		TYPE_WALL_HIT,			//�e�ƕǂ̏Փ�
		TYPE_MAX
	};

	CEffect(OBJTYPE nPriority);	//�R���X�g���N�^
	~CEffect();					//�f�X�g���N�^

	static HRESULT Load(void);	//���[�h����
	static void Unload(void);	//�A�����[�h����

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	LPDIRECT3DTEXTURE9 GetTexture(const TYPE &type) { return m_apTexture[type]; }	//�e�N�X�`�����̎擾

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//�e�N�X�`���̃|�C���^�z��
};

#endif