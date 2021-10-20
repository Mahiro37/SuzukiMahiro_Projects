//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include <XAudio2.h>

//*****************************************************************************
//�N���X�錾
//*****************************************************************************
class CSound
{
public:
	//�T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,			//�^�C�g��BGM
		SOUND_LABEL_GAME,				//�Q�[��BGM
		SOUND_LABEL_START,				//�����J�nSE
		SOUND_LABEL_FINISH,				//�����I��SE
		SOUND_LABEL_PLAYER_EXPLOSION,	//�v���C���[�̔���SE
		SOUND_LABEL_BULLET_EXPLOSION,	//�e�̔���SE
		SOUND_LABEL_WALL_HIT,			//�e�ƕǂ̏Փ�SE
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();	//�R���X�g���N�^
	~CSound();	//�f�X�g���N�^

	HRESULT Init(HWND hWnd);				//����������
	void Uninit(void);						//�I������
	HRESULT PlaySound(SOUND_LABEL label);	//�Đ�
	void StopSound(SOUND_LABEL label);		//��~(�w��)
	void StopSound(void);					//��~(�S��)

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	//�`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	//�`�����N�f�[�^�̓ǂݍ���

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "Data/Sounds/BGM/title.wav", -1 },			//�^�C�g��BGM
		{ "Data/Sounds/BGM/game.wav", -1 },				//�Q�[��BGM
		{ "Data/Sounds/SE/start.wav", 0 },				//�����J�nSE
		{ "Data/Sounds/SE/finish.wav", 0 },				//�����I��SE
		{ "Data/Sounds/SE/player_explosion.wav", 0 },	//�v���C���[�̔���SE
		{ "Data/Sounds/SE/bullet_explosion.wav", 0 },	//�e�̔���SE
		{ "Data/Sounds/SE/wall_hit.wav", 0 },			//�e�ƕǂ̏Փ�SE
	};
};

#endif