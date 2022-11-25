#include "DxLib.h"
#include<math.h>

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "AL4_03_02b";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	float circleX = 400.0f;
	float circleY = 100.0f;
	float radius = 20.0f;

	float lineStartX = 100.0f;
	float lineStartY = 200.0f;
	float lineEndX = 400.0f;
	float lineEndY = 300.0f;
	float cross = 0.0f;
	VECTOR vec_line,vec_circle;
	bool isHit = false;
	int color;
		
	//float vec_line_val;
	//float vec_circle_val;
	//float angle;
	//float dot = 0.0f;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		if (keys[KEY_INPUT_A]) {
			circleX -= 4;
		}
		if (keys[KEY_INPUT_D]) {
			circleX += 4;
		}
		if (keys[KEY_INPUT_W]) {
			circleY -= 4;
		}
		if (keys[KEY_INPUT_S]) {
			circleY += 4;
		}

		vec_line = VGet(lineEndX - lineStartX, lineEndY - lineStartY, 0.0f);
		vec_line = VNorm(vec_line);

		vec_circle = VGet(circleX - lineStartX, circleY - lineStartY, 0.0f);

		//vec_line_val = sqrt(pow(vec_line.x, 2) + pow(vec_line.y, 2));
		//vec_circle_val = sqrt(pow(vec_circle.x, 2) + pow(vec_circle.y, 2));
		//angle = (vec_line_val * vec_circle_val) / ()
		//dot = vec_line.x * vec_line.y + vec_circle.x * vec_circle.y;

		isHit = false;
		//�����蔻��
		if (circleX >= lineStartX && circleX < lineEndX) {
			// �O�ς��v�Z
			cross = vec_line.x * vec_circle.y - vec_line.y * vec_circle.x;

			if (cross > -radius && cross < radius) {
				isHit = true;
			}
			else {
				isHit = false;
			}
		}
		else {

			if (pow(circleX - lineStartX, 2) + pow(circleY - lineStartY, 2) <= radius * radius) {
				isHit = true;
			}

			if (pow(circleX - lineEndX, 2) + pow(circleY - lineEndY, 2) <= radius * radius) {
				isHit = true;
			}
		}

		if (isHit == true) {
			color = GetColor(255, 0, 0);
		}
		else {
			color = GetColor(255, 255, 255);
		}

		// �`�揈��
		DrawCircle(circleX, circleY, radius, color, true);
		DrawLine(lineStartX, lineStartY, lineEndX, lineEndY, GetColor(255, 255, 255));

		DrawFormatString(0, 0, GetColor(255, 255, 255), "WASD : �ړ�");
	
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
