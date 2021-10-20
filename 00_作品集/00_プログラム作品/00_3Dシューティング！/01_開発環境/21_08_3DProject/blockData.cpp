//=============================================================================
//
// 障害物データ管理 [blockData.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "blockData.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBlockData::CBlockData()
{
	memset(m_aCreateInfo, 0, sizeof(m_aCreateInfo));
	m_nCreateNum = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CBlockData::~CBlockData()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CBlockData::Init(void)
{
	// ファイルポイント
	FILE *pFile = NULL;

	// 変数宣言
	char cReadText[2048];	// 文字として読み取り用
	char cHeadText[2048];	// 文字の判別用
	char cDie[2048];		// 使わない文字

	// ファイルを開く
	pFile = fopen("Data/Text/03_block.txt", "r");

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

				// cHeadTextがBLOCK_DATASETの時
				if (strcmp(cHeadText, "BLOCK_DATASET") == 0 && m_nCreateNum < BLOCK_MAX)
				{
					// cHeadTextがEND_BLOCK_DATASETになるまで
					while (strcmp(cHeadText, "END_BLOCK_DATASET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[m_nCreateNum].pos.x, &m_aCreateInfo[m_nCreateNum].pos.y, &m_aCreateInfo[m_nCreateNum].pos.z);
						}
						else if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[m_nCreateNum].size.x, &m_aCreateInfo[m_nCreateNum].size.y, &m_aCreateInfo[m_nCreateNum].size.z);
							m_aCreateInfo[m_nCreateNum].collisionSize = m_aCreateInfo[m_nCreateNum].size * 10.0f;
						}
						else if (strcmp(cHeadText, "ROT") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[m_nCreateNum].rot.x, &m_aCreateInfo[m_nCreateNum].rot.y, &m_aCreateInfo[m_nCreateNum].rot.z);
							m_aCreateInfo[m_nCreateNum].rot = D3DXToRadian(m_aCreateInfo[m_nCreateNum].rot);
						}
					}

					//生成数を進める
					m_nCreateNum++;
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
void CBlockData::Uninit(void)
{
}