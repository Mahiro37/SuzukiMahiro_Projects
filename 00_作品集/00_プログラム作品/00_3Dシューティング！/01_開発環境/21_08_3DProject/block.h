//=============================================================================
//
// ��Q������ [block.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "model.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CCollision;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CBlock :public CModel
{
public:
	CBlock(OBJTYPE nPriority = OBJTYPE_BLOCK);
	~CBlock();

	static void Load();
	static void Unload();
	static CBlock *Create(const int nCreateNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void GetBlockData(void);								//��Q���f�[�^�̎擾����
	VECT GetVect(void) { return m_vect; }					//�x�N�g�����̎擾
	CCollision *GetCollision(void) { return m_pCollision; }	//�����蔻��C���X�^���X�̎擾

private:
	static LPD3DXMESH m_pMesh;			// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat;				// �}�e���A�����̐�

	int m_nCreateNum;					//������
	VECT m_vect;						//�x�N�g�����

	CCollision *m_pCollision;			//�����蔻��̃|�C���^
};

#endif