//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputJoystick;
class CCamera;
class CLight;
class CFade;
class CPlayer;
class CModel;
class CDebugProc;
class CMode;
class CSound;
class CPlayerData;
class CBulletData;
class CWallData;
class CBlockData;
class CFloorData;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CManager
{
public:
	//��ʑJ�ڂ̗񋓌^
	enum MODE
	{
		MODE_NONE = 0,
		MODE_TITLE,		//�^�C�g��
		MODE_GAME,		//�Q�[��
		MODE_MAX
	};

	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,HWND hWnd);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

	void LoadAll(void);		//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
	void UnloadAll(void);	//�e�N�X�`���̔j���܂Ƃ�

	void SetMode(MODE mode);	//���[�h�̐ݒ�
	
	static void CreateCamera(void);		//�J�����̐�������
	static void CreateLight(void);		//���C�g�̐�������
	static void CreateFade(MODE mode);	//�t�F�[�h�̐�������

	void SetNumFPS(const int &nCountFPS) { m_nCountFPS = nCountFPS; }

	static CRenderer* GetRenderer(void) { return m_pRenderer; }					//�����_���[
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }	//�L�[�{�[�h
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }			//�}�E�X
	static CInputJoystick* GetInputJoystick(void) { return m_pInputJoystick; }	//�Q�[���p�b�h
	static CCamera* GetCamera(void) { return m_pCamera; }						//�J����
	static CLight* GetLight(void) { return m_pLight; }							//���C�g
	static CFade* GetFade(void) { return m_pFade; }								//�t�F�[�h
	static CDebugProc* GetDebug(void) { return m_pDebugProc; }					//�f�o�b�O
	static MODE GetMode(void) { return m_mode; }								//���[�h
	static CSound* GetSound(void) { return m_pSound; }							//�T�E���h
	static CPlayerData* GetPlayerData(void) { return m_pPlayerData; }			//�v���C���[�f�[�^
	static CBulletData* GetBulletData(void) { return m_pBulletData; }			//�e�f�[�^
	static CWallData* GetWallData(void) { return m_pWallData; }					//�ǃf�[�^
	static CBlockData* GetBlockData(void) { return m_pBlockData; }				//��Q���f�[�^
	static CFloorData* GetFloorData(void) { return m_pFloorData; }				//���f�[�^

private:								  
	static CRenderer* m_pRenderer;				//�����_���[
	static CInputKeyboard* m_pInputKeyboard;	//�L�[�{�[�h
	static CInputMouse* m_pInputMouse;			//�}�E�X
	static CInputJoystick* m_pInputJoystick;	//�Q�[���p�b�h
	static CCamera* m_pCamera;					//�J����
	static CLight* m_pLight;					//���C�g
	static CFade* m_pFade;						//�t�F�[�h
	static CSound* m_pSound;					//�T�E���h
	static CPlayerData* m_pPlayerData;			//�v���C���[�f�[�^
	static CBulletData* m_pBulletData;			//�e�f�[�^
	static CWallData* m_pWallData;				//�ǃf�[�^
	static CBlockData* m_pBlockData;			//��Q���f�[�^
	static CFloorData* m_pFloorData;			//���f�[�^
	static CDebugProc* m_pDebugProc;			//�f�o�b�O
	static CMode* m_pMode;						//���[�h�̃|�C���^
	static MODE m_mode;							//���݂̃��[�h
	int m_nCountFPS;							// FPS�̒l
};	

#endif