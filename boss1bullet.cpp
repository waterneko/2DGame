//=============================================================================
//
// �{�X1�̒e���� [boss1bullet.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "boss1bullet.h"
#include "sound.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾ski
//*****************************************************************************
HRESULT MakeVertexBoss1bullet( int no );
void SetTextureBoss1bullet( int no, int cntPattern );
void SetVertexBoss1bullet( int no );
void MoveBoss1bullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1bullet = NULL;		// �e�N�X�`���ւ̃|���S��

BOSS1BULLET				boss1bulletWk[BOSS1BULLET_MAX];			// �o���b�g�\����

int						g_nTimer;								// �^�C�}�[
bool					g_bEnableTimer;							// �^�C�}�[����ON/OFF
int						g_time = 210;							// �^�C�}�[�̎���
//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss1bullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BULLET *boss1bullet = &boss1bulletWk[0];		// �{�X�P�̃o���b�g�|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSS1BULLET ,				// �t�@�C���̖��O
			&g_pD3DTextureBoss1bullet);				// �ǂݍ��ރ������̃|�C���^
		
	}

	// �^�C�}�[�̏�����
	g_nTimer = g_time;
	g_bEnableTimer = true;

	// �o���b�g�̏���������
	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		boss1bullet->use = false;										// ���g�p�i���˂���Ă��Ȃ��e�j
		boss1bullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		boss1bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		boss1bullet->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		boss1bullet->CountAnim = 0;										// �A�j���J�E���g��������
		
		boss1bullet->Texture = g_pD3DTextureBoss1bullet;				// �e�N�X�`�����
		MakeVertexBoss1bullet(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss1bullet(void)
{
	if (g_pD3DTextureBoss1bullet != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBoss1bullet->Release();
		g_pD3DTextureBoss1bullet = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss1bullet(void)
{
	BOSS1BULLET *boss1bullet = boss1bulletWk;				// �o���b�g�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			boss1bullet->CountAnim++;
			if ((boss1bullet->CountAnim % TIME_ANIMATION_BOSS1BULLET) == 0)
			{
				// �p�^�[���̐؂�ւ�
				boss1bullet->PatternAnim = (boss1bullet->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS1BULLET;
				
				// �e�N�X�`�����W��ݒ�
				SetTextureBoss1bullet(i, boss1bullet->PatternAnim);
				
			}

			// ������Ȃ������o���b�g�̏�������
			if (g_bEnableTimer)
			{
				g_nTimer--;
				if (g_nTimer < 0)
				{
					g_nTimer = 0;
					boss1bullet->use = false;
					boss1bullet->pos.x = -100.0f;
					g_nTimer = g_time;
				}
			}
			
			// �o���b�g�̈ړ�����
			if (boss1bullet->pos.x > player->pos.x && boss1bullet->pos.y > player->pos.y)
			{
				boss1bullet->pos.x -= BOSS1BULLET_SPEED;
				boss1bullet->pos.y -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x > player->pos.x && boss1bullet->pos.y < player->pos.y)
			{
				boss1bullet->pos.x -= BOSS1BULLET_SPEED;
				boss1bullet->pos.y += BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x < player->pos.x && boss1bullet->pos.y < player->pos.y)
			{
				boss1bullet->pos.x += BOSS1BULLET_SPEED;
				boss1bullet->pos.y += BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x < player->pos.x && boss1bullet->pos.y > player->pos.y)
			{
				boss1bullet->pos.x += BOSS1BULLET_SPEED;
				boss1bullet->pos.y -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x == player->pos.x && boss1bullet->pos.y > player->pos.y)
			{
				boss1bullet->pos.y -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x == player->pos.x && boss1bullet->pos.y < player->pos.y)
			{
				boss1bullet->pos.y += BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x > player->pos.x && boss1bullet->pos.y == player->pos.y)
			{
				boss1bullet->pos.x -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x < player->pos.x && boss1bullet->pos.y == player->pos.y)
			{
				boss1bullet->pos.x += BOSS1BULLET_SPEED;
			}

			SetVertexBoss1bullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss1bullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BULLET *boss1bullet = boss1bulletWk;				// �o���b�g�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, boss1bullet->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS1BULLET, boss1bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss1bullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BULLET *boss1bullet = &boss1bulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBoss1bullet( no );

	// rhw�̐ݒ�
	boss1bullet->vertexWk[0].rhw =
	boss1bullet->vertexWk[1].rhw =
	boss1bullet->vertexWk[2].rhw =
	boss1bullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss1bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss1bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET, 0.0f);
	boss1bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET);
	boss1bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss1bullet( int no, int cntPattern )
{
	BOSS1BULLET *boss1bullet = &boss1bulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET;
	
	boss1bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss1bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss1bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss1bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss1bullet( int no )
{
	BOSS1BULLET *boss1bullet = &boss1bulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	boss1bullet->vertexWk[0].vtx.x = boss1bullet->pos.x - TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[0].vtx.y = boss1bullet->pos.y - TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[0].vtx.z = 0.0f;

	boss1bullet->vertexWk[1].vtx.x = boss1bullet->pos.x + TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[1].vtx.y = boss1bullet->pos.y - TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[1].vtx.z = 0.0f;

	boss1bullet->vertexWk[2].vtx.x = boss1bullet->pos.x - TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[2].vtx.y = boss1bullet->pos.y + TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[2].vtx.z = 0.0f;

	boss1bullet->vertexWk[3].vtx.x = boss1bullet->pos.x + TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[3].vtx.y = boss1bullet->pos.y + TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�L���̔��ːݒ�
//=============================================================================
void SetBoss1bullet(D3DXVECTOR3 pos)
{
	BOSS1BULLET *boss1bullet = &boss1bulletWk[0];			// �o���b�g�̃|�C���^�[��������

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			boss1bullet->use = true;			// �g�p��Ԃ֕ύX����
			boss1bullet->pos = pos;				// ���W���Z�b�g			
			return;								// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BOSS1BULLET *GetBoss1bullet(int no)
{
	return(&boss1bulletWk[no]);
}
//=============================================================================
// �X�L���̈ړ��֐�
//=============================================================================
void MoveBoss1bullet(int no)
{
	PLAYER *player = GetPlayer(0);
	BOSS1BULLET *boss1bullet = &boss1bulletWk[0];			// �o���b�g�̃|�C���^�[��������
	for (int i = 0; i < BOSS1BULLET_MAX;i++, boss1bullet++)
	{
		boss1bullet->pos.x -= player->speedX;
	}

}