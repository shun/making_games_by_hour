// [1]�w�b�_�[���C���N���[�h����ꏊ

#include <stdio.h>      // [1-1]�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h>     // [1-2]�W�����C�u�����w�b�_�[���C���N���[�h����
#include <time.h>       // [1-3]���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>      // [1-4]�R���\�[�����o�̓w�b�_�[���C���N���[�h����
#include <vector>       // [1-5]�x�N�^�[�w�b�_�[���C���N���[�h����
#include <algorithm>    // [1-6]�A���S���Y���w�b�_�[���C���N���[�h����

// [2]�萔���`����ꏊ

#define TROOP_BASE      (5)     // [2-1]��{�������`����
#define TROOP_MAX       (9)     // [2-2]�ő啺�����`����
#define TROOP_UNIT      (1000)  // [2-3]�����̒P�ʂ��`����
#define START_YEAR      (1570)  // [2-4]�J�n�N���`����
#define CHRONOLOGY_MAX  (1024)  // [2-5]�N�\�̍ő啶�������`����

// [3]�񋓒萔���`����ꏊ

// [3-1]�喼�̎�ނ��`����
enum
{
    LORD_DATE,      // [3-1- 1]�ɒB�P�@
    LORD_UESUGI,    // [3-1- 2]�㐙���M
    LORD_TAKEDA,    // [3-1- 3]���c�M��
    LORD_HOJO,      // [3-1- 4]�k������
    LORD_TOKUGAWA,  // [3-1- 5]����ƍN
    LORD_ODA,       // [3-1- 6]�D�c�M��
    LORD_ASHIKAGA,  // [3-1- 7]�����`��
    LORD_MORI,      // [3-1- 8]�ї����A
    LORD_CHOSOKABE, // [3-1- 9]���@�䕔���e
    LORD_SIMAZU,    // [3-1-10]���Ë`�v
    LORD_MAX        // [3-1-11]��ނ̐�
};

// [3-2]��̎�ނ��`����
enum
{
    CASTLE_YONEZAWA,        // [3-2- 1]�đ��
    CASTLE_KASUGAYAMA,      // [3-2- 2]�t���R��
    CASTLE_TSUTSUJIGASAKI,  // [3-2- 3]�U�P�����
    CASTLE_ODAWARA,         // [3-2- 4]���c����
    CASTLE_OKAZAKI,         // [3-2- 5]�����
    CASTLE_GIFU,            // [3-2- 6]�򕌏�
    CASTLE_NIJO,            // [3-2- 7]�����
    CASTLE_YOSHIDAKORIYAMA, // [3-2- 8]�g�c�S�R��
    CASTLE_OKO,             // [3-2- 9]���L��
    CASTLE_UCHI,            // [3-2-10]����
    CASTLE_MAX              // [3-2-11]��ނ̐�
};

// [4]�\���̂�錾����ꏊ

// [4-1]�喼�̍\���̂�錾����
typedef struct {
    char familyName[16];    // [4-1-1]��
    char firstName[16];     // [4-1-2]��
} LORD;

// [4-2]��̍\���̂�錾����
typedef struct {
    const char*         name;               // [4-2-1]���O
    int                 owner;              // [4-2-2]���
    int                 troopCount;         // [4-2-3]����
    std::vector<int>    connectedCastles;   // [4-2-4]�ڑ����ꂽ��̃��X�g
} CASTLE;

// [5]�ϐ���錾����ꏊ

// [5-1]�喼�̔z���錾����
LORD lords[LORD_MAX] =
{
    {"�ɒB",    "�P�@"},    // [5-1- 1]LORD_DATE        �ɒB�P�@
    {"�㐙",    "���M"},    // [5-1- 2]LORD_UESUGI      �㐙���M
    {"���c",    "�M��"},    // [5-1- 3]LORD_TAKEDA      ���c�M��
    {"�k��",    "����"},    // [5-1- 4]LORD_HOJO        �k������
    {"����",    "�ƍN"},    // [5-1- 5]LORD_TOKUGAWA    ����ƍN
    {"�D�c",    "�M��"},    // [5-1- 6]LORD_ODA         �D�c�M��
    {"����",    "�`��"},    // [5-1- 7]LORD_ASHIKAGA    �����`��
    {"�ї�",    "���A"},    // [5-1- 8]LORD_MORI        �ї����A
    {"���@�䕔","���e"},    // [5-1- 9]LORD_CHOSOKABE   ���@�䕔���e
    {"����",    "�`�v"}     // [5-1-10]LORD_SIMAZU      ���Ë`�v
};

