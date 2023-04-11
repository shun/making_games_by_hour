// [1]�w�b�_�[���C���N���[�h����ꏊ

#include <stdio.h>  // [1-1]�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> // [1-2]�W�����C�u�����w�b�_�[���C���N���[�h����
#include <time.h>   // [1-3]���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>  // [1-4]�R���\�[�����o�̓w�b�_�[���C���N���[�h����
#include <vector>   // [1-5]�x�N�^�[�w�b�_�[���C���N���[�h����

// [2]�萔���`����ꏊ

#define MAZE_WIDTH  (8)                 // [2-1]���H�̕����`����
#define MAZE_HEIGHT (8)                 // [2-2]���H�̍������`����

#define GOAL_X      (MAZE_WIDTH - 1)    // [2-3]�S�[���̗���`����
#define GOAL_Y      (MAZE_HEIGHT - 1)   // [2-4]�S�[���̍s���`����

// [3]�񋓒萔���`����ꏊ

// [3-1]���ʂ̎�ނ��`����
enum
{
    DIRECTION_NORTH,    // [3-1-1]�k
    DIRECTION_WEST,     // [3-1-2]��
    DIRECTION_SOUTH,    // [3-1-3]��
    DIRECTION_EAST,     // [3-1-4]��
    DIRECTION_MAX       // [3-1-5]���ʂ̐�
};

// [3-2]�v���C���[����̑��Έʒu�̎�ނ��`����
enum
{
    LOCATION_FRONT_LEFT,    // [3-2-1]���O
    LOCATION_FRONT_RIGHT,   // [3-2-2]�E�O
    LOCATION_FRONT,         // [3-2-3]�O
    LOCATION_LEFT,          // [3-2-4]��
    LOCATION_RIGHT,         // [3-2-5]�E
    LOCATION_CENTER,        // [3-2-6]���S
    LOCATION_MAX            // [3-2-7]�ʒu�̐�
};

// [4]�\���̂�錾����ꏊ

// [4-1]�x�N�g���̍\���̂�錾����
typedef struct {
    int x, y;// [4-1-1]���W
} VEC2;

// [4-2]���H�̃}�X�̍\���̂�錾����
typedef struct {
    bool walls[DIRECTION_MAX];  // [4-2-1]�e���ʂ̕ǂ̗L��
} TILE;

// [4-3]�v���C���[�̍\���̂�錾����
typedef struct {
    VEC2 position;  // [4-3-1]���W
    int direction;  // [4-3-1]�����Ă������
} CHARACTER;

// [5]�ϐ���錾����ꏊ

// [5-1]�e���ʂ̃x�N�g����錾����
VEC2 directions[] =
{
    { 0,-1},    // DIRECTION_NORTH  �k
    {-1, 0},    // DIRECTION_WEST   ��
    { 0, 1},    // DIRECTION_SOUTH  ��
    { 1, 0}     // DIRECTION_EAST   ��
};

// [5-2]��ƂȂ�A�X�L�[�A�[�g��錾����
const char* all =
    "L       /\n"
    "#L     /#\n"
    "#|L _ /|#\n"
    "#|#|#|#|#\n"
    "#|#|_|#|#\n"
    "#|/   L|#\n"
    "#/     L#\n"
    "/       L\n";

// [5-3]���O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontLeftNorth =
    "         \n"
    "         \n"
    "  _      \n"
    " |#|     \n"
    " |_|     \n"
    "         \n"
    "         \n"
    "         \n";

// [5-4]�E�O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontRightNorth =
    "         \n"
    "         \n"
    "      _  \n"
    "     |#| \n"
    "     |_| \n"
    "         \n"
    "         \n"
    "         \n";

// [5-5]�O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontNorth =
    "         \n"
    "         \n"
    "    _    \n"
    "   |#|   \n"
    "   |_|   \n"
    "         \n"
    "         \n"
    "         \n";

// [5-6]�O�����̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontWest =
    "         \n"
    "         \n"
    " |L      \n"
    " |#|     \n"
    " |#|     \n"
    " |/      \n"
    "         \n"
    "         \n";

// [5-7]�O���E�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontEast =
    "         \n"
    "         \n"
    "      /| \n"
    "     |#| \n"
    "     |#| \n"
    "      L| \n"
    "         \n"
    "         \n";

// [5-8]�����O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* leftNorth =
    "         \n"
    "_        \n"
    "#|       \n"
    "#|       \n"
    "#|       \n"
    "_|       \n"
    "         \n"
    "         \n";

