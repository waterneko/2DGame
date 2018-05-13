//=============================================================================
//
// Main���� [main.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "icon.h"
#include "enemy.h"
#include "bullet.h"
#include "bulletenemy.h"
#include "bg.h"
#include "title.h"
#include "result.h"
#include "score.h"
#include "sound.h"
#include "gameover.h"
#include "skill.h"
#include "attack.h"
#include "life.h"
#include "mp.h"
#include "monster01.h"
#include "monster01bullet.h"
#include "monster02.h"
#include "portal.h"
#include "boss1.h"
#include "boss1bullet.h"
#include "boss1icon.h"
#include "boss1hp.h"
#include "boss1bg.h"
#include "blackportal.h"
#include "hoshizora.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("���@�g���̗�")				// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void CheckHit(void);
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

void InitGame(void);

#ifdef _DEBUG
void DrawDebugFont(void);
#endif

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^
int						g_nCountFPS;				// FPS�J�E���^
#endif

int						g_nStage = 0;				// �X�e�[�W�ԍ�

LPDIRECTSOUNDBUFFER8	g_pBGM;						// BGM�p�o�b�t�@

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// �E�B���h�E�̍����W
						CW_USEDEFAULT,																		// �E�B���h�E�̏���W
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hWnd, true)))
	{
		return -1;
	}

	//// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	//if (FAILED(Init(hWnd, false)))
	//{
	//	return -1;
	//}

	//bool flag = false;//�E�B���h�E�Y���[�h�p�̃t���O false�t���X�N���[�����[�h

	//if (MessageBox(hWnd, "�E�B���h�E�Y���[�h���N�����܂���", "���[�h�m�F", MB_YESNO) == IDYES)
	//{
	//	flag = true;//true�̓E�B���h�E�Y���[�h
	//}
	//if (FAILED(Init(hWnd, flag)))
	//{
	//	return -1;
	//}


	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;
	
	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPS�𑪒�
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

				Update();			// �X�V����
				Draw();				// �`�揈��
				
				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �J���[���[�h�̎w��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		//d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		d3dpp.BackBufferFormat           = D3DFMT_X8R8G8B8;					// �o�b�N�o�b�t�@

		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,								// �f�B�X�v���C�^�C�v
									hWnd,										// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,										// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&g_pD3DDevice)))							// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O���s��Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�

	// �e�N�X�`���X�e�[�W���Z��������
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

#ifdef _DEBUG
	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif
	
	// �T�E���h������
	InitSound(hWnd);
	// ���[�h�ƍĐ�
	g_pBGM = LoadSound(BGM_00);
	PlaySound(g_pBGM, E_DS8_FLAG_LOOP);

	// �v���C���[�̏���������
	InitPlayer(0);

	// �v���C���[�̃A�C�R������������
	InitIcon(0);

	// �G�l�~�[�̏���������
	InitEnemy(0);

	// �����X�^�[1�̏���������
	InitMonster01(0);

	// �����X�^�[�P�o���b�g�̏���������
	InitMonster01bullet(0);

	// �����X�^�[2�̏���������
	InitMonster02(0);

	// �o���b�g�̏���������
	InitBullet(0);

	// �X�L���̏���������
	InitSkill(0);

	// �A�^�b�N�̏���������
	InitAttack(0);

	// ���C�t�̏���������
	InitLife(0);

	// MP�̏���������
	InitMP(0);

	// �G�l�~�[�̃o���b�g�̏���������
	InitBulletenemy(0);

	// BG������
	InitBG(0);

	// ���@�w�̏���������
	InitPortal(0);

	// �u���b�N���@�w�̏���������
	InitBlackportal(0);

	// �{�X�P�̏���������
	InitBoss1(0);

	// �{�X�P�o���b�g�̏���������
	InitBoss1bullet(0);

	// �{�X�P�̃A�C�R���̏���������
	InitBoss1icon(0);

	// �{�X�P��HP�̏���������
	InitBoss1hp(0);

	// �{�X�P�̔w�i�̏���������
	InitBOSS1BG(0);
	
	// ����̏���������
	InitHoshizora(0);

	// �^�C�g��������
	InitTitle();

	// ���U���g������
	InitResult();

	// �I�[�o�[������
	InitGameover();

	// �X�R�A������
	InitScore(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// ���͏����̏I������
	UninitInput();

	// �v���C���[�̏I������
	UninitPlayer();

	// �v���C���[�̃A�C�R���̏I������
	UninitIcon();
	
	// �G�l�~�[�̏I������
	UninitEnemy();

	// �����X�^�[1�̏I������
	UninitMonster01();

	// �����X�^�[�P�o���b�g�̏I������
	UninitMonster01bullet();

	// �����X�^�[2�̏I������
	UninitMonster02();

	// �o���b�g�̏I������
	UninitBullet();

	// �G�l�~�[�̃o���b�g�̏I������
	UninitBulletenemy();

	// �X�L���̏I������
	UninitSkill();

	// �A�^�b�N�̏I������
	UninitAttack();

	// ���C�t�̏I������
	UninitLife();

	// MP�̏I������
	UninitMP();

	// BG�I������
	UninitBG();
	
	// ���@�w�̏I������
	UninitPortal();

	// �u���b�N���@�w�̏I������
	UninitBlackportal();

	// ����̏I������
	UninitHoshizora();

	// �{�X�P�̏I������
	UninitBoss1();

	// �{�X�PHP�̏I������
	UninitBoss1hp();

	// �{�X�P�o���b�g�̏I������
	UninitBoss1bullet();

	// �{�X�P�A�C�R���̏I������
	UninitBoss1icon();

	// �{�X�P�̔w�i�̏I������
	UninitBOSS1BG();

	// �^�C�g���I������
	UninitTitle();

	// ���U���g�I������
	UninitResult();

	// �I�[�o�[�I������
	UninitGameover();
	
	// �X�R�A�I������
	UninitScore();

	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
	}

	// �T�E���h�����̏I������
	if (g_pD3D != NULL)
	{
		g_pBGM->Release();
		g_pBGM = NULL;
	}
	UninitSound();

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();
	
	// ��ʑJ��
	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle();

		if (IsButtonTriggered(0, BUTTON_B))
		{
			SetStage(STAGE_GAME);
		}
		else if (IsButtonTriggered(0, BUTTON_START))
		{
			SetStage(STAGE_GAME);
		}
		break;

	case STAGE_GAME:
		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �v���C���[�̃A�C�R���̍X�V����
		UpdateIcon();

		// �G�l�~�[�̍X�V����
		UpdateEnemy();

		// �����X�^�[1�̍X�V����
		UpdateMonster01();

		// �����X�^�[�P�o���b�g�̍X�V����
		UpdateMonster01bullet();

		// �����X�^�[2�̍X�V����
		UpdateMonster02();

		// �o���b�g�̍X�V����
		UpdateBullet();

		// �X�L���̍X�V����
		UpdateSkill();

		// �A�^�b�N�̍X�V����
		UpdateAttack();

		// �G�l�~�[�̃o���b�g�̍X�V����
		UpdateBulletenemy();

		// ���@�w�̍X�V����
		UpdatePortal();


		// ���C�t�̍X�V����
		UpdateLife();

		// MP�̍X�V����
		UpdateMP();

		// BG�̍X�V����
		UpdateBG();

		// �X�R�A�̍X�V����
		UpdateScore();
		
		// �����蔻��
		CheckHit();

		if (IsButtonTriggered(0, BUTTON_Y))
		{
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_TITLE);
		}
		break;

	case STAGE_GAME_BOSS1:

		// �{�X�P�̔w�i�̍X�V����
		UpdateBOSS1BG();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �v���C���[�̃A�C�R���̍X�V����
		UpdateIcon();

		// �X�L���̍X�V����
		UpdateSkill();

		// �A�^�b�N�̍X�V����
		UpdateAttack();

		// ���C�t�̍X�V����
		UpdateLife();

		// MP�̍X�V����
		UpdateMP();

		// �u���b�N���@�w�̍X�V����
		UpdateBlackportal();

		// �{�X�P�̍X�V����
		UpdateBoss1();

		// �{�X�PHP�̍X�V����
		UpdateBoss1hp();

		// �{�X�P�̍X�V����
		UpdateBoss1bullet();

		// �{�X�P�A�C�R���̍X�V����
		UpdateBoss1icon();

		// �X�R�A�̍X�V����
		UpdateScore();

		// ����̍X�V����
		UpdateHoshizora();


		// �����蔻��
		CheckHit();

		if (IsButtonTriggered(0, BUTTON_Y))
		{
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_TITLE);
		}

		break;

	case STAGE_GAMEOVER:
		// �X�R�A�̍X�V����
		UpdateScore();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_TITLE);
		}
		else if(IsButtonTriggered(0, BUTTON_B))
		{
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_TITLE);
		}
		break;
	
	case STAGE_RESULT:
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_TITLE);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_TITLE);
		}

		break;

	//case STAGE_GAMEOVER:
	//	UpdateGameover();
	}

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// ��ʑJ��
		switch (g_nStage)
		{
		case STAGE_TITLE:
			DrawTitle();
			break;

		case STAGE_GAME:
		//case STAGE_GAME_END:
			// BG�̕`�揈��
			DrawBG();

			//�G�l�~�[�̕`�揈��
			DrawEnemy();

			// �����X�^�[1�̕`�揈��
			DrawMonster01();

			// �����X�^�[�P�o���b�g�̕`�揈��
			DrawMonster01bullet();

			// �����X�^�[2�̕`�揈��
			DrawMonster02();

			// �v���C���[�̕`�揈��
			DrawPlayer();

			// �v���C���[�̃A�C�R���̕`�揈��
			DrawIcon();

			// �o���b�g�̕`�揈��
			DrawBullet();

			// �G�l�~�[�̃o���b�g�̕`�揈��
			DrawBulletenemy();

			// �X�L���̕`�揈��
			DrawSkill();

			// �A�^�b�N�̕`�揈��
			DrawAttack();

			// ���@�w�̕`�揈��
			DrawPortal();
			
			// ���C�t�̕`�揈��
			DrawLife();

			// MP�̕`�揈��
			DrawMP();
			
			// �X�R�A�̕`�揈��
			//DrawScore();
			break;

		case STAGE_GAME_BOSS1:
			// �{�X�P�̔w�i�̕`�揈��
			DrawBOSS1BG();

			// �v���C���[�̕`�揈��
			DrawPlayer();

			// �v���C���[�̃A�C�R���̕`�揈��
			DrawIcon();

			// �X�L���̕`�揈��
			DrawSkill();

			// �A�^�b�N�̕`�揈��
			DrawAttack();

			// �u���b�N���@�w�̕`�揈��
			DrawBlackportal();

			// �{�X�P�̕`�揈��
			DrawBoss1();

			// �{�X�P�o���b�g�̕`�揈��
			DrawBoss1bullet();

			// �{�X�PHP�̕`�揈��
			DrawBoss1hp();

			// �{�X�P�A�C�R���̕`�揈��
			DrawBoss1icon();

			// ���C�t�̕`�揈��
			DrawLife();

			// MP�̕`�揈��
			DrawMP();

			// �X�R�A�̕`�揈��
			//DrawScore();

			// ����̕`�揈��
			DrawHoshizora();

			break;

		case STAGE_RESULT:
			DrawResult();
			break;

		case STAGE_GAMEOVER:
			DrawGameover();
			break;
		}

