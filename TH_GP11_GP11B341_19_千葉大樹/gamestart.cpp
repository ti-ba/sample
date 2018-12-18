//=============================================================================
//
// �^�C�g����ʏ��� [GameStart.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "gamestart.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexGameStart(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureGameStart = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		D3DTextureGameStartLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				vertexWkGameStart[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				vertexWkGameStartLogo[NUM_VERTEX];		// ���_���i�[���[�N

static VERTEX_2D				vertexWkpushLogo[NUM_VERTEX];		// ���_���i�[���[�N
static LPDIRECT3DTEXTURE9		D3DTexturepushLogo = NULL;	// �e�N�X�`���ւ̃|�C���^
//=============================================================================
// ����������
//=============================================================================
HRESULT InitGameStart(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAME_START,									// �t�@�C���̖��O
		&D3DTextureGameStart);								// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAME_START_LOGO,							// �t�@�C���̖��O
		&D3DTextureGameStartLogo);							// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PUSH_LOGO,									// �t�@�C���̖��O
		&D3DTexturepushLogo);								// �ǂݍ��ރ������[

	MakeVertexGameStart();									// ���_���̍쐬

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameStart(void)
{
	if (D3DTextureGameStart != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureGameStart->Release();
		D3DTextureGameStart = NULL;
	}

	if (D3DTextureGameStartLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureGameStartLogo->Release();
		D3DTextureGameStartLogo = NULL;
	}

	if (D3DTexturepushLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTexturepushLogo->Release();
		D3DTexturepushLogo = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameStart(void)
{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			SetStage(STAGE_GAME);
		}
		// �Q�[���p�b�h�ňړ�����
		else if (IsButtonRepeat(0, BUTTON_START))
		{
			SetStage(STAGE_GAME);
		}
		else if (IsButtonRepeat(0, BUTTON_B))
		{
			SetStage(STAGE_GAME);
		}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameStart(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureGameStart);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameStart, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureGameStartLogo);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkGameStartLogo, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTexturepushLogo);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkpushLogo, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGameStart(void)
{

	// ���_���W�̐ݒ�
	vertexWkGameStart[0].vtx = D3DXVECTOR3(GAMESTART_POS_X, GAMESTART_POS_Y, 0.0f);
	vertexWkGameStart[1].vtx = D3DXVECTOR3(GAMESTART_POS_X + GAMESTART_SIZE_X, GAMESTART_POS_Y, 0.0f);
	vertexWkGameStart[2].vtx = D3DXVECTOR3(GAMESTART_POS_X, GAMESTART_POS_Y + GAMESTART_SIZE_Y, 0.0f);
	vertexWkGameStart[3].vtx = D3DXVECTOR3(GAMESTART_POS_X + GAMESTART_SIZE_X, GAMESTART_POS_Y + GAMESTART_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkGameStart[0].rhw =
	vertexWkGameStart[1].rhw =
	vertexWkGameStart[2].rhw =
	vertexWkGameStart[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkGameStart[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStart[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStart[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStart[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkGameStart[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameStart[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameStart[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameStart[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	vertexWkGameStartLogo[0].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X, GAMESTARTLOGO_POS_Y, 0.0f);
	vertexWkGameStartLogo[1].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X + GAMESTARTLOGO_SIZE_X, GAMESTARTLOGO_POS_Y, 0.0f);
	vertexWkGameStartLogo[2].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X, GAMESTARTLOGO_POS_Y + GAMESTARTLOGO_SIZE_Y, 0.0f);
	vertexWkGameStartLogo[3].vtx = D3DXVECTOR3(GAMESTARTLOGO_POS_X + GAMESTARTLOGO_SIZE_X, GAMESTARTLOGO_POS_Y + GAMESTARTLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkGameStartLogo[0].rhw =
	vertexWkGameStartLogo[1].rhw =
	vertexWkGameStartLogo[2].rhw =
	vertexWkGameStartLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkGameStartLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStartLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStartLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkGameStartLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkGameStartLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkGameStartLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkGameStartLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkGameStartLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	vertexWkpushLogo[0].vtx = D3DXVECTOR3(PUSHLOGO_POS_X, PUSHLOGO_POS_Y, 0.0f);
	vertexWkpushLogo[1].vtx = D3DXVECTOR3(PUSHLOGO_POS_X + PUSHLOGO_SIZE_X, PUSHLOGO_POS_Y, 0.0f);
	vertexWkpushLogo[2].vtx = D3DXVECTOR3(PUSHLOGO_POS_X, PUSHLOGO_POS_Y + PUSHLOGO_SIZE_Y, 0.0f);
	vertexWkpushLogo[3].vtx = D3DXVECTOR3(PUSHLOGO_POS_X + PUSHLOGO_SIZE_X, PUSHLOGO_POS_Y + PUSHLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkpushLogo[0].rhw =
	vertexWkpushLogo[1].rhw =
	vertexWkpushLogo[2].rhw =
	vertexWkpushLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkpushLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkpushLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkpushLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkpushLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkpushLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkpushLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
