//=============================================================================
//
// ���[�r�[���� [movie.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _MOVIE_H_
#define _MOVIE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <dshow.h>
#include <control.h>
#include <string>
#include "atlstr.h"

//*****************************************************************************
//�N���X�錾
//*****************************************************************************
class CMovie
{
public:
	//�T�E���h�t�@�C��
	typedef enum
	{
		LABEL_TITLE = 0,	//�^�C�g��
		LABEL_MAX
	} MOVIE_LABEL;

	CMovie();	//�R���X�g���N�^
	~CMovie();	//�f�X�g���N�^

	HRESULT Init(HWND hWnd);	//����������
	void Uninit(void);			//�I������

	HRESULT PlayMovie(MOVIE_LABEL label);
	void StopMovie(MOVIE_LABEL label);
	void StopMovieAll(void);

private:
	IID m_cpGraph;
	IGraphBuilder* m_apGraphBuilder[LABEL_MAX];
	IMediaControl* m_apControl[LABEL_MAX];
	
	// �p�����[�^�\����
	typedef struct
	{
		CString pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} MOVIEPARAM;

	// �e���f�ނ̃p�����[�^
	MOVIEPARAM m_aParam[LABEL_MAX] =
	{
		{ "Data/Movies/title.mov", -1 },	//�^�C�g��
	};
};

//template <class T>
//class Com_ptr
//{
//private:
//	T* m_pInterface;   // �C���^�[�t�F�C�X�ւ̃|�C���^
//
//protected:
//	// �Q�ƃJ�E���^����
//	void AddRef(T* pInterface) {
//#if _DEBUG
//		// �f�o�b�O�łł͎Q�ƃJ�E���g���o�͂���
//		ULONG c = pInterface->AddRef();
//		ofstream ofs;
//		ofs.open("DEBUG.txt", ios::app);
//		ofs << pInterface << "\t[" << c << "]" << endl;
//		ofs.close();
//#else
//		pInterface->AddRef();
//#endif
//	}
//
//	// �Q�ƃJ�E���^����
//	void Release(T* pInterface) {
//#if _DEBUG
//		ULONG c = m_pInterface->Release();
//		ofstream ofs;
//		ofs.open("DEBUG.txt", ios::app);
//		ofs << m_pInterface << "\t[" << c << "]" << endl;
//		ofs.close();
//#else
//		m_pInterface->Release();
//#endif
//	}
//
//public:
//	// �f�t�H���g�R���X�g���N�^
//	// �R���X�g���N�^��explicit�錾���܂��B
//	// �����func(Com_ptr<IHoge> v)�Ƃ����֐��ɑ΂��āA
//	// func(pIHoge)�̂悤�ȈÖٌ^�ϊ�����͏o���܂���B
//	// �ʏ�A�|�C���^�̈��n�����ɂ��łɎQ�ƃJ�E���^��
//	// �C���N�������g����Ă���̂ŁAAddRef�͍s���܂���B
//	explicit Com_ptr(T* pInterface = NULL, BOOL add = FALSE) {
//		if (pInterface && add) {
//			AddRef(pInterface);
//		}
//		m_pInterface = pInterface;
//	}
//
//	// �R�s�[�R���X�g���N�^
//	Com_ptr(const Com_ptr& src) {
//		// �R�s�[���̎Q�ƃJ�E���^��1���₷
//		if (src.m_pInterface)
//			AddRef(src.m_pInterface);
//
//		// �R�s�[
//		m_pInterface = src.m_pInterface;
//	}
//
//	// �f�X�g���N�^
//	virtual ~Com_ptr() {
//		if (m_pInterface)
//			Release(m_pInterface);
//	}
//
//	// ���Z�q
//	// =������Z�q�i�����I�R�s�[�j
//	Com_ptr& operator =(const Com_ptr& src) {
//		// �����̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
//		if (m_pInterface)
//			Release(m_pInterface);
//
//		// �R�s�[���̎Q�ƃJ�E���^��1���₷
//		if (src.m_pInterface)
//			AddRef(src.m_pInterface);
//
//		// �R�s�[
//		m_pInterface = src.m_pInterface;
//
//		return *this;
//	}
//
//	// =������Z�q�i�C���^�[�t�F�C�X�o�^�j
//	void operator =(T* pInterface) {
//		// �����̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
//		if (m_pInterface)
//			Release(m_pInterface);
//
//		// �R�s�[
//		m_pInterface = pInterface;
//	}
//
//	// !=��r���Z�q
//	BOOL operator !=(int val) {
//		if (val != (int)m_pInterface)
//			return TRUE;
//		return FALSE;
//	}
//
//	// ==��r���Z�q
//	BOOL operator ==(int val) {
//		if (val == (int)m_pInterface)
//			return TRUE;
//		return FALSE;
//	}
//
//	// �����o�֐�
//	// �|�C���^�擾
//	T* GetPtr() { return m_pInterface; }
//
//	// �|�C���^�̃A�h���X���擾
//	T** GetPtrPtr() { return &m_pInterface; }
//
//	// �C���^�[�t�F�C�X�����֐��֓n����p�֐�
//	T** ToCreator() {
//		if (m_pInterface)
//			m_pInterface->Release();
//
//		return &m_pInterface;
//	}
//};
//

#endif