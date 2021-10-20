//=============================================================================
//
// 3D�I�u�W�F�N�g���� [scene3D.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CScene3D :public CScene
{
public:
	CScene3D(OBJTYPE nPriority);	//�R���X�g���N�^
	~CScene3D();					//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }							//�ʒu�̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }							//�p�x�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }						//�T�C�Y�̐ݒ�
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }	//�e�N�X�`���̐ݒ�

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�|�C���^

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_size;		//�傫��
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
};
#endif