//=============================================================================
//
// �w�i���� [boss1bg.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BOSS1BG_H_
#define _BOSS1BG_H_

// �}�N����`
#define TEXTURE_GAME_BOSS1BG	_T("data/TEXTURE/pipo-battlebg001.jpg")	// �T���v���p�摜
#define BOSS1BG_SIZE_X			(800)	// �e�N�X�`���T�C�Y
#define BOSS1BG_SIZE_Y			(600)	// ����
#define BOSS1BG_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define BOSS1BG_POS_Y			(0)		// ����
#define BOSS1BG_MAX				(1)		// �w�i�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// BOSS1BG�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} BOSS1BG;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBOSS1BG(int type);
void UninitBOSS1BG(void);
void UpdateBOSS1BG(void);
void DrawBOSS1BG(void);
BOSS1BG *GetBOSS1BG(int no);
#endif
