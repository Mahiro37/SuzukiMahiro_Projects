//=============================================================================
//
// �I�u�W�F�N�g���� [scene2d.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CScene2D :public CScene
{
public:
	//�A�j���[�V���������̗񋓌^
	typedef enum
	{
		ANIMATION_REPEAT = 0,	//���s�[�g����
		ANIMATION_UNREPEAT		//���s�[�g���Ȃ�
	}ANIMATION;

	//�e�N�X�`���𔽓]���邩�̗񋓌^
	typedef enum
	{
		NOT_INVERSION = 0,	//�ʏ�
		INVERSION			//���E���]
	}TEX;

	//��]�̌����̗񋓌^
	typedef enum
	{
		ROTATION_RIGHT = 0,	//�E��]
		ROTATION_LEFT		//����]
	}ROTATION;

	//�����蔻��̎�ނ̗񋓌^
	typedef enum
	{
		RECTANGLE_AND_RECTANGLE = 0,	//��`�Ƌ�`
		CIRCULAR_AND_CIRCULAR,			//�~�`�Ɖ~�`
		RECTANGLE_AND_CIRCLE,			//��`�Ɖ~�`
	}COLLISION;

	CScene2D();
	virtual ~CScene2D();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void InitAnimation(float fCounterAnim, float fPatternAnim, float fLineAnim);
	void UpdateAnimation(ANIMATION AnimConditions, TEX texType);
	void Rotation(D3DXVECTOR3 pos, D3DXVECTOR3 size, ROTATION rotation);
	void SetSize(D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);
	void SetColor(D3DXCOLOR color);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetSize(void);
	float GetRadian(void);
	TEX GetTexType(void);

private:
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXCOLOR m_color;						//�F
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���̃|�C���^
	static LPDIRECT3DDEVICE9 m_pDevice;		//�f�o�C�X�̃|�C���^
	int m_nCounterAnim;						//�A�j���[�V�����̑����J�E���g
	int m_nPatternAnim;						//�A�j���[�V�����̍s���J�E���g
	int m_nCounterLine;						//�A�j���[�V�����̗񐔃J�E���g
	float m_fAnimationSpeed;				//�A�j���[�V�����̑���
	float m_fAnimationPattern;				//�A�j���[�V�����̍s��
	float m_fAnimationLine;					//�A�j���[�V�����̗�
	float m_fRadian;						//�p�x
	TEX m_TexType;							//�e�N�X�`���̔��]���
};

#endif