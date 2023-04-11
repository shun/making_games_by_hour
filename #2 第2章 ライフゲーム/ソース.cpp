// [1]�w�b�_�[���C���N���[�h����ꏊ

#include <stdio.h>  // [1-1]�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> // [1-2]�W�����C�u�����w�b�_�[���C���N���[�h
#include <string.h> // [1-3]�����񑀍�w�b�_�[���C���N���[�h����
#include <time.h>   // [1-4]���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>  // [1-5]�R���\�[�����o�̓w�b�_�[���C���N���[�h����

// [2]�萔���`����ꏊ

#define FIELD_WIDTH     (160)           // [2-1]�t�B�[���h�̕����`����
#define FIELD_HEIGHT    (160)           // [2-2]�t�B�[���h�̍������`����

#define FPS             (10)            // [2-3]1�b������̍X�V�񐔂��`����
#define INTERVAL        (1000 / FPS)    // [2-4]�X�V�Ԋu�i�~���b�j���`����

// [3]�ϐ���錾����ꏊ

// [3-1]�t�B�[���h��錾����
bool field[FIELD_HEIGHT][FIELD_WIDTH] =
{
/*
    {0,1,0},
    {0,0,1},
    {1,1,1}
*/
};

// [4]�֐���錾����ꏊ

// [4-1]�t�B�[���h��`�悷��֐���錾����
void DrawField()
{
    system("cls");// [4-1-1]�`��O�ɉ�ʂ��N���A����

    // [4-1-2]�t�B�[���h�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [4-1-3]�t�B�[���h�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [4-1-4]�Z���������Ă���΁u���v���A����ł���΁u�@�v��`�悷��
            printf("%s", field[y][x] ? "��" : "�@");
        }

        printf("\n");// [4-1-5]1�s�`�悷�邲�Ƃɉ��s����
    }
}

// [4-2]�Ώۂ̃Z���Ɨאڂ��鐶�����Z���̐����擾����֐���錾����
int GetLivingCellsCount(int _x, int _y)
{
    int count = 0;// [4-2-1]�����Ă���Z���𐔂���J�E���^�[��錾����

    // [4-2-2]�Ώۂ̃Z���̏㉺1�}�X�𔽕�����
    for (int y = _y - 1; y <= _y + 1; y++)
    {
/*
        // [4-2-3]�㉺�Ƀ��[�v�����Ȃ��ꍇ�́A�s���͈͓����ǂ����𔻒肷��
        if ((y < 0) || (y >= FIELD_HEIGHT))
        {
            continue;// [4-2-4]�͈͊O�̍s�Ȃ̂ŃX�L�b�v����
        }
*/
        // [4-2-5]�㉺�Ƀ��[�v����Y���W��錾����
        int roopedY = (FIELD_HEIGHT + y) % FIELD_HEIGHT;

        // [4-2-6]�Ώۂ̃Z���̍��E1�}�X�𔽕�����
        for (int x = _x + -1; x <= _x + 1; x++)
        {
/*
            // [4-2-7]���E�Ƀ��[�v�����Ȃ��ꍇ�́A�񂪔͈͓����ǂ����𔻒肷��
            if ((x < 0) || (x >= FIELD_WIDTH))
            {
                continue;// [4-2-8]�͈͊O�̗�Ȃ̂ŃX�L�b�v����
            }
*/
            // [4-2-9]���E�Ƀ��[�v����X���W��錾����
            int roopedX = (FIELD_WIDTH + x) % FIELD_WIDTH;

            // [4-2-10]�Ώۂ̍��W���A���S�̃Z���Ɠ������ǂ����𔻒肷��
            if ((roopedX == _x) && (roopedY == _y))
            {
                continue;// [4-2-11]�Ώۂ̍��W���X�L�b�v����
            }

            // [4-2-12]�Ώۂ̃Z���������Ă����1���A����ł����0�����Z����
            count += field[roopedY][roopedX];
        }
    }

    return count;// [4-2-13]�����Ă���Z���̐���Ԃ�
}

