//=============================================================================
//
// life���� [life.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_


// �}�N����`
#define	NUM_LIFE				(2)			// �|���S����

#define TEXTURE_GAME_LIFE		_T("data/TEXTURE/life1.png")	// �摜
#define TEXTURE_LIFE_SIZE_X		(15)		// �e�N�X�`���T�C�Y
#define TEXTURE_LIFE_SIZE_Y		(15)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_LIFE	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_LIFE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_LIFE			(TEXTURE_PATTERN_DIVIDE_X_LIFE*TEXTURE_PATTERN_DIVIDE_Y_LIFE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_LIFE				(10)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define LIFE_MAX						(8)			// ���C�t�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// ���C�t�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} LIFE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLife(int type);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
LIFE *GetLife(int no);


#endif