#ifdef _DEBUG
		// �f�o�b�O�\��
		DrawDebugFont();
#endif
		
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// �f�o�b�O�\������
//=============================================================================
void DrawDebugFont(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	PLAYER *player = GetPlayer(0);
	BG *bg = GetBG(0);
	MONSTER01 *monster01 = GetMonster01(0);
	ATTACK *attack = GetAttack(0);
	BOSS1 *boss1 = GetBoss1(0);
	 //�e�L�X�g�`��
	//sprintf(str, _T("FPS:%d"), g_nCountFPS);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 20;
	//sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 40;
	//sprintf(str, "BOSS HP:%d", boss1->hp);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 60;
	//sprintf(str, "BG0X:%f", bg[0].pos.x);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 80;
	//sprintf(str, "MP:%d", player->mp);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

//=============================================================================
// ��ʑJ��
//=============================================================================
void SetStage( int stage )
{
	//if( state < 0 || state >= STATE_MAX ) return;

	g_nStage = stage;
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer(0);						// �v���C���[�̃|�C���^�[��������
	ENEMY *enemy = GetEnemy(0);							// �G�l�~�[�̃|�C���^�[��������
	BULLET *bullet = GetBullet(0);						// �o���b�g�̃|�C���^�[��������
	BULLETENEMY *bulletenemy = GetBulletenemy(0);		// �G�l�~�[�̃o���b�g�̃|�C���^�[��������
	MONSTER01 *monster01 = GetMonster01(0);				// �����X�^�[1�̃|�C���^�[������
	MONSTER02 *monster02 = GetMonster02(0);				// �����X�^�[2�̃|�C���^�[������
	ATTACK *attack = GetAttack(0);						// �A�^�b�N�X�L���̃|�C���^�[������
	SKILL *skill = GetSkill(0);							// �X�L���̃|�C���^�[��������
	BOSS1BULLET *boss1bullet = GetBoss1bullet(0);		// �{�X�P�̒e�|�C���^�[��������
	BOSS1 *boss1 = GetBoss1(0);							// �{�X�P�̃|�C���^�[��������
	BOSS1ICON *boss1icon = GetBoss1icon(0);				// �{�X�P�̃A�C�R����������
	BOSS1HP *boss1hp = GetBoss1hp(0);					// �{�X�PHP��������
	MONSTER01BULLET *monster01bullet = GetMonster01bullet(0);
	PORTAL *portal = GetPortal(0);						// �|�[�^���̃|�C���^�[��������
	BLACKPORTAL *blackportal = GetBlackportal(0);		// �u���b�N���@�w�̃|�C���^�[��������
	int cnt = 0;										// �G�̐��𐔂���

	// �G�Ƒ���L����(BB)
	player = GetPlayer(0);								// �v���C���[�̃|�C���^�[��������
	for( int i = 0; i < MONSTER01_MAX; i++, monster01++ )
	{
		if(monster01->use == false )	continue;

		if( CheckHitBB( GetPlayer(0)->pos, monster01->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X,TEXTURE_MONSTER01_SIZE_Y) ) )
		{

			// ����L�����N�^�[�͎���

			// �G�L�����N�^�[�͓|�����
			monster01->use = false;

			// HP��������
			player->hp -= 1;

		}
	}

	// �����X�^�[2�Ƒ���L����(BB)
	monster02 = GetMonster02(0);			// �����X�^�[�̃|�C���^�[��������
	for (int i = 0; i < MONSTER02_MAX; i++, monster01++)
	{
		if (monster02->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, monster02->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y)))
		{
			// HP��������
			player->hp -= 1;

			// �����X�^�[������
			monster02->use = false;

		}
	}

	// �v���C���[�ƃ|�[�^��(BB)
	portal = GetPortal(0);						// �|�[�^���̃|�C���^�[��������
	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		if (portal->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, portal->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_PORTAL_SIZE_X, TEXTURE_PORTAL_SIZE_Y)))
		{
			InitPlayer(3);			// �v���C���[�̍��W��������
			SetStage(STAGE_GAME_BOSS1);
			blackportal->use = true;
		}
	}


	// �A�^�b�N�X�L���ƃ����X�^�[1(BB)
	monster01 = GetMonster01(0);
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < MONSTER01_MAX; j++, monster01++)
		{
			if (monster01->use == false) continue;

			if (CheckHitBB(attack->pos, monster01->pos, D3DXVECTOR2(TEXTURE_ATTACK_SIZE_X, TEXTURE_ATTACK_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X, TEXTURE_MONSTER01_SIZE_Y)))
			{
				// �G��HP����
				monster01->hp -= 1;		

				// MP�̉�
				player->mp += 1;

				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}

	// �X�L���ƃ����X�^�[1(BB)
	skill = GetSkill(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < MONSTER01_MAX; j++, monster01++)
		{
			if (monster01->use == false) continue;

			if (CheckHitBB(skill->pos, monster01->pos, D3DXVECTOR2(TEXTURE_SKILL_SIZE_X, TEXTURE_SKILL_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X, TEXTURE_MONSTER01_SIZE_Y)))
			{
				// �G��HP����
				monster01->hp -= 10;

				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}

	// �A�^�b�N�X�L���ƃ����X�^�[2(BB)
	monster02 = GetMonster02(0);
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < MONSTER02_MAX; j++, monster02++)
		{
			if (monster02->use == false) continue;

			if (CheckHitBB(attack->pos, monster02->pos, D3DXVECTOR2(TEXTURE_ATTACK_SIZE_X, TEXTURE_ATTACK_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y)))
			{
				// �G��HP����
				monster02->hp -= 1;

				// MP�̉�
				player->mp += 1;

				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}

	// �X�L���ƃ����X�^�[2(BB)
	skill = GetSkill(0);
	monster02 = GetMonster02(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < MONSTER02_MAX; j++, monster02++)
		{
			if (monster02->use == false) continue;

			if (CheckHitBB(skill->pos, monster02->pos, D3DXVECTOR2(TEXTURE_SKILL_SIZE_X, TEXTURE_SKILL_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y)))
			{
				// �G��HP����
				monster02->hp -= 10;

				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}

	// �A�^�b�N�ƃG�l�~�[(BB)
	enemy = GetEnemy(0);
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBB(attack->pos, enemy->pos, D3DXVECTOR2(TEXTURE_ATTACK_SIZE_X, TEXTURE_ATTACK_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
			{
				// �G��HP����
				enemy->hp -= 10;

				// MP�̉�
				player->mp += 1;

				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}

	// �X�L���ƃG�l�~�|(BB)
	skill = GetSkill(0);
	enemy = GetEnemy(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBB(skill->pos, enemy->pos, D3DXVECTOR2(TEXTURE_SKILL_SIZE_X, TEXTURE_SKILL_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
			{
				// �G��HP����
				enemy->hp -= 200;

				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}



	// �X�L���ƃ{�X1(BC)
	boss1 = GetBoss1(0);
	skill = GetSkill(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < BOSS1_MAX; j++, boss1++)
		{
			if (boss1->use == false) continue;

			if (CheckHitBC(skill->pos, boss1->pos, TEXTURE_SKILL_SIZE_X, TEXTURE_BOSS1_SIZE_X))
			{
				// HP�̌���
				boss1->hp -= 200;

				// �X�R�A�v�Z
				AddScore(10);
			}
		}
	}

	// �A�^�b�N�ƃ{�X�P(BB)
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < BOSS1_MAX; j++, boss1++)
		{
			if (boss1->use == false) continue;
			
			if (CheckHitBC(attack->pos, boss1->pos,TEXTURE_ATTACK_SIZE_X,TEXTURE_BOSS1_SIZE_X))
			{
				// HP�̌���
				boss1->hp -= 10;

				// MP�̉�
				player->mp += 1;

				// �X�R�A�v�Z
				AddScore(1);
			}
		}
	}






	// �G�ƓG(BB)
	enemy = GetEnemy(0);									// �G�l�~�[�̃|�C���^�[��������
	for (int i = 0; i < ENEMY_MAX - 1; i++, enemy++)
	{
		if (enemy->use == false)	continue;

		if (CheckHitBB(GetEnemy(i)->pos, GetEnemy(i+1)->pos, D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
		{
			enemy->pos.x = enemy->pos.x +10.0f;
		}
	}


	// �e�ƓG(BC)
	enemy = GetEnemy(0);					// �G�l�~�[�̃|�C���^�[��������
	for( int i = 0; i < BULLET_MAX; i++, bullet++ )
	{
		if( bullet->use == false ) continue;

		for( int j = 0; j < ENEMY_MAX; j++, enemy++ )
		{
			if( enemy->use == false ) continue;

			if( CheckHitBC( bullet->pos, enemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY_SIZE_X ) )
			{
				bullet->use = false;	// �e�̏��ŏ������s��
				enemy->hp -= 1;			// HP�̌���
				if (enemy->hp == 0)
				{
					enemy->use = false;		// �G�͓|�����
				}

				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}


	// �{�X�̒e�ƃv���C���[(BC)
	boss1bullet = GetBoss1bullet(0);		// �{�X�P�̒e�|�C���^�[��������
	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == false) continue;

		if (CheckHitBB(boss1bullet->pos, player->pos, D3DXVECTOR2(TEXTURE_BOSS1BULLET_SIZE_X, TEXTURE_BOSS1BULLET_SIZE_Y), D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y)))
		{
			player->hp -= 2;				//HP�̌���
			boss1bullet->use = false;		//�e�̏��ŏ������s��
		}
	}


	// �����ƓG�̒e(BC)
	player = GetPlayer(0);			// �v���C���[�̃|�C���^�[��������
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		if (bulletenemy->use == false) continue;

		if (CheckHitBB(bulletenemy->pos, player->pos, D3DXVECTOR2(TEXTURE_BULLETENEMY_SIZE_X, TEXTURE_BULLETENEMY_SIZE_Y),D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y)))
		{
			bulletenemy->use = false;	// �e�̏��ŏ������s��
			bulletenemy->pos.x = enemy->pos.x;
			player->hp -= 1;			//hp������

		}

	}

	// �����ƃ����X�^�[�P�o���b�g(BB)
	monster01bullet = GetMonster01bullet(0);		// �����X�^�[�P�o���b�g�̃|�C���^�[��������
	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == false) continue;

		if (CheckHitBB(monster01bullet->pos, player->pos, D3DXVECTOR2(TEXTURE_MONSTER01BULLET_SIZE_X, TEXTURE_MONSTER01BULLET_SIZE_Y), D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y)))
		{
			monster01bullet->use = false;	// �e�̏��ŏ������s��
			monster01bullet->pos.x = -100.0f;
			player->hp -= 1;			//hp������

		}

	}


	// �A�^�b�N�ƃu���b�N���@�w(BC)
	blackportal = GetBlackportal(0);		// �u���b�N���@�w�̃|�C���^�[��������
	attack = GetAttack(0);					// �A�^�b�N�̃|�C���^�[��������
	boss1hp = GetBoss1hp(0);				// �{�X�PHP�̏�����
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < BLACKPORTAL_MAX; j++, blackportal++)
		{
			if (blackportal->use == false) continue;

			if (CheckHitBC(attack->pos, blackportal->pos, TEXTURE_ATTACK_SIZE_X,TEXTURE_BLACKPORTAL_SIZE_X))
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

				SetHoshizora(pos);

				boss1icon->use = true;
				for (int i = 0; i < BOSS1HP_MAX; i++,boss1hp++)
				{
					boss1hp->use = true;
				}
				blackportal->use = false;

				// �X�R�A�v�Z
				AddScore(1);
			}
		}
	}





	// �v���C���[��HP����
	player = GetPlayer(0);					// �v���C���[�̃|�C���^�[��������

	if (player->hp <= 0)
	{
		player->use = false;				// �v���C���[�͎���
	}

	// �����X�^�[�P��HP����
	monster01 = GetMonster01(0);			// �����X�^�[�̃|�C���^�[��������

	for (int j = 0; j < MONSTER01_MAX; j++, monster01++)
	{
		if (monster01->use == false) continue;

		if (monster01->hp <= 0)
		{
			SetMonster01die();
			//monster01->use = false;
		}
	}

	// �����X�^�[2��HP����
	monster02 = GetMonster02(0);			// �����X�^�[�̃|�C���^�[��������

	for (int j = 0; j < MONSTER02_MAX; j++, monster02++)
	{
		if (monster02->use == false) continue;

		if (monster02->hp <= 0)
		{
			//monster02->use = false;
			SetMonster02die();
		}
	}

	// �G�l�~�[��HP����
	enemy = GetEnemy(0);			// �G�l�~�[�̃|�C���^�[��������

	for (int j = 0; j < ENEMY_MAX; j++, enemy++)
	{
		if (enemy->use == false) continue;

		if (enemy->hp <= 0)
		{
			SetEnemydie();
		}
	}

	// �G���S�ł������ʑJ��
	//enemy = GetEnemy(0);					// �G�l�~�[�̃|�C���^�[��������
	//for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	//{
	//	if (enemy->use == true)
	//	{
	//		cnt++;
	//	}
	//}

	//// ���������ʓG���S�ŁH
	//if (cnt == 0)
	//{
	//	SetStage(STAGE_RESULT);
	//}
	
	// �v���C���[�����񂾂��ʑJ��
	player = GetPlayer(0);
	if (player->use == false)
	{
		SetStage(STAGE_GAMEOVER);
	}
	

	// �{�X�P��|������H
	if (boss1->hp < 0)
	{
		SetStage(STAGE_RESULT);

	}
	
}


