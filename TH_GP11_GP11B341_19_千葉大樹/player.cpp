//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : GP_11B_341_19 ��t�@���
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "bom.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer( int no );
void SetTexturePlayer( int no, int cntPattern );
void SetVertexPlayer( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

PLAYER					playerWk[PLAYER_MAX];			// �v���C���[�\����

LPDIRECTSOUNDBUFFER8	HitSE;							// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &playerWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PLAYER,				// �t�@�C���̖��O
			&D3DTexturePlayer);					// �ǂݍ��ރ������̃|�C���^

		HitSE = LoadSound(HIT_00);

	}

	// �v���C���[�̏���������
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;									// �g�p
		player->pos = D3DXVECTOR3(200.0f+200.0f, 300.0f, 0.0f);	// ���W�f�[�^��������
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		player->PatternAnim = rand() % ANIM_PATTERN_NUM;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		player->CountAnim = 0;								// �A�j���J�E���g��������
		player->firecount = 0;
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
		player->Radius = D3DXVec2Length(&temp);				// �v���C���[�̔��a��������
		player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// �v���C���[�̊p�x��������
		player->Texture = D3DTexturePlayer;					// �e�N�X�`�����
		MakeVertexPlayer(i);								// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (D3DTexturePlayer != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexturePlayer->Release();
		D3DTexturePlayer = NULL;
	}

	if (HitSE != NULL)
	{	// �e�N�X�`���̊J��
		HitSE->Release();
		HitSE = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];
	D3DXVECTOR3 pos = player->pos;
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			if (GetKeyboardPress(DIK_DOWN))
			{
				player->pos.y += 8.0f;
			}
			else if (GetKeyboardPress(DIK_UP))
			{
				player->pos.y -= 8.0f;
			}

			if (GetKeyboardPress(DIK_RIGHT))
			{
				player->pos.x += 8.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT))
			{
				player->pos.x -= 8.0f;
			}

			// ��]
			if (GetKeyboardPress(DIK_R))
			{
				player->rot.z += 0.1f;
			}

			// �g��k��
			if (GetKeyboardPress(DIK_F))
			{
				player->Radius -= 1.0f;
			}
			else if (GetKeyboardPress(DIK_T))
			{
				player->Radius += 1.0f;
			}


			// �Q�[���p�b�h�ňړ�����
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				player->pos.y += 2.0f;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				player->pos.y -= 2.0f;
			}

			if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->pos.x += 2.0f;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				player->pos.x -= 2.0f;
			}

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexPlayer(i);

			// �e����
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBullet(pos);
			}

			if (GetKeyboardPress(DIK_SPACE))
			{
				player-> firecount++;
				if (player->firecount == 8)
				{
					pos.y -= TEXTURE_PLAYER_SIZE_Y;
					SetBullet(pos);
					player->firecount = 0;
				}
			}
			else if(IsButtonRepeat(0, BUTTON_B))
			{
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBullet(pos);
				player->firecount = 0;
			}

			if (GetKeyboardTrigger(DIK_V))
			{	
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBom(pos);
			}
			else if (IsButtonRepeat(0, BUTTON_C))
			{
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBom(pos);
			}

			if (GetKeyboardRelease(DIK_SPACE))
			{
				player->firecount = 0;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &playerWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, player->Texture);

			// �|���S���̕`��
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &playerWk[no];

	// ���_���W�̐ݒ�
	SetVertexPlayer(no);

	// rhw�̐ݒ�
	player->vertexWk[0].rhw = 1.0f;
	player->vertexWk[1].rhw = 1.0f;
	player->vertexWk[2].rhw = 1.0f;
	player->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	player->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );
	player->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );

	player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	player->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int no, int cntPattern )
{
	PLAYER *player = &playerWk[no];
	
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;
	
	player->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	player->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	player->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	player->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];
	
	// ���_���W�̐ݒ�
	player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

