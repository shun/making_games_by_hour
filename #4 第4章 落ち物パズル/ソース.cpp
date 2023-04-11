// [1]�w�b�_�[���C���N���[�h����ꏊ

#include <stdio.h>  // [1-1]�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> // [1-2]�W�����C�u�����w�b�_�[���C���N���[�h����
#include <string.h> // [1-3]�����񑀍�w�b�_�[���C���N���[�h����
#include <time.h>   // [1-4]���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>  // [1-5]�R���\�[�����o�̓w�b�_�[���C���N���[�h����

// [2]�萔���`����ꏊ

#define FIELD_WIDTH         (12)            // [2-1]�t�B�[���h�̕����`����
#define FIELD_HEIGHT        (18)            // [2-2]�t�B�[���h�̍������`����

#define BLOCK_WIDTH_MAX     (4)             // [2-3]�u���b�N�̍ő啝���`����
#define BLOCK_HEIGHT_MAX    (4)             // [2-4]�u���b�N�̍ő卂�����`����

#define FPS                 (1)             // [2-5]1�b������̕`��p�x���`����
#define INTERVAL            (1000 / FPS)    // [2-6]�`��Ԋu�i�~���b�j���`����

// [3]�񋓒萔���`����ꏊ

// [3-1]�u���b�N�̎�ނ��`����
enum
{
    BLOCK_NONE, // [3-1-1]�u���b�N�Ȃ�
    BLOCK_HARD, // [3-1-2]�����Ȃ��u���b�N
    BLOCK_SOFT, // [3-1-3]������u���b�N
    BLOCK_FALL, // [3-1-4]�����u���b�N
    BLOCK_MAX   // [3-1-5]�u���b�N�̎�ނ̐�
};

// [3-2]�����u���b�N�̎�ނ��`����
enum
{
    BLOCK_SHAPE_I,  // [3-2-1]I�^
    BLOCK_SHAPE_L,  // [3-2-2]L�^
    BLOCK_SHAPE_MAX // [3-2-3]�����u���b�N�̎�ނ̐�
};

// [4]�\���̂�錾����ꏊ

// [4-1]�����u���b�N�̌`��̍\���̂�錾����
typedef struct {
    int size;                                           // [4-1-1]���ƍ���
    bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX];    // [4-1-2]�`��
} BLOCKSHAPE;

// [4-2]�����u���b�N�̍\���̂�錾����
typedef struct {
    int x, y;           // [4-2-1]���W
    BLOCKSHAPE shape;   // [4-2-2]�`��
} BLOCK;

// [5]�ϐ���錾����ꏊ

// [5-1]�����u���b�N�̌`���錾����
const BLOCKSHAPE blockShapes[BLOCK_SHAPE_MAX] =
{
    // [5-1-1]BLOCK_SHAPE_I I�^
    {
        3,// [5-1-2]int size    ���ƍ���

        // [5-1-3]bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX]   �`��
        {
            {0,1,0},
            {0,1,0},
            {0,1,0}
        }
    },

    // [5-1-4]BLOCK_SHAPE_L L�^
    {
        3,// [5-1-5]int size    ���ƍ���

        // [5-1-6]bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX]   �`��
        {
            {0,1,0},
            {0,1,1},
            {0,0,0}
        }
    },
};

// [5-2]�t�B�[���h��錾����
int field[FIELD_HEIGHT][FIELD_WIDTH];

// [5-3]�t�B�[���h�̏�����Ԃ�錾����
int defaultField[FIELD_HEIGHT][FIELD_WIDTH] =
{
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,1,1,1},
    {1,1,1,1,0,0,0,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
};

BLOCK block;// [5-4]�����u���b�N��錾����

// [6]�֐���錾����ꏊ

// [6-1]�����u���b�N�ƃt�B�[���h�̓����蔻����s���֐���錾����
bool BlockIntersectField()
{
    // [6-1-1]�����u���b�N�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < block.shape.size; y++)
    {
        // [6-1-2]�����u���b�N�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < block.shape.size; x++)
        {
            // [6-1-3]�Ώۂ̃}�X�Ƀu���b�N�����邩�ǂ����𔻒肷��
            if (block.shape.pattern[y][x])
            {
                // [6-1-4]�u���b�N�̃t�B�[���h��̗��錾����
                int globalX = block.x + x;

                // [6-1-5]�u���b�N�̃t�B�[���h��̍s��錾����
                int globalY = block.y + y;

                // [6-1-6]�u���b�N�ƃt�B�[���h�̓����蔻����s��
                if ((globalX < 0)                   // �񂪍��O���ǂ���
                    || (globalX >= FIELD_WIDTH)     // �񂪉E�O���ǂ���
                    || (globalY < 0)                // �s����O���ǂ���
                    || (globalY >= FIELD_HEIGHT)    // �s�����O���ǂ���

                    // �t�B�[���h��Ƀu���b�N�����邩�ǂ���
                    || (field[globalY][globalX] != BLOCK_NONE))
                {
                    return true;// [6-1-7]���������Ƃ������ʂ�Ԃ�
                }
            }
        }
    }

    return false;// [6-1-8]������Ȃ������Ƃ������ʂ�Ԃ�
}