// [5-9]�E���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* rightNorth =
    "         \n"
    "        _\n"
    "       |#\n"
    "       |#\n"
    "       |#\n"
    "       |_\n"
    "         \n"
    "         \n";

// [5-10]�O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* north =
    "         \n"
    "  _____  \n"
    " |#####| \n"
    " |#####| \n"
    " |#####| \n"
    " |_____| \n"
    "         \n"
    "         \n";

// [5-11]���̕ǂ̃A�X�L�[�A�[�g��錾����
const char* west =
    "L        \n"
    "#L       \n"
    "#|       \n"
    "#|       \n"
    "#|       \n"
    "#|       \n"
    "#/       \n"
    "/        \n";

// [5-12]�E�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* east =
    "        /\n"
    "       /#\n"
    "       |#\n"
    "       |#\n"
    "       |#\n"
    "       |#\n"
    "       L#\n"
    "        L\n";

// [5-13]�A�X�L�[�A�[�g�̃e�[�u����錾����
const char* aaTable[LOCATION_MAX][DIRECTION_MAX] =
{
    // LOCATION_FRONT_LEFT  ���O
    {
        frontLeftNorth,     // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },

    // LOCATION_FRONT_RIGHT �E�O
    {
        frontRightNorth,    // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },

    // LOCATION_FRONT       �O
    {
        frontNorth,         // DIRECTION_NORTH  �k
        frontWest,          // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        frontEast           // DIRECTION_EAST   ��
    },

    // LOCATION_LEFT        ��
    {
        leftNorth,          // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },

    // LOCATION_RIGHT       �E
    {
        rightNorth,         // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },

    // LOCATION_CENTER      ���S
    {
        north,              // DIRECTION_NORTH  �k
        west,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        east                // DIRECTION_EAST   ��
    }
};

// [5-14]�v���C���[����̑��΍��W�̃e�[�u����錾����
VEC2 locations[DIRECTION_MAX][LOCATION_MAX] =
{
    // DIRECTION_NORTH  �k
    {
        {-1,-1},    // LOCATION_FRONT_LEFT  ���O
        { 1,-1},    // LOCATION_FRONT_RIGHT �E�O
        { 0,-1},    // LOCATION_FRONT       �O
        {-1, 0},    // LOCATION_LEFT        ��
        { 1, 0},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    },

    // DIRECTION_WEST   ��
    {
        {-1, 1},    // LOCATION_FRONT_LEFT  ���O
        {-1,-1},    // LOCATION_FRONT_RIGHT �E�O
        {-1, 0},    // LOCATION_FRONT       �O
        { 0, 1},    // LOCATION_LEFT        ��
        { 0,-1},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    },

    // DIRECTION_SOUTH  ��
    {
        { 1, 1},    // LOCATION_FRONT_LEFT  ���O
        {-1, 1},    // LOCATION_FRONT_RIGHT �E�O
        { 0, 1},    // LOCATION_FRONT       �O
        { 1, 0},    // LOCATION_LEFT        ��
        {-1, 0},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    },

    // DIRECTION_EAST   ��
    {
        { 1,-1},    // LOCATION_FRONT_LEFT  ���O
        { 1, 1},    // LOCATION_FRONT_RIGHT �E�O
        { 1, 0},    // LOCATION_FRONT       �O
        { 0,-1},    // LOCATION_LEFT        ��
        { 0, 1},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    }
};

TILE maze[MAZE_HEIGHT][MAZE_WIDTH];  // [5-15]���H��錾����

CHARACTER player;// [5-16]�v���C���[��錾����

// [6]�֐���錾����ꏊ

// [6-1]�x�N�g�������Z����֐���錾����
VEC2 VecAdd(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]�x�N�g�������Z���ĕԂ�
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}

// [6-2]�Ώۂ̍��W�����H�͈͓̔����ǂ����𔻒肷��֐���錾����
bool IsInsideMaze(VEC2 _position)
{
    // [6-2-1]�Ώۂ̍��W�����H�͈͓̔����ǂ�����Ԃ�
    return (_position.x >= 0)
        && (_position.x < MAZE_WIDTH)
        && (_position.y >= 0)
        && (_position.y < MAZE_HEIGHT);
}

// [6-3]�ǂ��@��֐���錾����
void DigWall(VEC2 _position, int _direction)
{
    // [6-3-1]�Ώۂ̍��W�����H�͈͓̔����ǂ����𔻒肷��
    if (!IsInsideMaze(_position))
    {
        return;// [6-3-2]�֐��𔲂���
    }

    // [6-3-3]�Ώۂ̕ǂ��@��
    maze[_position.y][_position.x].walls[_direction] = false;

    // [6-3-4]�ׂ̃}�X�̍��W��錾����
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // [6-3-5]�ׂ̃}�X�����H�͈͓̔����ǂ����𔻒肷��
    if (IsInsideMaze(nextPosition))
    {
        // [6-3-6]�ׂ̕����̌@��ǂ̕��ʂ�錾����
        int nextDirection = (_direction + 2) % DIRECTION_MAX;

        // [6-3-7]�ׂ̕����̕ǂ��@��
        maze[nextPosition.y][nextPosition.x].walls[nextDirection] = false;
    }
}

// [6-4]�Ώۂ̕ǂ��@���Ă��悢���ǂ����𔻒肷��֐���錾����
bool CanDigWall(VEC2 _position, int _direction)
{
    // [6-4-1]�ׂ̍��W��錾����
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // [6-4-2]�ׂ̍��W�����H�͈͓̔��łȂ����ǂ����𔻒肷��
    if (!IsInsideMaze(nextPosition))
    {
        return false;// [6-4-3]�@���Ă͂����Ȃ��Ƃ������ʂ�Ԃ�
    }

    // [6-4-4]���ׂĂ̕��ʂ𔽕�����
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        // [6-4-5]�ǂ��@���Ă��邩�ǂ����𔻒肷��
        if (!maze[nextPosition.y][nextPosition.x].walls[i])
        {
            return false;// [6-4-6]�@���Ă͂����Ȃ��Ƃ������ʂ�Ԃ�
        }
    }

    return true;// [6-4-7]�@���Ă��悢�Ƃ������ʂ�Ԃ�
}

// [6-5]���H�������_���Ő�������֐���錾����
void GenerateMap()
{
    // [6-5-1]���H�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-5-2]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-5-3]�}�X�̂��ׂĂ̕��ʂ𔽕�����
            for (int i = 0; i < DIRECTION_MAX; i++)
            {
                // [6-5-4]�Ώۂ̕��ʂ�ǂɂ���
                maze[y][x].walls[i] = true;
            }
        }
    }

    // [6-5-5]���݂̍��W��錾����
    VEC2 currentPosition = { 0, 0 };

    // [6-5-6]�ǂ��@��ׂ��}�X�̃��X�g��錾����
    std::vector<VEC2> toDigWallPositions;

    // [6-5-7]�ǂ��@��ׂ��}�X�̃��X�g�Ɍ��݂̃}�X��������
    toDigWallPositions.push_back(currentPosition);

    // [6-5-8]�������[�v����
    while (1)
    {
        // [6-5-9]�@���ǂ̕��ʂ̃��X�g��錾����
        std::vector<int> canDigDirections;

        // [6-5-10]���ׂĂ̕��ʂ𔽕�����
        for (int i = 0; i < DIRECTION_MAX; i++)
        {
            // [6-5-11]�Ώۂ̕��ʂ̕ǂ��@���Ă��悢�̂ł����
            if (CanDigWall(currentPosition, i))
            {
                // [6-5-12]�@���ǂ̕��ʂ̃��X�g�ɒǉ�����
                canDigDirections.push_back(i);
            }
        }

        // [6-5-13]�@���ǂ����邩�ǂ����𔻒肷��
        if (canDigDirections.size() > 0)
        {
            // [6-5-14]�@��ǂ̕��ʂ�錾����
            int digDirection = canDigDirections[rand() % canDigDirections.size()];

            // [6-5-15]�Ώۂ̕ǂ��@��
            DigWall(currentPosition, digDirection);

            // [6-5-16]�@�����ǂ̌������Ɉړ�����
            currentPosition = VecAdd(currentPosition, directions[digDirection]);

            // [6-5-17]�ǂ��@��ׂ��}�X�̍��W���X�g�Ɍ��݂̍��W��������
            toDigWallPositions.push_back(currentPosition);
        }

        // [6-5-18]�@��邪�Ȃ��Ƃ�
        else
        {
            // [6-5-19]�ǂ��@��ׂ��}�X�̃��X�g���猻�݂̃}�X���폜����
            toDigWallPositions.erase(toDigWallPositions.begin());

            // [6-5-20]�ǂ��@��ׂ��}�X�̃��X�g���󂩂ǂ����𔻒肷��
            if (toDigWallPositions.size() <= 0)
            {
                break;// [6-5-21]���[�v�𔲂���
            }

            // [6-5-22]�ǂ��@��ׂ��}�X�̃��X�g����A�擪�̃}�X���擾���ړ�����
            currentPosition = toDigWallPositions.front();
        }
    }
}

