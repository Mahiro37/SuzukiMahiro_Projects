//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "character.h"
#include "bullet.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CPlayer :public CCharacter
{
public:
	CPlayer(OBJTYPE Priority = OBJTYPE_PLAYER);	//�R���X�g���N�^
	~CPlayer();									//�f�X�g���N�^

	static void Load();		//���[�h����
	static void Unload();	//�A�����[�h����

	static CPlayer *Create(const TYPE &type);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	TYPE GetType(void) { return m_type; }	//��ނ̎擾

private:
	static LPD3DXMESH m_apMesh[TYPE_MAX];		//���b�V�����̃|�C���^
	static LPD3DXBUFFER m_apBuffMat[TYPE_MAX];	//�}�e���A�����̃|�C���^
	static DWORD m_NumMat[TYPE_MAX];			//�}�e���A�����̐�

	TYPE m_type;	//�v���C���[�^�C�v
};

#endif