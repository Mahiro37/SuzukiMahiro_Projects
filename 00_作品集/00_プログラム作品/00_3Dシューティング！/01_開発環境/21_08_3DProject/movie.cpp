//=============================================================================
//
// ���[�r�[���� [movie.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "movie.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CMovie::CMovie()
{
	memset(&m_cpGraph, 0, sizeof(m_cpGraph));
	memset(&m_apGraphBuilder, 0, sizeof(m_apGraphBuilder));
	memset(&m_apControl, 0, sizeof(m_apControl));
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CMovie::~CMovie()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CMovie::Init(HWND hWnd)
{
	// std::wcout�̃��P�[����ݒ�
	std::wcout.imbue(std::locale("", std::locale::ctype));

	// �G���[�R�[�h
	HRESULT hResult = S_OK;

	// COM��������
	CoInitialize(NULL);

	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		// IGraphBuilder���擾
		hResult = ::CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&m_apGraphBuilder);
		if (!SUCCEEDED(hResult))
		{
			// �G���[
			return hResult;
		}

		// ���f�B�A�R���g���[���C���^�[�t�F�C�X�̎擾
		hResult = m_apGraphBuilder[nCount]->QueryInterface(IID_IMediaControl, (void**)(m_apControl));

		if (!SUCCEEDED(hResult))
		{
			// �G���[
			return hResult;
		}

		// ���f�B�A�C�x���g�C���^�[�t�F�C�X�̎擾
		hResult = m_apGraphBuilder[nCount]->QueryInterface(IID_IMediaEvent, (void **)(&m_cpGraph));
		if (!SUCCEEDED(hResult))
		{
			// �G���[
			return hResult;
		}

		// IMediaControl�̎擾
		hResult = m_apGraphBuilder[nCount]->QueryInterface(IID_IMediaControl, (void**)&m_apControl[nCount]);
		if (!SUCCEEDED(hResult))
		{
			// �G���[
			return hResult;
		}

		LPCSTR data = (LPCSTR)m_aParam[nCount].pFilename;
		LPCWSTR data2 = m_aParam[nCount].pFilename.AllocSysString();
		// FilterGraph�̐���
		hResult = m_apControl[nCount]->RenderFile((BSTR)data2);
		if (!SUCCEEDED(hResult))
		{
			// �G���[
			return hResult;
		}
	}
	
	return hResult;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CMovie::Uninit(void)
{
	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		// IMediaControl�̔j��
		if (m_apControl != nullptr)
		{
			m_apControl[nCount]->Release();
		}

		// IGraphBuilder�̔j��
		if (m_apGraphBuilder != nullptr)
		{
			m_apGraphBuilder[nCount]->Release();
		}
	}

	// COM�̏I��
	CoUninitialize();
}

//*****************************************************************************
//����̍Đ�
//*****************************************************************************
HRESULT CMovie::PlayMovie(MOVIE_LABEL label)
{
	// �G���[�R�[�h
	HRESULT hResult = S_OK;

	if (m_apControl[label] != nullptr)
	{
		// ����̍Đ�
		hResult = m_apControl[label]->Run();
		if (!SUCCEEDED(hResult))
		{
			// �G���[
			return hResult;
		}
	}

	return hResult;
}

//*****************************************************************************
//����̒�~
//*****************************************************************************
void CMovie::StopMovie(MOVIE_LABEL label)
{
	if (m_apControl[label] != nullptr)
	{
		// ����̍Đ�
		m_apControl[label]->Stop();
	}
}

//*****************************************************************************
//����̒�~
//*****************************************************************************
void CMovie::StopMovieAll(void)
{
	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		if (m_apControl[nCount] != nullptr)
		{
			// ����̍Đ�
			m_apControl[nCount]->Stop();
		}
	}
}