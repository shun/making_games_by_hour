// [1]�w�b�_�[���C���N���[�h����ꏊ

#include <stdio.h>  // [1-1]�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> // [1-2]�W�����C�u�����w�b�_�[���C���N���[�h����
#include <string.h> // [1-3]�����񑀍�w�b�_�[���C���N���[�h����
#include <time.h>   // [1-4]���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>  // [1-5]�R���\�[�����o�̓w�b�_�[���C���N���[�h����
#include <vector>   // [1-6]�x�N�^�[�w�b�_�[���C���N���[�h����

// [2]�萔���`����ꏊ

#define MAZE_WIDTH  (19)            // [2-1]���H�̕����`����
#define MAZE_HEIGHT (19)            // [2-2]���H�̍������`����

#define FPS         (2)             // [2-3]1�b������̍X�V�p�x���`����
#define INTERVAL    (1000 / FPS)    // [2-4]�X�V���Ƃ̑ҋ@���ԁi�~���b�j���`����

// [3]�񋓒萔���`����ꏊ

// [3-1]�L�����N�^�[�̎�ނ��`����
enum
{
    CHARACTER_PLAYER,   // [3-1-1]�v���C���[
    CHARACTER_RANDOM,   // [3-1-2]�C�܂��ꃂ���X�^�[
    CHARACTER_CHASE,    // [3-1-3]�ǂ����������X�^�[
    CHARACTER_AMBUSH,   // [3-1-4]���胂���X�^�[
    CHARACTER_SIEGE,    // [3-1-5]���݌��������X�^�[
    CHARACTER_MAX       // [3-1-6]�L�����N�^�[�̐�
};

// [3-2]�����̎�ނ��`����
enum
{
    DIRECTION_UP,       // [3-2-1]��
    DIRECTION_LEFT,     // [3-2-2]��
    DIRECTION_DOWN,     // [3-2-3]��
    DIRECTION_RIGHT,    // [3-2-4]�E
    DIRECTION_MAX       // [3-2-5]�����̐�
};

// [4]�\���̂�錾����ꏊ

// [4-1]�x�N�g���̍\���̂�錾����
typedef struct {
    int x, y;   // [4-1-1]���W
} VEC2;

// [4-2]�L�����N�^�[�̍\���̂�錾����
typedef struct {
    VEC2        position;           // [4-2-1]���W
    const VEC2  defaultPosition;    // [4-2-2]�������W
    VEC2        lastPosition;       // [4-2-3]�O��̍��W
} CHARACTER;

// [5]�ϐ���錾����ꏊ

// [5-1]���H��錾����
char maze[MAZE_HEIGHT][MAZE_WIDTH + 1];

// [5-2]���H�̏�����Ԃ�錾����
const char defaultMaze[MAZE_HEIGHT][MAZE_WIDTH + 1] =
{
    "#########o#########",
    "#ooooooo#o#ooooooo#",
    "#o###o#o#o#o#o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o###o###o###o#",
    "#ooooooooooooooooo#",
    "#o###o###o###o###o#",
    "#ooo#o#ooooo#o#ooo#",
    "###o#o#o###o#o#o###",
    "oooooooo# #oooooooo",
    "###o#o#o###o#o#o###",
    "#ooo#o#ooooo#o#ooo#",
    "#o###o###o###o###o#",
    "#oooooooo oooooooo#",
    "#o###o###o###o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o#o#o#o#o###o#",
    "#ooooooo#o#ooooooo#",
    "#########o#########"
};

