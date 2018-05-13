//=============================================================================
//
// �A�C�R������ [boss1icon.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BOSS1ICON_H_
#define _BOSS1ICON_H_

// �}�N����`
#define TEXTURE_GAME_BOSS1ICON		_T("data/TEXTURE/boss1icon.png")	// �T���v���p�摜
#define BOSS1ICON_SIZE_X			(100)	// �e�N�X�`���T�C�Y
#define BOSS1ICON_SIZE_Y			(100)	// ����
#define BOSS1ICON_POS_X				(0)		// �|���S���̏����ʒuX(����)
#define BOSS1ICON_POS_Y				(0)		// ����
#define BOSS1ICON_MAX				(1)		// �w�i�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// BG�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} BOSS1ICON;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss1icon(int type);
void UninitBoss1icon(void);
void UpdateBoss1icon(void);
void DrawBoss1icon(void);
BOSS1ICON *GetBoss1icon(int no);
#endif
