// Ad Maiorem Dei Gloriam!
#include "engine.h"

int main(void) {
    Engine engine;
    if (!engine_init(&engine)) {
        puts("Error: Could not start the engine. Exiting...\n");
        return -1;
    }
    return 0;
}