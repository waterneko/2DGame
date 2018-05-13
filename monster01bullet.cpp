//=============================================================================
//
// �����X�^�[�P�̒e���� [monster01bullet.cpp]
// Author :GP11A243 29 �N�V�� 
//
//=============================================================================
#include "main.h"
#include "monster01bullet.h"
#include "sound.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾ski
//*****************************************************************************
HRESULT MakeVertexMonster01bullet( int no );
void SetTextureMonster01bullet( int no, int cntPattern );
void SetVertexMonster01bullet( int no );
void MoveMonster01bullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster01bullet = NULL;			// �e�N�X�`���ւ̃|���S��

MONSTER01BULLET			monster01bulletWk[MONSTER01BULLET_MAX];			// �o���b�g�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMonster01bullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[0];		// �o���b�g�|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MONSTER01BULLET ,				// �t�@�C���̖��O
			&g_pD3DTextureMonster01bullet);				// �ǂݍ��ރ������̃|�C���^
		
	}

	// �^�C�}�[�̏�����


	// �o���b�g�̏���������
	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		monster01bullet->use = false;										// ���g�p�i���˂���Ă��Ȃ��e�j
		monster01bullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		monster01bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		monster01bullet->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		monster01bullet->CountAnim = 0;										// �A�j���J�E���g��������
		
		monster01bullet->Texture = g_pD3DTextureMonster01bullet;			// �e�N�X�`�����
		MakeVertexMonster01bullet(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMonster01bullet(void)
{
	if (g_pD3DTextureMonster01bullet != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMonster01bullet->Release();
		g_pD3DTextureMonster01bullet = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonster01bullet(void)
{
	MONSTER01BULLET *monster01bullet = monster01bulletWk;				// �o���b�g�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			monster01bullet->CountAnim++;
			if ((monster01bullet->CountAnim % TIME_ANIMATION_MONSTER01BULLET) == 0)
			{
				// �p�^�[���̐؂�ւ�
				monster01bullet->PatternAnim = (monster01bullet->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER01BULLET;
				
				// �e�N�X�`�����W��ݒ�
				SetTextureMonster01bullet(i, monster01bullet->PatternAnim);
				
			}
			// �o���b�g�̈ړ�����
			monster01bullet->pos.x -= MONSTER01BULLET_SPEED;

			// ������Ȃ������o���b�g�̏�������

			
			// �o���b�g�̈ړ�����

			// ��ʊO�܂Ői�񂾁H
			if (monster01bullet->pos.x < -TEXTURE_MONSTER01BULLET_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				monster01bullet->use = false;
				monster01bullet->pos.x = -100.0f;
			}

			SetVertexMonster01bullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonster01bullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01BULLET *monster01bullet = monster01bulletWk;				// �o���b�g�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, monster01bullet->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER01BULLET, monster01bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMonster01bullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexMonster01bullet( no );

	// rhw�̐ݒ�
	monster01bullet->vertexWk[0].rhw =
	monster01bullet->vertexWk[1].rhw =
	monster01bullet->vertexWk[2].rhw =
	monster01bullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	monster01bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	monster01bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster01bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET, 0.0f);
	monster01bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET);
	monster01bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMonster01bullet( int no, int cntPattern )
{
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET;
	
	monster01bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster01bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster01bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster01bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMonster01bullet( int no )
{
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	monster01bullet->vertexWk[0].vtx.x = monster01bullet->pos.x - TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[0].vtx.y = monster01bullet->pos.y - TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[0].vtx.z = 0.0f;

	monster01bullet->vertexWk[1].vtx.x = monster01bullet->pos.x + TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[1].vtx.y = monster01bullet->pos.y - TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[1].vtx.z = 0.0f;

	monster01bullet->vertexWk[2].vtx.x = monster01bullet->pos.x - TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[2].vtx.y = monster01bullet->pos.y + TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[2].vtx.z = 0.0f;

	monster01bullet->vertexWk[3].vtx.x = monster01bullet->pos.x + TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[3].vtx.y = monster01bullet->pos.y + TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�L���̔��ːݒ�
//=============================================================================
void SetMonster01bullet(D3DXVECTOR3 pos)
{
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[0];			// �o���b�g�̃|�C���^�[��������

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			monster01bullet->use = true;			// �g�p��Ԃ֕ύX����
			monster01bullet->pos = pos;				// ���W���Z�b�g			
			return;									// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �擾�֐�
//=============================================================================
MONSTER01BULLET *GetMonster01bullet(int no)
{
	return(&monster01bulletWk[no]);
}
//=============================================================================
// �X�L���̈ړ��֐�
//=============================================================================
void MoveMonster01bullet(int no)
{
	PLAYER *player = GetPlayer(0);
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[0];			// �o���b�g�̃|�C���^�[��������
	for (int i = 0; i < MONSTER01BULLET_MAX;i++, monster01bullet++)
	{
		monster01bullet->pos.x -= player->speedX;
	}

}