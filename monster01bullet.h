//=============================================================================
//
// �����X�^�[�P1�̒e���� [monster01bullet.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _MONSTER01BULLET_H_
#define _MONSTER01BULLET_


// �}�N����`
#define	NUM_MONSTER01BULLET				(2)		// �|���S����

#define TEXTURE_GAME_MONSTER01BULLET		_T("data/TEXTURE/monster01bullet.png")	// �摜
#define TEXTURE_MONSTER01BULLET_SIZE_X	(30)		// �e�N�X�`���T�C�Y
#define TEXTURE_MONSTER01BULLET_SIZE_Y	(30)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_MONSTER01BULLET			(TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET*TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MONSTER01BULLET				(10)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define MONSTER01BULLET_MAX							(5)	// �o���b�g�̍ő吔
#define MONSTER01BULLET_SPEED						(2)		// �o���b�g�̃X�s�[�h

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

} MONSTER01BULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMonster01bullet(int type);
void UninitMonster01bullet(void);
void UpdateMonster01bullet(void);
void DrawMonster01bullet(void);
void SetMonster01bullet(D3DXVECTOR3 pos);
MONSTER01BULLET *GetMonster01bullet(int no);
void MoveMonster01bullet(int no);

#endif