// [5-2]��̔z���錾����
CASTLE castles[CASTLE_MAX] =
{
    // [5-2-1]CASTLE_YONEZAWA   �đ��
    {
        "�đ��",   // const char* name         ���O
        LORD_DATE,  // int owner                ���
        TROOP_BASE, // int troopCount           ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_KASUGAYAMA,  // �t���R��
            CASTLE_ODAWARA      // ���c����
        }
    },

    // [5-2-2]CASTLE_KASUGAYAMA �t���R��
    {
        "�t���R��",     // const char* name     ���O
        LORD_UESUGI,    // int owner            ���
        TROOP_BASE,     // int troopCount       ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_YONEZAWA,        // �đ��
            CASTLE_TSUTSUJIGASAKI,  // �U�P�����
            CASTLE_GIFU             // �򕌏�
        }
    },

    // [5-2-3]CASTLE_TSUTSUJIGASAKI �U�P�����
    {
        "�U�P�����",   // const char* name     ���O
        LORD_TAKEDA,    // int owner            ���
        TROOP_BASE,     // int troopCount       ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_KASUGAYAMA,  // �t���R��
            CASTLE_ODAWARA,     // ���c����
            CASTLE_OKAZAKI      // �����
        }
    },

    // [5-2-4]CASTLE_ODAWARA    ���c����
    {
        "���c����", // const char* name         ���O
        LORD_HOJO,  // int owner                ���
        TROOP_BASE, // int troopCount           ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_YONEZAWA,        // �đ��
            CASTLE_TSUTSUJIGASAKI,  // �U�P�����
            CASTLE_OKAZAKI          // �����
        }
    },

    // [5-2-5]CASTLE_OKAZAKI    �����
    {
        "�����",       // const char* name     ���O
        LORD_TOKUGAWA,  // int owner            ���
        TROOP_BASE,     // int troopCount       ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_TSUTSUJIGASAKI,  // �U�P�����
            CASTLE_ODAWARA,         // ���c����
            CASTLE_GIFU             // �򕌏�
        }
    },

    // [5-2-6]CASTLE_GIFU   �򕌏�
    {
        "�򕌏�",   // const char* name         ���O
        LORD_ODA,   // int owner                ���
        TROOP_BASE, // int troopCount           ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_KASUGAYAMA,  // �t���R��
            CASTLE_OKAZAKI,     // �����
            CASTLE_NIJO         // �����
        }
    },

    // [5-2-7]CASTLE_NIJO   �����
    {
        "�����",       // const char* name     ���O
        LORD_ASHIKAGA,  // int owner            ���
        TROOP_BASE,     // int troopCount       ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_GIFU,            // �򕌏�
            CASTLE_YOSHIDAKORIYAMA, // �g�c�S�R��
            CASTLE_OKO              // ���L��
        }
    },

    // [5-2-8]CASTLE_YOSHIDAKORIYAMA    �g�c�S�R��
    {
        "�g�c�S�R��",   // const char* name     ���O
        LORD_MORI,      // int owner            ���
        TROOP_BASE,     // int troopCount       ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_NIJO,    // �����
            CASTLE_OKO,     // ���L��
            CASTLE_UCHI     // ����
        }
    },

    // [5-2-9]CASTLE_OKO    ���L��
    {
        "���L��",       // const char* name     ���O
        LORD_CHOSOKABE, // int owner            ���
        TROOP_BASE,     // int troopCount       ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_NIJO,            // �����
            CASTLE_YOSHIDAKORIYAMA, // �g�c�S�R��
            CASTLE_UCHI             // ����
        }
    },

    // [5-2-10]CASTLE_UCHI  ����
    {
        "����",         // const char* name     ���O
        LORD_SIMAZU,    // int owner            ���
        TROOP_BASE,     // int troopCount       ����

        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_YOSHIDAKORIYAMA, // �g�c�S�R��
            CASTLE_OKO              // ���L��
        }
    }
};

int year;  // [5-3]���݂̔N��錾����

int playerLord;// [5-4]�v���C���[�̑喼��錾����

char chronology[CHRONOLOGY_MAX];// [5-5]�N�\��錾����

// [6]�֐���錾����ꏊ

// [6-1]��̐��𐔂���֐���錾����
int GetCastleCount(int _lord)
{
    // [6-1-1]��̐���錾����
    int castleCount = 0;

    // [6-1-2]���ׂĂ̏�𔽕�����
    for (int i = 0; i < CASTLE_MAX; i++)
    {
        // [6-1-3]�Ώۂ̏�̏�傪�A�Ώۂ̑喼���ǂ����𔻒肷��
        if (castles[i].owner == _lord)
        {
            // [6-1-4]��̐������Z����
            castleCount++;
        }
    }

    // [6-1-5]��̐���Ԃ�
    return castleCount;
}

