#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_LINES 1024
#define MAX_LINE_LENGTH 256

void readLines(const char *filename, char lines[][MAX_LINE_LENGTH], int *count)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Failed to open file %s\n", filename);
        return;
    }

    while (fgets(lines[*count], MAX_LINE_LENGTH, file) && *count < MAX_LINES)
    {
        lines[*count][strcspn(lines[*count], "\n")] = 0;
        (*count)++;
    }

    fclose(file);
}

void writeLine(const char *filename, const char *line)
{
    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("Failed to open file %s\n", filename);
        return;
    }

    fprintf(file, "%s\n", line);
    fclose(file);
}

void printCurrentTime()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    printf("当前时间: %d-%02d-%02d %02d:%02d:%02d\n",
           tm_struct->tm_year + 1900,
           tm_struct->tm_mon + 1,
           tm_struct->tm_mday,
           tm_struct->tm_hour,
           tm_struct->tm_min,
           tm_struct->tm_sec);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void searchLines(char linesA[][MAX_LINE_LENGTH], int countA, char linesB[][MAX_LINE_LENGTH], int countB, const char *keyword)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < countA; i++)
    {
        if (strstr(linesA[i], keyword))
        {
            int found = 0;
            for (int j = 0; j < countB; j++)
            {
                if (strcmp(linesA[i], linesB[j]) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("%s - 已使用\n", linesA[i]);
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("%s - 未使用\n", linesA[i]);
            }
        }
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    // 添加系统调用，设置控制台输出编码为UTF-8,glibc不认识windows下的utf-8
    char linesA[MAX_LINES][MAX_LINE_LENGTH] = {0};
    char linesB[MAX_LINES][MAX_LINE_LENGTH] = {0};
    int countA = 0, countB = 0;
    int nowFlag = 0;

    // 检查是否存在-now参数
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-now") == 0)
        {
            nowFlag = 1;
        }
    }

    if (argc > 1 && strcmp(argv[1], "-list") == 0)
    {
        readLines(".\\outb.txt", linesB, &countB);
        for (int i = 0; i < countB; i++)
        {
            printf("%s\n", linesB[i]);
        }
    }
    else if (argc > 2 && strcmp(argv[1], "-search") == 0)
    {
        readLines("outa.txt", linesA, &countA);
        readLines("outb.txt", linesB, &countB);
        searchLines(linesA, countA, linesB, countB, argv[2]);
    }
    else if (argc > 1 && strcmp(argv[1], "-rand") == 0)
    {
        readLines("outa.txt", linesA, &countA);
        readLines("outb.txt", linesB, &countB);
        if (countA == 0)
        {
            printf("no map can selected \n");
        }
        else
        {
            srand(time(NULL));
            int index;
            int found = 0;
            char selectedLine[MAX_LINE_LENGTH] = {0};

            while (!found)
            {
                index = rand() % countA;
                strcpy(selectedLine, linesA[index]);

                found = 1;
                for (int i = 0; i < countB; i++)
                {
                    if (strcmp(selectedLine, linesB[i]) == 0)
                    {
                        found = 0;
                        break;
                    }
                }
                if (found)
                {
                    printf("%s\n", selectedLine);
                    writeLine("outb.txt", selectedLine);
                    break;
                }
            }
        }
    }
    else
    {
        printf("Usage:\n");
        printf("  .\\rand_map.exe -rand    随机选择一个地图，并将其记录到outb.txt中,已选内容可删除，删除行即可\n");
        printf("  .\\rand_map.exe -list    列出所有已记录的地图\n");
        printf("  .\\rand_map.exe -search <keyword>    搜索包含关键字的地图,红色表示已使用,绿色表示未使用\n");
        printf("  .\\rand_map.exe -now    显示当前时间，可以附加在任意参数后面\n");
        printf("  其他问题请查看readme.txt\n");
        printf("todo ...  \n");
    }

    if (nowFlag)
    {
        // debug
        printCurrentTime();
    }

    return 0;
}