//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBB( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2 )
{
	size1 /= 2.0f;	// ���T�C�Y�ɂ���
	size2 /= 2.0f;	// ����

	if( ((pos2.x + size2.x) > (pos1.x - size1.x)) && ((pos1.x + size1.x) > (pos2.x - size2.x)) &&
		((pos2.y + size2.y) > (pos1.y - size1.y)) && ((pos1.y + size1.y) > (pos2.y - size2.y)) )
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBC( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2 )
{
	
	D3DXVECTOR3 temp = pos1 - pos2;
	float len = D3DXVec3LengthSq(&temp);

	if (len <= ((size1 + size2) * (size1 + size2)))
	{
		return true;
	}

	return false;
}


//=============================================================================
// �Q�[���̍ď�������������
// �߂�l�F����
//=============================================================================
void InitGame(void)
{
	InitPlayer(1);			// �v���C���[�̍ď�����
	InitEnemy(1);			// �G�l�~�[�̍ď�����
	InitBullet(1);			// �o���b�g�̍ď�����
	InitBulletenemy(1);		// �G�l�~�[�̃o���b�g�̍ď�����
	InitPortal(1);			// ���@�w�̍ď�����
	InitSkill(1);			// �X�L���̍ď�����
	InitLife(1);			// ���C�t�̍ď�����
	InitMP(1);				// MP�̍ď�����
	InitAttack(1);			// �A�^�b�N�̍ď�����
	InitBoss1(1);			// �{�X�P�̍ď�����
	InitBoss1bullet(1);		// �{�X�P�e�̍ď�����
	InitBoss1hp(1);			// �{�X�PHP�̍ď�����
	InitBoss1icon(1);		// �{�X�P�A�C�R���̍ď�����
	InitMonster01(1);		// �����X�^�[�̍ď�����
	InitMonster01bullet(1);	// �����X�^�[1�̃o���b�g�ď�����
	InitMonster02(1);		// �����X�^�[�̍ď�����


	InitScore(1);		// �X�R�A�̍ď�����
	InitBG(1);			// BG�̍ď�����
	InitBOSS1BG(1);		// �{�X�P�̔w�i�̍ď�����
}