// [4-3]1�X�e�b�v���̃V�~�����[�V���������s����֐���錾����
void StepSimulation()
{
    // [4-3-1]���̐���̃t�B�[���h��錾����
    bool nextField[FIELD_HEIGHT][FIELD_WIDTH] = {};

    // [4-3-2]���ׂĂ̍s�𔽕�����
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        //  [4-3-3]���ׂĂ̗�𔽕�����
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [4-3-4]�Ώۂ̃Z���Ɨאڂ���A�����Ă���Z���̐���錾����
            int livingCellCount = GetLivingCellsCount(x, y);

            // [4-3-5]�אڂ��鐶�����Z���̐��ŕ��򂷂�
            if (livingCellCount <= 1)// [4-3-5]1�Ȃ�
            {
                // [4-3-6]�Ώۂ̃Z�������ł�����
                nextField[y][x] = false;
            }
            else if (livingCellCount == 2)// [4-3-7]2�Ȃ�
            {
                // [4-3-8]����ێ�
                nextField[y][x] = field[y][x];
            }
            else if (livingCellCount == 3)// [4-3-9]3�Ȃ�
            {
                // [4-3-10]�Ώۂ̃Z����a���^����������
                nextField[y][x] = true;
            }
            else// [4-3-11]4�ȏ�Ȃ�
            {
                // [4-3-12]�Ώۂ̃Z�������ł�����
                nextField[y][x] = false;
            }
        }
    }

    // [4-3-13]���̃X�e�b�v�̃t�B�[���h���A���݂̃t�B�[���h�ɃR�s�[����
    memcpy(field, nextField, sizeof field);
}

// [4-4]�p�^�[�����t�B�[���h�ɃR�s�[����֐���錾����
void PatternTransfer(
    int _destX, int _destY,
    int _srcWidth, int _srcHeight,
    bool* _pPattern)
{
    // [4-4-1]�p�^�[�����̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < _srcHeight; y++)
    {
        // [4-4-2]�p�^�[�����̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < _srcWidth; x++)
        {
            // [4-4-3]�p�^�[�����t�B�[���h�ɃR�s�[����
            field[_destY + y][_destX + x] = _pPattern[y * _srcWidth + x];
        }
    }
}

// [4-5]�v���O�������s�̊J�n�_��錾����
int main()
{
    const int patternWidth = 10;// [4-5-1]�p�^�[���̕���錾����
    const int patternHeight = 8;// [4-5-2]�p�^�[���̍�����錾����

    // [4-5-3]�p�^�[����錾����
    bool pattern[patternHeight][patternWidth] =
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,1,1,0},
        {0,0,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    // [4-5-4]�p�^�[�����t�B�[���h�̒��S�ɃR�s�[����
    PatternTransfer(
        FIELD_WIDTH / 2 - patternWidth / 2,     // int _destX
        FIELD_HEIGHT / 2 - patternHeight / 2,   // int _destY
        patternWidth,                           // int _srcWidth
        patternHeight,                          // int _srcHeight
        (bool*)pattern);                        // bool* _pPattern

    clock_t lastClock = clock();// [4-5-5]�O��̌o�ߎ��Ԃ�錾����

    // [4-5-6]���C�����[�v
    while (1)
    {
        clock_t newClock = clock();// [4-5-7]���݂̌o�ߎ��Ԃ�錾����

        // [4-5-8]�O��̌o�ߎ��Ԃ���A�ҋ@���Ԃ��o�߂��Ă��Ȃ����
        if (newClock < lastClock + INTERVAL)
        {
            continue;// [4-5-9]�ҋ@��Ԃɖ߂�
        }

        // [4-5-10]�O��o�ߎ��Ԃ��A���݂̌o�ߎ��ԂōX�V����
        lastClock = newClock;

        DrawField();// [4-5-11]�t�B�[���h��`�悷��֐����Ăяo��

//      _getch();// [4-5-12]�L�[�{�[�h���͂�҂�

        StepSimulation();// [4-5-13]�V�~�����[�V������i�߂�
    }
}