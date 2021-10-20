//=============================================================================
//
// 弾データ管理 [bulletData.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "bulletData.h"
#include "bullet.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBulletData::CBulletData()
{
	memset(m_aCreateInfo, 0, sizeof(m_aCreateInfo));
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CBulletData::~CBulletData()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CBulletData::Init(void)
{
	// ファイルポイント
	FILE *pFile = NULL;

	// 変数宣言
	char cReadText[2048];	// 文字として読み取り用
	char cHeadText[2048];	// 文字の判別用
	char cDie[2048];		// 使わない文字
	int nCreateNum = 0;		// 生成順のカウント＆生成数用

	// ファイルを開く
	pFile = fopen("Data/Text/02_bullet.txt", "r");

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

		// cHeadTextがSCRIPTのとき
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// cHeadTextがEND_SCRIPTになるまで
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				// cHeadTextがBULLET_DATASETかつnCreateNumがBULLET_MAXより小さいとき
				if (strcmp(cHeadText, "BULLET_DATASET") == 0 && nCreateNum < BULLET_MAX)
				{
					// cHeadTextがEND_BULLET_DATASETになるまで
					while (strcmp(cHeadText, "END_BULLET_DATASET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nCreateNum].nType);
						}
						else if (strcmp(cHeadText, "DISTANCE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[nCreateNum].distance.x, &m_aCreateInfo[nCreateNum].distance.y, &m_aCreateInfo[nCreateNum].distance.z);
						}
						else if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aCreateInfo[nCreateNum].modelSize.x, &m_aCreateInfo[nCreateNum].modelSize.y, &m_aCreateInfo[nCreateNum].modelSize.z);
							m_aCreateInfo[nCreateNum].collisionSize = m_aCreateInfo[nCreateNum].modelSize * 5.0f;
						}
						else if (strcmp(cHeadText, "MOVE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nCreateNum].fMove);
						}
						else if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nCreateNum].nLife);
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
void CBulletData::Uninit(void)
{
}

//*****************************************************************************
//弾データの取得処理
//*****************************************************************************
CBulletData::CreateInfo * CBulletData::GetCreateInfo(const int &nType)
{
	for (int nCount = 0; nCount < CBullet::TYPE_MAX; nCount++)
	{
		if (m_aCreateInfo[nCount].nType == nType)
		{
			return &m_aCreateInfo[nCount];
		}
	}

	return nullptr;
}