// [6-2]��{����`�悷��֐���錾����
void DrawScreen()
{
    system("cls");// [6-2-1]��ʂ��N���A����
/*
    // [6-2-1.5]�n�}�̃T���v����`�悷��
    printf("%s",
        "1570�˂�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�`\n"      // 01
        "�@�@�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@0�đ�5�@�`\n"      // 02
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`1�t��5�@�ɒB�@�`�`\n"      // 03
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�`�㐙�@�@�@�@�@�`�`\n"      // 04
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�@�@�@�@�@�@�@�@�`�`\n"      // 05
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@2�U�P5�@�@�@�`�`\n"      // 06
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�@���c�@�@�@�`�`�`\n"      // 07
        "�`�`�`�`�`�`�@�@�@�@�@�@�@5��5�@�@�@�@�@�@�@�@�`�`�`\n"      // 08
        "�`�`�`�`�@7�g�c5�@6���5�@�D�c�@4����5�@3���c5�@�`�`�`\n"      // 09
        "�`�`�`�@�@�ї��@�@�����@�@�@�@�@����@�@�k���`�`�`�`�`\n"      // 10
        "�`�`�@�`�`�`�`�`�`�`�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 11
        "�`�@�@�@�`�@8���L5�`�`�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 12
        "�`�@�@�@�`�`���@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 13
        "�`9����5�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 14
        "�`���Á`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 15
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n");    // 16
*/
    // [6-2-2]�n�}��1�s�ڂ�`�悷��
    printf("%d�˂�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�`\n",
        year);  // �N

    // [6-2-3]�n�}��2�s�ڂ�`�悷��
    printf("�@�@�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@%d%.4s%d�@�`\n",

        // �đ��̏�ԍ�
        CASTLE_YONEZAWA,

        // �đ��̖��O
        castles[CASTLE_YONEZAWA].name,

        // �đ��̕���
        castles[CASTLE_YONEZAWA].troopCount);

    // [6-2-4]�n�}��3�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`%d%.4s%d�@%.4s�@�`�`\n",

        // �t���R��̏�ԍ�
        CASTLE_KASUGAYAMA,

        // �t���R��̖��O
        castles[CASTLE_KASUGAYAMA].name,

        // �t���R��̕���
        castles[CASTLE_KASUGAYAMA].troopCount,

        // �đ��̖��̐�
        lords[castles[CASTLE_YONEZAWA].owner].familyName);

    // [6-2-5]�n�}��4�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�`%.4s�@�@�@�@�@�`�`\n",

        // �t���R��̖��̐�
        lords[castles[CASTLE_KASUGAYAMA].owner].familyName);

    // [6-2-6]�n�}��5�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�@�@�@�@�@�@�@�@�`�`\n");

    // [6-2-7]�n�}��6�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@%d%.4s%d�@�@�@�`�`\n",

        // �U�P����ق̏�ԍ�
        CASTLE_TSUTSUJIGASAKI,

        // �U�P����ق̖��O
        castles[CASTLE_TSUTSUJIGASAKI].name,

        // �U�P����ق̕���
        castles[CASTLE_TSUTSUJIGASAKI].troopCount);

    // [6-2-8]�n�}��7�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�@%.4s�@�@�@�`�`�`\n",

        // �U�P����ق̏��̐�**
        lords[castles[CASTLE_TSUTSUJIGASAKI].owner].familyName);

    // [6-2-9]�n�}��8�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�@�@�@�@�@�@�@%d%.4s%d�@�@�@�@�@�@�@�@�`�`�`\n",

        // �򕌏�̏�ԍ�
        CASTLE_GIFU,

        // �򕌏�̖��O
        castles[CASTLE_GIFU].name,

        // �򕌏�̕���
        castles[CASTLE_GIFU].troopCount);

    // [6-2-10]�n�}��9�s�ڂ�`�悷��
    printf("�`�`�`�`�@%d%.4s%d�@%d%.4s%d�@%.4s�@�@�@�@�@%d%.4s%d�@�`�`�`\n",

        // �g�c�S�R��̏�ԍ�
        CASTLE_YOSHIDAKORIYAMA,

        // �g�c�S�R��̖��O
        castles[CASTLE_YOSHIDAKORIYAMA].name,

        // �g�c�S�R��̕���
        castles[CASTLE_YOSHIDAKORIYAMA].troopCount,

        // �����̏�ԍ�
        CASTLE_NIJO,

        // �����̖��O
        castles[CASTLE_NIJO].name,

        // �����̕���
        castles[CASTLE_NIJO].troopCount,

        // �򕌏�̏��̐�
        lords[castles[CASTLE_GIFU].owner].familyName,

        // ���c����̏�ԍ�
        CASTLE_ODAWARA,

        // ���c����̖��O
        castles[CASTLE_ODAWARA].name,

        // ���c����̕���
        castles[CASTLE_ODAWARA].troopCount);

    // [6-2-11]�n�}��10�s�ڂ�`�悷��
    printf("�`�`�`�@�@%.4s�@�@%.4s�@�`�@�@�@%d%.4s%d�@%.4s�`�`�`�`�`\n",

        // �g�c�S�R��̏��̐�
        lords[castles[CASTLE_YOSHIDAKORIYAMA].owner].familyName,

        // �����̏��̐�
        lords[castles[CASTLE_NIJO].owner].familyName,

        // �����̏�ԍ�
        CASTLE_OKAZAKI,

        // �����̖��O
        castles[CASTLE_OKAZAKI].name,

        // �����̕���
        castles[CASTLE_OKAZAKI].troopCount,

        // ���c����̏��̐�
        lords[castles[CASTLE_ODAWARA].owner].familyName);

    // [6-2-12]�n�}��11�s�ڂ�`�悷��
    printf("�`�`�@�`�`�`�`�`�`�`�@�@�@�@�`�`%.4s�`�@�`�@�`�`�`�`�`\n",

        // �����̏��̐�
        lords[castles[CASTLE_OKAZAKI].owner].familyName);

    // [6-2-13]�n�}��12�s�ڂ�`�悷��
    printf("�`�@�@�@�`�@%d%.4s%d�@�`�@�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`\n",

        // ���L��̏�ԍ�
        CASTLE_OKO,

        // ���L��̖��O
        castles[CASTLE_OKO].name,

        // ���L��̕���
        castles[CASTLE_OKO].troopCount);

    // [6-2-14]�n�}��13�s�ڂ�`�悷��**
    printf("�`�@�@�@�`�@%.4s�@�`�`�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n",

        // ���L��̏��̐�**
        lords[castles[CASTLE_OKO].owner].familyName);

    // [6-2-15]�n�}��14�s�ڂ�`�悷��
    printf("�`%d%.4s%d�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n",

        // ����̏�ԍ�
        CASTLE_UCHI,

        // ����̖��O
        castles[CASTLE_UCHI].name,

        // ����̕���
        castles[CASTLE_UCHI].troopCount);

    // [6-2-16]�n�}��15�s�ڂ�`�悷��
    printf("�`%.4s�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n",

        // ����̏��̐�
        lords[castles[CASTLE_UCHI].owner].familyName);

    // [6-2-17]�n�}��16�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n");

    // [6-2-18]1�s�󂯂Ă���
    printf("\n");
}

