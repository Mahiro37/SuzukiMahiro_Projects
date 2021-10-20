//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
CScene *CScene::m_pTop[OBJTYPE_MAX] = {};
CScene *CScene::m_pCur[OBJTYPE_MAX] = {};
int CScene::m_nCntList = 0;
CScene::OBJTYPE CScene::m_UpdateTypeList[OBJTYPE_MAX] = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CScene::CScene(OBJTYPE nPriority)
{
	m_bDeath = false;

	m_objType = (OBJTYPE)nPriority;

	m_nPriority = nPriority;

	if (m_pTop[nPriority] == NULL)
	{ //先頭がNULLのとき
	  //先頭に保存
		m_pTop[nPriority] = this;
	}

	if (m_pCur[nPriority] == NULL)
	{ //最後尾がNULLのとき
	  //最後尾に保存
		m_pCur[nPriority] = this;
	}

	//最後尾の次に新しい情報を保存
	m_pCur[nPriority]->m_pNext = this;

	if (m_pCur[nPriority] == this)
	{
		m_pCur[nPriority]->m_pPrev = NULL;
	}
	else
	{
		//新しい情報を最後尾に指定
		m_pPrev = m_pCur[nPriority];
	}

	//最後尾を新しい情報にする
	m_pCur[nPriority] = this;

	//最後尾の次をNULLにする
	m_pCur[nPriority]->m_pNext = NULL;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CScene::~CScene()
{
}

//*****************************************************************************
//全ての更新処理
//*****************************************************************************
void CScene::UpdateAll(void)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == false)
			{
				//更新処理
				pScene->Update();
			}

			pScene = pSave;
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				if (pScene->m_pPrev != NULL)
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (m_pTop[nCount] == pScene)
				{
					m_pTop[nCount] = pScene->m_pNext;
				}

				if (m_pCur[nCount] == pScene)
				{
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

//*****************************************************************************
//選択したOBJTYPEのみの更新処理
//*****************************************************************************
void CScene::DesignationUpdateAll(const OBJTYPE* type)
{
	for (int nCount = 0; m_pTop[m_UpdateTypeList[nCount]] != NULL; nCount++)
	{
		CScene *pScene = m_pTop[m_UpdateTypeList[nCount]];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == false)
			{
				//更新処理
				pScene->Update();
			}

			pScene = pSave;
		}
	}

	for (int nCount = 0; m_pTop[m_UpdateTypeList[nCount]] != NULL; nCount++)
	{
		CScene *pScene = m_pTop[m_UpdateTypeList[nCount]];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				if (pScene->m_pPrev != NULL)
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (m_pTop[type[nCount]] == pScene)
				{
					m_pTop[type[nCount]] = pScene->m_pNext;
				}

				if (m_pCur[type[nCount]] == pScene)
				{
					m_pCur[type[nCount]] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

//*****************************************************************************
//全ての描画処理
//*****************************************************************************
void CScene::DrawAll(void)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			//描画処理
			CScene *pSave = pScene->m_pNext;
			pScene->Draw();
			pScene = pSave;
		}
	}
}

//*****************************************************************************
//全てのメモリの開放処理
//*****************************************************************************
void CScene::ReleaseAll(void)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			//終了処理
			CScene *pSave = pScene->m_pNext;
			pScene->Release();
			pScene = pSave;
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				if (pScene->m_pPrev != NULL)
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (m_pTop[nCount] == pScene)
				{
					m_pTop[nCount] = pScene->m_pNext;
				}

				if (m_pCur[nCount] == pScene)
				{
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

//*****************************************************************************
//選択したもの以外の解放処理
//*****************************************************************************
void CScene::DesignationReleaseAll(OBJTYPE type)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		if (nCount != type)
		{
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				//終了処理
				CScene *pSave = pScene->m_pNext;
				pScene->Release();
				pScene = pSave;
			}
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		if (nCount != type)
		{
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				CScene *pSave = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					if (pScene->m_pPrev != NULL)
					{
						pScene->m_pPrev->m_pNext = pScene->m_pNext;
					}

					if (pScene->m_pNext != NULL)
					{
						pScene->m_pNext->m_pPrev = pScene->m_pPrev;
					}

					if (m_pTop[nCount] == pScene)
					{
						m_pTop[nCount] = pScene->m_pNext;
					}

					if (m_pCur[nCount] == pScene)
					{
						m_pCur[nCount] = pScene->m_pPrev;
					}

					//オブジェクトを破棄
					delete pScene;
				}

				pScene = pSave;
			}
		}
	}
}

//*****************************************************************************
//更新するオブジェクトタイプの設定
//*****************************************************************************
void CScene::SetUpdateType(const OBJTYPE type, ...)
{
	memset(m_UpdateTypeList, 0, sizeof(m_UpdateTypeList));

	va_list args;
	va_start(args, type);
	m_UpdateTypeList[0] = type;

	int nCount = 1;
	do
	{
		m_UpdateTypeList[nCount] = va_arg(args, OBJTYPE);

		nCount++;
	} while (m_UpdateTypeList[nCount] != NULL);

	va_end(args);
}

//*****************************************************************************
//シーンの取得
//*****************************************************************************
CScene *CScene::GetScene(const int &nPriority)
{
	CScene *pScene = m_pTop[nPriority];

	if (pScene != NULL)
	{
		for (int nCount = 0; nCount < m_nCntList; nCount++)
		{
			if (pScene != NULL)
			{
				pScene = pScene->m_pNext;
			}
		}

		m_nCntList++;

		if (pScene == NULL)
		{
			m_nCntList = 0;
		}
	}

	return pScene;
}

//*****************************************************************************
//更新するオブジェクトタイプの取得
//*****************************************************************************
void CScene::GetUpdateType(OBJTYPE* type)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		type[nCount] = m_UpdateTypeList[nCount];
	}
}