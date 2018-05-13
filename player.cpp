//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
//#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "skill.h"
#include "attack.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer( int no );
void SetTexturePlayer( int no, int cntPattern );
void SetVertexPlayer( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer[4] = {};	// �e�N�X�`���ւ̃|���S��
// 0:���ʂ̏��
// 1:�U��
// 2:����


PLAYER					playerWk[PLAYER_MAX];			// �v���C���[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
			TEXTURE_READY_PLAYER,							// �t�@�C���̖��O
			&g_pD3DTexturePlayer[0]);						// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_STABBING_PLAYER,						// �t�@�C���̖��O
			&g_pD3DTexturePlayer[1]);						// �ǂݍ��ރ������[
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RUN_PLAYER,								// �t�@�C���̖��O
			&g_pD3DTexturePlayer[2]);						// �ǂݍ��ރ������[
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_CHARGE_PLAYER,								// �t�@�C���̖��O
			&g_pD3DTexturePlayer[3]);						// �ǂݍ��ރ������[

															// �v���C���[�̏���������
		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
			player->use = true;											// �g�p
			player->pos = D3DXVECTOR3(50.0f, 440.0f, 0.0f);				// ���W�f�[�^��������	
			player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
			player->PatternAnim = rand() % ANIM_PATTERN_NUM;			// �A�j���p�^�[���ԍ��������_���ŏ�����
			player->CountAnim = 0;										// �A�j���J�E���g��������
			player->hp = 5;												// �v���C���[��hp��������
			player->mp = 500;											// �v���C���[��mp��������
			player->speedX = 1.5f;										// �v���C���[�̃X�s�[�h��������
			player->speedY = 1.0f;										// �v���C���[�̃X�s�[�h��������

			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
			player->Radius = D3DXVec2Length(&temp);										// �v���C���[�̔��a��������
			player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// �v���C���[�̊p�x��������

			player->Texture = g_pD3DTexturePlayer[0];									// �e�N�X�`�����
			MakeVertexPlayer(i);														// ���_���̍쐬
		}
	}

	if (type == 3)
	{
		player->pos = D3DXVECTOR3(50.0f, 440.0f, 0.0f);				// ���W�f�[�^��������	
	}

	if (type == 1)
	{
		// �v���C���[�̏���������
		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
			player->use = true;											// �g�p
			player->pos = D3DXVECTOR3(50.0f, 440.0f, 0.0f);				// ���W�f�[�^��������	
			player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
			player->PatternAnim = rand() % ANIM_PATTERN_NUM;			// �A�j���p�^�[���ԍ��������_���ŏ�����
			player->CountAnim = 0;										// �A�j���J�E���g��������
			player->hp = 5;												// �v���C���[��hp��������
			player->mp = 500;											// �v���C���[��mp��������
			player->speedX = 1.5f;										// �v���C���[�̃X�s�[�h��������
			player->speedY = 1.0f;										// �v���C���[�̃X�s�[�h��������

			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
			player->Radius = D3DXVec2Length(&temp);										// �v���C���[�̔��a��������
			player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// �v���C���[�̊p�x��������

			player->Texture = g_pD3DTexturePlayer[0];									// �e�N�X�`�����
			MakeVertexPlayer(i);														// ���_���̍쐬
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer[0] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer[0]->Release();
		g_pD3DTexturePlayer[0] = NULL;
	}
	if (g_pD3DTexturePlayer[1] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer[1]->Release();
		g_pD3DTexturePlayer[1] = NULL;
	}
	if (g_pD3DTexturePlayer[2] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer[2]->Release();
		g_pD3DTexturePlayer[2] = NULL;
	}
	if (g_pD3DTexturePlayer[3] != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer[3]->Release();
		g_pD3DTexturePlayer[3] = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];							// �v���C���[�̃|�C���^�[��������
	SKILL *skill = GetSkill(0);								// �X�L���̃|�C���^�[��������


	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			player->CountAnim++;
			if ((player->CountAnim % TIME_ANIMATION) == 0)
			{				
				// �p�^�[���̐؂�ւ�
				player->PatternAnim = (player->PatternAnim + 1) % ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTexturePlayer(i, player->PatternAnim);
			}


			// �L�[�{�[�h���͂ňړ�(�ЂƂ܂��S�v���C���[�𓯂��L�[�œ��������Ⴄ)
			else
			{
				player->Texture = g_pD3DTexturePlayer[0];
			}
			if (GetKeyboardPress(DIK_S))
			{// �L�����̉��̈ړ�
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y += player->speedY;
			}
			else if (GetKeyboardPress(DIK_W))
			{// �L�����̏�̈ړ�
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y -= player->speedY;
			}
			if (GetKeyboardPress(DIK_D))
			{// �L�����̍��̈ړ�
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x += player->speedX;
			}
			else if (GetKeyboardPress(DIK_A))
			{// �L�����̉E�̈ړ�
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x -= player->speedX;
			}

			// �v���C���[��MP�̍ő�l
			if (player->mp > 500)
			{
				player->mp = 500;
			}

			//�v���C���[��HP�̍ő�l
			if (player->hp > 5)
			{
				player->hp = 5;
			}

			//// �Q�[���p�b�h�łňړ�����
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y += player->speedY;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y -= player->speedY;
			}

			if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x += player->speedX;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x -= player->speedX;
			}


			// �e����
			//if (GetKeyboardTrigger(DIK_SPACE))
			//{
			//	D3DXVECTOR3 pos = player->pos;
			//	pos.y -= TEXTURE_PLAYER_SIZE_Y;
			//	SetBullet(pos);
			//}
			//else if (IsButtonTriggered(0, BUTTON_B))
			//{
			//	D3DXVECTOR3 pos = player->pos;
			//	pos.y -= TEXTURE_PLAYER_SIZE_Y;
			//	SetBullet(pos);
			//}

			if ((GetKeyboardPress(DIK_K))|| (IsButtonPressed(0, BUTTON_B)))
			{// ���ʂ̍U��
				player->Texture = g_pD3DTexturePlayer[1];
				D3DXVECTOR3 pos = player->pos;
				pos.x += TEXTURE_PLAYER_SIZE_X + 50.0f;
				if ((GetKeyboardPress(DIK_A)) || (IsButtonPressed(0, BUTTON_LEFT)))
				{
					pos.x -= TEXTURE_PLAYER_SIZE_X + 150.0f;
					//player->pos.x += player->speedX;
				}
				SetAttack(pos);
			}
			if ((GetKeyboardTrigger(DIK_O)) || (IsButtonTriggered(0, BUTTON_A)))
			{// �X�L���̎g�p
				if (player->mp - 100 >= 0)
				{// MP�̌���
					player->mp -= 100;
					player->Texture = g_pD3DTexturePlayer[3];
					D3DXVECTOR3 pos = player->pos;
					pos.x += TEXTURE_PLAYER_SIZE_X + 50.0f;
					if ((GetKeyboardPress(DIK_D)) || (IsButtonPressed(0, BUTTON_RIGHT)))
					{
						pos.x += TEXTURE_PLAYER_SIZE_X - 50.0f;
						//player->pos.x -= player->speedX;
					}
					else if ((GetKeyboardPress(DIK_A)) || (IsButtonPressed(0, BUTTON_LEFT)))
					{
						pos.x -= TEXTURE_PLAYER_SIZE_X + 150.0f;
						//player->pos.x += player->speedX;
					}
					SetSkill(pos);
				}
			}

			// �v���C���[���O�ɏo����H
			if (player->pos.x > SCREEN_WIDTH)
			{
				player->pos.x -= 10.0f;
			}
			//else if(player->pos.y < 300)
			//{
			//	player->pos.y = 300.0f;
			//}
			else if (player->pos.y > SCREEN_HEIGHT)
			{
				player->pos.y -= 10.0f;
			}
			else if(player->pos.x < 0)
			{
				player->pos.x += 10.0f;
			}
			else if (player->pos.y < 0)
			{
				player->pos.y += 10.0f;
			}

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexPlayer(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	//// ���e�X�g��L����
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 128);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, player->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));
		}
	}

	//// ���e�X�g�𖳌���
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	// ���_���W�̐ݒ�
	SetVertexPlayer(no);

	// rhw�̐ݒ�
	player->vertexWk[0].rhw =
	player->vertexWk[1].rhw =
	player->vertexWk[2].rhw =
	player->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	player->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );
	player->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer(int no, int cntPattern)
{
	PLAYER *player = &playerWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	if (GetKeyboardPress(DIK_A)|| IsButtonPressed(0, BUTTON_LEFT))
	{
		player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	else if (GetKeyboardPress(DIK_D)|| IsButtonPressed(0, BUTTON_RIGHT))
	{
		player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	else
	{
		player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];
	
	// ���_���W�̐ݒ�
	player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

