//=============================================================================
//
// �G���� [monster01.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#include "main.h"
#include "monster01.h"
#include "monster01bullet.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMonster01( int no );
void SetTextureMonster01( int no, int cntPattern );
void SetVertexMonster01( int no );
void MoveMonster01(int no);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster01[2] = { NULL };		// �e�N�X�`���ւ̃|���S��

MONSTER01				monster01Wk[MONSTER01_MAX];			// �G�l�~�[�\����

int						g_nTimerMon1;								// �^�C�}�[
int						g_nTimerMon1Move;							// �^�C�}�[
int						g_nTimerMon1Move01;							// �^�C�}�[
int						g_nTimerMon1Move02;							// �^�C�}�[
int						g_nTimerMon1Move03;							// �^�C�}�[
int						g_nTimerMon1Bullet;							// �^�C�}�[
bool					g_bEnableTimerMon1;							// �^�C�}�[����ON/OFF
int						g_timeMon1 = 30;							// �^�C�}�[�̎���
int						g_timeMon1Move = 700;						// �^�C�}�[�̎���
int						g_timeMon1Move01 = 600;						// �^�C�}�[�̎���
int						g_timeMon1Move02 = 400;						// �^�C�}�[�̎���
int						g_timeMon1Move03 = 300;						// �^�C�}�[�̎���
int						g_timeMon1Bullet = 30;						// �^�C�}�[�̎���
//=============================================================================
// ����������
//=============================================================================
HRESULT InitMonster01(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01 *monster01 = monster01Wk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MONSTER01,				// �t�@�C���̖��O
			&g_pD3DTextureMonster01[0]);		// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_MONSTER01DIE,				// �t�@�C���̖��O
			&g_pD3DTextureMonster01[1]);		// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�}�[�̏�����
	g_nTimerMon1 = g_timeMon1;
	g_nTimerMon1Move = g_timeMon1Move;
	g_nTimerMon1Move01 = g_timeMon1Move01;
	g_nTimerMon1Move02 = g_timeMon1Move02;
	g_nTimerMon1Move03 = g_timeMon1Move03;
	g_nTimerMon1Bullet = g_timeMon1Bullet;
	g_bEnableTimerMon1 = true;


	// �G�l�~�[�̏���������
	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		monster01->use = true;										// �g�p
		monster01->pos = D3DXVECTOR3(450+i*80.0f,350.0+i*50.0f, 0.0f);	// ���W�f�[�^��������
		monster01->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		monster01->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		monster01->CountAnim = 0;									// �A�j���J�E���g��������
		monster01->hp = 100;										// �G�l�~�[��HP

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X, TEXTURE_MONSTER01_SIZE_Y);
		monster01->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		monster01->BaseAngle = atan2f(TEXTURE_MONSTER01_SIZE_Y, TEXTURE_MONSTER01_SIZE_X);	// �G�l�~�[�̊p�x��������

		monster01->Texture = g_pD3DTextureMonster01[0];				// �e�N�X�`�����
		MakeVertexMonster01(i);										// ���_���̍쐬
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMonster01(void)
{
	if (g_pD3DTextureMonster01[0] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMonster01[0]->Release();
		g_pD3DTextureMonster01[0] = NULL;
	}
	if (g_pD3DTextureMonster01[1] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMonster01[1]->Release();
		g_pD3DTextureMonster01[1] = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonster01(void)
{
	MONSTER01 *monster01 = monster01Wk;				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		if (monster01->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			monster01->CountAnim++;
			if ((monster01->CountAnim % TIME_ANIMATION_MONSTER01) == 0)
			{
				// �p�^�[���̐؂�ւ�
				monster01->PatternAnim = (monster01->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER01;

				// �e�N�X�`�����W��ݒ�
				SetTextureMonster01(i, monster01->PatternAnim);			}
			
			//�G�̈ړ�
			if (g_bEnableTimerMon1)
			{
				g_nTimerMon1Move --;
				g_nTimerMon1Move01--;
				g_nTimerMon1Move02--;
				if (g_nTimerMon1Move > 0)
				{
					monster01Wk[0].pos.y += 0.3f;
				}
				if (g_nTimerMon1Move01 > 0)
				{
					monster01Wk[1].pos.y += 0.3f;
				}
				if (g_nTimerMon1Move02 > 0)
				{
					monster01Wk[2].pos.y += 0.3f;
				}

				if (g_nTimerMon1Move < 0 )
				{
					monster01Wk[0].pos.y -= 0.3f;
					if (g_nTimerMon1Move < -g_timeMon1Move)
					{
						g_nTimerMon1Move = g_timeMon1Move;
					}
				}
				if (g_nTimerMon1Move01 < 0)
				{
					monster01Wk[1].pos.y -= 0.3f;

					if (g_nTimerMon1Move01 < -g_timeMon1Move01)
					{
						g_nTimerMon1Move01 = g_timeMon1Move01;
					}
				}
				if (g_nTimerMon1Move02 < 0)
				{
					monster01Wk[2].pos.y -= 0.3f;

					if (g_nTimerMon1Move02 < -g_timeMon1Move02)
					{
						g_nTimerMon1Move02 = g_timeMon1Move02;
					}
				}
			}

			 //�e����
			if (g_bEnableTimerMon1)
			{
				g_nTimerMon1Bullet--;
				if (g_nTimerMon1Bullet < 0)
				{
					D3DXVECTOR3 pos = monster01->pos;
					pos.x -= TEXTURE_MONSTER01BULLET_SIZE_Y;
					SetMonster01bullet(pos);
					g_nTimerMon1Bullet = g_timeMon1Bullet;
				}
			}

			SetVertexMonster01(i);	// �ړ���̍��W�Œ��_��ݒ�

		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonster01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01 *monster01 = monster01Wk;				// �G�l�~�[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		if (monster01->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, monster01->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER01, monster01->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMonster01( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01 *monster01 = &monster01Wk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexMonster01( no );

	// rhw�̐ݒ�
	monster01->vertexWk[0].rhw =
	monster01->vertexWk[1].rhw =
	monster01->vertexWk[2].rhw =
	monster01->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	monster01->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	monster01->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster01->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01, 0.0f);
	monster01->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01);
	monster01->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER01, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER01);

	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMonster01( int no, int cntPattern )
{
	MONSTER01 *monster01 = &monster01Wk[no];			// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER01;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER01;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01;
	
	monster01->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster01->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster01->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster01->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMonster01( int no )
{
	MONSTER01 *monster01 = &monster01Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	monster01->vertexWk[0].vtx.x = monster01->pos.x - cosf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[0].vtx.y = monster01->pos.y - sinf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[0].vtx.z = 0.0f;

	monster01->vertexWk[1].vtx.x = monster01->pos.x + cosf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[1].vtx.y = monster01->pos.y - sinf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[1].vtx.z = 0.0f;

	monster01->vertexWk[2].vtx.x = monster01->pos.x - cosf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[2].vtx.y = monster01->pos.y + sinf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[2].vtx.z = 0.0f;

	monster01->vertexWk[3].vtx.x = monster01->pos.x + cosf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[3].vtx.y = monster01->pos.y + sinf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
MONSTER01 *GetMonster01(int no)
{
	return(&monster01Wk[no]);
}

//=============================================================================
// �����X�^�[1�ړ��֐�
//=============================================================================
void MoveMonster01(int no)
{
	MONSTER01 *monster01 = &monster01Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		monster01->pos.x -= player->speedX;
	}

}

//=============================================================================
//�����X�^�[1�̎��S����
//=============================================================================
void SetMonster01die(void)
{
	MONSTER01 *monster01 = monster01Wk;			// �G�l�~�[�̃|�C���^�[��������

	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		if (monster01->hp <= 0)
		{
			monster01->Texture = g_pD3DTextureMonster01[1];
			if (g_bEnableTimerMon1)
			{
				g_nTimerMon1--;
				if (g_nTimerMon1 < 0)
				{
					g_nTimerMon1 = 0;
					monster01->use = false;
					g_nTimerMon1 = g_timeMon1;
				}
			}
		}
	}
}