// [5-3]�L�����N�^�[�̔z���錾����
CHARACTER characters[CHARACTER_MAX] =
{
    // [5-3-1]CHARACTER_PLAYER  �v���C���[
    {
        {},         // [5-3-2]VEC2          position
        {9, 13},    // [5-3-3]const VEC2    defaultPosition
        {},         // [5-3-4]VEC2          lastPosition
    },

    // [5-3-5]CHARACTER_RANDOM  �C�܂��ꃂ���X�^�[
    {
        {},         // [5-3-6]VEC2          position
        {1, 1},     // [5-3-7]const VEC2    defaultPosition
        {},         // [5-3-8]VEC2          lastPosition
    },

    // [5-3-9]CHARACTER_CHASE   �ǂ����������X�^�[
    {
        {},         // [5-3-10]VEC2         position
        {17, 1},    // [5-3-11]const VEC2   defaultPosition
        {},         // [5-3-12]VEC2         lastPosition
    },

    // [5-3-13]CHARACTER_AMBUSH ���胂���X�^�[
    {
        {},         // [5-3-14]VEC2         position
        {1, 17},    // [5-3-15]const VEC2   defaultPosition
        {},         // [5-3-16]VEC2         lastPosition
    },

    // [5-3-17]CHARACTER_SIEGE      ���݌��������X�^�[
    {
        {},         // [5-3-18]VEC2         position
        {17, 17},   // [5-3-19]const VEC2   defaultPosition
        {},         // [5-3-20]VEC2         lastPosition
    }
};

// [5-4]�����̃x�N�g���̔z���錾����
VEC2 directions[DIRECTION_MAX] =
{
    { 0,-1},    // [5-4-1]DIRECTION_UP      ��
    {-1, 0},    // [5-4-2]DIRECTION_LEFT    ��
    { 0, 1},    // [5-4-3]DIRECTION_DOWN    ��
    { 1, 0}     // [5-4-4]DIRECTION_RIGHT   �E
};

// [6]�֐���錾����ꏊ

// [6-1]�x�N�g�������Z����֐���錾����
VEC2 Vec2Add(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]���Z�����x�N�g����Ԃ�
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}

// [6-2]�x�N�g�������Z����֐���錾����
VEC2 Vec2Subtract(VEC2 _v0, VEC2 _v1)
{
    // [6-2-1]���Z�����x�N�g����Ԃ�
    return
    {
        _v0.x - _v1.x,
        _v0.y - _v1.y
    };
}

// [6-3]�x�N�g���ǂ��������������ǂ����𔻒肷��֐���錾����
bool Vec2Equal(VEC2 _v0, VEC2 _v1)
{
    // [6-3-1]�x�N�g���ǂ��������������ǂ�����Ԃ�
    return (_v0.x == _v1.x) && (_v0.y == _v1.y);
}

// [6-4]�㉺���E�Ƀ��[�v�������W���擾����֐���錾����
VEC2 GetLoopPosition(VEC2 _position)
{
    // [6-4-1]�㉺���E�Ƀ��[�v�������W��Ԃ�
    return
    {
        (MAZE_WIDTH + _position.x) % MAZE_WIDTH,
        (MAZE_HEIGHT + _position.y) % MAZE_HEIGHT
    };
}

// [6-5]�����_���Ȉړ�����擾����֐���錾����
VEC2 GetRandomPosition(CHARACTER _character)
{
    // [6-5-1]�ړ���̌��̃��X�g��錾����
    std::vector<VEC2> positions;

    // [6-5-2]���ׂĂ̕����𔽕�����
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        // [6-5-3]�e�����̍��W��錾����
        VEC2 newPosition = Vec2Add(_character.position, directions[i]);

        // [6-5-4]�Ώۂ̍��W���㉺���E�Ƀ��[�v������
        newPosition = GetLoopPosition(newPosition);

        // [6-5-5]�Ώۂ̍��W�Ɉړ��\���ǂ����𔻒肷��
        if (
            // �ǂł͂Ȃ�
            (maze[newPosition.y][newPosition.x] != '#')

            // ���O��̍��W�Ɠ����ł͂Ȃ�
            && (!Vec2Equal(newPosition, _character.lastPosition))
        )
        {
            // [6-5-6]�Ώۂ̍��W���ړ���̌��̃��X�g�ɒǉ�����
            positions.push_back(newPosition);
        }
    }

    // [6-5-7]�ړ���̌��̒����烉���_���ō��W��Ԃ�
    return positions[rand() % positions.size()];
}

