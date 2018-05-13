//=============================================================================
//
// �w�i���� [bg.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

// �}�N����`
#define TEXTURE_GAME_BG00		_T("data/TEXTURE/mori.png")	// �T���v���p�摜
#define BG00_SIZE_X			(1920)	// �e�N�X�`���T�C�Y
#define BG00_SIZE_Y			(1080)	// ����
#define BG00_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define BG00_POS_Y			(0)		// ����
#define BG_MAX				(1)		// �w�i�̍ő吔

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

} BG;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
BG *GetBG(int no);
#endif