// [6-6]�}�b�v��`�悷��֐���錾����
void DrawMap()
{
    // [6-6-1]���H�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-6-2]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            //  [6-6-3]�k�̕ǂ�`�悷��
            printf("�{%s�{", maze[y][x].walls[DIRECTION_NORTH] ? "�\" : "�@");
        }

        printf("\n");// [6-6-4]1�s�`�悷�邲�Ƃɉ��s����

        // [6-6-5]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-6]���̃A�X�L�[�A�[�g��錾����
            char floorAA[] = "�@";

            // [6-6-7]�v���C���[�̍��W��`�撆�Ȃ�
            if ((x == player.position.x) && (y == player.position.y))
            {
                // [6-6-8]���ʂ̃A�X�L�[�A�[�g��錾����
                const char* directionAA[] =
                {
                    "��",    // DIRECTION_NORTH  �k
                    "��",    // DIRECTION_WEST   ��
                    "��",    // DIRECTION_SOUTH  ��
                    "��"     // DIRECTION_EAST   ��
                };

                // [6-6-9]���̃A�X�L�[�A�[�g�Ƀv���C���[�̃A�X�L�[�A�[�g���R�s�[����
                strcpy_s(floorAA, directionAA[player.direction]);
            }

            // [6-6-10]�S�[���̍��W��`�撆�Ȃ�
            else if ((x == GOAL_X) && (y == GOAL_Y))
            {
                // [6-6-11]���̃A�X�L�[�A�[�g�ɃS�[���̃A�X�L�[�A�[�g���R�s�[����
                strcpy_s(floorAA, "�f");
            }

            // [6-6-12]���̕ǁA���S�̏��A���̕ǂ�`�悷��
            printf("%s%s%s",
                maze[y][x].walls[DIRECTION_WEST] ? "�b" : "�@",
                floorAA,
                maze[y][x].walls[DIRECTION_EAST] ? "�b" : "�@");
        }

        printf("\n");// [6-6-13]1�s�`�悷�邲�Ƃɉ��s����

        // [6-6-14]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-15]��̕ǂ�`�悷��
            printf("�{%s�{", maze[y][x].walls[DIRECTION_SOUTH] ? "�\" : "�@");
        }

        printf("\n");// [6-6-16]1�s�`�悷�邲�Ƃɉ��s����
    }
}

