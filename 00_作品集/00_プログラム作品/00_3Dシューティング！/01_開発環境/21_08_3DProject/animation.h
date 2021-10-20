//=============================================================================
//
// �A�j���[�V�������� [animation.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CAnimation : public CScene
{
public:
	//���s�[�g���邩�ǂ����̗񋓌^
	typedef enum
	{
		REP_REPEAT = 0,	//���s�[�g����
		REP_UNREPEAT	//���s�[�g���Ȃ�
	}REP;

	CAnimation(OBJTYPE nPriority);	//�R���X�g���N�^
	~CAnimation();					//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	//�e��ݒ�
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }									//�ʒu�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }								//�傫���̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }									//�p�x�̐ݒ�
	void SetCol(const D3DXCOLOR &col) { m_col = col; }										//�F�̐ݒ�
	void SetTex(const int &nAnimLine, const int &nAnimColumn, const int &nAnimSpeed)
	{ m_nAnimLine = nAnimLine; m_nAnimColumn = nAnimColumn; m_nAnimSpeed = nAnimSpeed; }	//�e�N�X�`�����W�̐ݒ�
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }			//�e�N�X�`���̎�ނ̐ݒ�
	void SetRepeat(const REP &repeat) { m_repeat = repeat; }								//���s�[�g���邩�̐ݒ�

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//�ʒu�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; }	//�傫���̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//�p�x�̎擾
	D3DXCOLOR GetCol(void) { return m_col; }		//�F�̎擾

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_size;		//�傫��
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXCOLOR m_col;		//�F

	int m_nAnimLine;	//�A�j���[�V�����̍s��
	int m_nAnimColumn;	//�A�j���[�V�����̗�
	int m_nAnimSpeed;	//�A�j���[�V�����̐؂�ւ����x
	int m_nCntLine;		//�A�j���[�V�����̍s���J�E���g
	int m_nCntColumn;	//�A�j���[�V�����̗񐔃J�E���g
	int m_nCntAnim;		//�A�j���[�V�����̃J�E���g

	REP m_repeat;		//���s�[�g����
};
#endif