// [6-6]�ڕW�n�_�ւ̍ŒZ�o�H�̍ŏ��̍��W���擾����֐���錾����
VEC2 GetChasePosition(CHARACTER _character, VEC2 _targetPosition)
{
    // [6-6-1]�o�H��T�����ׂ����W�̃��X�g��錾����
    std::vector<VEC2> toCheckPositions;

    // [6-6-2]�T��������L�����N�^�[���g�̍��W��T�����ׂ����W�̃��X�g�ɒǉ�����
    toCheckPositions.push_back(_character.position);

    // [6-6-3]�T���J�n�n�_����e�}�X�ւ̋�����ێ�����z���錾����
    int distances[MAZE_HEIGHT][MAZE_WIDTH];

    // [6-8-4]���H�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-6-5]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-6]�Ώۂ̃}�X�ւ̋����𖢐ݒ�Ƃ��ď���������
            distances[y][x] = -1;
        }
    }

    // [6-6-7]�T��������L�����N�^�[���g�̍��W�ւ̋�����0�ɐݒ肷��
    distances[_character.position.y][_character.position.x] = 0;

    // [6-6-8]�T���J�n�n�_����e�}�X�ւ̌o�H��ێ�����z���錾����
    std::vector<VEC2> routes[MAZE_HEIGHT][MAZE_WIDTH];

    // [6-6-9]�T�����ׂ����W�̃��X�g����ɂȂ�܂Ŕ�������
    while (!toCheckPositions.empty())
    {
        // [6-6-10]���ׂĂ̕����𔽕�����
        for (int i = 0; i < DIRECTION_MAX; i++)
        {
            // [6-8-11]�T�����̍��W�ɗאڂ���e�����̍��W���擾����
            VEC2 newPosition = Vec2Add(toCheckPositions.front(), directions[i]);

            // [6-6-12]�Ώۂ̍��W���㉺���E�Ƀ��[�v���������W�ɕϊ�����
            newPosition = GetLoopPosition(newPosition);

            // [6-6-13]�Ώۂ̍��W�ւ̋�����錾����
            int newDistance =
                distances[toCheckPositions.front().y][toCheckPositions.front().x] + 1;

            // [6-6-14]�Ώۂ̍��W��T�����ׂ����ǂ����𔻒肷��
            if (
                (
                	// ���ݒ�ł���
                    (distances[newPosition.y][newPosition.x] < 0)

                    // �������͍ŒZ�o�H�ł���
                    || (newDistance < distances[newPosition.y][newPosition.x])
                )

                // ���ǂł͂Ȃ�
                && (maze[newPosition.y][newPosition.x] != '#')
            )
            {
                // [6-6-15]�Ώۂ̍��W�ւ̋������X�V����
                distances[newPosition.y][newPosition.x] = newDistance;

                // [6-6-16]�Ώۂ̍��W��T�����ׂ����W�̃��X�g�֒ǉ�����
                toCheckPositions.push_back(newPosition);

                // [6-6-17]�Ώۂ̍��W�ւ̌o�H���A1�O�̍��W�̌o�H�ŏ���������
                routes[newPosition.y][newPosition.x] =
                    routes[toCheckPositions.front().y][toCheckPositions.front().x];

                // [6-6-18]�Ώۂ̍��W�ւ̌o�H�ɁA�Ώۂ̍��W��ǉ�����
                routes[newPosition.y][newPosition.x].push_back(newPosition);
            }
        }

        // [6-6-19]�T�����ׂ����W�̃��X�g����擪�̍��W���폜����
        toCheckPositions.erase(toCheckPositions.begin());
    }

    // [6-6-20]�ڕW�n�_�ւ̌o�H�����邩�ǂ����𔻒肷��
    if (
        // �o�H������
        (!routes[_targetPosition.y][_targetPosition.x].empty())

        // ���O��̍��W�ƈႤ���W�ł����
        && (!Vec2Equal(
            routes[_targetPosition.y][_targetPosition.x].front(),
            _character.lastPosition)
        )
    )
    {
        // [6-6-21]�ڕW�n�_�ւ̌o�H��1�ڂ̍��W��Ԃ�
        return routes[_targetPosition.y][_targetPosition.x].front();
    }
    // [6-6-22]�ڕW�n�_�ւ̌o�H���Ȃ����
    else
    {
        // [6-6-23]�����_���ȍ��W��Ԃ�
        return GetRandomPosition(_character);
    }
}

