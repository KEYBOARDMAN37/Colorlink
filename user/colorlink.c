#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/unistd.h"

#define true 1
#define false 0
typedef int bool;

int board[10][10] = {};
int length;
int sum;
int score;
int mode; // Easy1?Normal2?Hard3?
int myrand(int n)
{
    static int lcg = 0;
    int x;
    lcg = 1664525 * lcg + 1013904223;
    x = lcg % n;
    return x < 0 ? x + n : x;
}
void init()
{
    int i, j, k, c, m;
    int direct_couple = length * length / 4;
    int rest_couple = length * length / 4;
    int flag;

    int color = 0;
    int row[100] = {};
    int col[100] = {};
    int point = 0;
    int reg, rand;
    score = 0;
    sum = length * length / 2;
    for (i = 0; i < length; i++)
        for (j = 0; j < length; j++)
            board[i][j] = 0;
    while (direct_couple)
    {
        flag = 0;
        i = myrand(length);
        j = myrand(length);
        reg = length + 1;
        while (board[i][j] != 0)
        {
            if (reg > 100000)
                reg = 0;
            rand = reg % length + 1;
            reg += 1;
            i = myrand(rand);
            j = myrand(rand);
        }
        k = myrand(4);

        if (k == 0 && i + 1 < length)
            if (board[i + 1][j] == 0)
            {
                c = (color % (length / 2 + 1) + 1);
                color += 1;
                board[i + 1][j] = c;
                board[i][j] = c;
                flag = 1;
            }
        if (k == 1 && i - 1 >= 0)
            if (board[i - 1][j] == 0)
            {

                c = (color % (length / 2 + 1) + 1);
                color += 1;
                board[i - 1][j] = c;
                board[i][j] = c;
                flag = 1;
            }
        if (k == 2 && j + 1 < length)
            if (board[i][j + 1] == 0)
            {
                c = (color % (length / 2 + 1) + 1);
                color += 1;
                board[i][j + 1] = c;
                board[i][j] = c;
                flag = 1;
            }
        if (k == 3 && j - 1 >= 0)
            if (board[i][j - 1] == 0)
            {
                c = (color % (length / 2 + 1) + 1);
                color += 1;
                board[i][j - 1] = c;
                board[i][j] = c;
                flag = 1;
            }
        if (flag == 1)
            direct_couple -= 1;
    }
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {
            if (board[i][j] == 0)
            {
                row[point] = i;
                col[point++] = j;
            }
        }
    }
    color = 0;
    while (rest_couple)
    {

        i = myrand(point);
        reg = point + 1;
        while (board[row[i]][col[i]] != 0)
        {
            if (reg > 100000)
                reg = 0;
            rand = reg % point + 1;
            reg += 1;
            i = myrand(rand);
        }
        if (board[row[i]][col[i]] == 0)
        {
            m = myrand(point);
            reg = point + 1;

            while (board[row[m]][col[m]] != 0 || m == i)
            {
                if (reg > 100000)
                    reg = 0;
                rand = reg % point + 1;
                reg += 1;
                m = myrand(rand);
            }
            c = (color % (length / 2 + 1) + 1); // 1~length/2+1
            color += 1;
            board[row[i]][col[i]] = c;
            board[row[m]][col[m]] = c;
            rest_couple = rest_couple - 1;
        }
    }
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}
bool legal(char* s)
{

    if (s[0] >= '0' && s[0] <= '0' + length - 1 && s[2] >= '0' && s[2] <= '0' + length - 1)
        return true;

    return false;
}

