//=============================================================================
//
// ���󏈗� [hoshizora.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _HOSHIZORA_H_
#define _HOSHIZORA_H_


// �}�N����`
#define	NUM_HOSHIZORA				(2)			// �|���S����

#define TEXTURE_GAME_HOSHIZORA		_T("data/TEXTURE/hoshihikari.png")	// �摜
#define TEXTURE_HOSHIZORA_SIZE_X	(800)		// �e�N�X�`���T�C�Y
#define TEXTURE_HOSHIZORA_SIZE_Y	(600)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA	(20)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_HOSHIZORA			(TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA*TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_HOSHIZORA			(5)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define HOSHIZORA_MAX						(1)			// �o���b�g�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} HOSHIZORA;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHoshizora(int type);
void UninitHoshizora(void);
void UpdateHoshizora(void);
void DrawHoshizora(void);
void SetHoshizora(D3DXVECTOR3 pos);
HOSHIZORA *GetHoshizora(int no);

#endif
