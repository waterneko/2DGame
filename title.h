//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : GP11A243 29 �N�V��
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/bg_ZT004.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/logo.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_ENTER	_T("data/TEXTURE/enter.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(800)							// �^�C�g���̕�
#define	TITLE_SIZE_Y		(600)							// �^�C�g���̍���
#define	TITLELOGO_POS_X		(150)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_POS_Y		(100)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_SIZE_X	(500)							// �^�C�g�����S�̕�
#define	TITLELOGO_SIZE_Y	(100)							// �^�C�g�����S�̍���
#define	TITLEENTER_SIZE_X	(200)							// �^�C�g�����S�̕�
#define	TITLEENTER_SIZE_Y	(40)							// �^�C�g�����S�̍���
#define	TITLEENTER_POS_X	(300)							// �^�C�g�����S�̕\���ʒu
#define	TITLEENTER_POS_Y	(500)							// �^�C�g�����S�̕\���ʒu

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
