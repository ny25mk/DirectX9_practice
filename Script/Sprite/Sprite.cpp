#include "Sprite.h"
#include "../Texture/Texture.h"

Sprite::Sprite(){

	Reset();

}

Sprite::Sprite(Texture* source){

	Reset();
	SetTexture(source);

}

void Sprite::Reset(){

	texture = NULL;
	cPos = Cp_Middlecenter;
	origX = origY = 0.0f;
	texWidth = 0;
	sWidth = sHeight = 0;
	SetRect(&drawRect, 0, 0, 0, 0);

}

void Sprite::SetTexture(Texture* source){

	if(source == NULL){
		return;
	}

	texture = source;

	int height;
	texture->GetTextureSize(&texWidth, &height);
	SetSpriteSize(texWidth, height);

}

void Sprite::SetSpriteSize(const int width, const int height){

	sWidth = width;
	sHeight = height;

	SetCenterPosition(cPos);
	SetFrame(0);

}

void Sprite::GetSpriteSize(int* width, int* height){

	*width = sWidth;
	*height = sHeight;

}

void Sprite::SetSpriteRect(const int left, const int top, const int right, const int bottom){

	sWidth = right - left;
	sHeight = bottom - top;

	drawRect.left = left;
	drawRect.right = right;
	drawRect.top = top;
	drawRect.top = bottom;

	SetCenterPosition(cPos);

}

void Sprite::SetCenterPosition(const BYTE pos){

	cPos = pos;

	if(pos & Cp_Left){
		origX = 0.0f;
	} else if(pos & Cp_Right){
		origX = (float)sWidth;
	} else{
		origX = (float)sWidth / 2.0f;
	}

	if(pos & Cp_Top){
		origY = 0.0f;
	} else if(pos & Cp_Bottom){
		origY = (float)sHeight;
	} else{
		origY = (float)sHeight / 2.0f;
	}

}

BYTE Sprite::GetCenterPosition() const{

	return cPos;
}

void Sprite::SetFrame(const int frame){

	int d = texWidth / sWidth;

	if(d == 0){
		return;
	}

	int xPos = frame % d;
	int yPos = frame / d;

	drawRect.left = xPos * sWidth;
	drawRect.right = drawRect.left + sWidth;
	drawRect.top = yPos * sHeight;
	drawRect.bottom = drawRect.top + sHeight;

}

void Sprite::Draw(const float x, const float y, const int alpha) const{

	Draw(x, y, 1.0f, 1.0f, alpha);

}

void Sprite::Draw(const float x, const float y, const float r, const int alpha) const{

	Draw(x, y, 1.0f, 1.0f, r, alpha);

}

void Sprite::Draw(const float x, const float y, const float ex, const float ey, const int alpha) const{

	Draw(x, y, ex, ey, 0.0f, alpha);

}

void Sprite::Draw(const float x, const float y, const float ex, const float ey,const float r, const int alpha) const{

	if(texture == NULL){
		//DXTRACE_MSG(_T("�e�N�X�`�����ǂݍ��܂�Ă��܂���"));
		return;
	}

	D3DXMATRIX mtrx1, mtrx2;

	//���_���d�ˍ��킹�镽�s�ړ�
	D3DXMatrixTranslation(&mtrx1, -origX, -origY, 0.0f);

	//�g��s��ƍ���
	if(ex != 1.0f || ey != 1.0f){
		D3DXMatrixScaling(&mtrx2, ex, ey, 1.0f);
		D3DXMatrixMultiply(&mtrx1, &mtrx1, &mtrx2);
	}

	if(r != 0.0f){
		D3DXMatrixRotationZ(&mtrx2, r);
		D3DXMatrixMultiply(&mtrx1, &mtrx1, &mtrx2);
	}

	//�w��̏ꏊ�ֈړ�����s��Ƃ̍���
	D3DXMatrixTranslation(&mtrx2, x, y, 0.0f);
	D3DXMatrixMultiply(&mtrx1, &mtrx1, &mtrx2);

	pSprite->Begin(NULL);

	pSprite->SetTransform(&mtrx1);

	pSprite->Draw(
		texture->GetTexture(),				//�X�v���C�g�ɓ\��t�������e�N�X�`��
		&drawRect,							//�e�N�X�`���̐؂���
		NULL,								//�摜�̒��S���W�i�x�_�j
		NULL,								//�摜�̍��W
		(0x00FFFFFF | (BYTE)alpha << 24)	//�s�N�Z���ɂ��̒l���|�����킹�F�����Ɠ����x��ύX����
	);

	pSprite->End();
	
}