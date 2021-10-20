//=============================================================================
//
// プレイヤーデータ管理 [playerData.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "playerData.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CPlayerData::CPlayerData()
{
	memset(m_aCreateInfo, 0, sizeof(m_aCreateInfo));
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CPlayerData::~CPlayerData()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CPlayerData::Init(void)
{
	// ファイルポイント
	FILE *pFile = NULL;

	// 変数宣言
	char cReadText[2048];	// 文字として読み取り用
	char cHeadText[2048];	// 文字の判別用
	char cDie[2048];		// 使わない文字
	int nCreateNum = 0;		// 生成数のナンバー

	// ファイルを開く
	pFile = fopen("Data/Text/01_player.txt", "r");

	// 開けたら
	if (pFile != NULL)
	{
		// SCRIPTの文字が見つかるまで
		while (strcmp(cHeadText, "SCRIPT") != 0)//strcmp(比較1, 比較2)→2つの引数を比べて同じなら0を返す
		{
			// テキストからcReadText分文字を受け取る
			fgets(cReadText, sizeof(cReadText), pFile);
			//fgets(代入する変数, 一行の最大文字数, ファイルポインタ)→ファイルから文字列を一行取得する

			// cReedTextをcHeadTextに格納
			sscanf(cReadText, "%s", &cHeadText);
			//sscanf(解析対象の文字列変数, 解析するフォーマット(例：%d,%f,%c...), 解析フォーマットに応じた変数を必要なだけ順に並べる(第３引数以降))
			//→第１引数の文字列を第２引数のフォーマットに従い解析して指定された変数へ格納する
		}

		// cHeadTextがSCRIPTの時
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// cHeadTextがEND_SCRIPTになるまで
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				// cHeadTextがPLAYER_DATASETの時
				if (strcmp(cHeadText, "PLAYER_DATASET") == 0 && nCreateNum < CCharacter::TYPE_MAX)
				{
					// cHeadTextがEND_PLAYER_DATASETになるまで
					while (strcmp(cHeadText, "END_PLAYER_DATASET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nCreateNum].type);
						}
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[nCreateNum].pos.x, &m_aCreateInfo[nCreateNum].pos.y, &m_aCreateInfo[nCreateNum].pos.z);
						}
						else if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[nCreateNum].modelSize.x, &m_aCreateInfo[nCreateNum].modelSize.y, &m_aCreateInfo[nCreateNum].modelSize.z);
							m_aCreateInfo[nCreateNum].collisionSize = D3DXVECTOR3(
																		m_aCreateInfo[nCreateNum].modelSize.x * 15.66f,
																		m_aCreateInfo[nCreateNum].modelSize.y * 3.57f,
																		m_aCreateInfo[nCreateNum].modelSize.z * 9.51f);
						}
						else if (strcmp(cHeadText, "ROT") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[nCreateNum].rot.x, &m_aCreateInfo[nCreateNum].rot.y, &m_aCreateInfo[nCreateNum].rot.z);
							m_aCreateInfo[nCreateNum].rot = D3DXToRadian(m_aCreateInfo[nCreateNum].rot);
						}
						else if (strcmp(cHeadText, "MOVE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nCreateNum].fMove);
						}
						else if (strcmp(cHeadText, "BULLET_TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nCreateNum].nBulletType);
						}
					}

					//生成数を進める
					nCreateNum++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	// 開けなかったら
	else
	{
		printf("開けれませんでした\n");

		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CPlayerData::Uninit(void)
{
}

//*****************************************************************************
//終了処理
//*****************************************************************************
CPlayerData::CreateInfo* CPlayerData::GetCreateInfo(const CCharacter::TYPE &type)
{
	for (int nCount = 0; nCount < CCharacter::TYPE_MAX; nCount++)
	{
		if (m_aCreateInfo[nCount].type == type)
		{
			return &m_aCreateInfo[nCount];
		}
	}

	return nullptr;
}