//=============================================================================
//
// �{�X1�̒e���� [boss1bulletl.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _BOSS1BULLET_H_
#define _BOSS1BULLET_


// �}�N����`
#define	NUM_BOSS1BULLET				(2)		// �|���S����

#define TEXTURE_GAME_BOSS1BULLET		_T("data/TEXTURE/boss1bullet.png")	// �摜
#define TEXTURE_BOSS1BULLET_SIZE_X	(50)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSS1BULLET_SIZE_Y	(50)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSS1BULLET			(TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET*TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSS1BULLET				(8)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOSS1BULLET_MAX							(1)	// �o���b�g�̍ő吔
#define BOSS1BULLET_SPEED						(2)	// �o���b�g�̃X�s�[�h

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

} BOSS1BULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss1bullet(int type);
void UninitBoss1bullet(void);
void UpdateBoss1bullet(void);
void DrawBoss1bullet(void);
void SetBoss1bullet(D3DXVECTOR3 pos);
BOSS1BULLET *GetBoss1bullet(int no);
void MoveBoss1bullet(int no);

#endif