// [6-3]�Q�[��������������֐���錾����
void Init()
{
    year = START_YEAR;// [6-3-1]�N�����Z�b�g����

    // [6-3-2]���ׂĂ̏�𔽕�����
    for (int i = 0; i < CASTLE_MAX; i++)
    {
        // [6-3-3]��������������
        castles[i].owner = i;

        // [6-3-4]����������������
        castles[i].troopCount = TROOP_BASE;
    }

    // [6-3-5]�N�\���N���A����
    sprintf_s(chronology, "");

    DrawScreen();// [6-3-6]��{����`�悷���ʂ��Ăяo��

    // [6-3-7]�喼�̑I���𑣂����b�Z�[�W��\������
    printf("���₩�����܁A���炪����́@���̂�����\n"
        "�ǂ��Ɂ@����܂��邩�H�I�i0�`%d�j\n",
        CASTLE_MAX - 1);    // ��ԍ��̍ő�l

    printf("\n");// [6-3-8]1�s�󂯂�

    // [6-3-9]�I�����ꂽ���ێ�����ϐ���錾����
    int selectedCastle;

    // [6-3-10]�͈͓��̏�ԍ������͂����܂Ŕ�������
    do {
        selectedCastle = _getch() - '0';// [6-3-11]��ԍ�����͂���
    } while ((selectedCastle < 0) || (selectedCastle >= CASTLE_MAX));

    // [6-3-12]�I��������̏����v���C���[�̑喼�Ƃ���
    playerLord = castles[selectedCastle].owner;

    // [6-3-13]���肵���喼��ʒm���郁�b�Z�[�W��\������
    printf("%s���܁A%s����@�Ă񂩂Ƃ�����\n�߂����܂��傤���I\n",
        lords[playerLord].firstName,    // �I�����ꂽ�喼�̖�
        castles[playerLord].name);      // �I�����ꂽ��̖��O

    _getch();// [6-3-14]�L�[�{�[�h���͂�҂�
}

// [6-4]�U���̊֐���錾����
void Siege(
    int _offensiveLord,         // �U�ߍ��񂾑喼
    int _offensiveTroopCount,   // �U�ߍ��񂾕���
    int _castle)                // �U�ߍ��܂ꂽ��
{
    system("cls");// [6-4-1]��ʂ��N���A����

    // [6-4-2]�U���̖��O��\������
    printf("�`%s�́@���������`\n", castles[_castle].name);

    printf("\n");// [6-4-3]1�s�󂯂�

    // [6-4-4]�U�ߍ��܂ꂽ�喼��錾����
    int defensiveLord = castles[_castle].owner;

    // [6-4-5]�������[�v����
    while (1)
    {
        // [6-4-6]����̌o�߂�\������
        printf("%s����i%4d�ɂ�j�@�w�@%s����i%4d�ɂ�j\n",

            // �U�ߍ��񂾑喼�̐�
            lords[_offensiveLord].familyName,

            // �U�ߍ��񂾕���
            _offensiveTroopCount * TROOP_UNIT,

            // �U�ߍ��܂ꂽ�喼�̐�
            lords[defensiveLord].familyName,

            // �U�ߍ��܂ꂽ��̕���
            castles[_castle].troopCount * TROOP_UNIT);

        _getch();// [6-4-7]�L�[�{�[�h���͂�҂�

        // [6-4-8]�U�炢���ꂩ�̕�����0�ȉ����ǂ������肷��
        if ((_offensiveTroopCount <= 0) || (castles[_castle].troopCount <= 0))
        {
            break;// [6-4-9]���[�v�𔲂���
        }

        // [6-4-10]0�`2�̗������A0���ǂ����𔻒肷��
        if (rand() % 3 == 0)
        {
            castles[_castle].troopCount--;// [6-4-11]������̕������炷
        }

        // [6-4-12]0�`2�̗������A1��2�Ȃ�
        else
        {
            _offensiveTroopCount--;// [6-4-13]�U�����̕������炷
        }
    }

    printf("\n");// [6-4-14]1�s�󂯂�

    // [6-4-15]������̕����S�ł������ǂ����𔻒肷��
    if (castles[_castle].troopCount <= 0)
    {
        // [6-4-16]���邵�����b�Z�[�W��\������
        printf("%s�@�炭���傤�I�I\n", castles[_castle].name);

        printf("\n");// [6-4-17]1�s�󂯂�

        // [6-4-18]�U�����̑喼�̏�ɂ���
        castles[_castle].owner = _offensiveLord;

        // [6-4-19]�U�����̕�����邳����
        castles[_castle].troopCount = _offensiveTroopCount;

        // [6-4-20]��傪�U�ߍ��񂾑喼�ɕς�������b�Z�[�W��\������
        printf("%s�́@%s���́@���̂ƂȂ�܂�\n",
            castles[_castle].name,
            lords[_offensiveLord].familyName);

        printf("\n");// [6-4-21]1�s�󂯂�

        // [6-4-22]������̑喼���A������ׂĎ��������ǂ����𔻒肷��
        if (GetCastleCount(defensiveLord) <= 0)
        {
            char str[128];  // [6-4-23]�ǉ����镶�����錾����

            // [6-4-24]�ǉ����镶������쐬����
            sprintf_s(str, "%d�˂�@%s%s���@%s�Ł@%s%s���@�ق�ڂ�\n",
                year,                               // �łڂ����N
                lords[_offensiveLord].familyName,   // �łڂ����喼�̐�
                lords[_offensiveLord].firstName,    // �łڂ����喼�̖�
                castles[_castle].name,              // ���̖��O
                lords[defensiveLord].familyName,    // �łڂ��ꂽ�喼�̐�
                lords[defensiveLord].firstName);    // �łڂ��ꂽ�喼�̖�

            // [6-4-25]�N�\�ɕ������ǉ�����
            strcat_s(chronology, str);
        }
    }

    // [6-4-26]������̕����S�ł��Ă��Ȃ����
    else
    {
        // [6-4-27]�U�������S�ł������b�Z�[�W��\������
        printf("%s����@�����߂I�I\n"
            "\n"
            "%s���񂪁@%s���@�܂��肫��܂����I\n",
            lords[_offensiveLord].familyName,
            lords[defensiveLord].familyName,
            castles[_castle].name);
    }
}

