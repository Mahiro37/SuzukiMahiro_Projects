//=============================================================================
//
// UI���� [ui.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define INIT_FINISH_UI_TIME (120)	//��������UI�̕\������(�����l)

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CUi:public CScene2D
{
public:
	//UI�̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_TITLE,			//�^�C�g��
		TYPE_RESULT,		//���U���g
		TYPE_START,			//�Q�[���J�n
		TYPE_WIN_PLAYER_1,	//1P�̏���
		TYPE_WIN_PLAYER_2,	//2P�̏���
		TYPE_DRAW,			//��������
		TYPE_MAX
	}UI_TYPE;

	CUi(OBJTYPE nPriority);	//�R���X�g���N�^
	~CUi();					//�f�X�g���N�^

	static HRESULT Load(void);	//���[�h����
	static void Unload(void);	//�A�����[�h����

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	LPDIRECT3DTEXTURE9 GetTexture(const UI_TYPE &type) { return m_apTexture[type]; }	//�e�N�X�`�����̎擾
	UI_TYPE GetUiType(void) { return m_type; }											//UI�^�C�v�̎擾

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//�e�N�X�`���̃|�C���^�z��
	UI_TYPE m_type;	//UI�^�C�v
};

#endif