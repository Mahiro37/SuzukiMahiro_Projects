//=============================================================================
//
// ��Q���f�[�^�Ǘ� [blockData.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "blockData.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBlockData::CBlockData()
{
	memset(m_aCreateInfo, 0, sizeof(m_aCreateInfo));
	m_nCreateNum = 0;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBlockData::~CBlockData()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CBlockData::Init(void)
{
	// �t�@�C���|�C���g
	FILE *pFile = NULL;

	// �ϐ��錾
	char cReadText[2048];	// �����Ƃ��ēǂݎ��p
	char cHeadText[2048];	// �����̔��ʗp
	char cDie[2048];		// �g��Ȃ�����

	// �t�@�C�����J��
	pFile = fopen("Data/Text/03_block.txt", "r");

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

				// cHeadText��BLOCK_DATASET�̎�
				if (strcmp(cHeadText, "BLOCK_DATASET") == 0 && m_nCreateNum < BLOCK_MAX)
				{
					// cHeadText��END_BLOCK_DATASET�ɂȂ�܂�
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

					//��������i�߂�
					m_nCreateNum++;
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
void CBlockData::Uninit(void)
{
}