#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "radio.h"
#include "music.h"

int now_playing_menu(Queue *q);

int main(int argc, char *argv[]) {
    Radio *r;
    Queue *q;
    FILE *f;
    int i, num_songs;

    if (argc < 2) return EXIT_FAILURE;

    r = radio_init();
    f = fopen(argv[1], "r");
    if (!f || radio_readFromFile(f, r) == ERROR) {
        if (f) fclose(f);
        radio_free(r);
        return EXIT_FAILURE;
    }
    fclose(f);

    q = queue_new();
    num_songs = radio_getNumberOfMusic(r);
    for (i = 0; i < num_songs; i++) {
        queue_push(q, radio_getMusicIndex(r, i));
    }
    while (!queue_isEmpty(q)) {
        if (now_playing_menu(q) != 1) {
            break;
        }
    }

    queue_free(q);
    radio_free(r);
    return EXIT_SUCCESS;
}

int now_playing_menu(Queue *q)
{
    int option;
    
    Music *m = (Music *)queue_pop(q);

    if (!m) return 2;

    music_formatted_print(stdout, m);
    
    printf("Upcoming:\n");
    queue_print(stdout, q, (p_queue_ele_print)music_plain_print);
    printf("\n1. Next song\n");
    printf("2. Exit\n");
    printf("Choose an option: ");
    if (scanf("%d", &option) != 1) return 2;
    
    return option;
}