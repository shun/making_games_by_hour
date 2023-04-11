// [1]�w�b�_�[���C���N���[�h����ꏊ

#include <stdio.h>  // [1-1]�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> // [1-2]�W�����C�u�����w�b�_�[���C���N���[�h����
#include <string.h>	// [1-3]�����񑀍�w�b�_�[���C���N���[�h����
#include <time.h>   // [1-4]���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>  // [1-5]�R���\�[�����o�̓w�b�_�[���C���N���[�h����

// [2]�萔���`����ꏊ

#define SPELL_COST  (3) // [2-1]�����̏���MP���`����

// [3]�񋓒萔���`����ꏊ

// [3-1]�����X�^�[�̎�ނ��`����
enum
{
    MONSTER_PLAYER, // [3-1-1]�v���C���[
    MONSTER_SLIME,  // [3-1-2]�X���C��
    MONSTER_BOSS,   // [3-1-3]����
    MONSTER_MAX     // [3-1-4]�����X�^�[�̎�ނ̐�
};

// [3-2]�L�����N�^�[�̎�ނ��`����
enum
{
    CHARACTER_PLAYER,   // [3-2-1]�v���C���[
    CHARACTER_MONSTER,  // [3-2-2]�����X�^�[
    CHARACTER_MAX       // [3-2-3]�L�����N�^�[�̎�ނ̐�
};

// [3-3]�R�}���h�̎�ނ��`����
enum
{
    COMMAND_FIGHT,  // [3-3-1]�키
    COMMAND_SPELL,  // [3-3-2]����
    COMMAND_RUN,    // [3-3-3]������
    COMMAND_MAX     // [3-3-4]�R�}���h�̎�ނ̐�
};

// [4]�\���̂�錾����ꏊ

// [4-1]�L�����N�^�[�̍\���̂�錾����
typedef struct {
    int hp;                 // [4-1-1]HP
    int maxHp;              // [4-1-2]�ő�HP
    int mp;                 // [4-1-3]MP
    int maxMp;              // [4-1-4]�ő�MP
    int attack;             // [4-1-5]�U����
    char name[4 * 2 + 1];   // [4-1-6]���O
    char aa[256];           // [4-1-7]�A�X�L�[�A�[�g
    int command;            // [4-1-8]�R�}���h
    int target;             // [4-1-9]�U���Ώ�
}CHARACTER;

// [5]�ϐ���錾����ꏊ

// [5-1]�����X�^�[�̃X�e�[�^�X�̔z���錾����
CHARACTER monsters[MONSTER_MAX] =
{
    // [5-1-1]MONSTER_PLAYER    �v���C���[
    {
        100,        // [5-1-2]int hp                HP
        100,        // [5-1-3]int maxHp             �ő�HP
        15,         // [5-1-4]int mp                MP
        15,         // [5-1-5]int maxMp             �ő�MP
        30,         // [5-1-6]int attack            �U����
        "�䂤����", // [5-1-7]char name[4 * 2 + 1]  ���O
    },

    // [5-1-8]MONSTER_SLIME �X���C��
    {
        3,          // [5-1-9]int hp                HP
        3,          // [5-1-10]int maxHp            �ő�HP
        0,          // [5-1-11]int mp               MP
        0,          // [5-1-12]int maxMp            �ő�MP
        2,          // [5-1-13]int attack           �U����
        "�X���C��", // [5-1-14]char name[4 * 2 + 1] ���O

        // [5-1-15]char aa[256] �A�X�L�[�A�[�g
        "�^�E�D�E�_\n"
        "�`�`�`�`�`"
    },

    // [5-1-16]MONSTER_BOSS ����
    {
        255,        // [5-1-17]int hp               HP
        255,        // [5-1-18]int maxHp            �ő�HP
        0,          // [5-1-19]int mp               MP
        0,          // [5-1-20]int maxMp            �ő�MP
        50,         // [5-1-21]int attack           �U����
        "�܂���",   // [5-1-22]char name[4 * 2 + 1] ���O

        // [5-1-23]char aa[256] �A�X�L�[�A�[�g
        "�@�@�`���`\n"
        "�Ձi���M���j��"
    }
};

// [5-2]�L�����N�^�[�̔z���錾����
CHARACTER characters[CHARACTER_MAX];

// [5-3]�R�}���h�̖��O��錾����
char commandNames[COMMAND_MAX][4 * 2 + 1] = {
    "��������", // [5-3-1]COMMAND_FIGHT �키
    "�������", // [5-3-2]COMMAND_SPELL ����
    "�ɂ���"    // [5-3-3]COMMAND_RUN   ������
};

// [6]�֐���錾����ꏊ