// [6-2]��������s�̃u���b�N���폜����֐���錾����
void EraseLine()
{
    // [6-2-1]���ׂĂ̍s�𔽕�����
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [6-2-2]���̍s������������ǂ����̃t���O��錾����
        bool completed = true;

        // [6-2-3]���ׂĂ̗�𔽕�����
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [6-2-4]�Ώۂ̃}�X�Ƀu���b�N���Ȃ����ǂ������肷��
            if (field[y][x] == BLOCK_NONE)
            {
                completed = false;// [6-2-5]�����Ȃ�����

                break;// [6-2-6]���̍s�̃`�F�b�N�𔲂���
            }
        }

        // [6-2-7]���̍s������������ǂ������肷��
        if (completed)
        {
            // [6-2-8]���ׂĂ̗�𔽕�����
            for (int x = 0; x < FIELD_WIDTH; x++)
            {
                // [6-2-9]�Ώۂ̃}�X��������u���b�N�Ȃ�
                if (field[y][x] == BLOCK_SOFT)
                {
                    // [6-2-10]�Ώۂ̃}�X�̃u���b�N������
                    field[y][x] = BLOCK_NONE;
                }
            }

            // [6-2-11]���ׂĂ̗�𔽕�����
            for (int x = 0; x < FIELD_WIDTH; x++)
            {
                // [6-2-12]�������s����擪�̍s�܂Ŕ�������
                for (int y2 = y; y2 >= 0; y2--)
                {
                    // [6-2-13]�����Ȃ��u���b�N�����������甽���𔲂���
                    if(field[y2][x] == BLOCK_HARD)
                        break;

                    // [6-2-14]�擪�̍s���ǂ����𔻒肷��
                    if (y2 == 0)
                    {
                        // [6-2-15]�u���b�N������
                        field[y2][x] = BLOCK_NONE;
                    }

                    // [6-2-16]�擪�̍s�łȂ����
                    else
                    {
                        // [6-2-17]��̃}�X�������Ȃ��u���b�N�łȂ����ǂ����𔻒肷��
                        if (field[y2 - 1][x] != BLOCK_HARD)
                        {
                            // [6-2-18]��̃}�X�����̃}�X�ɃR�s�[����
                            field[y2][x] = field[y2 - 1][x];
                        }
                    }
                }
            }
        }
    }
}

// [6-3]��ʂ�`�悷��֐���錾����
void DrawScreen()
{
    // [6-3-1]��ʃo�b�t�@�[��錾����
    int screen[FIELD_HEIGHT][FIELD_WIDTH];

    // [6-3-2]�t�B�[���h����ʃo�b�t�@�[�ɃR�s�[����
    memcpy(screen, field, sizeof field);

    // [6-3-3]�t�B�[���h�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < BLOCK_HEIGHT_MAX; y++)
    {
        // [6-3-4]�t�B�[���h�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < BLOCK_WIDTH_MAX; x++)
        {
            // [6-3-5]�u���b�N�����邩�ǂ����𔻒肷��
            if (block.shape.pattern[y][x])
            {
                // [6-3-6]��ʃo�t�@�[�ɗ����u���b�N����������
                screen[block.y + y][block.x + x] = BLOCK_FALL;
            }
        }
    }

    // [6-3-7]��ʂ��N���A����
    system("cls");

    // [6-3-8]�t�B�[���h�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [6-3-9]�t�B�[���h�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [6-3-10]�u���b�N�̎�ނŕ��򂷂�
            switch (screen[y][x])
            {
            case BLOCK_NONE: printf("�@");    break;// [6-3-11]�u���b�N�Ȃ�
            case BLOCK_HARD: printf("�{");    break;// [6-3-12]�����Ȃ��u���b�N
            case BLOCK_SOFT: printf("��");    break;// [6-3-13]������u���b�N
            case BLOCK_FALL: printf("��");    break;// [6-3-14]�����u���b�N
            }
        }

        printf("\n");// [6-3-15]���s����
    }
}

// [6-4]�����u���b�N����]������֐���錾����
void RotateBlock()
{
    // [6-4-1]��]��̃u���b�N��錾����
    BLOCK rotatedBlock = block;

    // [6-4-2]�����u���b�N�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < block.shape.size; y++)
    {
        // [6-4-3]�����u���b�N�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < block.shape.size; x++)
        {
            // [6-4-4]��]��̃u���b�N�̌`����쐬����
            rotatedBlock.shape.pattern[block.shape.size - 1 - x][y] =
                block.shape.pattern[y][x];
        }
    }

    // [6-4-5]��]��̃u���b�N��K�p����
    block = rotatedBlock;
}

