//=============================================================================
//
// �X�R�A�A�^�b�N���� [score_attack.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCORE_ATTACK_H_
#define _SCORE_ATTACK_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CScore;
class CMessage;
class CFade;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CScoreAttack :public CMode
{
public:
	CScoreAttack();
	~CScoreAttack();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void AddScore(int nNum);

	static CScore *GetScore(void);

private:
	static CScore *m_pScore;	//�X�R�A�̃|�C���^
	CMessage *m_pMessage;		//���b�Z�[�W�̃|�C���^
	CFade *m_pFade;				//�t�F�[�h�̃|�C���^
	bool m_bStartPush;		//�X�^�[�g�{�^�������������̔���
};

#endif