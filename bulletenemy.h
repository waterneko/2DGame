//=============================================================================
//
// �o���b�g���� [bulletenemy.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BULLETENEMY_H_
#define _BULLETENEMY_H_


// �}�N����`
#define	NUM_BULLETENEMY				(2)			// �|���S����

#define TEXTURE_GAME_BULLETENEMY	_T("data/TEXTURE/promin_pipo004_.png")	// �摜
#define TEXTURE_BULLETENEMY_SIZE_X	(100)								// �e�N�X�`���T�C�Y
#define TEXTURE_BULLETENEMY_SIZE_Y	(100)								// ����

#define TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BULLETENEMY			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BULLETENEMY				(30)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BULLETENEMY_MAX						(ENEMY_MAX * 2) // �o���b�g�̍ő吔

#define BULLETENEMY_SPEED					(5.0f)		// �o���b�g�̈ړ��X�s�[�h


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

} BULLETENEMY;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBulletenemy(int type);
void UninitBulletenemy(void);
void UpdateBulletenemy(void);
void DrawBulletenemy(void);
void SetBulletenemy(D3DXVECTOR3 pos);
BULLETENEMY *GetBulletenemy(int no);


#endif