// [6-7]���H���[��3D���_�ŕ`�悷��֐���錾����
void Draw3D()
{
    // [6-7-1]��ʃo�b�t�@�[��錾����
    char screen[] =
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n";

    // [6-7-2]���ׂĂ̑��Έʒu�𔽕�����
    for (int i = 0; i < LOCATION_MAX; i++)
    {
        // [6-7-3]��Έʒu��錾����
        VEC2 position = VecAdd(player.position, locations[player.direction][i]);

        // [6-7-4]��Έʒu�����H�͈̔͊O���ǂ����𔻒肷��
        if (!IsInsideMaze(position))
            continue;// [6-7-5]���̑��Έʒu�փX�L�b�v����

        // [6-7-6]���ׂĂ̕��ʂ𔽕�����
        for (int j = 0; j < DIRECTION_MAX; j++)
        {
            // [6-7-7]���Ε��ʂ�錾����
            int direction = (DIRECTION_MAX + j - player.direction) % DIRECTION_MAX;

            // [6-7-8]�Ώۂ̕ǂ��Ȃ����ǂ����𔻒肷��
            if (!maze[position.y][position.x].walls[j])
            {
                continue;// [6-7-9]���̕��ʂփX�L�b�v����
            }

            // [6-7-10]��������A�X�L�[�A�[�g���Ȃ����ǂ����𔻒肷��
            if (!aaTable[i][direction])
            {
                continue;// [6-7-11]���̑��Έʒu�փX�L�b�v����
            }

            // [6-7-12]��ʃo�b�t�@�[�̂��ׂĂ̕����𔽕�����
            for (int k = 0; k < sizeof(screen); k++)
            {
                // [6-7-13]�Ώۂ̕������X�y�[�X�łȂ����ǂ������肷��
                if (aaTable[i][direction][k] != ' ')
                {
                    // [6-7-14]��ʃo�b�t�@�[�ɍ�������A�X�L�[�A�[�g����������
                    screen[k] = aaTable[i][direction][k];
                }
            }
        }
    }

    // [6-7-15]��ʃo�b�t�@�[�̂��ׂĂ̕����𔽕�����
    for (int i = 0; i < sizeof(screen); i++)
    {
        // [6-7-16]��ʃo�b�t�@�[�̔��p������S�p�����ɕϊ����ĕ`�悷��
        switch (screen[i])
        {
        case ' ':   printf("�@");    break; // [6-7-17]�u �v���u�@�v�Ƃ��ĕ`�悷��
        case '#':   printf("�@");    break; // [6-7-18]�u#�v���u�@�v�Ƃ��ĕ`�悷��
        case '_':   printf("�Q");    break; // [6-7-19]�u_�v���u�Q�v�Ƃ��ĕ`�悷��
        case '|':   printf("�b");    break; // [6-7-20]�u|�v���u�b�v�Ƃ��ĕ`�悷��
        case '/':   printf("�^");    break; // [6-7-21]�u/�v���u�^�v�Ƃ��ĕ`�悷��
        case 'L':   printf("�_");    break; // [6-7-22]�uL�v���u�_�v�Ƃ��ĕ`�悷��
        default:

            // [6-7-23]��L�ȊO�̕����͂��̂܂ܕ`�悷��
            printf("%c", screen[i]);

            break;
        }
    }
}