// [6-5]�v���O�����̎��s�J�n�_��錾����
int main()
{
    srand((unsigned int)time(NULL));// [6-5-1]�������V���b�t������

start:  // [6-5-2]�Q�[���̊J�n���x��
    ;   // [6-5-3]��

    Init();// [6-5-4]�Q�[�������Z�b�g����֐����Ăяo��

    // [6-5-5]���C�����[�v
    while (1)
    {
        int turnOrder[CASTLE_MAX];  // [6-5-6]�^�[���̏��̃e�[�u����錾����

        // [6-5-7]�^�[���̏�������������
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            turnOrder[i] = i;// [6-5-8]�^�[���̏�������������
        }

        // [6-5-9]���ׂĂ̏�𔽕�����
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            // [6-5-10]�^�[���������_���ɓ���ւ���
            std::swap(turnOrder[i], turnOrder[rand() % CASTLE_MAX]);
        }

        // [6-5-11]���ׂẴ^�[���𔽕�����
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            DrawScreen();// [6-5-12]��{����ʂ��ĕ`�悷��

            // [6-5-13]���ׂẴ^�[���𔽕�����
            for (int j = 0; j < CASTLE_MAX; j++)
            {
                // [6-5-14]���݂̃^�[���̏�ɃJ�[�\����`�悷��
                printf("%s", (j == i) ? "��" : "�@");

                // [6-5-15]�e�^�[���̏�̖��O��`�悷��
                printf("%.4s", castles[turnOrder[j]].name);
            }

            // [6-5-16]���s����1�s�󂯂�
            printf("\n\n");

            // [6-5-17]���݂̃^�[���̏�̔ԍ���錾����
            int currentCastle = turnOrder[i];

            // [6-5-18]���b�Z�[�W��\������
            printf("%s���́@%s�́@�Ђ傤���傤���イ�c\n",
                lords[castles[currentCastle].owner].familyName, // ���̐�
                castles[currentCastle].name);                   // ��̖��O

            printf("\n");// [6-5-19]1�s�󂯂�

            // [6-5-20]���݂̏�̏�傪�v���C���[���ǂ����𔻒肷��
            if (castles[currentCastle].owner == playerLord)
            {
                // [6-5-21]�i�R��̏�̎w��𑣂����b�Z�[�W��\������
                printf("%s���܁A�ǂ��Ɂ@���񂮂�@���܂����H\n",
                    lords[castles[currentCastle].owner].firstName);

                printf("\n");// [6-5-22]1�s�󂯂�

                // [6-5-23]���ׂĂ̐ڑ����ꂽ��𔽕�����
                for (int j = 0; j < (int)castles[currentCastle].connectedCastles.size(); j++)
                {
                    // [6-5-24]�ڑ����ꂽ��̔ԍ��Ɩ��O��\������
                    printf("%d %s\n",
                        castles[currentCastle].connectedCastles[j],
                        castles[castles[currentCastle].connectedCastles[j]].name);
                }

                printf("\n");// [6-5-25]1�s�󂯂�

                // [6-5-26]�i�R��̏����͂��Đ錾����
                int targetCastle = _getch() - '0';

                // [6-5-27]���݂̏�ƑΏۂ̏邪�ڑ����Ă��邩�ǂ�����ێ�����t���O��錾����
                bool isConnected = false;

                // [6-5-28]���݂̏�Ɛڑ����Ă��邷�ׂĂ̏�𔽕�����
                for (int castle : castles[currentCastle].connectedCastles)
                {
                    // [6-5-29]�Ώۂ̏�Ƃ̐ڑ����m�F�ł�����
                    if (castle == targetCastle)
                    {
                        isConnected = true;// [6-5-30]�ڑ��̗L���̃t���O�𗧂Ă�

                        break;// [6-5-31]�����𔲂���
                    }
                }

                // [6-5-32]�ڑ����Ă���邪�I�΂�Ȃ�������
                if (!isConnected)
                {
                    // [6-5-33]�i�R������߂郁�b�Z�[�W��\������
                    printf("���񂮂���@�Ƃ��߂܂���\n");

                    _getch();// [6-5-34]�L�[�{�[�h���͂�҂�

                    continue;// [6-5-35]���̍��̕]��ɃX�L�b�v����
                }

                // [6-5-36]���݂̏�̕������ő�i�R���Ƃ��Đ錾����
                int troopMax = castles[currentCastle].troopCount;

                // [6-5-37]�i�R�悪�v���C���[�̏邩�ǂ����𔻒肷��
                if (castles[targetCastle].owner == playerLord)
                {
                    // [6-5-38]�i�R��̏�̋󂫕�����錾����
                    int targetCapacity = TROOP_MAX - castles[targetCastle].troopCount;

                    // [6-5-39]���݂̏�̕������A�i�R��̋󂫕����̏��Ȃ��ق����ő�i�R�����Ƃ���
                    troopMax = std::min(troopMax, targetCapacity);
                }

                // [6-5-40]���͂��ꂽ���ʒm���āA�ړ����镺���̓��͂𑣂����b�Z�[�W��\������
                printf("%s�Ɂ@�Ȃ񂺂�ɂ�@���񂮂�@���܂����H�i0�`%d�j\n",
                    castles[targetCastle].name,	// �i�R��̏�̖��O
                    troopMax);					// �i�R����

                // [6-5-41]�i�R������錾����
                int troopCount;

                // [6-5-42]�͈͓��̕��������͂����܂Ŕ�������
                do {
                    troopCount = _getch() - '0';// [6-5-43]�i�R��������͂���
                } while ((troopCount < 0) || (troopCount > troopMax));

                // [6-5-44]���݂̏�̕������A�ړ����镪�������炷
                castles[currentCastle].troopCount -= troopCount;

                // [6-5-45]�ړ��悪�v���C���[�̏�Ȃ�
                if (castles[targetCastle].owner == playerLord)
                {
                    // [6-5-46]�i�R��̏�̕����ɁA�ړ����������Z����
                    castles[targetCastle].troopCount += troopCount;
                }

                // [6-5-47]���s����
                printf("\n");

                // [6-5-48]���͂��ꂽ�i�R������ʒm����
                printf("%s�Ɂ@%d�ɂ�%s",
                    castles[targetCastle].name, // �i�R��̏�̖��O
                    troopCount * TROOP_UNIT,	// �i�R����

                    // �i�R��̏�̏�傪�v���C���[���ǂ����𔻒肷��
                    (castles[targetCastle].owner == playerLord)
                    ? "�@���ǂ��@���܂���"          // �v���C���[�̏�Ȃ�
                    : "�Ł@������񂶂�`�I�I");  // �G�̏�Ȃ�

                // [6-5-49]�i�R�悪�G�̏邩�ǂ����𔻒肷��
                if (castles[targetCastle].owner != playerLord)
                {
                    _getch();// [6-5-50]�L�[�{�[�h���͂�҂�

                    // [6-5-51]�U���̊֐����Ăяo��
                    Siege(
                        playerLord,     // int _offensiveLord       �U�ߍ��񂾑喼
                        troopCount,     // int _offensiveTroopCount �U�ߍ��񂾕���
                        targetCastle);  // int _castle              �U�ߍ��܂ꂽ��
                }
            }

            // [6-5-52]���݂̏�̏�傪�v���C���[�łȂ����
            else
            {
                // [6-5-53]�ڑ����ꂽ�G�̏�̃��X�g��錾����
                std::vector<int> connectedEnemyCastles;

                // [6-5-54]���ׂĂ̐ڑ����ꂽ��𔽕�����
                for (int j = 0;
                    j < (int)castles[currentCastle].connectedCastles.size();
                    j++)
                {
                    // [6-5-55]�G�̏邩�ǂ����𔻒肷��
                    if (castles[castles[currentCastle].connectedCastles[j]].owner
                        != castles[currentCastle].owner)
                    {
                        // [6-5-56]�ڑ����ꂽ�G�̏�̃��X�g�ɉ�����
                        connectedEnemyCastles.push_back(
                            castles[currentCastle].connectedCastles[j]);
                    }
                }

                // [6-5-57]�ڑ����ꂽ�G�̏邪���邩�ǂ����𔻒肷��
                if (connectedEnemyCastles.size() > 0)
                {
                    // [6-5-58]���̏��Ȃ����ɕ��ёւ���
                    sort(connectedEnemyCastles.begin(), connectedEnemyCastles.end(),
                        // 2�̏���r���郉���_
                        [](int _castle0, int _castle1)
                        {
                            // ���X�g�̌��̏�̂ق����A�����������ǂ����𔻒肵�ĕԂ�
                            return castles[_castle0].troopCount< castles[_castle1].troopCount;
                        }
                    );

                    // [6-5-59]�ł����̏��Ȃ���݂̂ɂȂ�܂Ŕ�������
                    while (
                        // �אڂ���G�̏邪2��ȏ�ł���
                        (connectedEnemyCastles.size() > 1)

                        // �����̒��ōł������̏��Ȃ�����������̑����邪�����
                        && (castles[connectedEnemyCastles.front()].troopCount
                            < castles[connectedEnemyCastles.back()].troopCount))
                    {
                        // [6-5-60]���X�g����Ō�����폜����
                        connectedEnemyCastles.pop_back();
                    }

                    // [6-5-61]�U�ߍ��ޏ��錾����
                    int targetCastle =
                        connectedEnemyCastles[rand() % connectedEnemyCastles.size()];

                    // [6-5-62]�U�ߍ��ނ��ǂ����𔻒肷��
                    if (
                        // ��������l�ȏ�ł��邩
                        (castles[currentCastle].troopCount >= TROOP_BASE)

                        // ������̕���������������������đ����2�{�ȏ�ł����
                        || (castles[currentCastle].troopCount - 1
                            >= castles[targetCastle].troopCount * 2))
                    {
                        // [6-5-63]�U�ߍ��ޕ�����錾����
                        int troopCount = std::max(castles[currentCastle].troopCount - 1, 0);

                        // [6-5-64]���݂̏�̕�������U�ߍ��ޕ��������Z����
                        castles[currentCastle].troopCount -= troopCount;

                        // [6-5-65]�U�ߍ��ރ��b�Z�[�W��\������
                        printf("%s�́@%s%s���@%s�Ɂ@���߂��݂܂����I\n",
                            castles[currentCastle].name,
                            lords[castles[currentCastle].owner].familyName,
                            lords[castles[currentCastle].owner].firstName,
                            castles[targetCastle].name);

                        _getch();// [6-5-66]�L�[�{�[�h���͂�҂�

                        // [6-5-67]�U���̊֐����Ăяo��
                        Siege(

                            // int _offensiveLord       �U�ߍ��񂾑喼
                            castles[currentCastle].owner,

                            // int _offensiveTroopCount �U�ߍ��񂾕���
                            troopCount,

                            // int _castle              �U�ߍ��܂ꂽ��
                            targetCastle);
                    }
                }

                // [6-5-68]�ڑ����ꂽ�G�̏邪�Ȃ����
                else
                {
                    // [6-5-69]�ڑ����ꂽ�O���̏�̃��X�g��錾����
                    std::vector<int> frontCastles;

                    // [6-5-70]���ׂĂ̐ڑ����ꂽ��𔽕�����
                    for (int neighbor : castles[currentCastle].connectedCastles)
                    {
                        // [6-5-71]�אڂ����ɐڑ����ꂽ���ׂĂ̏�𔽕�����
                        for (int neighborNeighbor : castles[neighbor].connectedCastles)
                        {
                            // [6-5-72]�Ώۂ̏邪�G�̏�ɗאڂ��Ă��邩�ǂ����𔻒肷��
                            if (castles[neighborNeighbor].owner != castles[neighbor].owner)
                            {
                                frontCastles.push_back(neighbor);// [6-5-73]�O���̏�̃��X�g�ɒǉ�����

                                break;// [6-5-74]�����𔲂���
                            }
                        }
                    }

                    // [6-5-75]���𑗂��̃��X�g��錾����
                    std::vector<int> destCastles =

                        // �O���̏邪�Ȃ����ǂ����𔻒肷��
                        frontCastles.empty()

                            // �Ȃ���ΐڑ����ꂽ��̃��X�g��ݒ肷��
                            ? castles[currentCastle].connectedCastles

                            // ����ΑO���̏�̃��X�g��ݒ肷��
                            : frontCastles;

                    // [6-5-76]���̏��Ȃ����ɕ��ёւ���
                    sort(destCastles.begin(), destCastles.end(),
                        [](int _castle0, int _castle1)
                        {
                            return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );

                    // [6-5-77]�ł����̏��Ȃ���݂̂ɂȂ�܂Ŕ�������
                    while (
                        // ���𑗂��̏�̌�₪��������
                        (destCastles.size() > 1)

                        // �����̒��ōł������̏��Ȃ�����������̑����邪�����
                        && (castles[destCastles.front()].troopCount
                            < castles[destCastles.back()].troopCount))
                    {
                        // [6-5-78]���X�g����Ō�����폜����
                        destCastles.pop_back();
                    }

                    // [6-5-79]���𑗂���錾����
                    int targetCastle = destCastles[rand() % destCastles.size()];

                    // [6-5-80]���镺����錾����
                    int sendTroopCount = TROOP_MAX - castles[targetCastle].troopCount;

                    // [6-5-81]���𑗂��̏邪�O�����ǂ����𔻒肷��
                    if (!frontCastles.empty())
                    {
                        // [6-5-82]�����̋󂫕����Ƒ��茳�̕����̂����A���Ȃ�������ݒ肷��
                        sendTroopCount = std::min(

                            // �����̋󂫕���
                            sendTroopCount,

                            // ���茳�̕���
                            castles[currentCastle].troopCount);
                    }

                    // [6-5-83]���𑗂��̏邪�O���łȂ������̏�Ȃ�
                    else
                    {
                        // [6-5-84]�����̋󂫕����Ƒ��茳�̗]�蕺���̂����A���Ȃ�������ݒ肷��
                        sendTroopCount = std::min(

                            // �����̋󂫕���
                            sendTroopCount,

                            // ���茳�̕���
                            castles[currentCastle].troopCount - (TROOP_BASE - 1));
                    }

                    // [6-5-85]���镺�����邩�ǂ����𔻒肷��
                    if (sendTroopCount > 0)
                    {
                        // [6-5-86]���茳�̕��������炷
                        castles[currentCastle].troopCount -= sendTroopCount;

                        // [6-5-87]�����̕����𑝂₷
                        castles[targetCastle].troopCount += sendTroopCount;

                        // [6-5-88]���m���ړ��������b�Z�[�W��\������
                        printf("%s����@%s�Ɂ@%d�ɂ�@���ǂ����܂���\n",
                            castles[currentCastle].name,
                            castles[targetCastle].name,
                            sendTroopCount* TROOP_UNIT);
                    }
                }
            }

            _getch();// [6-5-89]�L�[�{�[�h���͂�҂�

            // [6-5-90]�v���C���[�̏邪�Ȃ����ǂ����𔻒肷��
            if (GetCastleCount(playerLord) <= 0)
            {
                DrawScreen();// [6-5-91]��ʂ�`�悷��

                printf("%s", chronology);// [6-5-92]�N�\��\������

                printf("\n");// [6-5-93]1�s�󂯂�

                // [6-5-94]�Q�[���I�[�o�[�̃��b�Z�[�W��\������
                printf("�f�`�l�d�@�n�u�d�q\n");

                _getch();// [6-5-95]�L�[�{�[�h���͂�҂�

                goto start;// [6-5-96]�Q�[���̊J�n���x���ɃW�����v����
            }

            // [6-5-97]�v���C���[���ׂĂ̏�����L���Ă��邩�ǂ����𔻒肷��
            else if (GetCastleCount(playerLord) >= CASTLE_MAX)
            {
                DrawScreen();// [6-5-98]��ʂ�`�悷��

                printf("%s", chronology);// [6-5-99]�N�\��\������

                // [6-5-100]�G���f�B���O�̃��b�Z�[�W��\������
                printf("%d�˂�@%s%s���@�������������傤����Ɂ@�ɂ񂺂���\n"
                    "%d�˂�@%s%s���@%s�΂��ӂ��@�Ђ炭\n"
                    "\n"
                    "�s�g�d�@�d�m�c",
                    year + 3,                       // ���Α叫�R�ɂȂ����N
                    lords[playerLord].familyName,   // �v���C���[�̑喼�̐�
                    lords[playerLord].firstName,    // �v���C���[�̑喼�̖�
                    year + 3,                       // ���{���J�����N
                    lords[playerLord].familyName,   // �v���C���[�̑喼�̐�
                    lords[playerLord].firstName,    // �v���C���[�̑喼�̖�
                    lords[playerLord].familyName);  // ���{�̖��O

                _getch();// [6-5-101]�L�[�{�[�h���͂�҂�

                goto start;// [6-5-102]�Q�[���J�n���x���ɃW�����v����
            }
        }

        year++;// [6-5-103]�N��i�߂�

        // [6-5-104]���ׂĂ̏�𔽕�����
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            // [6-5-105]�Ώۂ̏�̕�������{�����������ǂ����𔻒肷��
            if (castles[i].troopCount < TROOP_BASE)
            {
                castles[i].troopCount++;// [6-5-106]�����𑝂₷
            }

            // [6-5-107]�Ώۂ̏�̕�������{������葽�����ǂ����𔻒肷��
            else if (castles[i].troopCount > TROOP_BASE)
            {
                castles[i].troopCount--;// [6-5-108]���������炷
            }
        }

        // [6-5-109]�u�{�\���̕ρv�C�x���g���N��������𖞂����Ă��邩�ǂ����𔻒肷��
        if (
            // 1582�N�ł���
            (year == 1582)
            
            // ���D�c�Ƃ����������L���Ă���
            && (castles[CASTLE_NIJO].owner == LORD_ODA))
        {
            // [6-5-110]�D�c�Ƒ喼�̐����u�H�āv�ɏ���������
            strcpy_s(lords[LORD_ODA].familyName, "�H��");

            // [6-5-111]�D�c�Ƒ喼�̖����u�G�g�v�ɏ���������
            strcpy_s(lords[LORD_ODA].firstName, "�G�g");

            DrawScreen();// [6-5-112]��ʂ��ĕ`�悷��

            // [6-5-113]�u�{�\���̕ρv�C�x���g�̃��b�Z�[�W��\������
            printf(
                "���q���G�u�Ă��́@�{�\���Ɂ@����I\n"
                "\n"
                "���q���G���@�{�\���́@�D�c�M�����@���イ���������I\n"
                "\n"
                "�D�c�M���u���ЂɁ@����΂��c\n"
                "\n"
                "�D�c�M���́@�{�\���Ɂ@�Ђ��͂Ȃ��@�����������I\n"
                "\n"
                "�����A�H�ďG�g���@�R��̂��������Ł@���q���G���@�������A\n"
                "�D�c���́@���������́@�������@���񂾂����I\n");

            _getch();// [6-5-114]�L�[�{�[�h���͂�҂�
        }
    }
}