// [6-5]�����u���b�N������������֐���錾����
void InitBlock()
{
    // [6-5-1]�����u���b�N�̌`����A�����_���ɐݒ肷��
    block.shape = blockShapes[rand() % BLOCK_SHAPE_MAX];

    // [6-5-2]�����u���b�N�̗�𒆐S�ɂ���
    block.x = FIELD_WIDTH / 2 - block.shape.size / 2;

    block.y = 0;// [6-5-3]�����u���b�N�̍s��擪�ɂ���

    // [6-5-4]�����u���b�N����]������񐔂�錾����
    int rotateCount = rand() % 4;

    // [6-5-5]�����u���b�N����]������񐔂�����������
    for (int i = 0; i < rotateCount; i++)
    {
        // [6-5-6]�����u���b�N����]������
        RotateBlock();
    }
}

// [6-6]�Q�[��������������֐���錾����
void Init()
{
    // [6-6-1]�t�B�[���h�ɏ�����Ԃ��R�s�[����
    memcpy(field, defaultField, sizeof field);

    InitBlock();// [6-6-2]�u���b�N������������֐����Ăяo��

    DrawScreen();// [6-6-3]��ʂ�`�悷��֐����Ăяo��
}

// [6-7]�����u���b�N�𗎉�������֐���錾����
void FallBlock()
{
    BLOCK lastBlock = block;// [6-7-1]�u���b�N�̈ړ��O�̏�Ԃ�錾����

    block.y++;// [6-7-2]�u���b�N�𗎉�������

    // [6-7-3]�u���b�N�ƃt�B�[���h���d�Ȃ������ǂ������肷��
    if (BlockIntersectField())
    {
        // [6-7-4]�����u���b�N���ړ��O�̏�Ԃɖ߂�
        block = lastBlock;

        // [6-7-5]�����u���b�N�̂��ׂĂ̍s�𔽕�����
        for (int y = 0; y < BLOCK_HEIGHT_MAX; y++)
        {
            // [6-7-6]�����u���b�N�̂��ׂĂ̗�𔽕�����
            for (int x = 0; x < BLOCK_WIDTH_MAX; x++)
            {
                // [6-7-7]�u���b�N������}�X���ǂ����𔻒肷��
                if (block.shape.pattern[y][x])
                {
                    // [6-7-8]�t�B�[���h�ɏ�����u���b�N����������
                    field[block.y + y][block.x + x] = BLOCK_SOFT;
                }
            }
        }

        // [6-7-9]��������u���b�N���폜����֐����Ăяo��
        EraseLine();

        // [6-7-10]�u���b�N������������֐����Ăяo��
        InitBlock();

        // [6-7-11]�u���b�N�ƃt�B�[���h���d�Ȃ������ǂ������肷��
        if (BlockIntersectField())
        {
            Init();// [6-7-12]�Q�[��������������
        }
    }

    DrawScreen();// [6-7-13]��ʂ�`�悷��֐����Ăяo��
}

// [6-8]�v���O�������s�̊J�n�_��錾����
int main()
{
    srand((unsigned int)time(NULL));// [6-8-1]�������V���b�t������

    // [6-8-2]�Q�[��������������֐����Ăяo��
    Init();

    clock_t lastClock = clock();// [6-8-3]�O��̍X�V������ێ�����ϐ���錾����

    // [6-8-4]���C�����[�v
    while (1)
    {
        clock_t newClock = clock();// [6-8-5]���݂̎�����錾����
        
        // [6-8-6]�ҋ@���Ԃ��o�߂�����
        if (newClock >= lastClock + INTERVAL)
        {
            lastClock = newClock;// [6-8-7]�O��̍X�V���������݂̎����ōX�V����

            FallBlock();// [6-8-8]�����u���b�N�𗎉�������֐����Ăяo��
        }

        // [6-8-9]�L�[�{�[�h���͂����������ǂ������肷��
        if (_kbhit())
        {
            // [6-8-10]�u���b�N�̈ړ��O�̏�Ԃ�錾����
            BLOCK lastBlock = block;

            // [6-8-11]���͂��ꂽ�L�[�ɂ���ĕ��򂷂�
            switch (_getch())
            {
            case 'w':       // [6-8-12]w�L�[�������ꂽ��
                break;

            case 's':       // [6-8-13]s�L�[�������ꂽ��
                block.y++;  // [6-8-14]�u���b�N�����Ɉړ�����
                break;

            case 'a':       // [6-8-15]a�L�[�������ꂽ��
                block.x--;  // [6-8-16]�u���b�N�����Ɉړ�����
                break;

            case 'd':       // [6-8-17]d�L�[�������ꂽ��
                block.x++;  // [6-8-18]�u���b�N���E�Ɉړ�����
                break;

            default:// [6-8-19]�ړ��ȊO�̃L�[�������ꂽ��

                // [6-8-20]�����u���b�N����]������֐����Ăяo��
                RotateBlock();

                break;
            }

            // [6-8-21]�u���b�N�ƃt�B�[���h���d�Ȃ������ǂ������肷��
            if (BlockIntersectField())
            {
                // [6-8-22]�u���b�N���ړ��O�̏�Ԃɖ߂�
                block = lastBlock;
            }
            // [6-8-23]�u���b�N�ƃt�B�[���h���d�Ȃ�Ȃ����
            else
            {
                // [6-8-24]��ʂ�`�悷��֐����Ăяo��
                DrawScreen();
            }
        }
    }
}