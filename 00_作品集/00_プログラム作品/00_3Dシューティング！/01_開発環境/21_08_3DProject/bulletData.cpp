//=============================================================================
//
// �e�f�[�^�Ǘ� [bulletData.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "bulletData.h"
#include "bullet.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBulletData::CBulletData()
{
	memset(m_aCreateInfo, 0, sizeof(m_aCreateInfo));
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBulletData::~CBulletData()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CBulletData::Init(void)
{
	// �t�@�C���|�C���g
	FILE *pFile = NULL;

	// �ϐ��錾
	char cReadText[2048];	// �����Ƃ��ēǂݎ��p
	char cHeadText[2048];	// �����̔��ʗp
	char cDie[2048];		// �g��Ȃ�����
	int nCreateNum = 0;		// �������̃J�E���g���������p

	// �t�@�C�����J��
	pFile = fopen("Data/Text/02_bullet.txt", "r");

	// �J������
	if (pFile != NULL)
	{
		// SCRIPT�̕�����������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)//strcmp(��r1, ��r2)��2�̈������ׂē����Ȃ�0��Ԃ�
		{
			// �e�L�X�g����cReadText���������󂯎��
			fgets(cReadText, sizeof(cReadText), pFile);
			//fgets(�������ϐ�, ��s�̍ő啶����, �t�@�C���|�C���^)���t�@�C�����當�������s�擾����

			// cReedText��cHeadText�Ɋi�[
			sscanf(cReadText, "%s", &cHeadText);
			//sscanf(��͑Ώۂ̕�����ϐ�, ��͂���t�H�[�}�b�g(��F%d,%f,%c...), ��̓t�H�[�}�b�g�ɉ������ϐ���K�v�Ȃ������ɕ��ׂ�(��R�����ȍ~))
			//����P�����̕�������Q�����̃t�H�[�}�b�g�ɏ]����͂��Ďw�肳�ꂽ�ϐ��֊i�[����
		}

		// cHeadText��SCRIPT�̂Ƃ�
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// cHeadText��END_SCRIPT�ɂȂ�܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				// cHeadText��BULLET_DATASET����nCreateNum��BULLET_MAX��菬�����Ƃ�
				if (strcmp(cHeadText, "BULLET_DATASET") == 0 && nCreateNum < BULLET_MAX)
				{
					// cHeadText��END_BULLET_DATASET�ɂȂ�܂�
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

					//��������i�߂�
					nCreateNum++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	// �J���Ȃ�������
	else
	{
		printf("�J����܂���ł���\n");

		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CBulletData::Uninit(void)
{
}

//*****************************************************************************
//�e�f�[�^�̎擾����
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