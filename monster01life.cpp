//=============================================================================
//
// ���C�t���� [monster01life.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "monster01.h"
#include "monster01life.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMonster01life( int no );
void SetTextureMonster01life( int no, int cntPattern );
void SetVertexMonster01life( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster01life = NULL;				// �e�N�X�`���ւ̃|���S��

MONSTER01LIFE			monster01lifeWk[MONSTER01LIFE_MAX];				// ���C�t�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMonster01life(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01LIFE *monster01life = &monster01lifeWk[0];		// ���C�t�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MONSTER01LIFE,				// �t�@�C���̖��O
			&g_pD3DTextureMonster01life);			// �ǂݍ��ރ������̃|�C���^
		
	}
	

	// ���C�t�̏���������
	for (int i = 0; i < MONSTER01LIFE_MAX; i++, monster01life++)
	{
		monster01life->use = true;										// ���g�p�i���˂���Ă��Ȃ��e�j
		monster01life->pos = D3DXVECTOR3(25.0f + i* 30.0f, 25.0f, 0.0f);// ���W�f�[�^��������
		monster01life->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		monster01life->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		monster01life->CountAnim = 0;									// �A�j���J�E���g��������
		
		monster01life->Texture = g_pD3DTextureMonster01life;			// �e�N�X�`�����
		MakeVertexMonster01life(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMonster01life(void)
{
	if (g_pD3DTextureMonster01life != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMonster01life->Release();
		g_pD3DTextureMonster01life = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonster01life(void)
{
	MONSTER01LIFE *monster01life = monster01lifeWk;				// ���C�t�̃|�C���^�[��������
	MONSTER01 *monster01 = GetMonster01(0);						// �����X�^�[�P�̏��Q�b�g
	
	for (int i = 0; i < monster01->hp; i++, monster01life++)
	{
		if (monster01life->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			monster01life->CountAnim++;
			if ((monster01->CountAnim % TIME_ANIMATION_MONSTER01LIFE) == 0)
			{
				// �p�^�[���̐؂�ւ�
				monster01life->PatternAnim = (monster01life->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER01LIFE;

				// �e�N�X�`�����W��ݒ�
				SetTextureMonster01life(i, monster01life->PatternAnim);
				}

			}
			
			SetVertexMonster01life(i);				// �ړ���̍��W�Œ��_��ݒ�
		}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonster01life(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01LIFE *monster01life = monster01lifeWk;				// ���C�t�̃|�C���^�[��������
	MONSTER01 *monster01 = GetMonster01(0);						// �����X�^�[�P�̏��Q�b�g
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < monster01->hp; i++, monster01life++)
	{
		if (monster01life->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, monster01life->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER01LIFE, monster01life->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMonster01life( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01LIFE *monster01life = &monster01lifeWk[no];			// ���C�t�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexMonster01life( no );

	// rhw�̐ݒ�
	monster01life->vertexWk[0].rhw =
	monster01life->vertexWk[1].rhw =
	monster01life->vertexWk[2].rhw =
	monster01life->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	monster01life->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01life->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01life->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01life->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	monster01life->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster01life->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE, 0.0f);
	monster01life->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE);
	monster01life->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMonster01life( int no, int cntPattern )
{
	MONSTER01LIFE *monster01life = &monster01lifeWk[no];			// ���C�t�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE;
	
	monster01life->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster01life->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster01life->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster01life->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMonster01life( int no )
{
	MONSTER01LIFE *monster01life = &monster01lifeWk[no];			// ���C�t�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	monster01life->vertexWk[0].vtx.x = monster01life->pos.x - TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[0].vtx.y = monster01life->pos.y - TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[0].vtx.z = 0.0f;

	monster01life->vertexWk[1].vtx.x = monster01life->pos.x + TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[1].vtx.y = monster01life->pos.y - TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[1].vtx.z = 0.0f;

	monster01life->vertexWk[2].vtx.x = monster01life->pos.x - TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[2].vtx.y = monster01life->pos.y + TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[2].vtx.z = 0.0f;

	monster01life->vertexWk[3].vtx.x = monster01life->pos.x + TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[3].vtx.y = monster01life->pos.y + TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���C�t�擾�֐�
//=============================================================================
MONSTER01LIFE *GetMonster01life(int no)
{
	return(&monster01lifeWk[no]);
}

