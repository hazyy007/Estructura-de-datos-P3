#include <stdio.h>
#include <stdlib.h>
#include "radio.h"

int main(int argc, char *argv[]) {
    Radio *r;
    long from_id, to_id;
    FILE *f;

    if (argc < 4) {
        printf("Uso: %s <fichero.txt> <id_origen> <id_destino>\n", argv[0]);
        return EXIT_FAILURE;
    }

    from_id = atol(argv[2]);
    to_id = atol(argv[3]);

    r = radio_init();
    f = fopen(argv[1], "r");
    if (!f || radio_readFromFile(f, r) == ERROR) {
        if (f) fclose(f);
        radio_free(r);
        return EXIT_FAILURE;
    }
    fclose(f);

    printf("Radio:\n");
    radio_print(stdout, r);

    printf("\n---DFS---\n");
    radio_depthSearch(r, from_id, to_id);

    printf("\n---BFS---\n");
    radio_breadthSearch(r, from_id, to_id);

    radio_free(r);
    return EXIT_SUCCESS;
}