// [6-1]�Q�[��������������֐���錾����
void Init()
{
    // [6-1-1]�v���C���[�̃X�e�[�^�X������������
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

// [6-2]�퓬�V�[���̉�ʂ�`�悷��֐���錾����
void DrawBattleScreen()
{
    // [6-2-1]��ʂ��N���A����
    system("cls");

    // [6-2-2]�v���C���[�̖��O��\������
    printf("%s\n", characters[CHARACTER_PLAYER].name);

    // [6-2-3]�v���C���[�̃X�e�[�^�X��\������
    printf("�g�o�F%d�^%d�@�l�o�F%d�^%d\n",
        characters[CHARACTER_PLAYER].hp,
        characters[CHARACTER_PLAYER].maxHp,
        characters[CHARACTER_PLAYER].mp,
        characters[CHARACTER_PLAYER].maxMp);

    // [6-2-4]1�s�󂯂�
    printf("\n");

    // [6-2-5]�����X�^�[�̃A�X�L�[�A�[�g��`�悷��
    printf("%s", characters[CHARACTER_MONSTER].aa);

    // [6-2-6]�����X�^�[�̂g�o��\������
    printf("�i�g�o�F%d�^%d�j\n",
        characters[CHARACTER_MONSTER].hp,
        characters[CHARACTER_MONSTER].maxHp);

    // [6-2-7]1�s�󂯂�
    printf("\n");
}

// [6-3]�R�}���h��I������֐���錾����
void SelectCommand()
{
    // [6-3-1]�v���C���[�̃R�}���h������������
    characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

    // [6-3-2]�R�}���h�����肳���܂Ń��[�v����
    while (1)
    {
        // [6-3-3]�퓬��ʂ�`�悷��֐����Ăяo��
        DrawBattleScreen();

        // [6-3-4]�R�}���h�̈ꗗ��\������
        for (int i = 0; i < COMMAND_MAX; i++)
        {
            // [6-3-5]�I�𒆂̃R�}���h�Ȃ�
            if (i == characters[CHARACTER_PLAYER].command)
            {
                // [6-3-6]�J�[�\����`�悷��
                printf("��");
            }
            // [6-3-7]�I�𒆂̃R�}���h�łȂ����
            else
            {
                // [6-3-8]�S�p�X�y�[�X��`�悷��
                printf("�@");
            }

            // [6-3-9]�R�}���h�̖��O��\������
            printf("%s\n", commandNames[i]);
        }

        // [6-3-10]���͂��ꂽ�L�[�ɂ���ĕ��򂷂�
        switch (_getch())
        {
        case 'w':   // [6-3-11]w�L�[�������ꂽ��

            // [6-3-12]��̃R�}���h�ɐ؂�ւ���
            characters[CHARACTER_PLAYER].command--;

            break;

        case 's':   // [6-3-13]s�L�[�������ꂽ��

            // [6-3-14]���̃R�}���h�ɐ؂�ւ���
            characters[CHARACTER_PLAYER].command++;

            break;

        default:    // [6-3-15]��L�ȊO�̃L�[�������ꂽ��
            return; // [6-3-16]�֐��𔲂���
        }

        // [6-3-17]�J�[�\�����㉺�Ƀ��[�v������
        characters[CHARACTER_PLAYER].command =
            (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
    }
}

// [6-4]�퓬�V�[���̊֐���錾����
void Battle(int _monster)
{
    // [6-4-1]�����X�^�[�̃X�e�[�^�X������������
    characters[CHARACTER_MONSTER] = monsters[_monster];

    // [6-4-2]�v���C���[�̍U���Ώۂ������X�^�[�ɐݒ肷��
    characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

    // [6-4-3]�����X�^�[�̍U���Ώۂ��v���C���[�ɐݒ肷��
    characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

    // [6-4-4]�퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
    DrawBattleScreen();

    // [6-4-5]�퓬�V�[���̍ŏ��̃��b�Z�[�W��\������
    printf("%s���@�����ꂽ�I\n", characters[CHARACTER_MONSTER].name);

    // [6-4-6]�L�[�{�[�h���͂�҂�
    _getch();

    // [6-4-7]�퓬���I������܂Ń��[�v����
    while (1)
    {
        // [6-4-8]�R�}���h��I������֐����Ăяo��
        SelectCommand();

        // [6-4-9]�e�L�����N�^�[�𔽕�����
        for (int i = 0; i < CHARACTER_MAX; i++)
        {
            // [6-4-10]�퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
            DrawBattleScreen();

            // [6-4-11]�I�����ꂽ�R�}���h�ŕ��򂷂�
            switch (characters[i].command)
            {
            case COMMAND_FIGHT: // [6-4-12]�키
            {
                // [6-4-13]�U�������郁�b�Z�[�W��\������
                printf("%s�́@���������I\n", characters[i].name);

                // [6-4-14]�L�[�{�[�h���͂�҂�
                _getch();

                // [6-4-15]�G�ɗ^����_���[�W���v�Z����
                int damage = 1 + rand() % characters[i].attack;

                // [6-4-16]�G�Ƀ_���[�W��^����
                characters[characters[i].target].hp -= damage;

                // [6-4-17]�G��HP�����̒l�ɂȂ������ǂ����𔻒肷��
                if (characters[characters[i].target].hp < 0)
                {
                    // [6-4-18]�G��HP��0�ɂ���
                    characters[characters[i].target].hp = 0;
                }

                // [6-4-19]�퓬�V�[���̉�ʂ��ĕ`�悷��֐����Ăяo��
                DrawBattleScreen();

                // [6-4-20]�G�Ƀ_���[�W��^�������b�Z�[�W��\������
                printf("%s�Ɂ@%d�́@�_���[�W�I\n",
                    characters[characters[i].target].name,
                    damage);

                // [6-4-21]�L�[�{�[�h���͂�҂�
                _getch();

                break;
            }
            case COMMAND_SPELL: // [6-4-22]����

                // [6-4-23]MP������邩�ǂ����𔻒肷��
                if (characters[i].mp < SPELL_COST)
                {
                    // [6-4-24]MP������Ȃ����b�Z�[�W��\������
                    printf("�l�o���@����Ȃ��I\n");

                    // [6-4-25]�L�[�{�[�h���͂�҂�
                    _getch();

                    // [6-4-26]�����������鏈���𔲂���
                    break;
                }

                // [6-4-27]MP���������
                characters[i].mp -= SPELL_COST;

                // [6-4-28]��ʂ��ĕ`�悷��
                DrawBattleScreen();

                // [6-4-29]���������������b�Z�[�W��\������
                printf("%s�́@�q�[�����@�ƂȂ����I\n", characters[i].name);

                // [6-4-30]�L�[�{�[�h���͂�҂�
                _getch();

                // [6-4-31]HP���񕜂�����
                characters[i].hp = characters[i].maxHp;

                // [6-4-32]�퓬�V�[���̉�ʂ��ĕ`�悷��
                DrawBattleScreen();

                // [6-4-33]HP���񕜂������b�Z�[�W��\������
                printf("%s�̂������@�����ӂ������I\n", characters[i].name);

                // [6-4-34]�L�[�{�[�h���͂�҂�
                _getch();

                break;

            case COMMAND_RUN:   // [6-4-35]������

                // [6-4-36]�����o�������b�Z�[�W��\������
                printf("%s�́@�ɂ��������I\n", characters[i].name);

                // [6-4-37]�L�[�{�[�h���͂�҂�
                _getch();

                // [6-4-38]�퓬�����𔲂���
                return;

                break;
            }

            // [6-4-39]�U���Ώۂ�|�������ǂ����𔻒肷��
            if (characters[characters[i].target].hp <= 0)
            {
                // [6-4-40]�U���Ώۂɂ���ď����𕪊򂳂���
                switch (characters[i].target)
                {
                // [6-4-41]�v���C���[�Ȃ�
                case CHARACTER_PLAYER:

                    // [6-4-42]�v���C���[�����񂾃��b�Z�[�W��\������
                    printf("���Ȃ��́@���ɂ܂���");

                    break;

                // [6-4-43]�����X�^�[�Ȃ�
                case CHARACTER_MONSTER:

                    // [6-4-44]�����X�^�[�̃A�X�L�[�A�[�g�������\�����Ȃ��悤�ɏ���������
                    strcpy_s(characters[characters[i].target].aa, "\n");

                    // [6-4-45]�퓬�V�[���̉�ʂ��ĕ`�悷��֐����Ăяo��
                    DrawBattleScreen();

                    // [6-4-46]�����X�^�[��|�������b�Z�[�W��\������
                    printf("%s���@���������I\n", characters[characters[i].target].name);

                    break;
                }

                // [6-4-47]�L�[�{�[�h���͂�҂�
                _getch();

                // [6-4-48]�퓬�V�[���̊֐��𔲂���
                return;
            }
        }
    }
}

// [6-6]�v���O�����̎��s�J�n�_��錾����
int main()
{
    // [6-6-1]�������V���b�t������
    srand((unsigned int)time(NULL));

    // [6-6-2]�Q�[��������������֐����Ăяo��
    Init();

    // [6-6-3]�퓬�V�[���̊֐����Ăяo��
    Battle(MONSTER_BOSS);
}