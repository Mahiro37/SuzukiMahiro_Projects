//=============================================================================
//
// ������ [floor.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene3d.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CFloor :public CScene3D
{
public:
	CFloor(OBJTYPE Priority = CScene::OBJTYPE_FLOOR);	//�R���X�g���N�^
	~CFloor();											//�f�X�g���N�^

	static void Load();		//���[�h����
	static void Unload();	//�A�����[�h����

	static CFloor *Create(const int &nCreateNum);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void GetFloorData(void);	//���f�[�^�̎擾����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^

	int m_nCreateNum;	//������
};

#endif