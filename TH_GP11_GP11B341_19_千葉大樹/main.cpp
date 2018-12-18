//=============================================================================
//
// Main���� [main.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "enemy2.h"
#include "boss.h"
#include "bullet.h"
#include "bg.h"
#include "title.h"
#include "curea.h"
#include "score.h"
#include "sound.h"
#include <time.h>
#include "enemybullet.h"
#include "guage.h"
#include "enemyguage.h"
#include "tyutogeme.h"
#include "nakami.h"
#include "gamestart.h"
#include "tyutoenemy.h"
#include "gameover.h"
#include "bom.h"
#include "bomguage.h"
#include "effect.h"
#include "effect2.h"
#include "bossbullet.h"
#include "bossguage.h"
#include "enemyguage2.h"
#include "enemybullet2.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("�V���[�e�B���O�Q�[��")		// �E�C���h�E�̃L���v�V������
#define SAFE_RELEASE(ptr)
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

#ifdef _DEBUG
void DrawDebugFont(void);
#endif

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9				D3D = NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		D3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
LPD3DXFONT				D3DXFont = NULL;		// �t�H���g�ւ̃|�C���^
int						CountFPS;				// FPS�J�E���^
#endif

int						Stage =3;				// �^�C�g�����

LPDIRECTSOUNDBUFFER8	BGM;					// BGM�p�o�b�t�@
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
		(HBRUSH)(COLOR_WINDOW + 1),
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
		CW_USEDEFAULT,											// �E�B���h�E�̍����W
		CW_USEDEFAULT,											// �E�B���h�E�̏���W
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,		// �E�B���h�E����
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hWnd, true)))
	{
		return -1;
	}

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
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
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
			dwCurrentTime = timeGetTime();			// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				CountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPS�𑪒�
