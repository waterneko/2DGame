//=============================================================================
//
// �G���� [boss1.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "boss1.h"
#include "input.h"
#include "player.h"
#include "boss1bullet.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBoss1( int no );
void SetTextureBoss1( int no, int cntPattern );
void SetVertexBoss1( int no );
void MoveBoss1(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1 = NULL;		// �e�N�X�`���ւ̃|���S��

BOSS1					boss1Wk[BOSS1_MAX];				// �{�X�P�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss1(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1 *boss1 = boss1Wk;					// �{�X�P�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSS1,				// �t�@�C���̖��O
			&g_pD3DTextureBoss1);			// �ǂݍ��ރ������̃|�C���^
	}

	// �{�X�P�̏���������
	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		boss1->use = false;										// �s�g�p
		boss1->pos = D3DXVECTOR3(600.0f, 300.0f, 0.0f);			// ���W�f�[�^��������
		boss1->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		boss1->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		boss1->CountAnim = 0;									// �A�j���J�E���g��������
		boss1->hp = 100000;										// �{�X�P��HP

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS1_SIZE_X, TEXTURE_BOSS1_SIZE_Y);
		boss1->Radius = D3DXVec2Length(&temp);					// �{�X�P�̔��a��������
		boss1->BaseAngle = atan2f(TEXTURE_BOSS1_SIZE_Y, TEXTURE_BOSS1_SIZE_X);	// �{�X�P�̊p�x��������

		boss1->Texture = g_pD3DTextureBoss1;					// �e�N�X�`�����
		MakeVertexBoss1(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss1(void)
{
	if (g_pD3DTextureBoss1 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBoss1->Release();
		g_pD3DTextureBoss1 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss1(void)
{
	BOSS1 *boss1 = boss1Wk;				// �{�X�P�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		if (boss1->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			boss1->CountAnim++;
			if ((boss1->CountAnim % TIME_ANIMATION_BOSS1) == 0)
			{
				// �p�^�[���̐؂�ւ�
				boss1->PatternAnim = (boss1->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS1;

				// �e�N�X�`�����W��ݒ�
				SetTextureBoss1(i, boss1->PatternAnim);			}
			
			// �{�X�P�̒e����
			if (boss1->pos.x - player->pos.x < 500)
			{
				D3DXVECTOR3 pos = boss1->pos;
				pos.x = boss1->pos.x + 50.0f;
				pos.y = boss1->pos.y - 50.0f;
				SetBoss1bullet(pos);
			}
			//�G�̈ړ�
			SetVertexBoss1(i);	// �ړ���̍��W�Œ��_��ݒ�

		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1 *boss1 = boss1Wk;				// �{�X�P�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		if (boss1->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, boss1->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS1, boss1->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss1( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1 *boss1 = &boss1Wk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBoss1( no );

	// rhw�̐ݒ�
	boss1->vertexWk[0].rhw =
	boss1->vertexWk[1].rhw =
	boss1->vertexWk[2].rhw =
	boss1->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss1->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss1->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1, 0.0f);
	boss1->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1);
	boss1->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS1, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS1);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss1( int no, int cntPattern )
{
	BOSS1 *boss1 = &boss1Wk[no];			// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS1;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS1;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1;
	
	boss1->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss1->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss1->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss1->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss1( int no )
{
	BOSS1 *boss1 = &boss1Wk[no];			// �{�X�P�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	boss1->vertexWk[0].vtx.x = boss1->pos.x - cosf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[0].vtx.y = boss1->pos.y - sinf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[0].vtx.z = 0.0f;

	boss1->vertexWk[1].vtx.x = boss1->pos.x + cosf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[1].vtx.y = boss1->pos.y - sinf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[1].vtx.z = 0.0f;

	boss1->vertexWk[2].vtx.x = boss1->pos.x - cosf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[2].vtx.y = boss1->pos.y + sinf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[2].vtx.z = 0.0f;

	boss1->vertexWk[3].vtx.x = boss1->pos.x + cosf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[3].vtx.y = boss1->pos.y + sinf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �{�X�P�擾�֐�
//=============================================================================
BOSS1 *GetBoss1(int no)
{
	return(&boss1Wk[no]);
}

//=============================================================================
// �{�X�P�ړ��֐�
//=============================================================================
void MoveBoss1(int no)
{
	BOSS1 *boss1 = &boss1Wk[no];			// �{�X�P�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		boss1->pos.x -= player->speedX;
	}

}