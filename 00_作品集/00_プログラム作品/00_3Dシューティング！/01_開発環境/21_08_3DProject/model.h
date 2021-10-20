//=============================================================================
//
// ���f������ [model.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define EDGE_NUM (4)	//�ӂ̐�

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CModel:public CScene
{
public:
	//���_�ʒu�p�̗񋓌^
	typedef enum
	{
		VER_A=0,	//����
		VER_B,		//�E��
		VER_C,		//�E��
		VER_D,		//����
		VER_MAX
	}VERTEX;

	//�����x�N�g���p�̍\����
	typedef struct
	{
		D3DXVECTOR3 a;	//����
		D3DXVECTOR3 b;	//�E��
		D3DXVECTOR3 c;	//�E��
		D3DXVECTOR3 d;	//����
		D3DXVECTOR3 ab;	//AB�x�N�g��
		D3DXVECTOR3 bc;	//BC�����x�N�g��
		D3DXVECTOR3 cd;	//CD�����x�N�g��
		D3DXVECTOR3 da;	//DA�����x�N�g��
		D3DXVECTOR3 ad;	//AD�����x�N�g��
		D3DXVECTOR3 dc;	//DC�����x�N�g��
		D3DXVECTOR3 cb;	//CB�����x�N�g��
		D3DXVECTOR3 ba;	//BA�����x�N�g��
		D3DXVECTOR3 x1;	//�����x�N�g���̎n�_
		D3DXVECTOR3 x2;	//�����x�N�g���̏I�_
		D3DXVECTOR3 direction;	//�����x�N�g��
	}VECT;

	// ���b�V�����̍\����
	typedef struct
	{
		D3DXVECTOR3 pos, nor;
		FLOAT tu, tv;
	}MESHVERTEX;

	CModel(OBJTYPE nPriority);
	~CModel();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	D3DXVECTOR3 VertexRotate(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const VERTEX &vertexType);

	void BindModel(const LPD3DXMESH &pMesh, const LPD3DXBUFFER &pBuffMat, const DWORD &nNumMat, const int &nldxModelParent = 0)
	{ m_pMesh = pMesh; m_pBuffMat = pBuffMat; m_nNumMat = nNumMat; m_nldxModelParent = nldxModelParent; }						//���f���̃e�N�X�`���ݒ�
	void BindTexture(const LPDIRECT3DTEXTURE9 &Texture, const int &nCount) { m_pTexture[nCount] = Texture; }					//�e�N�X�`���̐ݒ�
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }																		//���W�̐ݒ�
	void SetPosOld(const D3DXVECTOR3 &posOld) { m_posOld = posOld; }															//�ߋ��̍��W�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }																	//�傫���̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }																		//�p�x�̐ݒ�
	void SetVectOld(const D3DXVECTOR3 &vectOld) { m_VectOld = vectOld; }														//�ߋ��̃x�N�g���̐ݒ�
	void SetMove(const D3DXVECTOR3 &move) { m_pos += move; }																	//�ړ��ʂ̐ݒ�
	void SetWorldMatrix(const D3DXMATRIX &mtxWorld) { m_mtxWorld = mtxWorld; }													//���[���h���W�̐ݒ�

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//���݂̍��W���
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }	//�Â����W���
 	D3DXVECTOR3 GetSize(void) { return m_size; }		//�傫���̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }			//�p�x���
	D3DXVECTOR3 GetVectOld(void) { return m_VectOld; }	//�p�x���
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }	//���[���h���W�̎擾

private:
	LPD3DXMESH m_pMesh;							//���b�V�����̃|�C���^
	MESHVERTEX *m_MeshVertices;					//���b�V���̏��
	WORD *m_pIndices;							//�C���f�b�N�X��
	DWORD m_dwNumFaces;							//���b�V���̖ʂ̐�
	WORD *m_pEdges;								//�G�b�W�̐�
	LPD3DXBUFFER m_pBuffMat;					//�}�e���A�����̃|�C���^
	DWORD m_nNumMat;							//�}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;						//�s��v�Z�p
	int m_nldxModelParent;						//�e���f���̃C���f�b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//�e�N�X�`���̏��

	D3DXVECTOR3 m_pos;		//���W
	D3DXVECTOR3 m_posOld;	//�Â����W
	D3DXVECTOR3 m_size;		//�傫��
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXVECTOR3 m_VectOld;	//�ߋ��̃x�N�g��
};

#endif