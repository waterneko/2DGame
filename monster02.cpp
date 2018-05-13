//=============================================================================
//
// �G���� [monster02.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "monster02.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMonster02( int no );
void SetTextureMonster02( int no, int cntPattern );
void SetVertexMonster02( int no );
void MoveMonster02(int no);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster02[2] = { NULL };		// �e�N�X�`���ւ̃|���S��

MONSTER02				monster02Wk[MONSTER02_MAX];					// �G�l�~�[�\����

int						g_nTimerMon2;								// �^�C�}�[
int						g_nTimerMon2Move;							// �^�C�}�[
bool					g_bEnableTimerMon2;							// �^�C�}�[����ON/OFF
int						g_timeMon2 = 30;							// �^�C�}�[�̎���
int						g_timeMon2Move = 300;						// �^�C�}�[�̎���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMonster02(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER02 *monster02 = monster02Wk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MONSTER02,				// �t�@�C���̖��O
			&g_pD3DTextureMonster02[0]);		// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MONSTER02DIE,				// �t�@�C���̖��O
			&g_pD3DTextureMonster02[1]);		// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�}�[�̏�����
	g_nTimerMon2 = g_timeMon2;
	g_nTimerMon2Move = g_timeMon2Move;
	g_bEnableTimerMon2 = true;


	// �G�l�~�[�̏���������
	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		monster02->use = true;										// �g�p
		monster02Wk[0].pos = D3DXVECTOR3(1300.0f, 350.0f, 0.0f);	// ���W�f�[�^��������
		monster02Wk[1].pos = D3DXVECTOR3(1300.0f, 450.0f, 0.0f); 	// ���W�f�[�^��������
		monster02->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		monster02->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		monster02->CountAnim = 0;									// �A�j���J�E���g��������
		monster02->hp = 200;										// �G�l�~�[��HP

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y);
		monster02->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		monster02->BaseAngle = atan2f(TEXTURE_MONSTER02_SIZE_Y, TEXTURE_MONSTER02_SIZE_X);	// �G�l�~�[�̊p�x��������

		monster02->Texture = g_pD3DTextureMonster02[0];				// �e�N�X�`�����
		MakeVertexMonster02(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMonster02(void)
{
	if (g_pD3DTextureMonster02[0] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMonster02[0]->Release();
		g_pD3DTextureMonster02[0] = NULL;
	}
	if (g_pD3DTextureMonster02[1] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMonster02[1]->Release();
		g_pD3DTextureMonster02[1] = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonster02(void)
{
	MONSTER02 *monster02 = monster02Wk;				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		if (monster02->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			monster02->CountAnim++;
			if ((monster02->CountAnim % TIME_ANIMATION_MONSTER02) == 0)
			{
				// �p�^�[���̐؂�ւ�
				monster02->PatternAnim = (monster02->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER02;

				// �e�N�X�`�����W��ݒ�
				SetTextureMonster02(i, monster02->PatternAnim);			}
			
			if (monster02->pos.x - player->pos.x < 600)
			{
				monster02->pos.x -= MONSTER02_SPEED;

				if (monster02->pos.x - player->pos.x < 100)
				{

					if (monster02->pos.x > player->pos.x && monster02->pos.y > player->pos.y)
					{
						monster02->pos.x -= MONSTER02_SPEED;
						monster02->pos.y -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x > player->pos.x && monster02->pos.y < player->pos.y)
					{
						monster02->pos.x -= MONSTER02_SPEED;
						monster02->pos.y += MONSTER02_SPEED;
					}
					else if (monster02->pos.x < player->pos.x && monster02->pos.y < player->pos.y)
					{
						monster02->pos.x += MONSTER02_SPEED;
						monster02->pos.y += MONSTER02_SPEED;
					}
					else if (monster02->pos.x < player->pos.x && monster02->pos.y > player->pos.y)
					{
						monster02->pos.x += MONSTER02_SPEED;
						monster02->pos.y -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x == player->pos.x && monster02->pos.y > player->pos.y)
					{
						monster02->pos.y -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x == player->pos.x && monster02->pos.y < player->pos.y)
					{
						monster02->pos.y += MONSTER02_SPEED;
					}
					else if (monster02->pos.x > player->pos.x && monster02->pos.y == player->pos.y)
					{
						monster02->pos.x -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x < player->pos.x && monster02->pos.y == player->pos.y)
					{
						monster02->pos.x += MONSTER02_SPEED;
					}
				}
			}

			SetVertexMonster02(i);	// �ړ���̍��W�Œ��_��ݒ�

		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonster02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER02 *monster02 = monster02Wk;				// �G�l�~�[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		if (monster02->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, monster02->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER02, monster02->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMonster02( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER02 *monster02 = &monster02Wk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexMonster02( no );

	// rhw�̐ݒ�
	monster02->vertexWk[0].rhw =
	monster02->vertexWk[1].rhw =
	monster02->vertexWk[2].rhw =
	monster02->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	monster02->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster02->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster02->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster02->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	monster02->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster02->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER02, 0.0f);
	monster02->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER02);
	monster02->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER02, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER02);

	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMonster02( int no, int cntPattern )
{
	MONSTER02 *monster02 = &monster02Wk[no];			// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER02;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER02;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER02;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER02;
	
	monster02->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster02->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster02->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster02->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMonster02( int no )
{
	MONSTER02 *monster02 = &monster02Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	monster02->vertexWk[0].vtx.x = monster02->pos.x - cosf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[0].vtx.y = monster02->pos.y - sinf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[0].vtx.z = 0.0f;

	monster02->vertexWk[1].vtx.x = monster02->pos.x + cosf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[1].vtx.y = monster02->pos.y - sinf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[1].vtx.z = 0.0f;

	monster02->vertexWk[2].vtx.x = monster02->pos.x - cosf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[2].vtx.y = monster02->pos.y + sinf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[2].vtx.z = 0.0f;

	monster02->vertexWk[3].vtx.x = monster02->pos.x + cosf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[3].vtx.y = monster02->pos.y + sinf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
MONSTER02 *GetMonster02(int no)
{
	return(&monster02Wk[no]);
}

//=============================================================================
// �����X�^�[2�ړ��֐�
//=============================================================================
void MoveMonster02(int no)
{
	MONSTER02 *monster02 = &monster02Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		monster02->pos.x -= player->speedX;
	}

}

//=============================================================================
//�����X�^�[2�̎��S����
//=============================================================================
void SetMonster02die(void)
{
	MONSTER02 *monster02 = monster02Wk;			// �G�l�~�[�̃|�C���^�[��������

	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		if (monster02->hp <= 0)
		{
			monster02->Texture = g_pD3DTextureMonster02[1];
			if (g_bEnableTimerMon2)
			{
				g_nTimerMon2--;
				if (g_nTimerMon2 < 0)
				{
					g_nTimerMon2 = 0;
					monster02->use = false;
					g_nTimerMon2 = g_timeMon2;
				}
			}
		}
	}
}