#endif
				dwFPSLastTime = dwCurrentTime;		// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;		// ��������������ۑ�

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
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
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
	D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (D3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;					// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth =  SCREEN_WIDTH;		// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;		// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat = d3ddm.Format;		// �J���[���[�h�̎w��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;						// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;							// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT,		// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,								// �f�B�X�v���C�^�C�v
		hWnd,										// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,										// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&D3DDevice)))								// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&D3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&D3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// �J�����O���s��Ȃ�
	D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���u�����h���s��
	D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�

#ifdef _DEBUG
	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(D3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &D3DXFont);
#endif

	// �T�E���h������
	InitSound(hWnd);
	SAFE_RELEASE(BGM);
	// ���[�h�ƍĐ�
	BGM = LoadSound(BGM_01);
	PlaySound(BGM, E_DS8_FLAG_LOOP);


	// �v���C���[�̏���������
	InitPlayer(0);

	// �G�l�~�[�̏���������
	InitEnemy(0);

	// �G�l�~�[�̏�����
	//InitEnemy2(0);

	// �{�X�̏�����
	InitBoss(0);

	// �{�X�Q�[�W�̏�����
	InitBossguage(0);

	// �o���b�g�̏���������
	InitBullet(0);

	InitBossBullet(0);

	InitEnemyBullet2(0);

	// �{���̏�����
	InitBom(0);

	// �{���̃Q�[�W������
	InitBomGuage(0);

	// BG������
	InitBG(0);

	// �^�C�g��������
	InitTitle();

	// �Q�[���^�C�g��������
	InitGameStart();

	// �N���A������
	InitCurea();

	// �Q�[���I�[�o�[������
	InitGameover();

	// �X�R�A������
	InitScore(0);

	// �G�̒e�̏�����
	InitEnemyBullet(0);

	// �{�X�̒e
	InitBossBullet(0);

	// �Q�[�W������
	InitGuage(0);

	// �G�l�~�[�Q�[�W������
	InitEnemyGuage(0);

	// �G�l�~�[�Q�[�W�Q������
	InitEnemyGuage2(0);

	// �`���[�g�G�l�~�[������
	InitTyutoEnemy(0);

	// �`���[�g�Q�[��������
	InitTyutoGame( hWnd,  bWindow);

	// �G�t�F�N�g������
	InitEffect(0);

	// �G�t�F�N�g�Q������
	InitEffect2(0);

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
	//UninitPlayer();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �G�l�~�[�̏I������
	//UninitEnemy2();

	// �{�X�̏I������
	//UninitBoss();

	// �{�X�Q�[�W�̏I������
	UninitBossguage();

	// �{�X�̒e�̏I������
	UninitBossBullet();

	// �o���b�g�̏I������
	UninitBullet();

	//�{���̏I������
	UninitBom();

	//�{���̃Q�[�W�̏I������
	UninitBomGuage();

	// BG�I������
	UninitBG();

	// �^�C�g���I������
	UninitTitle();

	// �Q�[���^�C�g���I������
	UninitGameStart();

	// �N���A�I������
	UninitCurea();

	//�Q�[���I�[�o�[�I������
	UninitGameover();

	// �X�R�A�I������
	UninitScore();

	// �G�̒e�I������
	UninitEnemyBullet();

	//�Q�[�W�I������
	UninitGuage();

	//�G�l�~�[�Q�[�W�I������
	UninitEnemyGuage();

	// �G�l�~�[�Q�[�W�Q�I������
	UninitEnemyGuage2();

	//�`���[�g�G�l�~�[�I������
	UninitTyutoEnemy();

	//�`���[�g�Q�[���I������
	UninitTyutoGame();

	// �G�t�F�N�g�I������
	UninitEffect();

	// �G�t�F�N�g�Q�I������
	UninitEffect2();

	UninitEnemyBullet2();

	if (D3DDevice != NULL)
	{// �f�o�C�X�̊J��
		D3DDevice->Release();
	}

	if (D3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		D3D->Release();
	}

	SAFE_RELEASE(BGM)
	UninitSound();
#define SAFE_RELEASE(ptr)
	
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	
	// ���͂̍X�V����
	UpdateInput();
	
	// ��ʑJ��
	switch (Stage)
	{
		// ���͂̍X�V����
	case STAGE_TITLE:
		UpdateTitle();
		break;

	case STAGE_TYUTO_GAME:
		UpdateTyutoGame();
		break;

	case STAGE_GAME_START:
		UpdateGameStart();
		break;

	case STAGE_GAME:	
		UpdateNakami();
		break;

	case STAGE_BOSS:
		UpdateBoss();
		break;

	case STAGE_SCORE:
		UpdateScore();
		break;

	case STAGE_CUREA:
		UpdateCurea();
		break;
		
	case STAGE_GAME_OVER:
		UpdateGameover();
		break;
	}
	

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(D3DDevice->BeginScene()))
	{
		// ��ʑJ��
		switch (Stage)
		{
		case STAGE_TITLE:
			DrawTitle();
			break;

		case STAGE_TYUTO_GAME:
			DrawTyutoGame();
			break;

		case STAGE_GAME_START:
			DrawGameStart();
			break;

		case STAGE_GAME:
			DrawNakami();
			break;

		case STAGE_BOSS:
			DrawBoss();
			break;

		case STAGE_SCORE:
			DrawScore();
			break;

		case  STAGE_CUREA:
			DrawCurea();
			break;

		case STAGE_GAME_OVER:
			DrawGameover();
			break;
		}

#ifdef _DEBUG
		// �f�o�b�O�\��
		DrawDebugFont();
#endif

		// Direct3D�ɂ��`��̏I��
		D3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(D3DDevice);
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

	// �e�L�X�g�`��
	sprintf(str, _T("FPS:%d"), CountFPS);
	D3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	rect.top = 20;
	sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
	D3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}
#endif

//=============================================================================
// ��ʑJ��
//=============================================================================
void SetStage(int stage)
{
	if( stage < 0 || stage >= STAGE_MAX ) return;

	Stage = stage;
}

