#include <stdio.h>
#define SIZE 8
#define BLANK 0  //�ť�
#define BLACK 1
#define WHITE 2
#define BOUND (x+((a+1) * dx) > -1) && (x+((a+1) * dx) < SIZE) && (y+((a+1) * dy) > -1) && (y+((a+1) * dy) < SIZE)  //�P�_�O�_�W�X���

// ��b�O y, �a�b�O x
// �q���մ�, �H���´�

int chess[SIZE][SIZE] ={{0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,1,2,0,0,0},
                        {0,0,0,2,1,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}};

int next[2][SIZE][SIZE] = {0};
int position[2] = {0};  //��Ʀ^�ǭ�

//�Nnext�}�C�̪��ȳ]��0
void clear(void){
    for(int a = 1; a < 3; a++)
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < SIZE; y++)
                next[a][x][y] = 0;
    return;
}

//�M��´ѻP�մѩҦ��i�H�U����m�Υi½��Ѥl���ƥ��x�s�bnext�}�C��
void findChessToFlip(void){
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++){

            int flip = 0;
            int antiColor = 0;
            int color = chess[x][y];
            if(color == BLACK) antiColor = WHITE;
            if(color == WHITE) antiColor = BLACK;

            if(chess[x][y] != BLANK){
                for(int dy = -1; dy < 2; dy++){
                    for(int dx = -1; dx < 2; dx++){
                        if(dx != 0 || dy != 0){
                            flip = 0;
                            for(int a = 1; a < (SIZE-1); a++){
                                if(BOUND){
                                    if(chess[x+(a * dx)][y+(a * dy)] == antiColor){
                                        flip++;
                                        if(chess[x+((a+1) * dx)][y+((a+1) * dy)] == 0){
                                            next[color][x+((a+1) * dx)][y+((a+1) * dy)] += flip;
                                            break;
                                        }
                                    }
                                    else break;
                                }
                                else break;
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}

//��J�C�� ��X���C��Ҧ��i�H�U����m�Υi½��Ѥl���ƥ�
void checkNewStep(int color){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            if(next[color][i][j] > 0)
                printf("(%c, %d) �i½�� %d �l\n", j+'a', i+1, next[color][i][j]);
    }
    return;
}

//��X�ѽL
void outputArray(void){
    printf("  a b c d e f g h\n");
    for (int i = 0; i < SIZE; i++){
        printf("%d ", (i+1));
        for (int j = 0; j < SIZE; j++)
            printf("%d ", chess[i][j]);
        printf("\n");
    }
    return;
}

//��J�C�� ��X���C��i�H½�̦h�Ѥl����m �ÿ�X�Ӧ�m
void findMostValueChess(int color){
    int value = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(next[color][i][j] > value){
                value = next[color][i][j];
                position[1] = i;
                position[2] = j;
            }
        }
    }
    if(color == 1)
        printf("�´ѤU (%c, %d)\n", position[2]+'a', position[1]+1);
    if(color == 2)
        printf("�մѤU (%c, %d)\n", position[2]+'a', position[1]+1);
    return;
}

//��J�C�� �P�_���C��O�_���Ѥl�i�U ���^��1 �L�^��0
int noChessToFlip(int color){
    int u = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(next[color][i][j] > 0){
                u++;
            }
        }
    }
    if(u == 0) return 0;
    if(u > 0) return 1;
}

//��J�U���Ѥl���C�� ½�Ѥl���ѽL
void flipChess(int x, int y, int color){
    int flipCheck = next[BLACK][x][y];
    int flip, antiColor;
    if(color == BLACK) antiColor = WHITE;
    if(color == WHITE) antiColor = BLACK;
    chess[x][y] = color;
    for(int dy = -1; dy < 2; dy++){
        for(int dx = -1; dx < 2; dx++){
            if(dx != 0 || dy != 0){
                flip = 0;
                for(int a = 1; a < (SIZE-1); a++){
                    if(BOUND){
                        if(chess[x+(a * dx)][y+(a * dy)] == antiColor){
                            flip++;
                            if(chess[x+((a+1) * dx)][y+((a+1) * dy)] == color){
                                flipCheck -= flip;
                                int b = a;
                                for(b; b > 0; b--){
                                    chess[x+(b * dx)][y+(b * dy)] = color;
                                }
                                break;
                            }
                        }
                        else break;
                    }
                    else break;
                }
            }
        }
    }
    // if(flipCheck == 0){
    //     printf("OK");
    // }
    return;
}

//��J�C�� ��J�U�Ѫ���m �L�k�U�ѫh���s��J ��½�Ѥl
void input(int color){
    char a;
    int b, x, y;
    while(1){
        printf("��J�z�n�U����m");
        scanf("%1c %1d", &a, &b);
        x = b - 1;
        y = a - 'a';
        if(next[color][x][y] > 0)
            break;
        else
            continue;
    }
    flipChess(x, y, color);
    return;
}

//�έp�ק��ѽL�U�C��Ѥl���ƥ� �ÿ�X���ɵ��G
void resultOfTheGame(void){
    int numOfWhite=0, numOfBlack=0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            if(chess[i][j] == BLACK)
                numOfBlack++;
            else if(chess[i][j] == WHITE)
                numOfWhite++;
    }

    if(numOfBlack > numOfWhite)
        printf("�¤�� %d:%d", numOfBlack, numOfWhite);
    else if(numOfBlack < numOfWhite)
        printf("�դ�� %d:%d", numOfWhite, numOfBlack);
    else if(numOfBlack == numOfWhite)
        printf("�M�� %d:%d", numOfBlack, numOfWhite);
    return;
}

int main(){
    char b, c;
    int a, x, y, time=0, num;
    int color, antiColor;
    
    printf("�ѧ��}�l\n�´ѥ��U�մѫ�U\n�п�ܴѤl�C��\n");
    while(1){
        printf("��ܶ´ѽп�JB;��ܥմѽп�JW\n");
        scanf("%c", &c);
        if(c == 'B'){
            color = BLACK;
            break;
        }
        else if(c == 'W'){
            color = WHITE;
            break;
        }
        else
            continue;
    }

    if(color == BLACK){
        antiColor = WHITE;
        num = 0;
    }
    if(color == WHITE){
        antiColor = BLACK;
        num = 1;
    }

    findChessToFlip();
    for(int time = 0; noChessToFlip(BLACK) + noChessToFlip(WHITE) > 0; time++){
        if(time % 2 == num && noChessToFlip(color) > 0){
            outputArray();
            printf("���a�i�U����m�G\n");
            checkNewStep(color);
            input(color);
            clear();
            findChessToFlip();
        }
        if(time % 2 == !num && noChessToFlip(antiColor) > 0){
            findMostValueChess(antiColor);
            flipChess(position[1], position[2], antiColor);
            clear();
            findChessToFlip();
        }

    }

    printf("�ѧ�����\n");
    resultOfTheGame();

    return 0;
}