void show()
{
    int i = 0;
    int j = 0;
    char line[70] = {};
    int point = 0;
    int k = 0;
    printf("\nYour Score is:%d\n\n", score);

    for (i = 0; i < length; i++)
    {

        if (i == 0)
            line[point++] = ' ';
        line[point++] = ' ';
        line[point++] = ' ';
        line[point++] = '0' + i;
    }
    line[point++] = '\n';
    for (k = 0; k < point; k++)
    {
        printf("%c", line[k]);
        line[k] = '\0';
    } //          the 1.st row ( 0,1,2,3,)
    point = 0;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {

            if (j == 0)
            {
                line[point++] = '0' + i;
                line[point++] = ' ';
            } // 1.st col(0,1,2....)

            line[point++] = '0' + board[i][j]; // if exist

            line[point++] = ' ';
        }

        line[point++] = '\n'; //
        printf("\n");
        for (k = 0; k < point; k++)
        {
            if (k == 0)
            {
                printf("%c", line[k]);
            }
            else if (line[k] == '0')
            {
                printf("  ");
            }
            else if (line[k] == '1')
            {
                printf("\033[41;1m \033[0m");
                printf("\033[41;1m \033[0m");
            }
            else if (line[k] == '2')
            {
                printf("\033[42;1m \033[0m");
                printf("\033[42;1m \033[0m");
            }
            else if (line[k] == '3')
            {
                printf("\033[43;1m \033[0m");
                printf("\033[43;1m \033[0m");
            }
            else if (line[k] == '4')
            {
                printf("\033[44;1m \033[0m");
                printf("\033[44;1m \033[0m");
            }
            else if (line[k] == '5')
            {
                printf("\033[45;1m \033[0m");
                printf("\033[45;1m \033[0m");
            }
            else if (line[k] == '6')
            {
                printf("\033[46;1m \033[0m");
                printf("\033[46;1m \033[0m");
            }
            else
            {
                printf("%c", line[k]);
            }
            line[k] = '\0';
        } // end
        point = 0;
    }
    printf("\n\n\n");
}
bool OneCorner(int x1, int y1,
    int x2, int y2)
{
    int temp;
    int i;
    int flag1 = 0;
    int flag2 = 0;
    if (x1 == x2 || y1 == y2)
        return false;
    if (((x1 > x2) ^ (y1 > y2)) == 0)
    {
        if (x2 > x1)
        {
            temp = x2;
            x2 = x1;
            x1 = temp;
            temp = y2;
            y2 = y1;
            y1 = temp;
        }
        for (i = y1-1; i >= y2; i--)
            if (board[x1][i] != 0)
                flag1 = 1;
        for (i = x1; i > x2; i--)
            if (board[i][y2] != 0)
                flag1 = 1;
        for (i = x1-1; i >= x2; i--)
            if (board[i][y1] != 0)
                flag2 = 1;
        for (i = y1; i > y2; i--)
            if (board[x2][i] != 0)
                flag2 = 1;
        if (flag1 && flag2 == 1)
            return false;
        return true;
    }
    else
    {
        if (x1 < x2)
        {
            temp = x2;
            x2 = x1;
            x1 = temp;
            temp = y2;
            y2 = y1;
            y1 = temp;
        }
        for (i = y1+1; i <= y2; i++)
            if (board[x1][i] != 0)
                flag1 = 1;
        for (i = x1; i > x2; i--)
            if (board[y2][i] != 0)
                flag1 = 1;
        for (i = x1-1; i >= x2; i--)
            if (board[i][y1] != 0)
                flag2 = 1;
        for (i = y1; i < y2; i++)
            if (board[x2][i] != 0)
                flag2 = 1;
        if (flag1 && flag2== 1)
            return false;
        return true;
    }

    return false;
}
bool TwoCorner(int x1, int y1,
    int x2, int y2)
{
    int i, j;
    for (i = x1 - 1, j = y1; i >= 0; i--)
    {
        if (board[i][j] != 0)
            break;
        else if (OneCorner(i, j, x2, y2))
            return true;
    }
    for (i = x1, j = y1 - 1; j >= 0; i--)
    {
        if (board[i][j] != 0)
            break;
        else if (OneCorner(i, j, x2, y2))
            return true;
    }
    for (i = x1 + 1, j = y1; i < length; i++)
    {
        if (board[i][j] != 0)
            break;
        else if (OneCorner(i, j, x2, y2))
            return true;
    }
    for (i = x1, j = y1 - 1; j >= 0 && j < length; j++)
    {
        if (board[i][j] != 0)
            break;
        else if (OneCorner(i, j, x2, y2))
            return true;
    }

    return false;
}