// [6-8]�Q�[��������������֐���錾����
void Init()
{
    GenerateMap();// [6-8-1]���H�������_���Ő�������֐����Ăяo��

    player.position = { 0,0 };// [6-8-2]�v���C���[�̍��W������������

    player.direction = DIRECTION_NORTH;// [6-8-3]�v���C���[�̕��ʂ�����������
}

// [6-9]�v���O�����̎��s�J�n�_��錾����
int main()
{
    srand((unsigned int)time(NULL));// [6-9-1]�������V���b�t������

    Init();// [6-9-2]�Q�[��������������֐����Ăяo��

    // [6-9-3]���C�����[�v
    while (1)
    {
        system("cls");// [6-9-4]��ʂ��N���A����

        // [6-9-5]���H���[��3D���_�ŕ`�悷��֐����Ăяo��
        Draw3D();

        // [6-9-6]�}�b�v��`�悷��֐����Ăяo��
        DrawMap();

        // [6-9-7]���͂��ꂽ�L�[�ŕ��򂷂�
        switch (_getch())
        {
        case 'w':// [6-9-8]w�L�[�������ꂽ��

            // [6-9-9]�v���C���[�̖ڂ̑O���ǂłȂ����ǂ����𔻒肷��
            if (!maze[player.position.y][player.position.x].walls[player.direction])
            {
                // [6-9-10]�O�i��̍��W��錾����
                VEC2 nextPosition = VecAdd(player.position, directions[player.direction]);

                // [6-9-11]�O�i��̍��W�����H�͈͓̔����ǂ����𔻒肷��
                if (IsInsideMaze(nextPosition))
                {
                    // [6-9-12]�O�i��̍��W��K�p����
                    player.position = nextPosition;

                    // [6-9-13]�S�[���ɓ��B�������ǂ����𔻒肷��
                    if ((player.position.x == GOAL_X) && (player.position.y == GOAL_Y))
                    {
                        system("cls");// [6-9-14]��ʂ��N���A����

                        // [6-9-15]���b�Z�[�W��\������
                        printf(
                            "�@���@���@�b�n�m�f�q�`�s�t�k�`�s�h�n�m�r�@���@��\n"
                            "\n"
                            "�@���Ȃ��͂��Ɂ@�ł񂹂̂܂悯���@�Ăɂ��ꂽ�I\n"
                            "\n"
                            "�@�������A���炭���Ƃ��ɂ����@�u�Ȃ��܁v�Ƃ���\n"
                            "���������̂Ȃ��@��������Ăɂ����@���Ȃ��ɂƂ��āA\n"
                            "�܂悯�̂����₫���@���날���ā@�݂���̂ł������c\n"
                            "\n"
                            "�@�@�@�@�@�@�@�`�@�s�g�d�@�d�m�c�@�`\n");

                        _getch();// [6-9-16]�L�[�{�[�h���͂�҂�

                        Init();// [6-9-17]�Q�[��������������
                    }
                }
            }

            break;

        case 's':// [6-9-18]s�L�[�������ꂽ��

            player.direction += 2;// [6-9-19]��������

            break;

        case 'a':// [6-9-20]a�L�[�������ꂽ��

            player.direction++;// [6-9-21]��������

            break;

        case 'd':// [6-9-22]d�L�[�������ꂽ��

            player.direction--;// [6-9-23]�E������

            break;
        }

        // [6-9-24]�v���C���[�̌����Ă�����ʂ�͈͓��ɕ␳����
        player.direction = (DIRECTION_MAX + player.direction) % DIRECTION_MAX;
    }
}