//=============================================================================
//
// �v���C���[�f�[�^�Ǘ� [playerData.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "playerData.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CPlayerData::CPlayerData()
{
	memset(m_aCreateInfo, 0, sizeof(m_aCreateInfo));
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CPlayerData::~CPlayerData()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CPlayerData::Init(void)
{
	// �t�@�C���|�C���g
	FILE *pFile = NULL;

	// �ϐ��錾
	char cReadText[2048];	// �����Ƃ��ēǂݎ��p
	char cHeadText[2048];	// �����̔��ʗp
	char cDie[2048];		// �g��Ȃ�����
	int nCreateNum = 0;		// �������̃i���o�[

	// �t�@�C�����J��
	pFile = fopen("Data/Text/01_player.txt", "r");

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

		// cHeadText��SCRIPT�̎�
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// cHeadText��END_SCRIPT�ɂȂ�܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				// cHeadText��PLAYER_DATASET�̎�
				if (strcmp(cHeadText, "PLAYER_DATASET") == 0 && nCreateNum < CCharacter::TYPE_MAX)
				{
					// cHeadText��END_PLAYER_DATASET�ɂȂ�܂�
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
void CPlayerData::Uninit(void)
{
}

//*****************************************************************************
//�I������
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