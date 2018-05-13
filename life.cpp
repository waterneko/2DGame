//=============================================================================
//
// ���C�t���� [life.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "life.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexLife( int no );
void SetTextureLife( int no, int cntPattern );
void SetVertexLife( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLife = NULL;		// �e�N�X�`���ւ̃|���S��

LIFE					lifeWk[LIFE_MAX];				// ���C�t�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitLife(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LIFE *life = &lifeWk[0];		// ���C�t�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_LIFE,				// �t�@�C���̖��O
			&g_pD3DTextureLife);			// �ǂݍ��ރ������̃|�C���^
		
	}
	
	PLAYER *player = GetPlayer(0);		//�v���C���[�̏��Q�b�g

	// ���C�t�̏���������
	for (int i = 0; i < player->hp; i++, life++)
	{
		life->use = true;										// �g�p
		life->pos = D3DXVECTOR3(100.0f + i* 30.0f, 25.0f, 0.0f);// ���W�f�[�^��������
		life->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		life->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		life->CountAnim = 0;									// �A�j���J�E���g��������
		
		life->Texture = g_pD3DTextureLife;					// �e�N�X�`�����
		MakeVertexLife(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	if (g_pD3DTextureLife != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureLife->Release();
		g_pD3DTextureLife = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife(void)
{
	LIFE *life = lifeWk;				// ���C�t�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̏��Q�b�g
	
	for (int i = 0; i < player->hp; i++, life++)
	{
		if (life->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			life->CountAnim++;
			if ((life->CountAnim % TIME_ANIMATION_LIFE) == 0)
			{
				// �p�^�[���̐؂�ւ�
				life->PatternAnim = (life->PatternAnim + 1) % ANIM_PATTERN_NUM_LIFE;

				// �e�N�X�`�����W��ݒ�
				SetTextureLife(i, life->PatternAnim);
				}

			}
			
			SetVertexLife(i);				// �ړ���̍��W�Œ��_��ݒ�
		}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LIFE *life = lifeWk;				// ���C�t�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̏��Q�b�g

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < player->hp; i++, life++)
	{
		if (life->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, life->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_LIFE, life->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexLife( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LIFE *life = &lifeWk[no];			// ���C�t�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexLife( no );

	// rhw�̐ݒ�
	life->vertexWk[0].rhw =
	life->vertexWk[1].rhw =
	life->vertexWk[2].rhw =
	life->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	life->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	life->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	life->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	life->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	life->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	life->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_LIFE, 0.0f);
	life->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_LIFE);
	life->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_LIFE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LIFE);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureLife( int no, int cntPattern )
{
	LIFE *life = &lifeWk[no];			// ���C�t�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_LIFE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_LIFE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_LIFE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_LIFE;
	
	life->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	life->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	life->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	life->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexLife( int no )
{
	LIFE *life = &lifeWk[no];			// ���C�t�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	life->vertexWk[0].vtx.x = life->pos.x - TEXTURE_LIFE_SIZE_X;
	life->vertexWk[0].vtx.y = life->pos.y - TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[0].vtx.z = 0.0f;

	life->vertexWk[1].vtx.x = life->pos.x + TEXTURE_LIFE_SIZE_X;
	life->vertexWk[1].vtx.y = life->pos.y - TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[1].vtx.z = 0.0f;

	life->vertexWk[2].vtx.x = life->pos.x - TEXTURE_LIFE_SIZE_X;
	life->vertexWk[2].vtx.y = life->pos.y + TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[2].vtx.z = 0.0f;

	life->vertexWk[3].vtx.x = life->pos.x + TEXTURE_LIFE_SIZE_X;
	life->vertexWk[3].vtx.y = life->pos.y + TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���C�t�擾�֐�
//=============================================================================
LIFE *GetLife(int no)
{
	return(&lifeWk[no]);
}

