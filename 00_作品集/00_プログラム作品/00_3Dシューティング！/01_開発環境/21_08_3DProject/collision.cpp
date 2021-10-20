//=============================================================================
//
// �����蔻��̏��� [collision.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "collision.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH CCollision::m_apMesh[TYPE_MAX] = {};
LPD3DXBUFFER CCollision::m_apBuffMat[TYPE_MAX] = {};

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CCollision::CCollision(OBJTYPE nPriority) :CModel(nPriority)
{
	m_CollisionType = TYPE_NONE;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CCollision::~CCollision()
{
}

//*****************************************************************************
//���[�h
//*****************************************************************************
void CCollision::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�|���S���̍쐬
	D3DXCreatePolygon(
		pDevice,						//�f�o�C�X���
		10.0f,							//�ӂ̒���
		4,								//�ӂ̐�
		&m_apMesh[TYPE_POLYGON],		//���b�V�����
		&m_apBuffMat[TYPE_POLYGON]);	//�o�b�t�@���

	//���̍쐬
	D3DXCreateBox(
		pDevice,					//�f�o�C�X���
		1.0f,						//����
		1.0f,						//����
		1.0f,						//����
		&m_apMesh[TYPE_BOX],		//���b�V�����
		&m_apBuffMat[TYPE_BOX]);	//�o�b�t�@���

	//���̍쐬
	D3DXCreateSphere(
		pDevice,					//�f�o�C�X���
		1.0f,						//��O�̉~�̔��a
		10,							//�X���C�X�̐�
		10,							//�X�^�b�N��
		&m_apMesh[TYPE_SPHERE],		//���b�V�����
		&m_apBuffMat[TYPE_SPHERE]);	//�o�b�t�@���

	//�~���̍쐬
	D3DXCreateCylinder(
		pDevice,						//�f�o�C�X���
		1.0f,							//��O�̉~�̔��a
		1.0f,							//���̉~�̔��a
		1.0f,							//�~���̒���
		10,								//�X���C�X(�~�̒��_��)
		1,								//�X�^�b�N(�~���̕�����)
		&m_apMesh[TYPE_CYLINDER],		//���b�V�����
		&m_apBuffMat[TYPE_CYLINDER]);	//�o�b�t�@���
}

