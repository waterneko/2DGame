//=============================================================================
//
// �A�C�R������ [icon.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _ICON_H_
#define _ICON_H_

// �}�N����`
#define TEXTURE_GAME_ICON		_T("data/TEXTURE/chara.png")	// �T���v���p�摜
#define ICON_SIZE_X			(80)	// �e�N�X�`���T�C�Y
#define ICON_SIZE_Y			(80)	// ����
#define ICON_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define ICON_POS_Y			(0)		// ����
#define ICON_MAX				(1)		// �w�i�̍ő吔

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

} ICON;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitIcon(int type);
void UninitIcon(void);
void UpdateIcon(void);
void DrawIcon(void);
#endif
