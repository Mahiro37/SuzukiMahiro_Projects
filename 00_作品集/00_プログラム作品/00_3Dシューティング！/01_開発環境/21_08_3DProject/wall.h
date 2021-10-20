//=============================================================================
//
// �Ǐ��� [wall.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

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
class CWall :public CModel
{
public:
	//�ǂ̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BACK,		//��
		TYPE_RIGHT,		//�E
		TYPE_FRONT,		//��O
		TYPE_LEFT,		//��
		TYPE_MAX
	}TYPE;

	CWall(OBJTYPE nPriority = OBJTYPE_WALL);	//�R���X�g���N�^
	~CWall();									//�f�X�g���N�^

	static void Load();		//���[�h����
	static void Unload();	//�A�����[�h����

	static CWall *Create(const int &nCreateNum);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void GetWallData(void);									//�ǃf�[�^�̎擾����
	TYPE GetType(void) { return m_type; }					//��ނ̎擾
	VECT GetVect(void) { return m_vect; }					//�x�N�g�����̎擾
	CCollision *GetCollision(void) { return m_pCollision; }	//�����蔻��C���X�^���X�̎擾

private:
	static LPD3DXMESH m_pMesh;			// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat;				// �}�e���A�����̐�

	TYPE m_type;						//���
	int m_nCreateNum;					//������
	VECT m_vect;						//�x�N�g�����

	CCollision *m_pCollision;			//�����蔻��̃|�C���^
};

#endif