// [6-7]���H��`�悷��֐���錾����
void DrawMaze()
{
    // [6-7-1]��ʃo�b�t�@�[��錾����
    char screen[MAZE_HEIGHT][MAZE_WIDTH + 1];

    // [6-7-2]��ʃo�b�t�@�[�ɖ��H���R�s�[����
    memcpy(screen, maze, sizeof maze);

    // [6-7-3]���ׂẴL�����N�^�[�𔽕�����
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        // [6-7-4]�L�����N�^�[�̔ԍ�����ʃo�b�t�@�[�ɏ�������
        screen[characters[i].position.y][characters[i].position.x] = i;
    }

    system("cls");// [6-7-5]��ʂ��N���A����

    // [6-7-6]���H�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-7-7]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-7-8]�}�X��`�悷��
            switch (screen[y][x])
            {
            case ' ':               printf("�@");    break;  // [6-7-9]��
            case '#':               printf("��");    break;  // [6-7-10]�ǂ�`�悷��
            case 'o':               printf("�E");    break;  // [6-7-11]�h�b�g
            case CHARACTER_PLAYER:  printf("��");    break;  // [6-7-12]�v���C���[
            case CHARACTER_RANDOM:  printf("��");    break;  // [6-7-13]�C�܂��ꃂ���X�^�[
            case CHARACTER_CHASE:   printf("��");    break;  // [6-7-14]�ǂ����������X�^�[
            case CHARACTER_AMBUSH:  printf("��");    break;  // [6-7-15]���胂���X�^�[
            case CHARACTER_SIEGE:   printf("��");    break;  // [6-7-16]���݌��������X�^�[
            }
        }

        // [6-7-17]1�s�`�悷�邲�Ƃɉ��s����
        printf("\n");
    }
}

// [6-8]�Q�[��������������֐���錾����
void Init()
{
    // [6-8-1]���H�ɏ�����Ԃ��R�s�[����
    memcpy(maze, defaultMaze, sizeof maze);

    // [6-8-2]���ׂẴL�����N�^�[�𔽕�����
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        // [6-8-3]�L�����N�^�[�̍��W������������
        characters[i].position
            = characters[i].lastPosition
            = characters[i].defaultPosition;
    }
}

// [6-9]�Q�[���I�[�o�[�̊֐���錾����
bool IsGameOver()
{
    // [6-9-1]���ׂẴ����X�^�[�𔽕�����
    for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
    {
        // [6-9-2]�Ώۂ̃����X�^�[�ƃv���C���[�̍��W���������ǂ����𔻒肷��
        if (Vec2Equal(
            characters[i].position,                 // �Ώۂ̃����X�^�[�̍��W
            characters[CHARACTER_PLAYER].position)) // �v���C���[�̍��W
        {
            // [6-9-3]��ʂ��N���A����
            system("cls");

            // [6-9-4]���H�̍����̔���������������
            for (int j = 0; j < MAZE_HEIGHT / 2; j++)
            {
                // [6-9-5]���s����
                printf("\n");
            }

            // [6-9-6]�Q�[���I�[�o�[�̃��b�Z�[�W��\������
            printf("�@�@�@�@�@�f�`�l�d�@�n�u�d�q");

            // [6-9-7]�L�[�{�[�h���͂�҂�
            _getch();

            // [6-9-8]�Q�[���I�[�o�[�ɂȂ����Ƃ������ʂ�Ԃ�
            return true;
        }
    }

    // [6-9-9]�Q�[���I�[�o�[�ɂȂ�Ȃ������Ƃ������ʂ�Ԃ�
    return false;
}

