#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "radio.h"
#include "music.h"

int main(int argc, char *argv[]) {
    Radio *r;
    List *l;
    FILE *f;
    int i, num_songs;
    Music *m;

    if (argc < 2) {
        printf("Uso: %s <fichero_radio.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    r = radio_init();
    f = fopen(argv[1], "r");
    if (!f || radio_readFromFile(f, r) == ERROR) {
        if (f) fclose(f);
        radio_free(r);
        return EXIT_FAILURE;
    }
    fclose(f);

    l = list_new();
    num_songs = radio_getNumberOfMusic(r);

    for (i = 0; i < num_songs; i++) {
        m = radio_getMusicIndex(r, i);
        if (i % 2 == 0) {
            list_pushBack(l, m);
        } else {
            list_pushFront(l, m);
        }
    }

    printf("Finished inserting. Now we extract from the beginning:\n");
    for (i = 0; i < num_songs / 2; i++) {
        m = (Music *)list_popFront(l);
        music_plain_print(stdout, m);
        printf(" ");
    }
    printf("\n\n");

    printf("Now we extract from the end:\n");
    while (!list_isEmpty(l)) {
        m = (Music *)list_popBack(l);
        music_plain_print(stdout, m);
        printf(" ");
    }
    printf("\n");

    list_free(l);
    radio_free(r);
    return EXIT_SUCCESS;
}