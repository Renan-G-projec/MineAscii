// Ad Maiorem Dei Gloriam!
#include "engine.h"

int main(void) {
    Engine engine;
    if (engine_init(&engine) != 0) {
        puts("Error: Could not start the engine. Exiting...\n");
        return -1;
    }

    engine_start_gameloop(&engine);
    engine_destroy(&engine);
    return 0;
}