// [6-10]�G���f�B���O�̊֐���錾����
bool IsComplete()
{
    // [6-10-1]���H�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-10-2]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-10-3]�Ώۂ̃}�X���h�b�g���ǂ����𔻒肷��
            if (maze[y][x] == 'o')
            {
                // [6-10-4]�N���A�ł͂Ȃ��Ƃ������ʂ�Ԃ�
                return false;
            }
        }
    }

    // [6-10-5]��ʂ��N���A����
    system("cls");

    // [6-10-6]���H�̍����̔���������������
    for (int i = 0; i < MAZE_HEIGHT / 2; i++)
    {
        // [6-10-7]���s����
        printf("\n");
    }

    // [6-10-8]�G���f�B���O�̃��b�Z�[�W��\������
    printf("�@�@�b�n�m�f�q�`�s�t�k�`�s�h�n�m�r�I");

    // [6-10-9]�L�[�{�[�h���͂�҂�
    _getch();

    // [6-10-10]�N���A�����Ƃ������ʂ�Ԃ�
    return true;
}

// [6-11]�v���O�����̎��s�J�n�_��錾����
int main()
{
    // [6-11-1]���������݂̎����ŃV���b�t������
    srand((unsigned int)time(NULL));

start:  // [6-11-2]�Q�[���̊J�n���x��
    ;   // [6-11-3]��

    // [6-11-4]�Q�[��������������֐����Ăяo��
    Init();

    // [6-11-5]���H��`�悷��֐����Ăяo��
    DrawMaze();

    // [6-11-6]�O��̍X�V������錾����
    time_t lastClock = clock();

    // [6-11-7]���C�����[�v
    while (1)
    {
        // [6-11-8]���݂̎�����錾����
        time_t newClock = clock();

        // [6-11-9]�O��̍X�V����ҋ@���Ԃ��o�߂������ǂ����𔻒肷��
        if (newClock > lastClock + INTERVAL)
        {
            // [6-11-10]�O��̍X�V���������݂̎����ōX�V����
            lastClock = newClock;

            // [6-11-11]���ׂẴ����X�^�[�𔽕�����
            for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
            {
                // [6-11-12]�ړ���̍��W��錾����
                VEC2 newPosition = characters[i].position;

                // [6-11-13]�����X�^�[�̎�ނɂ���ĕ��򂷂�
                switch (i)
                {
                    // [6-11-14]�C�܂��ꃂ���X�^�[
                case CHARACTER_RANDOM:

                    // [6-11-15]�����_���Ȉړ���̍��W��ݒ肷��
                    newPosition = GetRandomPosition(characters[i]);

                    break;

                // [6-11-16]�ǂ����������X�^�[
                case CHARACTER_CHASE:

                    // [6-11-17]�v���C���[��ǂ���������W��ݒ肷��
                    newPosition =
                        GetChasePosition(characters[i], characters[CHARACTER_PLAYER].position);

                    break;

                // [6-11-18]���胂���X�^�[
                case CHARACTER_AMBUSH:
                {
                    // [6-11-19]�v���C���[�̌����x�N�g����錾����
                    VEC2 playerDirection = Vec2Subtract(
                        characters[CHARACTER_PLAYER].position,
                        characters[CHARACTER_PLAYER].lastPosition);

                    // [6-11-20]�ڕW�n�_��錾����
                    VEC2 targetPosition = characters[CHARACTER_PLAYER].position;

                    // [6-11-21]3�񔽕�����
                    for (int j = 0; j < 3; j++)
                    {
                        // [6-11-22]�ڕW�n�_�Ƀv���C���[�̌����x�N�g�������Z����
                        targetPosition = Vec2Add(targetPosition, playerDirection);
                    }

                    // [6-11-23]�ڕW�n�_���㉺���E�Ƀ��[�v���������W�ɕϊ�����
                    targetPosition = GetLoopPosition(targetPosition);

                    // [6-11-24]�ڕW�n�_��ڎw�����W��ݒ肷��
                    newPosition = GetChasePosition(characters[i], targetPosition);

                    break;
                }
                // [6-11-25]���݌��������X�^�[
                case CHARACTER_SIEGE:
                {
                    // [6-11-26]�ǂ����������X�^�[����v���C���[�ւ̃x�N�g�����擾����
                    VEC2 chaseToPlayer = Vec2Subtract(
                        characters[CHARACTER_PLAYER].position,  // �v���C���[�̍��W
                        characters[CHARACTER_CHASE].position);  // �ǂ����������X�^�[�̍��W

                    // [6-11-27]�ړI�n��錾����
                    VEC2 targetPosition =

                        // �x�N�g�������Z����
                        Vec2Add(

                            // �v���C���[�̍��W
                            characters[CHARACTER_PLAYER].position,
                            
                            // �ǂ����������X�^�[����v���C���[�ւ̃x�N�g��
                            chaseToPlayer);

                    // [6-11-28]�ڕW�n�_���㉺���E�Ƀ��[�v���������W�ɕϊ�����
                    targetPosition = GetLoopPosition(targetPosition);

                    // [6-11-29]�ڕW�n�_��ڎw�����W��ݒ肷��
                    newPosition = GetChasePosition(characters[i], targetPosition);

                    break;
                }
                }

                // [6-11-30]�O��̍��W�����݂̍��W�ōX�V����
                characters[i].lastPosition = characters[i].position;

                // [6-11-31]�ړ���Ɉړ�������
                characters[i].position = newPosition;
            }

            // [6-11-32]�Q�[���I�[�o�[�ɂȂ������ǂ����𔻒肷��
            if (IsGameOver())
            {
                goto start; // [6-11-33]�Q�[���̊J�n���x���ɃW�����v����
            }

            // [6-11-34]��ʂ��ĕ`�悷��
            DrawMaze();
        }

        // [6-11-35]�L�[�{�[�h���͂����������ǂ����𔻒肷��
        if (_kbhit())
        {
            // [6-11-36]�v���C���[�̐V�������W��錾����
            VEC2 newPosition = characters[CHARACTER_PLAYER].position;

            // [6-11-37]���͂��ꂽ�L�[�ɂ���ĕ��򂷂�
            switch (_getch())
            {
            case 'w':   newPosition.y--;    break;  // [6-11-38]w�������ꂽ���ֈړ�����
            case 's':   newPosition.y++;    break;  // [6-11-39]s�������ꂽ�牺�ֈړ�����
            case 'a':   newPosition.x--;    break;  // [6-11-40]a�������ꂽ�獶�ֈړ�����
            case 'd':   newPosition.x++;    break;  // [6-11-41]d�������ꂽ��E�ֈړ�����
            }

            // [6-11-42]�ړ���̍��W���㉺���E�Ƀ��[�v������
            newPosition = GetLoopPosition(newPosition);

            // [6-11-43]�ړ��悪�ǂłȂ��ǂ����𔻒肷��
            if (maze[newPosition.y][newPosition.x] != '#')
            {
                // [6-11-44]�v���C���[�̑O��̍��W�����݂̍��W�ōX�V����
                characters[CHARACTER_PLAYER].lastPosition =
                    characters[CHARACTER_PLAYER].position;

                // [6-11-45]�v���C���[�̍��W���X�V����
                characters[CHARACTER_PLAYER].position = newPosition;

                // [6-11-46]�Q�[���I�[�o�[�ɂȂ������ǂ����𔻒肷��
                if (IsGameOver())
                {
                    goto start; // [6-11-47]�Q�[���̊J�n���x���ɃW�����v����
                }

                // [6-11-48]�v���C���[�̍��W�Ƀh�b�g�����邩�ǂ����𔻒肷��
                if (maze[characters[CHARACTER_PLAYER].position.y]
                                    [characters[CHARACTER_PLAYER].position.x] == 'o')
                {
                    // [6-11-49]�v���C���[�̍��W�̃h�b�g������
                    maze[characters[CHARACTER_PLAYER].position.y]
                        [characters[CHARACTER_PLAYER].position.x] = ' ';

                    // [6-11-50]�N���A�������ǂ����𔻒肷��
                    if (IsComplete())
                    {
                        goto start; // [6-11-51]�Q�[���̊J�n���x���ɃW�����v����
                    }
                }
            }

            // [6-11-52]���H���ĕ`�悷��
            DrawMaze();
        }
    }
}