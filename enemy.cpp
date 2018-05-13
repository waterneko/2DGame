//=============================================================================
//
// �G���� [enemy.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "player.h"
#include "bulletenemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy( int no );
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy[2] = {};		// �e�N�X�`���ւ̃|���S��

ENEMY					enemyWk[ENEMY_MAX];				// �G�l�~�[�\����

int						g_nTimerEnemy;								// �^�C�}�[
int						g_nTimerEnemyM;								// �^�C�}�[
bool					g_bEnableTimerEnemy;						// �^�C�}�[����ON/OFF
int						g_timeEnemy = 30;							// �^�C�}�[�̎���
int						g_timeEnemyM = 300;							// �^�C�}�[�̎���
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY,				// �t�@�C���̖��O
			&g_pD3DTextureEnemy[0]);		// �ǂݍ��ރ������̃|�C���^
											// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMYDIE,			// �t�@�C���̖��O
			&g_pD3DTextureEnemy[1]);		// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;										// �g�p
		enemy->pos = D3DXVECTOR3(1800.0f, 600.0f, 0.0f);		// ���W�f�[�^��������
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy->CountAnim = 0;									// �A�j���J�E���g��������
		enemy->hp = 2000;										// �G�l�~�[��HP
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
		enemy->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy->Texture = g_pD3DTextureEnemy[0];					// �e�N�X�`�����
		MakeVertexEnemy(i);										// ���_���̍쐬
	}

	g_bEnableTimerEnemy = true;
	g_nTimerEnemy = g_timeEnemy;
	g_nTimerEnemyM = g_timeEnemyM;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy[0] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy[0]->Release();
		g_pD3DTextureEnemy[0] = NULL;
	}
	if (g_pD3DTextureEnemy[1] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy[1]->Release();
		g_pD3DTextureEnemy[1] = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = enemyWk;				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			enemy->CountAnim++;
			if ((enemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
			{
				// �p�^�[���̐؂�ւ�
				enemy->PatternAnim = (enemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;

				// �e�N�X�`�����W��ݒ�
				SetTextureEnemy(i, enemy->PatternAnim);			}
			
			//�G�̈ړ�
			if (g_bEnableTimerEnemy)
			{
				g_nTimerEnemyM--;
				if (g_nTimerEnemyM > 0)
				{
					enemy->pos.y -= 2.0f;
				}
				if (g_nTimerEnemyM < 0)
				{
					enemy->pos.y += 2.0f;
					if (g_nTimerEnemyM < -g_timeEnemyM)
					{
						g_nTimerEnemyM = g_timeEnemyM;
					}
				}
			}


			// �e����
			if(enemy->use ==true)
			{ 
			D3DXVECTOR3 pos = enemy->pos;
			pos.x = enemy->pos.x;
			SetBulletenemy(pos);
			
			}

			SetVertexEnemy(i);	// �ړ���̍��W�Œ��_��ݒ�

		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;				// �G�l�~�[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, enemy->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexEnemy( no );

	// rhw�̐ݒ�
	enemy->vertexWk[0].rhw =
	enemy->vertexWk[1].rhw =
	enemy->vertexWk[2].rhw =
	enemy->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY);
	enemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY);

	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy( int no, int cntPattern )
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	
	enemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy( int no )
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy->vertexWk[0].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.z = 0.0f;

	enemy->vertexWk[1].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.z = 0.0f;

	enemy->vertexWk[2].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.z = 0.0f;

	enemy->vertexWk[3].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}

//=============================================================================
// �ړ��֐�
//=============================================================================
void MoveEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->pos.x -= player->speedX;
	}

}

//=============================================================================
//���S����
//=============================================================================
void SetEnemydie(void)
{
	ENEMY *enemy = enemyWk;			// �G�l�~�[�̃|�C���^�[��������

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->hp <= 0)
		{
			enemy->Texture = g_pD3DTextureEnemy[1];
			if (g_bEnableTimerEnemy)
			{
				g_nTimerEnemy--;
				if (g_nTimerEnemy < 0)
				{
					g_nTimerEnemy = 0;
					enemy->use = false;
					g_nTimerEnemy = g_timeEnemy;
				}
			}
		}
	}
}