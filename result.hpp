#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct Ranking {
    int rank;
    char name[100];
    int score;
};

int search(Ranking ranking[], int time) {
    for (int i = 0; i < 9; i++) {
        if (time > ranking[i].score) return i;
    }
    return -1;
}

void insert(Ranking *ranking, int index, Ranking player) {
    for (int i = 9; i >= index; i--) {
        ranking[i].rank = i + 1;
        ranking[i + 1] = ranking[i];
    }
    ranking[index] = player;
}

void draw_result(int time, char *name) {
    clear();

    FILE *fp;
    if ((fp = fopen("./text/ranking.txt", "r")) == NULL) {
        mvprintw(3, 3, "rankingファイルがありません!!");
        refresh();
        sleep(2);
        clear();
        return;
    }

    mvprintw(1, 2, "     あなたのスコアは%dです！", time);
    mvprintw(3, 2, "じゅんい\tおなまえ\tとくてん");

    int height = 5;
    Ranking ranking[11];

    int i = 0;
    while (fscanf(fp, "%d %s %d", &ranking[i].rank, ranking[i].name,
                  &ranking[i].score) != EOF) {
        // mvprintw(height, 2,"%2d\t%s\t%2d", ranking[i].rank,ranking[i].name,
        // ranking[i].score);
        i++;
    }

    int index = search(ranking, time);
    mvprintw(height, 2, "%d", index);

    if (index != -1) {
        Ranking r;
        strcpy(r.name, name), r.score = time, r.rank = index;
        insert(ranking, index, r);
    }
    fclose(fp);

    for (int i = 0; i < 10; i++) {
        mvprintw(height, 2, "%2d\t\t%s\t\t%2d", i + 1, ranking[i].name,
                 ranking[i].score);
        height += 1;
    }
    mvprintw(height + 2, 2, "       qキーでタイトルにもどる");

    fp = fopen("./text/ranking.txt", "w");
    for (int i = 0; i < 10; i++) {
        fprintf(fp, "%d %s %d\n", i + 1, ranking[i].name, ranking[i].score);
    }

    fclose(fp);
    refresh();

    int ch = 0;
    while (1) {
        ch = getch();
        if (ch == 'q') break;
    }

    clear();
}
