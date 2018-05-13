//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "bulletenemy.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBulletenemy( int no );
void SetTextureBulletenemy( int no, int cntPattern );
void SetVertexBulletenemy( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBulletenemy = NULL;		// �e�N�X�`���ւ̃|���S��

BULLETENEMY					bulletenemyWk[BULLETENEMY_MAX];			// �o���b�g�\����

LPDIRECTSOUNDBUFFER8	g_eSE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBulletenemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLETENEMY *bulletenemy = &bulletenemyWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_BULLETENEMY,			// �t�@�C���̖��O
			&g_pD3DTextureBulletenemy);			// �ǂݍ��ރ������̃|�C���^
		
		g_eSE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		bulletenemy->use = false;										// ���g�p�i���˂���Ă��Ȃ��e�j
		bulletenemy->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		bulletenemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		bulletenemy->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		bulletenemy->CountAnim = 0;										// �A�j���J�E���g��������
		
		bulletenemy->Texture = g_pD3DTextureBulletenemy;				// �e�N�X�`�����
		MakeVertexBulletenemy(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBulletenemy(void)
{
	if (g_pD3DTextureBulletenemy != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBulletenemy->Release();
		g_pD3DTextureBulletenemy = NULL;
	}

	if (g_eSE != NULL)
	{	// �e�N�X�`���̊J��
		g_eSE->Release();
		g_eSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBulletenemy(void)
{
	BULLETENEMY *bulletenemy = bulletenemyWk;				// �o���b�g�̃|�C���^�[��������
	ENEMY *enemy = GetEnemy(0);								// �G�l�~�[�̃|�C���^�[��������
	enemy = GetEnemy(0);
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
			if (bulletenemy->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{
				bulletenemy->CountAnim++;
				if ((bulletenemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
				{
					// �p�^�[���̐؂�ւ�
					bulletenemy->PatternAnim = (bulletenemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;

					// �e�N�X�`�����W��ݒ�
					SetTextureBulletenemy(i, bulletenemy->PatternAnim);
				}

				// �o���b�g�̈ړ�����
				bulletenemy->pos.x -= BULLETENEMY_SPEED;
			

				// ��ʊO�܂Ői�񂾁H
				if(bulletenemy->pos.x < 0)	// ��ʊO����
				{
				bulletenemy->use = false;
				bulletenemy->pos.x = enemy->pos.x;
				}
			
				SetVertexBulletenemy(i);				// �ړ���̍��W�Œ��_��ݒ�
			}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBulletenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLETENEMY *bulletenemy = bulletenemyWk;				// �o���b�g�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		if (bulletenemy->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bulletenemy->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLETENEMY, bulletenemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBulletenemy( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLETENEMY *bulletenemy = &bulletenemyWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBulletenemy( no );

	// rhw�̐ݒ�
	bulletenemy->vertexWk[0].rhw =
	bulletenemy->vertexWk[1].rhw =
	bulletenemy->vertexWk[2].rhw =
	bulletenemy->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bulletenemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletenemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletenemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletenemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bulletenemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bulletenemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY, 0.0f);
	bulletenemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY);
	bulletenemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY);

	//bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBulletenemy( int no, int cntPattern )
{
	BULLETENEMY *bulletenemy = &bulletenemyWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY;
	
	bulletenemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bulletenemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bulletenemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bulletenemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

	//bulletenemy->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	//bulletenemy->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	//bulletenemy->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	//bulletenemy->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBulletenemy( int no )
{
	BULLETENEMY *bulletenemy = &bulletenemyWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	bulletenemy->vertexWk[0].vtx.x = bulletenemy->pos.x - TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[0].vtx.y = bulletenemy->pos.y - TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[0].vtx.z = 0.0f;

	bulletenemy->vertexWk[1].vtx.x = bulletenemy->pos.x + TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[1].vtx.y = bulletenemy->pos.y - TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[1].vtx.z = 0.0f;

	bulletenemy->vertexWk[2].vtx.x = bulletenemy->pos.x - TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[2].vtx.y = bulletenemy->pos.y + TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[2].vtx.z = 0.0f;

	bulletenemy->vertexWk[3].vtx.x = bulletenemy->pos.x + TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[3].vtx.y = bulletenemy->pos.y + TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBulletenemy(D3DXVECTOR3 pos)
{
	BULLETENEMY *bulletenemy = &bulletenemyWk[0];			// �o���b�g�̃|�C���^�[��������

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		if (bulletenemy->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			bulletenemy->use = true;				// �g�p��Ԃ֕ύX����
			bulletenemy->pos = pos;				// ���W���Z�b�g
			
			// ���ˉ��Đ�
			PlaySound(g_eSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BULLETENEMY *GetBulletenemy(int no)
{
	return(&bulletenemyWk[no]);
}

