//=============================================================================
//
// 2D�I�u�W�F�N�g���� [scene2D.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CScene2D :public CScene
{
public:
	CScene2D(OBJTYPE nPriority);	//�R���X�g���N�^
	~CScene2D();					//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��


	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }							//�ʒu�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }						//�傫���̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }							//�p�x�̐ݒ�
	void SetCol(const D3DXCOLOR &color) { m_color = color; }						//�F�̐ݒ�
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }	//�e�N�X�`���̐ݒ�

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//�ʒu�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; }	//�ʒu�̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//�ʒu�̎擾
	D3DXCOLOR GetCol(void) { return m_color; }		//�F�̎擾

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	//�e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�|�C���^

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_size;	//�傫��
	D3DXVECTOR3 m_rot;	//�p�x
	D3DXCOLOR m_color;	//�F
	float m_fAngle;		//�p�x
	float m_fLength;	//���a
};

#endif // !_SCENE2D_H_
