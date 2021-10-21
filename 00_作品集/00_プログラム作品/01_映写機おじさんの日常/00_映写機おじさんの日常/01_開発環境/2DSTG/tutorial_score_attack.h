//=============================================================================
//
// �`���[�g���A������(�X�R�A�A�^�b�N���[�h) [tutorial_score_attack.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _TUTORIAL_SCORE_ATTACK_H_
#define _TUTORIAL_SCORE_ATTACK_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CScore;
class CUi;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CTutorialScoreAttack :public CMode
{
public:
	CTutorialScoreAttack();
	~CTutorialScoreAttack();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddScore(int nNum);

private:
	CScore *m_pScore;			//�X�R�A�̃|�C���^
	CUi* m_pDescriptionUi;		//��������̃|�C���^
};

#endif