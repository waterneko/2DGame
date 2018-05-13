//=============================================================================
//
// HP���� [boss1hp.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BOSS1HP_H_
#define _BOSS1HP_H_


// �}�N����`
#define	NUM_BOSS1HP				(2)			// �|���S����

#define TEXTURE_GAME_BOSS1HP		_T("data/TEXTURE/bosshp.png")	// �摜
#define TEXTURE_BOSS1HP_SIZE_X		(1)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSS1HP_SIZE_Y		(15)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSS1HP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSS1HP			(TEXTURE_PATTERN_DIVIDE_X_BOSS1HP*TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSS1HP				(10)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOSS1HP_MAX							(200)	// HP�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// HP�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} BOSS1HP;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss1hp(int type);
void UninitBoss1hp(void);
void UpdateBoss1hp(void);
void DrawBoss1hp(void);
BOSS1HP *GetBoss1hp(int no);


#endif
