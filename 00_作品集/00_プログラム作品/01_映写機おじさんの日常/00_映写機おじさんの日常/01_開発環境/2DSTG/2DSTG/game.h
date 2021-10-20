//=============================================================================
//
// �Q�[������ [game.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"
#include "item.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CFade;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CGame :public CMode
{
public:
	//�X�e�[�W�̗񋓌^
	typedef enum
	{
		GAME_STAGE_1 = 0,	//�X�e�[�W�P
		GAME_STAGE_2,		//�X�e�[�W�Q
		GAME_STAGE_3,		//�X�e�[�W�R
		GAME_STAGE_CLEAR	//�X�e�[�W�N���A
	}GAME_STAGE;

	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetStageNum(int nStageNum);
	static void UpdateStock(list<CItem::ITEMTYPE> StockItem);

	int GetStageNum(void);

private:
	CFade *m_pFade;			//�t�F�[�h�̃|�C���^
	bool m_bClear;			//�N���A����
	static int m_nCntStage;	//�X�e�[�W�ԍ�
	bool m_bStartPush;		//�X�^�[�g�{�^�������������̔���
};

#endif