//=============================================================================
//
// ���f�[�^�Ǘ� [floorData.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _FLOOR_DATA_H_
#define _FLOOR_DATA_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FLOOR_MAX (32)	//���̍ő吔

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CFloorData
{
public:
	//�Ǐ��̍\����
	struct CreateInfo
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 size;	//�傫��
		D3DXVECTOR3 rot;	//�p�x
	};

	CFloorData();	//�R���X�g���N�^
	~CFloorData();	//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������

	CreateInfo* GetCreateInfo(const int &nCount) { return &m_aCreateInfo[nCount]; }	//�������̎擾
	int GetCreateNum(void) { return m_nCreateNum; }									//�������̎擾

private:
	CreateInfo m_aCreateInfo[FLOOR_MAX];	//�������
	int m_nCreateNum;						//�������̃J�E���g���������p
};

#endif