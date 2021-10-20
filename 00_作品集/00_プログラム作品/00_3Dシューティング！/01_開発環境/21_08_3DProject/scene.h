//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_OBJECT (256)			//�I�u�W�F�N�g�̍ő吔
#define MAX_VERTEX_SQUARE (4)		//��`�̒��_��
#define VERTEX_COLLISION_NUM (2)	//�����蔻�莞�̒��_��

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CScene
{
public:
	//�I�u�W�F�N�g�^�C�v�̗񋓌^
	enum OBJTYPE
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BULLET,						//�o���b�g
		OBJTYPE_PLAYER,						//�v���C���[
		OBJTYPE_WALL,						//��
		OBJTYPE_BLOCK,						//��Q��
		OBJTYPE_FLOOR,						//��
		OBJTYPE_COLLISION,					//�����蔻��
		OBJTYPE_EFFECT_EXPLOSION,			//�����G�t�F�N�g
		OBJTYPE_EFFECT_EXPLOSION_BULLET,	//�e�̔����G�t�F�N�g
		OBJTYPE_UI_START,					//�X�^�[�gUI
		OBJTYPE_UI_WIN_PLAYER_1,			//�v���C���[�P����UI
		OBJTYPE_UI_WIN_PLAYER_2,			//�v���C���[�Q����UI
		OBJTYPE_UI_DRAW,					//��������UI
		OBJTYPE_UI_TITLE,					//�^�C�g��UI
		OBJTYPE_FADE,						//�t�F�[�h
		OBJTYPE_MAX
	};

	CScene(OBJTYPE nPriority = OBJTYPE_NONE);	//�R���X�g���N�^
	virtual ~CScene();							//�f�X�g���N�^

	virtual HRESULT Init(void) = 0;	//����������
	virtual void Uninit(void) = 0;	//�I������
	virtual void Update(void) = 0;	//�X�V����
	virtual void Draw(void) = 0;	//�`�揈��

	static void ReleaseAll(void);							//�S�Ẵ������̊J������
	static void DesignationReleaseAll(OBJTYPE type);		//�I���������̈ȊO�̉������
	static void UpdateAll(void);							//�S�Ă̍X�V����
	static void DesignationUpdateAll(const OBJTYPE* type);	//�I������OBJTYPE�݂̂̍X�V����
	static void DrawAll(void);								//�S�Ă̕`�揈��

	void SetObjType(const OBJTYPE &objType){ m_objType = objType; }	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	static void SetUpdateType(const OBJTYPE type, ...);				//�X�V����I�u�W�F�N�g�^�C�v�̐ݒ�(�Ō�̈����ɂ͐�΂�NULL������)

	OBJTYPE GetObjType(void) { return m_objType; }	//�I�u�W�F�N�g�^�C�v�̎擾
	static CScene *GetScene(const int &nPriority);	//�V�[���̎擾
	static void GetUpdateType(OBJTYPE* type);		//�X�V����I�u�W�F�N�g�^�C�v�̎擾

protected:
	void Release(void) { m_bDeath = true; }	//�������̊J������

private:
	OBJTYPE m_objType;								//�I�u�W�F�N�g�̎��
	static CScene *m_pTop[OBJTYPE_MAX];				//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[OBJTYPE_MAX];				//���݂̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;								//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;								//���̃I�u�W�F�N�g�ւ̃|�C���^
	int m_nPriority;								//�`�揇��
	bool m_bDeath;									//���S�t���O
	static int m_nCntList;							//���X�g�̃J�E���g
	static OBJTYPE m_UpdateTypeList[OBJTYPE_MAX];	//�X�V����I�u�W�F�N�g�^�C�v
};

#endif