//=============================================================================
//
// �r���{�[�h���� [billboard.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CBillboard : public CScene
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_PLAYER1_BULLET,	//�e(�v���C���[�P)
		TYPE_PLAYER1_BOMB,		//�{��(�v���C���[�P)
		TYPE_PLAYER2_BULLET,	//�e(�v���C���[�Q)
		TYPE_PLAYER2_BOMB,		//�{��(�v���C���[�Q)
		TYPE_MAX
	};

	CBillboard(OBJTYPE nPriority);	//�R���X�g���N�^
	~CBillboard();					//�f�X�g���N�^

	static HRESULT Load(void);	//���[�h����
	static void Unload(void);	//�A�����[�h����

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	//�e��ݒ�
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }												//�ʒu�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }											//�傫���̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }												//�p�x�̐ݒ�
	void SetCol(const D3DXCOLOR &col) { m_col = col; }													//�F�̐ݒ�
	void SetType(const TYPE &pTexture) { m_type = pTexture; }											//�e�N�X�`���̎�ނ̐ݒ�
	void SetTexture(const float &fTexX, const float &fTexY, const float &fTexX2, const float &fTexY2)
	{ m_fTexX = fTexX; m_fTexX2 = fTexX2; m_fTexY = fTexY; m_fTexY2 = fTexY2; }							//�e�N�X�`�����W�̐ݒ�

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//�ʒu�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; }	//�傫���̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//�p�x�̎擾
	D3DXCOLOR GetCol(void) { return m_col; }		//�F�̎擾
	TYPE GetType(void) { return m_type; }			//��ނ̎擾

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^

	static TYPE m_type;		//���
	D3DXVECTOR3 m_pos;		//�ʒu���W
	D3DXVECTOR3 m_size;		//�T�C�Y
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXCOLOR m_col;		//�F
	float m_fTexX;			//�e�N�X�`��X���W
	float m_fTexX2;			//�e�N�X�`��X2���W
	float m_fTexY;			//�e�N�X�`��Y���W
	float m_fTexY2;			//�e�N�X�`��Y2���W
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
};
#endif