bool Direct(int x1, int y1,
    int x2, int y2)
{
    int i = 0;
    bool ymatch = true;
    bool xmatch = true;
    if (!(x1 == x2 || y1 == y2))
        return false;
    if (x1 == x2)
    {
        if (y1 > y2)
        {
            for (i = y2 + 1; i < y1; i++)
            {
                if (board[x1][i] != 0)
                {
                    ymatch = false;
                }
            }
        }
        if (y2 > y1)
        {
            for (i = y1 + 1; i < y2; i++)
            {
                if (board[x1][i] != 0)
                {
                    ymatch = false;
                }
            }
        }
    }
    if (y1 == y2)
    {
        if (x1 > x2)
        {
            for (i = x2 + 1; i < x1; i++)
            {
                if (board[i][y1] != 0)
                    xmatch = false;
            }
        }
        if (x2 > x1)
        {
            for (i = x1 + 1; i < x2; i++)
            {
                if (board[i][y1] != 0)
                    xmatch = false;
            }
        }
    }
    return (xmatch && ymatch);
}
bool match(int x1, int y1,
    int x2, int y2)
{

    if (board[x1][y1] != board[x2][y2] || (x1 == x2 && y1 == y2))
    {
        printf("You choose wrong pattern!\n");
        return false;
    }
    if (Direct(x1, y1, x2, y2) || 
    OneCorner(x1, y1, x2, y2) || TwoCorner(x1, y1, x2, y2))
        return true;
    return false;
}
void autosolve()
{
    int i, j, m, n = 0;
    int color = 0;
    int flag, flag1 = 0;
    int reg_i = 0;
    flag = 0;
    while (!flag)
    {
        flag1 = 0;
        if (reg_i == length - 1)
            break;
        i = reg_i;
        for (j = 0; j < length; j++)
        {
            if (board[i][j] != 0)
            {
                flag1 = 1;
                color = board[i][j];
                break;
            }
        }

        if (flag1 == 0)
        {
            for (i = reg_i + 1; i < length; i++)
            {
                for (j = 0; j < length; j++)
                {
                    if (board[i][j] != 0)
                    {
                        flag1 = 1;
                        color = board[i][j];
                        break;
                    }
                }
                if (flag1 == 1)
                    break;
            }
        }

        for (m = length - 1; m >= 0; m--)
        {
            for (n = length - 1; n >= 0; n--)
            {
                if (board[m][n] == color)
                {
                    if (m == i && n == j)
                        break;
                    if (Direct(i, j, m, n) || OneCorner(i, j, m, n) 
                    || TwoCorner(i, j, m, n))
                    {
                        flag = 1;
                        board[i][j] = 0;
                        board[m][n] = 0;
                        break;
                    }
                }
            }
            if (flag == 1)
                break;
        }
        reg_i++;
    }
    sum -= 1;
}
void play(char* s)
{
    int x1, x2, y1, y2;
    bool ret;

    x1 = s[0] - '0';
    y1 = s[2] - '0';
    x2 = s[4] - '0';
    y2 = s[6] - '0';

    ret = match(x1, y1, x2, y2);
    if (ret)
    {
        board[x1][y1] = 0;
        board[x2][y2] = 0;
        sum -= 1;
        score += 1;
    }
    else
    {
        printf("Unable To Do ANYTHING!\n");
    }
}
int main()
{
    int i = 0;
    char s[100] = {};
    bool ret;
    while (1)
    {
        printf("Easy--E    Normal--N    Hard--H\n");
        printf("Please Choose Difficulty:");
        fflush(stdout);
        for (i = 0; i < 10; i++)
        {
            s[i] = getchar();
            if (s[i] == '\n')
                break;
        }
        if (s[0] == 'H')
        {
            length = 10;
            break;
        }
        if (s[0] == 'N')
        {
            length = 8;
            break;
        }
        if (s[0] == 'E')
        {
            length = 6;
            break;
        }
        else
            printf("Invalid choice! Please choose again!\n");
    }
    printf("\n");
    init();
    do
    {
	
        if (sum == 0)
        {
            printf("Victory!!!!\n");
            fflush(stdout);
            break;
        }
        for (i = 0; s[i] != '\0'; i++)
        {
            s[i] = '\0';
        }
        show();
        printf(">");
        fflush(stdout);
        for (i = 0; i < 100; i++)
        {
            s[i] = getchar();
            if (s[i] == '\n')
                break;
        }

        
        if ((s[0] == 'q' || s[0] == 'Q')
         && (s[1] == 'u' || s[1] == 'U') 
         && (s[2] == 'i' || s[2] == 'I') 
         && (s[3] == 't' || s[3] == 'T'))
            break;
        if (s[0] == 'h' && s[1] == 'e' 
        && s[2] == 'l' && s[3] == 'p')
            autosolve();
        else
        {
            ret = legal(s);
            if (ret == false)
                printf("AGAIN!\n");
            play(s);
        }

    } while (1);

    exit(0);
    return 0;
}

