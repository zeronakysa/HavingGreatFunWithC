#include "functions.h"

int main(int argc, char** argv)
{
    struct user *config;

    if (argv[1])
        memTest(argc, argv);

    config = launch();

    if(config->language == 1){ // So EN
        fflush(stdin);
        puts("Language are set in English (set in config.ini)");
        printf("Hi %s, nice to see you!\n", config->nickname);
        menuEN();
    }else if(config->language == 0){ // So FR
        fflush(stdin);
        puts("La langue est defini en Francais (dans config.ini)");
        printf("Bonjour %s, heureux de te voir !", config->nickname);
        menuFR();
    }
    remove("tmp");
    remove("tmpM");
    return 0;
}
//struct user *config;
//config = launch();