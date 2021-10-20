//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"
#include "tcp_client.h"
#include "protocol_ranking.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CScore;
class CUi;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CRanking :public CMode
{
public:
	CRanking();
	~CRanking();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static int SetRanking(int nScore);

	void GetRanking(void);

private:
	static CProtocolRanking::RankingData m_aRankingData[MAX_RANKING];	//�����L���O�f�[�^
	CScore *m_apScore[MAX_RANKING];										//�X�R�A
	CUi *m_apUi[MAX_RANKING];											//����UI
	int m_nCntScore;													//�X�R�A�𐶐�����J�E���g
	bool m_bUpdateScore;												//�X�R�A���X�V���邩�̔���
};

#endif