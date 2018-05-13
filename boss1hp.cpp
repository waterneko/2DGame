//=============================================================================
//
// HP���� [boss1hp.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "boss1hp.h"
#include "boss1.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBoss1hp( int no );
void SetTextureBoss1hp( int no, int cntPattern );
void SetVertexBoss1hp( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1hp = NULL;		// �e�N�X�`���ւ̃|���S��

BOSS1HP					boss1hpWk[BOSS1HP_MAX];				// HP�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss1hp(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1HP *boss1hp = &boss1hpWk[0];		// HP�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSS1HP,				// �t�@�C���̖��O
			&g_pD3DTextureBoss1hp);				// �ǂݍ��ރ������̃|�C���^
		
	}
	
	BOSS1 *boss1 = GetBoss1(0);		// �{�X�P�̏��Q�b�g

	// ���C�t�̏���������
	for (int i = 0; i < boss1->hp / 500 ; i++, boss1hp++)
	{
		boss1hp->use = false;											// ���g�p
		boss1hp->pos = D3DXVECTOR3(700.0f - i* 1.0f, 60.0f, 0.0f);		// ���W�f�[�^��������
		boss1hp->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
		boss1hp->PatternAnim = 0;										// �A�j���p�^�[���ԍ��������_���ŏ�����
		boss1hp->CountAnim = 0;											// �A�j���J�E���g��������
		
		boss1hp->Texture = g_pD3DTextureBoss1hp;						// �e�N�X�`�����
		MakeVertexBoss1hp(i);											// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss1hp(void)
{
	if (g_pD3DTextureBoss1hp != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBoss1hp->Release();
		g_pD3DTextureBoss1hp = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss1hp(void)
{
	BOSS1HP *boss1hp = boss1hpWk;						// HP�̃|�C���^�[��������
	BOSS1 *boss1 = GetBoss1(0);							// �{�X�P�̏��Q�b�g
	
	for (int i = 0; i < boss1->hp / 500; i++, boss1hp++)
	{
		if (boss1hp->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			boss1hp->CountAnim++;
			if ((boss1hp->CountAnim % TIME_ANIMATION_BOSS1HP) == 0)
			{
				// �p�^�[���̐؂�ւ�
				boss1hp->PatternAnim = (boss1hp->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS1HP;

				// �e�N�X�`�����W��ݒ�
				SetTextureBoss1hp(i, boss1hp->PatternAnim);
				}

			}
			
			SetVertexBoss1hp(i);			// �ړ���̍��W�Œ��_��ݒ�
		}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss1hp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1HP *boss1hp = boss1hpWk;				// ���C�t�̃|�C���^�[��������
	BOSS1 *boss1 = GetBoss1(0);					// �v���C���[�̏��Q�b�g

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < boss1->hp / 500; i++, boss1hp++)
	{
		if (boss1hp->use == true)				// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, boss1hp->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS1HP, boss1hp->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss1hp( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1HP *boss1hp = &boss1hpWk[no];			// ���C�t�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBoss1hp( no );

	// rhw�̐ݒ�
	boss1hp->vertexWk[0].rhw =
	boss1hp->vertexWk[1].rhw =
	boss1hp->vertexWk[2].rhw =
	boss1hp->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss1hp->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1hp->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1hp->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1hp->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�(�}
	boss1hp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1hp->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1HP, 0.0f);
	boss1hp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP);
	boss1hp->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS1HP, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss1hp( int no, int cntPattern )
{
	BOSS1HP *boss1hp = &boss1hpWk[no];			// ���C�t�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS1HP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS1HP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1HP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP;
	
	boss1hp->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss1hp->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss1hp->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss1hp->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�(�y
//=============================================================================
void SetVertexBoss1hp( int no )
{
	BOSS1HP *boss1hp = &boss1hpWk[no];			// HP�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	boss1hp->vertexWk[0].vtx.x = boss1hp->pos.x - TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[0].vtx.y = boss1hp->pos.y - TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[0].vtx.z = 0.0f;

	boss1hp->vertexWk[1].vtx.x = boss1hp->pos.x + TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[1].vtx.y = boss1hp->pos.y - TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[1].vtx.z = 0.0f;

	boss1hp->vertexWk[2].vtx.x = boss1hp->pos.x - TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[2].vtx.y = boss1hp->pos.y + TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[2].vtx.z = 0.0f;

	boss1hp->vertexWk[3].vtx.x = boss1hp->pos.x + TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[3].vtx.y = boss1hp->pos.y + TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���C�t�擾�֐�
//=============================================================================
BOSS1HP *GetBoss1hp(int no)
{
	return(&boss1hpWk[no]);
}

