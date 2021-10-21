//=============================================================================
//
// �^�C������ [time.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "number.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define TIME_NUM			(2)			//�^�C���̌���
#define TIME_START_NUM		(60)		//�J�n���̃^�C��

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CTime :public CScene
{
public:
	CTime();
	~CTime();
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTime, CNumber::TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime);
	void SaveTime(int nTime);
	void SetStopTime(bool bTimeStop);
	void ResetTotalTime(void);

	int GetTime(void);
	int GetTotalTime(void);
	int GetSaveTime(void);

private:
	static CNumber *m_pNumber[TIME_NUM];	//�����̃|�C���^�z��
	int m_nTime;							//�^�C��
	int m_nTotalTime;						//�����^�C��
	int m_nSaveTime;						//�ۑ������^�C��
	int m_nTimeCounter;						//1�b���J�E���g����
	bool m_bTimeStop;						//�^�C����i�߂邩�̔���
};

#endif