//=============================================================================
//
// �ǃf�[�^�Ǘ� [wallData.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _WALL_DATA_H_
#define _WALL_DATA_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WALL_MAX (32)	//�ǂ̍ő吔

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CWallData
{
public:
	//�Ǐ��̍\����
	struct CreateInfo
	{
		int nType;					//���
		D3DXVECTOR3 pos;			//�ʒu
		D3DXVECTOR3 size;			//�傫��
		D3DXVECTOR3 rot;			//�p�x
		D3DXVECTOR3 collisionSize;	//�����蔻��̑傫��
	};

	CWallData();	//�R���X�g���N�^
	~CWallData();	//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������

	CreateInfo* GetCreateInfo(const int &nCount) { return &m_aCreateInfo[nCount]; }	//�������̎擾
	int GetCreateNum(void) { return m_nCreateNum; }									//�������̎擾

private:
	CreateInfo m_aCreateInfo[WALL_MAX];	//�������
	int m_nCreateNum;					//�������̃J�E���g���������p
};

#endif