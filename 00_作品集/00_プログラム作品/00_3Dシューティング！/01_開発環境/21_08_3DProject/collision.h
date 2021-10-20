//=============================================================================
//
// �����蔻��̏��� [collision.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "model.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CCollision :public CModel
{
public:
	//�����蔻��^�C�v�̗񋓌^
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_POLYGON,	//�|���S��
		TYPE_BOX,		//��
		TYPE_SPHERE,	//��
		TYPE_CYLINDER,	//�~��
		TYPE_MAX
	};

	//�e�ƒ��_�Ƃ̋����Ɏg���\����
	struct DISTANCE
	{
		D3DXVECTOR3 pos;	//�ʒu
		float length;		//����
		int rank;			//����
	};

	CCollision(OBJTYPE nPriority = OBJTYPE_COLLISION);	//�R���X�g���N�^
	~CCollision();										//�f�X�g���N�^

	static void Load();		//���[�h����
	static void Unload();	//�A�����[�h����

	static CCollision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, TYPE type);	//��������

	HRESULT Init();		//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	static bool RectangleCollision(const D3DXVECTOR3 &pPos1, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &pPos2, const D3DXVECTOR3 &size2);
	static bool SphereCollision(const D3DXVECTOR3 &pos1, const float &size1, const D3DXVECTOR3 &pos2, const float &size2);
	static bool RectangleCircularCollision(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &RectangleSize, const float &RectangleRadian, const D3DXVECTOR3 &CircularPos, const float &CircularRadius);
	bool WallCollision(const VECT &WallVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &fPlayerRot);
	void BlockCollision(bool &pbHit, VECT &dirVect, const D3DXVECTOR3 &BlockRot, const VECT &BlockVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &PlayerRot, const D3DXVECTOR3 &SlideVect);
	D3DXVECTOR3 SlideVect(const D3DXVECTOR3 &PlayerMove, const D3DXVECTOR3 &WallVect);
	D3DXVECTOR3 ReflectionVect(const D3DXVECTOR3 &MoveVect, const D3DXVECTOR3 &DirectionVect, const D3DXVECTOR3 &rot);
	void DirectionVect(const D3DXVECTOR3 &rot, D3DXVECTOR3 &pVect, DISTANCE* distanceData, VECT &dirVect);

private:
	static LPD3DXMESH m_apMesh[TYPE_MAX];		//���b�V�����̃|�C���^
	static LPD3DXBUFFER m_apBuffMat[TYPE_MAX];	//�}�e���A�����̃|�C���^
	TYPE m_CollisionType;						//�����蔻��̃^�C�v
};
#endif