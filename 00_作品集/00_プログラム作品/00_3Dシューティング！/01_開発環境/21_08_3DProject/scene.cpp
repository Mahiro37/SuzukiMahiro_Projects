//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
CScene *CScene::m_pTop[OBJTYPE_MAX] = {};
CScene *CScene::m_pCur[OBJTYPE_MAX] = {};
int CScene::m_nCntList = 0;
CScene::OBJTYPE CScene::m_UpdateTypeList[OBJTYPE_MAX] = {};

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CScene::CScene(OBJTYPE nPriority)
{
	m_bDeath = false;

	m_objType = (OBJTYPE)nPriority;

	m_nPriority = nPriority;

	if (m_pTop[nPriority] == NULL)
	{ //�擪��NULL�̂Ƃ�
	  //�擪�ɕۑ�
		m_pTop[nPriority] = this;
	}

	if (m_pCur[nPriority] == NULL)
	{ //�Ō����NULL�̂Ƃ�
	  //�Ō���ɕۑ�
		m_pCur[nPriority] = this;
	}

	//�Ō���̎��ɐV��������ۑ�
	m_pCur[nPriority]->m_pNext = this;

	if (m_pCur[nPriority] == this)
	{
		m_pCur[nPriority]->m_pPrev = NULL;
	}
	else
	{
		//�V���������Ō���Ɏw��
		m_pPrev = m_pCur[nPriority];
	}

	//�Ō����V�������ɂ���
	m_pCur[nPriority] = this;

	//�Ō���̎���NULL�ɂ���
	m_pCur[nPriority]->m_pNext = NULL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CScene::~CScene()
{
}

//*****************************************************************************
//�S�Ă̍X�V����
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
				//�X�V����
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

				//�I�u�W�F�N�g��j��
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

//*****************************************************************************
//�I������OBJTYPE�݂̂̍X�V����
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
				//�X�V����
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

				//�I�u�W�F�N�g��j��
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

//*****************************************************************************
//�S�Ă̕`�揈��
//*****************************************************************************
void CScene::DrawAll(void)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			//�`�揈��
			CScene *pSave = pScene->m_pNext;
			pScene->Draw();
			pScene = pSave;
		}
	}
}

//*****************************************************************************
//�S�Ẵ������̊J������
//*****************************************************************************
void CScene::ReleaseAll(void)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			//�I������
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

				//�I�u�W�F�N�g��j��
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

//*****************************************************************************
//�I���������̈ȊO�̉������
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
				//�I������
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

					//�I�u�W�F�N�g��j��
					delete pScene;
				}

				pScene = pSave;
			}
		}
	}
}

//*****************************************************************************
//�X�V����I�u�W�F�N�g�^�C�v�̐ݒ�
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
//�V�[���̎擾
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
//�X�V����I�u�W�F�N�g�^�C�v�̎擾
//*****************************************************************************
void CScene::GetUpdateType(OBJTYPE* type)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		type[nCount] = m_UpdateTypeList[nCount];
	}
}