//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include <XAudio2.h>

//*****************************************************************************
//クラス宣言
//*****************************************************************************
class CSound
{
public:
	//サウンドファイル
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,			//タイトルBGM
		SOUND_LABEL_GAME,				//ゲームBGM
		SOUND_LABEL_START,				//試合開始SE
		SOUND_LABEL_FINISH,				//試合終了SE
		SOUND_LABEL_PLAYER_EXPLOSION,	//プレイヤーの爆発SE
		SOUND_LABEL_BULLET_EXPLOSION,	//弾の爆発SE
		SOUND_LABEL_WALL_HIT,			//弾と壁の衝突SE
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();	//コンストラクタ
	~CSound();	//デストラクタ

	HRESULT Init(HWND hWnd);				//初期化処理
	void Uninit(void);						//終了処理
	HRESULT PlaySound(SOUND_LABEL label);	//再生
	void StopSound(SOUND_LABEL label);		//停止(指定)
	void StopSound(void);					//停止(全て)

private:
	// パラメータ構造体
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	//チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	//チャンクデータの読み込み

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	// 各音素材のパラメータ
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "Data/Sounds/BGM/title.wav", -1 },			//タイトルBGM
		{ "Data/Sounds/BGM/game.wav", -1 },				//ゲームBGM
		{ "Data/Sounds/SE/start.wav", 0 },				//試合開始SE
		{ "Data/Sounds/SE/finish.wav", 0 },				//試合終了SE
		{ "Data/Sounds/SE/player_explosion.wav", 0 },	//プレイヤーの爆発SE
		{ "Data/Sounds/SE/bullet_explosion.wav", 0 },	//弾の爆発SE
		{ "Data/Sounds/SE/wall_hit.wav", 0 },			//弾と壁の衝突SE
	};
};

#endif