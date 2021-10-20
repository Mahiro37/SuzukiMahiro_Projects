//=============================================================================
//
// ムービー処理 [movie.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "movie.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CMovie::CMovie()
{
	memset(&m_cpGraph, 0, sizeof(m_cpGraph));
	memset(&m_apGraphBuilder, 0, sizeof(m_apGraphBuilder));
	memset(&m_apControl, 0, sizeof(m_apControl));
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CMovie::~CMovie()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CMovie::Init(HWND hWnd)
{
	// std::wcoutのロケールを設定
	std::wcout.imbue(std::locale("", std::locale::ctype));

	// エラーコード
	HRESULT hResult = S_OK;

	// COMを初期化
	CoInitialize(NULL);

	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		// IGraphBuilderを取得
		hResult = ::CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&m_apGraphBuilder);
		if (!SUCCEEDED(hResult))
		{
			// エラー
			return hResult;
		}

		// メディアコントロールインターフェイスの取得
		hResult = m_apGraphBuilder[nCount]->QueryInterface(IID_IMediaControl, (void**)(m_apControl));

		if (!SUCCEEDED(hResult))
		{
			// エラー
			return hResult;
		}

		// メディアイベントインターフェイスの取得
		hResult = m_apGraphBuilder[nCount]->QueryInterface(IID_IMediaEvent, (void **)(&m_cpGraph));
		if (!SUCCEEDED(hResult))
		{
			// エラー
			return hResult;
		}

		// IMediaControlの取得
		hResult = m_apGraphBuilder[nCount]->QueryInterface(IID_IMediaControl, (void**)&m_apControl[nCount]);
		if (!SUCCEEDED(hResult))
		{
			// エラー
			return hResult;
		}

		LPCSTR data = (LPCSTR)m_aParam[nCount].pFilename;
		LPCWSTR data2 = m_aParam[nCount].pFilename.AllocSysString();
		// FilterGraphの生成
		hResult = m_apControl[nCount]->RenderFile((BSTR)data2);
		if (!SUCCEEDED(hResult))
		{
			// エラー
			return hResult;
		}
	}
	
	return hResult;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CMovie::Uninit(void)
{
	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		// IMediaControlの破棄
		if (m_apControl != nullptr)
		{
			m_apControl[nCount]->Release();
		}

		// IGraphBuilderの破棄
		if (m_apGraphBuilder != nullptr)
		{
			m_apGraphBuilder[nCount]->Release();
		}
	}

	// COMの終了
	CoUninitialize();
}

//*****************************************************************************
//動画の再生
//*****************************************************************************
HRESULT CMovie::PlayMovie(MOVIE_LABEL label)
{
	// エラーコード
	HRESULT hResult = S_OK;

	if (m_apControl[label] != nullptr)
	{
		// 動画の再生
		hResult = m_apControl[label]->Run();
		if (!SUCCEEDED(hResult))
		{
			// エラー
			return hResult;
		}
	}

	return hResult;
}

//*****************************************************************************
//動画の停止
//*****************************************************************************
void CMovie::StopMovie(MOVIE_LABEL label)
{
	if (m_apControl[label] != nullptr)
	{
		// 動画の再生
		m_apControl[label]->Stop();
	}
}

//*****************************************************************************
//動画の停止
//*****************************************************************************
void CMovie::StopMovieAll(void)
{
	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		if (m_apControl[nCount] != nullptr)
		{
			// 動画の再生
			m_apControl[nCount]->Stop();
		}
	}
}