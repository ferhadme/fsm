#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif // _WIN32

#define RED 0
#define YELLOW 1
#define GREEN 2

#define RD   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

#define NEXT_LIGHT(state) (state + 1) % 3

const char *lights[] = {"red", "yellow", "green"};
const char *light_color_codes[] = {RD, YEL, GRN};


void usage(const char *prog)
{
    printf("Usage: %s state\n", prog);
    printf("\tstate: %s|%s|%s\n",
           lights[RED], lights[YELLOW], lights[GREEN]);
}

int right_light(const char *light)
{
    for (int i = 0; i < sizeof(char *) / sizeof(lights); i++) {
        if (strcmp(light, lights[i]) != 0)
            return 0;
    }
    return 1;
}

int get_state(const char *state)
{
    if (strcmp(state, "red") == 0)
        return RED;
    if (strcmp(state, "yellow") == 0)
        return YELLOW;
    if (strcmp(state, "green") == 0)
        return GREEN;
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        usage(argv[0]);
        return 1;
    }

    int state = get_state(argv[1]);
    if (state == -1) {
        usage(argv[0]);
        return 1;
    }

    int s = 0;
    while (s++ <= 10) {
        printf("State: %s%s%s\n",
               light_color_codes[state], lights[state], RESET);
        state = NEXT_LIGHT(state);
        sleep(1);
    }

    return 0;
}