//*****************************************************************************
//�A�����[�h
//*****************************************************************************
void CCollision::Unload()
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apMesh[nCount] != NULL)
		{
			//���b�V���̔j��
			m_apMesh[nCount]->Release();
			m_apMesh[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apBuffMat[nCount] != NULL)
		{
			//�o�b�t�@�̔j��
			m_apBuffMat[nCount]->Release();
			m_apBuffMat[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//�����蔻��̐���
//*****************************************************************************
CCollision * CCollision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, TYPE type)
{
	CCollision *pCollision = new CCollision;

	if (pCollision != NULL)
	{
		//�����蔻����̐ݒ�
		pCollision->m_CollisionType = type;
		pCollision->SetPos(pos);
		pCollision->SetSize(size);
		pCollision->SetRot(rot);

		//�����蔻��̏���������
		pCollision->Init();

		return pCollision;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CCollision::Init()
{
	//���f�����̐ݒ�
	BindModel(m_apMesh[m_CollisionType], m_apBuffMat[m_CollisionType], 1);

	//���f�����̏�����
	CModel::Init();

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CCollision::Uninit(void)
{
	CModel::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CCollision::Update(void)
{
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CCollision::Draw(void)
{
#ifdef _DEBUG
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�F�̐ݒ�
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_apBuffMat[m_CollisionType]->GetBufferPointer();
	mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	//���C���[�t���[���ŕ`��
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�`��
	CModel::Draw();

	//���C���[�t���[�������ǂ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
}

//*****************************************************************************
//��`�̓����蔻��
//*****************************************************************************
bool CCollision::RectangleCollision(const D3DXVECTOR3 &pPos1, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &pPos2, const D3DXVECTOR3 &size2)
{
	//�Z----------------------------------�Z
	// pPos1    : �����鑤�̈ʒu
	// size1    : �����鑤�̃T�C�Y
	// pPos2    : ���Ă��鑤�̈ʒu
	// size2    : ���Ă��鑤�̃T�C�Y
	// �߂�l   : �����������ǂ�����Ԃ�
	//�Z----------------------------------�Z

	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pPos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pPos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pPos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pPos2;   //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	// �����������ǂ�����Ԃ�
	return bHit;
}

//*****************************************************************************
//���̓����蔻��
//*****************************************************************************
bool CCollision::SphereCollision(const D3DXVECTOR3 &pos1, const float &size1, const D3DXVECTOR3 &pos2, const float &size2)
{
	//�Z-------------------------------------------------�Z
	// pos1     : �Ԃ��鑤�̈ʒu
	// size1    : �Ԃ��鑤�̃T�C�Y
	// pos2     : �Ԃ����鑤�̈ʒu
	// size2    : �Ԃ����鑤�̃T�C�Y
	// �߂�l   : �Ԃ��鑤���~�̒��ɓ����Ă��邩�ǂ���
	//�Z-------------------------------------------------�Z

	float distance = powf(pos1.x - pos2.x, 2.0f) + powf(pos1.y - pos2.y, 2.0f) + powf(pos1.z - pos2.z, 2.0f); //�ʒu
	float radius = powf(size1 + size2, 2.0f); //���a

	if (distance < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************
//�����蔻��(��`�Ɖ~�`)
//*****************************************************************************
bool CCollision::RectangleCircularCollision(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &RectangleSize, const float &RectangleRadian, const D3DXVECTOR3 &CircularPos, const float &CircularRadius)
{
	//��`�̊p�x���O�ɂ������̉~�`�̍��W�����߂�
	D3DXVECTOR3 NewCircularPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NewCircularPos.x = (float)(cos(RectangleRadian) * (CircularPos.x - RectanglePos.x) -
		sin(RectangleRadian) * (CircularPos.z - RectanglePos.z) + RectanglePos.x);
	NewCircularPos.z = (float)(sin(RectangleRadian) * (CircularPos.x - RectanglePos.x) +
		cos(RectangleRadian) * (CircularPos.z - RectanglePos.z) + RectanglePos.z);

	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2) - CircularRadius) ||
		NewCircularPos.x >(RectanglePos.x + (RectangleSize.x / 2) + CircularRadius) ||
		NewCircularPos.z < (RectanglePos.z - (RectangleSize.z / 2) - CircularRadius) ||
		NewCircularPos.z >(RectanglePos.z + (RectangleSize.z / 2) + CircularRadius))
	{ //�u��`�̊O�g + �~�̔��a�v�͈̔͂ɓ����Ă��Ȃ��Ƃ�
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.z < (RectanglePos.z - (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z - (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̍���̔���
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.z < (RectanglePos.z - (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z - (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̉E��̔���
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.z >(RectanglePos.z + (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z + (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̍����̔���
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.z > (RectanglePos.z + (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z + (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̉E���̔���
		return false;
	}

	return true;
}

//*****************************************************************************
//�ǐ�p�̓����蔻��(��`�Ƌ�`)
//*****************************************************************************
bool CCollision::WallCollision(const VECT &WallVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &fPlayerRot)
{
	//�S���_�̍��W�p�ϐ�
	D3DXVECTOR3 ver[MAX_VERTEX_SQUARE];
	memset(&ver, 0, sizeof(ver));

	//�v���C���[��2���_�̍��W(X,Z)�����߂�
	ver[0] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + ((PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + ((PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);
	ver[1] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + (-(PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + (-(PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);

	//D�n�_����e���_(P�n�_)�ւ̃x�N�g���p�ϐ�(DP�x�N�g��)
	D3DXVECTOR3 Vdp[VERTEX_COLLISION_NUM];
	memset(&Vdp, 0, sizeof(Vdp));

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//DP�x�N�g�������߂�
		Vdp[nCount] = ver[nCount] - WallVect.d;
	}

	//DC�x�N�g����DP�x�N�g���̊O�ώ擾�p�ϐ�
	D3DXVECTOR3 vCross[VERTEX_COLLISION_NUM];
	memset(&vCross, 0, sizeof(vCross));

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//DC�x�N�g����DP�x�N�g���̊O�ς����߂�
		D3DXVec3Cross(&vCross[nCount], &WallVect.dc, &Vdp[nCount]);
	}

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//�O�ς����Ȃ�ΉE���A���Ȃ�΍����A0�Ȃ璼����
		if (vCross[nCount].y <= 0)
		{ //�O�ς��O�ȉ��̂Ƃ�
			return true;
		}
	}

	return false;
}

//*****************************************************************************
//��Q����p�̓����蔻��(��`�Ƌ�`)
//*****************************************************************************
void CCollision::BlockCollision(bool &pbHit, VECT &dirVect, const D3DXVECTOR3 &BlockRot, const VECT &BlockVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &fPlayerRot, const D3DXVECTOR3 &SlideVect)
{
	//�S���_�̍��W�p�ϐ�
	D3DXVECTOR3 ver[VERTEX_COLLISION_NUM] = {};
	memset(&ver, 0, sizeof(ver));

	//�v���C���[��2���_�̍��W(X,Z)�����߂�
	ver[0] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + ((PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + ((PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);
	ver[1] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + (-(PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + (-(PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);

	//�e�ƒ��_�Ƃ̋����p
	CCollision::DISTANCE DistanceData[VER_MAX];
	memset(&DistanceData, 0, sizeof(DistanceData));

	//�e���_�̈ʒu����
	DistanceData[VER_A].pos = BlockVect.a;
	DistanceData[VER_B].pos = BlockVect.b;
	DistanceData[VER_C].pos = BlockVect.c;
	DistanceData[VER_D].pos = BlockVect.d;

	//�e���_����e�̒��S�܂ł̋������v�Z����
	DistanceData[VER_A].length = D3DXVec3Length(&(PlayerPos - BlockVect.a));
	DistanceData[VER_B].length = D3DXVec3Length(&(PlayerPos - BlockVect.b));
	DistanceData[VER_C].length = D3DXVec3Length(&(PlayerPos - BlockVect.c));
	DistanceData[VER_D].length = D3DXVec3Length(&(PlayerPos - BlockVect.d));

	//�����̐ݒ�(��)
	DistanceData[VER_A].rank = 1;
	DistanceData[VER_B].rank = 2;
	DistanceData[VER_C].rank = 3;
	DistanceData[VER_D].rank = 4;

	//�v���C���[�̂Q���_���q�����x�N�g���̌v�Z
	D3DXVECTOR3 PlayerVerVect = ZeroVector3;
	PlayerVerVect.x = roundf(ver[1].x) - roundf(ver[0].x);
	PlayerVerVect.y = roundf(ver[1].y) - roundf(ver[0].y);
	PlayerVerVect.z = roundf(ver[1].z) - roundf(ver[0].z);

	//�v���C���[�̂Q���_�̂����̂P���_�Ə�Q���̂P���_���q�����x�N�g���̑���p
	D3DXVECTOR3 PlayerBlockVect[MAX_VERTEX_SQUARE];
	memset(&PlayerBlockVect, 0, sizeof(PlayerBlockVect));

	for (int nCount = 0; nCount < MAX_VERTEX_SQUARE; nCount++)
	{
		//�v���C���[�̂Q���_�̂����̂P���_�Ə�Q���̂P���_���q�����x�N�g���̌v�Z
		PlayerBlockVect[nCount] = DistanceData[nCount].pos - ver[0];

		float a = D3DXVec3Dot(&PlayerVerVect, &PlayerBlockVect[nCount]);

		//�v���C���[�̂Q���_���q�����x�N�g���̒������v�Z
		float fPlayerVerVectLength = D3DXVec3Length(&PlayerVerVect);

		//�v���C���[�̂Q���_�̂����̂P���_�Ə�Q���̂P���_���q�����x�N�g���̒����̌v�Z
		float fPlayerBlockVectLength = D3DXVec3Length(&PlayerBlockVect[nCount]);

		if (a <= fPlayerVerVectLength * fPlayerBlockVectLength + 1.5f && a >= fPlayerVerVectLength * fPlayerBlockVectLength - 1.5f)
		{ //�Q�̃x�N�g���̓��ς��O�̂Ƃ�
			if (fPlayerVerVectLength >= fPlayerBlockVectLength && SlideVect == ZeroVector3)
			{ //�v���C���[�̂Q���_���q�����x�N�g���̒������A�v���C���[�̂Q���_�̂����̂P���_�Ə�Q���̂P���_���q�����x�N�g���̒����̂ق����Z���Ƃ�				
				pbHit = true;
				return;
			}
		}
	}

	//��ԋ߂��Q���_�̕����x�N�g�����Z�o
	DirectionVect(BlockRot, ZeroVector3, DistanceData, dirVect);

	//X�n�_(�����x�N�g���̎n�_)����e���_(P�n�_)�ւ̃x�N�g���p�ϐ�(XP�x�N�g��)
	D3DXVECTOR3 Vxp[MAX_VERTEX_SQUARE];
	memset(&Vxp, 0, sizeof(Vxp));

	//�����x�N�g����XP�x�N�g���̊O�ώ擾�p�ϐ�
	D3DXVECTOR3 vCross[MAX_VERTEX_SQUARE];
	memset(&vCross, 0, sizeof(vCross));

	//�����x�N�g���i�[�p
	D3DXVECTOR3 DirVec[MAX_VERTEX_SQUARE];
	memset(&DirVec, 0, sizeof(DirVec));

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//XP�x�N�g�������߂�
		Vxp[0] = ver[nCount] - BlockVect.a;
		Vxp[1] = ver[nCount] - BlockVect.d;
		Vxp[2] = ver[nCount] - BlockVect.c;
		Vxp[3] = ver[nCount] - BlockVect.b;

		//�����x�N�g���̑��
		DirVec[0] = BlockVect.ad;
		DirVec[1] = BlockVect.dc;
		DirVec[2] = BlockVect.cb;
		DirVec[3] = BlockVect.ba;

		int nCntHit = 0;	//�S�ӂ��ꂼ��̊O�ς��O��菬�����Ƃ��̉񐔃J�E���g�p

		for (int nCnt = 0; nCnt < MAX_VERTEX_SQUARE; nCnt++)
		{
			//�����x�N�g����XP�x�N�g���̊O�ς����߂�
			D3DXVec3Cross(&vCross[nCnt], &DirVec[nCnt], &Vxp[nCnt]);

			//�O�ς����Ȃ�ΉE���A���Ȃ�΍����A0�Ȃ璼����
			if (vCross[nCnt].y <= 0)
			{ //�O�ς��O��菬�����Ƃ�
				//�J�E���g��i�߂�
				nCntHit++;
			}
		}

		if (nCntHit >= MAX_VERTEX_SQUARE)
		{ //�O�ς��O��菬�����Ƃ���MAX_VERTEX_SQUARE�ȏゾ�����Ƃ�
			pbHit = true;
			return;
		}
	}
}

//*****************************************************************************
// �v���C���[�̕ǂ���x�N�g���v�Z
//*****************************************************************************
D3DXVECTOR3 CCollision::SlideVect(const D3DXVECTOR3 &PlayerMove, const D3DXVECTOR3 &WallVect)
{
	//�@���x�N�g���̌v�Z
	D3DXVECTOR3 vCross = ZeroVector3;
	D3DXVECTOR3 vect = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Cross(&vCross, &vect, &WallVect);

	//�@���x�N�g���𐳋K��
	D3DXVECTOR3 NormalizedNormalVect = ZeroVector3;
	D3DXVec3Normalize(&NormalizedNormalVect, &vCross);

	//�ǂ���x�N�g����Ԃ�
	return PlayerMove - (D3DXVec3Dot(&PlayerMove, &NormalizedNormalVect)) * NormalizedNormalVect;
}

//*****************************************************************************
// ���˃x�N�g���v�Z
//*****************************************************************************
D3DXVECTOR3 CCollision::ReflectionVect(const D3DXVECTOR3 &MoveVect, const D3DXVECTOR3 &DirectionVect, const D3DXVECTOR3 &rot)
{
	//�@���x�N�g���̌v�Z
	D3DXVECTOR3 vCross = ZeroVector3;
	D3DXVECTOR3 vect = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Cross(&vCross, &vect, &DirectionVect);

	//�@���x�N�g���𐳋K��
	D3DXVECTOR3 NormalizedNormalVect = ZeroVector3;
	D3DXVec3Normalize(&NormalizedNormalVect, &vCross);

	//���˃x�N�g����Ԃ�
	return MoveVect - 2 * (D3DXVec3Dot(&MoveVect, &NormalizedNormalVect)) * NormalizedNormalVect;
}

//*****************************************************************************
// �S���_�|���S���̕����x�N�g���v�Z
//*****************************************************************************
void CCollision::DirectionVect(const D3DXVECTOR3 &rot, D3DXVECTOR3 &pVect, DISTANCE* distanceData, VECT &dirVect)
{
	DISTANCE Distance[VER_MAX];
	memset(Distance, 0, sizeof(Distance));

	for (int nCount = 0; nCount < VER_MAX; nCount++)
	{
		Distance[nCount] = distanceData[nCount];
	}

	//�����������ɂ���(�Q�񓯂�����������)
	for (int nCnt = 0; nCnt < VER_MAX; nCnt++)
	{
		for (int nCount = 0; nCount < VER_MAX; nCount++)
		{
			if (Distance[nCnt].length > Distance[nCount].length)
			{
				if (Distance[nCnt].rank < Distance[nCount].rank)
				{
					int nKeep = Distance[nCnt].rank;
					Distance[nCnt].rank = Distance[nCount].rank;
					Distance[nCount].rank = nKeep;
				}
			}
		}
	}
	for (int nCnt = 0; nCnt < VER_MAX; nCnt++)
	{
		for (int nCount = 0; nCount < VER_MAX; nCount++)
		{
			if (Distance[nCnt].length > Distance[nCount].length)
			{
				if (Distance[nCnt].rank < Distance[nCount].rank)
				{
					int nKeep = Distance[nCnt].rank;
					Distance[nCnt].rank = Distance[nCount].rank;
					Distance[nCount].rank = nKeep;
				}
			}
		}
	}

	//�e���ʂ��Ƃ̈ʒu����p�ϐ�
	D3DXVECTOR3 Pos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	D3DXVECTOR3	Pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	D3DXVECTOR3	Pos3 = D3DXVECTOR3(0.0f, 0.0f, 0.0);

	//�e���ʂ��Ƃ̋�������p�ϐ�
	float fLength1 = 0.0f;
	float fLength2 = 0.0f;
	float fLength3 = 0.0f;

	//�e���ʂ��Ƃ̔z��ԍ��擾�p�ϐ�
	int nType1 = 0;
	int nType2 = 0;
	int nType3 = 0;

	for (int nCount = 0; nCount < VER_MAX; nCount++)
	{
		if (Distance[nCount].rank == 1)
		{
			Pos1 = Distance[nCount].pos;
			fLength1 = Distance[nCount].length;
			nType1 = nCount;
		}
		else if (Distance[nCount].rank == 2)
		{
			Pos2 = Distance[nCount].pos;
			fLength2 = Distance[nCount].length;
			nType2 = nCount;
		}
		else if (Distance[nCount].rank == 3)
		{
			Pos3 = Distance[nCount].pos;
			fLength3 = Distance[nCount].length;
			nType3 = nCount;
		}
	}

	if (fLength2 == fLength3)
	{
		dirVect.direction = ZeroVector3;
		dirVect.x1 = Pos1;
		dirVect.x2 = ZeroVector3;
	}
	else if (nType1 == VER_A && nType2 == VER_D)
	{
		dirVect.direction = Pos2 - Pos1;
		dirVect.x1 = Pos1;
		dirVect.x2 = Pos2;
	}
	else if (nType1 == VER_D && nType2 == VER_A)
	{
		dirVect.direction = Pos1 - Pos2;
		dirVect.x1 = Pos2;
		dirVect.x2 = Pos1;
	}
	else if (nType1 > nType2)
	{
		dirVect.direction = Pos2 - Pos1;
		dirVect.x1 = Pos1;
		dirVect.x2 = Pos2;
	}
	else if (nType1 < nType2)
	{
		dirVect.direction = Pos1 - Pos2;
		dirVect.x1 = Pos2;
		dirVect.x2 = Pos1;
	}

	//���˃x�N�g���̌v�Z
	pVect = ReflectionVect(pVect, dirVect.direction, rot);
}