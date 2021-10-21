//=============================================================================
//
// �X�R�A���ʏ��� [ScoreScreen.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCORESCREEN_H_
#define _SCORESCREEN_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CScore;

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define SCORE_	(4)	//�X�R�A��

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CScoreScreen :public CMode
{
public:
	//�X�R�A�̎�ނ̗񋓌^
	typedef enum
	{
		SCORE_TYPE_0 = 0,	//�Q�[���X�R�A
		SCORE_TYPE_1,		//�^�C���{�[�i�X
		SCORE_TYPE_2,		//�c�@�{�[�i�X
		SCORE_TYPE_3,		//�����X�R�A
		SCORE_TYPE_MAX
	}SCORE_TYPE;

	CScoreScreen();
	~CScoreScreen();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SaveScore(int nScore);
	static void SaveTotalTime(int nTotalTime);
	static void SavePlayerLife(int nPlayerLife);

private:
	CScore *m_pScore[SCORE_TYPE_MAX];	//�X�R�A�̃|�C���^
	static int m_nScore;				//�Q�[���X�R�A
	static int m_nTotalTime;			//�����^�C��
	static int m_nRanking;				//�����L���O����
	static int m_nScoreBonus;			//�^�C���{�[�i�X
	static int m_nPlayerLife;			//�v���C���[�̎c�@
	int m_nTotalScore;					//�����X�R�A
	int m_nPlayerLifeBonus;				//�c�@�{�[�i�X
	float m_fAddNum;					//�X�R�A���Z�̉��o�p�J�E���g
	bool m_bSet[SCORE_TYPE_MAX];		//���Z���o���I���������̔���
};

#endif