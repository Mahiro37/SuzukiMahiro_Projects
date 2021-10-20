//=============================================================================
//
// ��Q���f�[�^�Ǘ� [blockData.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BLOCK_DATA_H_
#define _BLOCK_DATA_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK_MAX (32)	//��Q���̍ő吔

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CBlockData
{
public:
	//�Ǐ��̍\����
	struct CreateInfo
	{
		D3DXVECTOR3 pos;				//�ʒu
		D3DXVECTOR3 size;				//�傫��
		D3DXVECTOR3 rot;				//�p�x
		D3DXVECTOR3 collisionSize;		//�����蔻��̑傫��
	};

	CBlockData();	//�R���X�g���N�^
	~CBlockData();	//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������

	CreateInfo* GetCreateInfo(const int &nCount) { return &m_aCreateInfo[nCount]; }	//�������̎擾
	int GetCreateNum(void) { return m_nCreateNum; }									//�������̎擾

private:
	CreateInfo m_aCreateInfo[BLOCK_MAX];	//�������
	int m_nCreateNum;						//�������̃J�E���g���������p
};

#endif