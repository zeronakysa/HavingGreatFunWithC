#include "functions.h"

struct user* launch(){


    char* fileToRead = "config.ini";
    char* fileToWrite = "config.ini";
    char** buffer = {'\0'};
    struct user *config = NULL;
    char* tmp;

    FILE *read;
    FILE *write;

    read = fopen(fileToRead, "r");
    if(read == NULL){
        write = fopen(fileToWrite, "w+");
        if(write == NULL){
            puts("Erreur while creating config file.");
            exit(EXIT_FAILURE);
        }else{
            fclose(write);
            config = allocateConfig(1);
            input(config);
            config = hardwaretoStruct(config);
            printToConfig(*config);
            free(config);
            read = fopen(fileToRead, "r");
        }
    }
    buffer = readFLinesConfigToBuffer(buffer);
    config = allocateConfig(1);

    config->id = atoi(buffer[0]);
    strcpy(config->nickname, buffer[1]);
    config->language = (int) strtol(buffer[2], &tmp, 2);
    strcpy(config->bddName, buffer[18]);
    strcpy(config->bddAdress, buffer[19]);

    config = hardwaretoStruct(config);

//    printf("%s\n", buffer[3]);
//    printf("%s\n", buffer[4]);
//    config->hardInfos.inf1 = (unsigned long)atol(buffer[3]);
//    config->hardInfos.inf2 = (unsigned long)atol(buffer[4]);
//    config->hardInfos.inf3 =  ( strtof(buffer[5], &tmp) / 1073741824);
//    config->hardInfos.inf4 =  ( strtof(buffer[6], &tmp) / 1073741824);
//    config->hardInfos.inf5 = atoi(buffer[7]);
//    config->hardInfos.inf6 = atoi(buffer[8]);
//    config->hardInfos.inf7 = atoi(buffer[9]);
//    config->hardInfos.inf8 = atoi(buffer[10]);
//    sprintf(config->hardInfos.inf9, "%s", buffer[11]);
//    sprintf(config->hardInfos.inf10, "%s", buffer[12]);
//    config->hardInfos.inf11 = atoi(buffer[13]);
//    config->hardInfos.inf12 = atoi(buffer[14]);
//    config->hardInfos.inf13 = atoi(buffer[15]);
//    config->hardInfos.inf14 = atoi(buffer[16]);
//    config->hardInfos.inf15 = atoi(buffer[17]);

    fclose(read);

    return config;
}

void startMenuEN(){
    puts("\n\n=====HAVING GREAT FUN WITH C=====\n");
    puts("1 - Reminder Project");
    puts("2 - Hardware Informations");
    puts("3 - CPU Bench");
    puts("4 - Network Bench");
    puts("5 - Memory Bench");
    puts("6 - Global Bench");
    puts("7 - Leaderboard");
    puts("8 - Edit profile");
    puts("99 - Quit\n");

    puts("Please make your choice: ");
}

void menuEN(){
    int choice = 0;
    char path[5][5] = {1};
    int iTmp = 0;
    int choiceLeaderboard = 0;
    float resultNetwork = 0;
    struct user *config;
    config = launch();
    //float timer = 0;
    //char start = 's';
    //char end = 'e';

    while(choice != 99){
        //ToDO: verif scanf
        startMenuEN();
        sleep(1);
        scanf("%d", &choice);
        switch (choice){
            case 1:
                reminder();
                break;
            case 2:
                hardwareInfos();
                break;
            case 3:
                iTmp = cpuBench();
                printf("CPU's bench result: %d\n",iTmp);
                createResult(1, config->nickname, iTmp);
                break;
            case 4:
                for(int i = 0; i < 4; i++){
                    printf("Response time:%dms", (calculatePing()));
                }
                for(int i = 0; i < 4000; ++i) {
                    resultNetwork+=sendPacketToServer(10000);
                }
                printf("\nSpeed: %.2lfMb/s", (38.14/resultNetwork));
                printf("\n");
                createResult(4, config->nickname, ((int) ((38.14/resultNetwork)*100)));
                break;
            case 5:
                iTmp = memTest(1,(char **)path);
                printf("Memory's bench result: %d\n",iTmp);
                createResult(2, config->nickname, iTmp);
                sleep(2);
            case 6:
                iTmp = cpuBench();
                sleep(2);
                iTmp += memTest(1,(char **)path);
                sleep(2);
                createResult(5, config->nickname, iTmp);
                break;
            case 7:
                system("cls");
                puts("1 - Best CPU");
                puts("2 - Best RAM");
                puts("3 - Best write speed");
                puts("4 - Best network");
                puts("5 - Best global performance");
                puts("Choose wich categorie you want to see: ");
                scanf("%d", &choiceLeaderboard);
                getLeaderboard(choiceLeaderboard);
                break;
            case 8:
                system("cls");
                fflush(stdin);
                puts("The following operation gonna create a fully new user");
                puts("Do you want to continue (1 = yes, 0 = no)? [1/0]");
                scanf("%d",&choice);
                if (choice == 1){
                    remove("config.ini");
                    ShellExecute(0,"open",EXECNAME,NULL,NULL,1);
                    exit(EXIT_SUCCESS);
                }else
                    continue;
                break;
            case 99:
                exit(EXIT_SUCCESS);
                break;
            default:
                puts("No valid argument received, try again.");
                break;
        }
        fflush(stdin);
        system("pause");
        system("cls");
    }
}

void startMenuFR(){
    puts("\n\n=====HAVING GREAT FUN WITH C=====\n");
    puts("1 - Rappel Projet");
    puts("2 - Informations sur le materiel");
    puts("3 - Test CPU");
    puts("4 - Test Reseau");
    puts("5 - Test Memoire");
    puts("6 - Test Globale");
    puts("7 - Classement");
    puts("8 - Editer profile");
    puts("99 - Quitter\n");

    puts("Merci de faire votre choix: ");
}

void menuFR(){
    int iTmp = 0;
    struct user *config;
    config = launch();
    int choice = 0;
    int choiceLeaderboard = 0;
    float resultNetwork = 0;
    char path[5][5] = {1};
    //float timer = 0;
    //char start = 's';
    //char end = 'e';

    while(choice != 99){
        //ToDO: verif scanf
        startMenuFR();
        sleep(1);
        scanf("%d", &choice);
        switch (choice){
            case 1:
                reminder();
                break;
            case 2:
                hardwareInfos();
                break;
            case 3:
                //timer = fTimer(start, timer);
                //memoryTest();
                //timer = fTimer(end, timer);
                //printf("Execution time: %lf seconde(s)", timer);
                iTmp = cpuBench();
                printf("Resultat du test CPU: %d\n",iTmp);
                createResult(1, config->nickname, iTmp);
                break;
            case 4:
                for(int i = 0; i < 4; i++){
                    printf("Temps de reponse:%dms", (calculatePing()));
                }
                for(int i = 0; i < 4000; ++i) {
                    resultNetwork+=sendPacketToServer(10000);
                }
                printf("\nVitesse: %.2lfMb/s", (38.14/resultNetwork));
                printf("\n");
                createResult(4, config->nickname, ((int) ((38.14/resultNetwork)*100)));
                break;
            case 5:
                iTmp = memTest(1,(char **)path);
                printf("Resultat du test memoire: %d\n",iTmp);
                createResult(2, config->nickname, iTmp);
                sleep(2);
                break;
            case 6:
                iTmp = cpuBench();
                sleep(2);
                iTmp += memTest(1,(char **)path);
                sleep(2);
                createResult(5, config->nickname, iTmp);
                break;
            case 7:
                system("cls");
                puts("1 - Meilleur CPU");
                puts("2 - Meilleur RAM");
                puts("3 - Meilleur censure");
                puts("4 - Meilleur internet");
                puts("5 - Meilleur global");
                puts("Choisissez quel categorie vous voulez voir: ");
                scanf("%d", &choiceLeaderboard);
                getLeaderboard(choiceLeaderboard);
                break;
            case 8:
                system("cls");
                fflush(stdin);
                puts("L'action suivante vous crera un nouvel utilisateur au complet");
                puts("Voulez vous continuer ? (1 = oui, 0 = non)? [1/0]");
                scanf("%d",&choice);
                if (choice == 1){
                    remove("config.ini");
                    ShellExecute(0,"open",EXECNAME,NULL,NULL,1);
                    exit(EXIT_SUCCESS);
                }else
                    continue;
                break;
            case 99:
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
        fflush(stdin);
        fflush(stdout);
        system("pause");
    }
}

void reminder(){
    puts("Description: Application permettant de faire des benchmark* de divers composants. "
                 "Le but est de récupérer par l'API Windows les information système nécéssaire, les stocké et s'en servir pour faire des tests. "
                 "Des tests sont envisagable sur la mémoire vive (charge maximum de stockage + vitesse), "
                 "sur le CPU (nb d'instruction réel selon un temps + prise en charge du multi-thread) "
                 "sur la vitesse de la mémoire ROM (temps d'écriture, lecture). "
                 "D'autres options sont envisageable si le projet avance bien, par exemple: réseau, graphique, sonore, température interne et autres.\n"
                 "\n"
                 "*Un benchmark est un test visant a connaitre les performances d'un composant interne.\n"
                 "\n"
                 "Système requis: Windows\n"
                 "\n"
                 "API: Oui\n"
                 "Détails: Au minimum windows.h, math.h et time.h et une autre pour un accès BDD.\n"
                 "\n"
                 "Interface graphique: Oui\n"
                 "Détails: Non choisi pour le moment\n"
                 "\n"
                 "Exploitation de fichier: Oui\n"
                 "Détails: \n"
                 "- config.ini => prise en compte de \"profil utilisateur\" ce dernier contiendras des chose basique tel que sa dernière visite, ses derniers score, la liste de ses composant, les derniers test utilisers, la langue utilisé, son pseudo, etc\n"
                 "- scenario => suite de test sur plusieurs composant pouvant être sauvgardé afin d'avoir un \"scénario typique\" pour faire des tests sur plusieurs machine (par exemple)\n"
                 "- stats globale => fichier mis à jour depuis un serveur regroupdant les moyenne des tests ou les scores d'autres utilisateurs\n"
                 "\n"
                 "Temps estimé sur tout le projet: 50h");
}

float fTimer(char action, float starter){
    float result = 0;

    if (action == 's'){
        result = (float)clock()/CLOCKS_PER_SEC;
    }else if( action == 'e'){
        result = (float)clock()/CLOCKS_PER_SEC - starter;
    }
    return result;
}

struct user* allocateConfig(int size) {
    struct user *array = NULL;

    if ((array = malloc(size * sizeof(struct user))) != NULL) {
        for (int i = 0; i < size; i++) {
            array[i].id = i;
            strcpy(array[i].nickname, "anonymus");
            array[i].language = 1;
            strcpy(array[i].bddName, "test4");
            strcpy(array[i].bddAdress, "81.57.99.100");
        }
    }
    return array;
}

void input(struct user* s){

    char tmp[60] = {'\0'};

    //ToDO: Verif on scanf

    puts("Enter your nickname:");
    do{
        fflush(stdin);
        fgets(tmp, 60, stdin);
        if(strlen(tmp) <= 3){
            perror("Nickname to short");
            strcpy(tmp, "Zero");
            system("pause");
        }
        else{
            tmp[strlen(tmp) - 1] = '\0';
        }
        system("cls");
        puts("Nickname already use, try another.");
    }while (getUser(tmp));
    strcpy(s->nickname,tmp);
    createUser(s->nickname);
    fflush(stdin);
    system("cls");
    s->id = getId( s->nickname);
    puts("Select your language: 0 = FR; 1 = EN;");
    scanf("%d",&s->language);
    fflush(stdin);
}

void printToConfig(struct user config){
    FILE* write = fopen("config.ini", "w+");

    fprintf(write,"###USER###\n");
    fprintf(write,"ID =        %d\n", config.id);
    fprintf(write,"Nickname =  %s\n", config.nickname);
    fprintf(write,"Language =  %d\n", config.language);
    fprintf(write,"#Lang: 1:EN/0:FR\n\n");
    fprintf(write,"###HARDWARE###\n");
    fprintf(write,"Total virtual Mem(octets) =       %llu\n",config.hardInfos.inf1);
    fprintf(write,"Total Physical Mem(octets) =      %llu\n",config.hardInfos.inf2);
    fprintf(write,"Total virtual Mem(Go) =           %.2lf\n",config.hardInfos.inf3);
    fprintf(write,"Total Physical Mem(Go) =          %.2lf\n",config.hardInfos.inf4);
    fprintf(write,"Processor information:\n");
    fprintf(write,"  OEM ID =                        %d\n",config.hardInfos.inf5);
    fprintf(write,"  Number of processors =          %d\n",config.hardInfos.inf6);
    fprintf(write,"  Page size =                     %d\n",config.hardInfos.inf7);
    fprintf(write,"  Processor type =                %d\n",config.hardInfos.inf8);
    fprintf(write,"  Minimum application address =   %s\n",config.hardInfos.inf9);
    fprintf(write,"  Maximum application address =   %s\n",config.hardInfos.inf10);
    fprintf(write,"  Active processor mask =         %d\n",config.hardInfos.inf11);
    fprintf(write,"Processor Base Frequency(MHz) =   %d\n",config.hardInfos.inf12);
    fprintf(write,"Maximum Frequency(MHz) =          %d\n",config.hardInfos.inf13);
    fprintf(write,"Bus (Reference) Frequency(MHz) =  %d\n",config.hardInfos.inf14);
    fprintf(write,"Amount of cores =                 %d\n\n",config.hardInfos.inf15);
    fprintf(write,"###BDD###\n");
    fprintf(write,"BDDName =                         %s\n",config.bddName);
    fprintf(write,"BDDAdress =                       %s\n",config.bddAdress);

    fclose(write);
}

void hardwareInfos(){
    SYSTEM_INFO siSysInfo;

    // Copy the hardware information to the SYSTEM_INFO structure.

    GetSystemInfo(&siSysInfo);

    // Display the contents of the SYSTEM_INFO structure.


    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
    DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
    DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

    printf("Total virtual Mem:       %lld\n",totalVirtualMem);
    printf("Total virtual Mem used:  %lld\n",virtualMemUsed);
    printf("Total Physical Mem:      %lld\n",totalPhysMem);
    printf("Total Physical Mem used: %lld\n",physMemUsed);

    printf("Total virtual Mem :      %.2lfGo\n",(double) totalVirtualMem / 1073741824);
    printf("Total virtual Mem used:  %.2lfGo\n",(double) virtualMemUsed / 1073741824);
    printf("Total Physical Mem:      %.2lfGo\n",(double) totalPhysMem / 1073741824);
    printf("Total Physical Mem used: %.2lfGo\n",(double) physMemUsed / 1073741824);

    printf("Hardware information: \n");
    printf("  OEM ID: %ld\n", siSysInfo.dwOemId);
    printf("  Number of processors: %ld\n", siSysInfo.dwNumberOfProcessors);
    printf("  Page size: %ld\n", siSysInfo.dwPageSize);
    printf("  Processor type: %ld\n", siSysInfo.dwProcessorType);
    printf("  Minimum application address: %p\n", siSysInfo.lpMinimumApplicationAddress);
    printf("  Maximum application address: %p\n", siSysInfo.lpMaximumApplicationAddress);
    printf("  Active processor mask: %ld\n", siSysInfo.dwActiveProcessorMask);
}

struct user* hardwaretoStruct(struct user* config){

    int cpuInfo[4] = { 0, 0, 0, 0 };
    __cpuid(0x0,cpuInfo[0],cpuInfo[1],cpuInfo[2],cpuInfo[3]);
    if (cpuInfo[0] >= 0x16) {
        __cpuid(0x16,cpuInfo[0],cpuInfo[1],cpuInfo[2],cpuInfo[3]);
    } else {
        printf("CPUID level 16h unsupported\r\n");
    }

    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;

    config->hardInfos.inf1 = (unsigned long long) totalVirtualMem;
    config->hardInfos.inf2 = (unsigned long long) totalPhysMem;
    config->hardInfos.inf3 = (float) ( (double) totalVirtualMem / 1073741824);
    config->hardInfos.inf4 = (float) ( (double) totalPhysMem / 1073741824);
    config->hardInfos.inf5 = (int) siSysInfo.dwOemId;
    config->hardInfos.inf6 = (int) siSysInfo.dwNumberOfProcessors;
    config->hardInfos.inf7 = (int) siSysInfo.dwPageSize;
    config->hardInfos.inf8 = (int) siSysInfo.dwProcessorType;
    sprintf(config->hardInfos.inf9, "%p", siSysInfo.lpMinimumApplicationAddress);
    sprintf(config->hardInfos.inf10, "%p", siSysInfo.lpMaximumApplicationAddress);
    config->hardInfos.inf11 = (int) siSysInfo.dwActiveProcessorMask;
    config->hardInfos.inf12 = cpuInfo[0];
    config->hardInfos.inf13 = cpuInfo[1];
    config->hardInfos.inf14 = cpuInfo[2];
    config->hardInfos.inf15 = omp_get_max_threads();

    return config;
}

void *current_Memory(void *nothing) {

    ShellExecute(0,"open","CPUusage.exe",NULL,NULL,0);

    while(!_kbhit() || _getch() != 'q'){
        FILE* tmp;
        char cpuUse[10];
        tmp = fopen("tmp", "r");
        fgets(cpuUse, 10, tmp);

        system("cls");
        fflush(stdin);
        _cputs( "Press 'q' for exit! \n");
        SYSTEM_INFO siSysInfo;

        // Copy the hardware information to the SYSTEM_INFO structure.

        GetSystemInfo(&siSysInfo);

        // Display the contents of the SYSTEM_INFO structure.

        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
        DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
        DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
        DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

        printf("Total virtual Mem used:  %.2lfGo/%.2lfGo\n",(double) virtualMemUsed / 1073741824, (double) totalVirtualMem / 1073741824);
        printf("Total Physical Mem used: %.2lfGo/%.2lfGo\n",(double) physMemUsed / 1073741824, (double) totalPhysMem / 1073741824);
        printf("Acutal CPU use:          %.2lf%%\n", atof(cpuUse));
        _cputs( "Test in progress.. \n");
        fclose(tmp);
        sleep(1);
    }
        puts("exit");
        //system("TASKKILL -F /im CPUusage.exe");
        //system("TASKKILL -F /im tests.exe");
        //ShellExecute(0,"open","tests.exe",NULL,NULL,1);
/* the function must return something - NULL will do */
    return NULL;

}

void *inc_num(void *y_void_ptr) {

    int *y_ptr = (int *)y_void_ptr;

    int num = 0;

    int limit = 1000000;

    for (num = 1; num <= limit; num++) {
        int i = 2;
        while(i <= num) {
            if(num % i == 0)
                break;
            i++;
        }
        if(i == num)
            (*y_ptr)++;
    }

/* the function must return something - NULL will do */
    return NULL;
}

int cpuTest1(){

    int a = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);
    res = a;
    return res;

}

int cpuTest2(){

    int a = 0;
    int b = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t inc_num2_thread;

    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num2_thread, NULL, inc_num, &b)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num2_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);
    res = (a + b) / 2;
    return res;

}

int cpuTest3(){

    int a = 0;
    int b = 0;
    int c = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t inc_num2_thread;
    pthread_t inc_num3_thread;
    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num2_thread, NULL, inc_num, &b)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num3_thread, NULL, inc_num, &c)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num2_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num3_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);
    res = (a + b + c) / 3;
    return res;

}

int cpuTest4(){

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t inc_num2_thread;
    pthread_t inc_num3_thread;
    pthread_t inc_num4_thread;
    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num2_thread, NULL, inc_num, &b)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num3_thread, NULL, inc_num, &c)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num4_thread, NULL, inc_num, &d)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num2_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num3_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num4_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);
    res = (a + b + c + d) / 4;
    return res;
}

int cpuTest5(){

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t inc_num2_thread;
    pthread_t inc_num3_thread;
    pthread_t inc_num4_thread;
    pthread_t inc_num5_thread;
    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num2_thread, NULL, inc_num, &b)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num3_thread, NULL, inc_num, &c)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num4_thread, NULL, inc_num, &d)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num5_thread, NULL, inc_num, &e)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num2_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num3_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num4_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num5_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);
    res = (a + b + c + d + e) / 5;
    return res;

}

int cpuTest6(){

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t inc_num2_thread;
    pthread_t inc_num3_thread;
    pthread_t inc_num4_thread;
    pthread_t inc_num5_thread;
    pthread_t inc_num6_thread;
    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num2_thread, NULL, inc_num, &b)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num3_thread, NULL, inc_num, &c)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num4_thread, NULL, inc_num, &d)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num5_thread, NULL, inc_num, &e)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num6_thread, NULL, inc_num, &f)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num2_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num3_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num4_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num5_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num6_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);
    res = (a + b + c + d + e + f) / 6;
    return res;
}

int cpuTest7(){

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int g = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t inc_num2_thread;
    pthread_t inc_num3_thread;
    pthread_t inc_num4_thread;
    pthread_t inc_num5_thread;
    pthread_t inc_num6_thread;
    pthread_t inc_num7_thread;
    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num2_thread, NULL, inc_num, &b)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num3_thread, NULL, inc_num, &c)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num4_thread, NULL, inc_num, &d)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num5_thread, NULL, inc_num, &e)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num6_thread, NULL, inc_num, &f)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num7_thread, NULL, inc_num, &g)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num2_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num3_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num4_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num5_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num6_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num7_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);
    res = (a + b + c + d + e + f + g) / 7;
    return res;
}

int cpuTest8(){

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int g = 0;
    int h = 0;
    int res = 0;

/* this variable is our reference to the second thread */
    pthread_t inc_num1_thread;
    pthread_t inc_num2_thread;
    pthread_t inc_num3_thread;
    pthread_t inc_num4_thread;
    pthread_t inc_num5_thread;
    pthread_t inc_num6_thread;
    pthread_t inc_num7_thread;
    pthread_t inc_num8_thread;
    pthread_t currentMemory;

    pthread_create(&currentMemory, NULL, current_Memory, NULL);

    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num1_thread, NULL, inc_num, &a)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num2_thread, NULL, inc_num, &b)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num3_thread, NULL, inc_num, &c)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num4_thread, NULL, inc_num, &d)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num5_thread, NULL, inc_num, &e)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num6_thread, NULL, inc_num, &f)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num7_thread, NULL, inc_num, &g)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* create a thread which executes inc_prime(&x) */
    if(pthread_create(&inc_num8_thread, NULL, inc_num, &h)){
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
/* wait for the thread to finish */
    if(pthread_join(inc_num1_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num2_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num3_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num4_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num5_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num6_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num7_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    /* wait for the thread to finish */
    if(pthread_join(inc_num8_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    pthread_kill(currentMemory, 0);

    res = (a + b + c + d + e + f + g + h) /8;

    return res;

}

int cpuBench(){

    int res = 0;
    double start, end;
    double runTime;
    start = omp_get_wtime();

    switch (omp_get_max_threads()){
        case 1:
            res = cpuTest1();
            break;
        case 2:
            res = cpuTest2();
            break;
        case 3:
            res = cpuTest3();
            break;
        case 4:
            res = cpuTest4();
            break;
        case 5:
            res = cpuTest5();
            break;
        case 6:
            res = cpuTest6();
            break;
        case 7:
            res = cpuTest7();
            break;
        case 8:
            res = cpuTest8();
            break;
        default:
            puts("Error, number of core unsupported");
            perror("1");
            return 1;
    }
    end = omp_get_wtime();
    runTime = end - start;
    res = res / (int)runTime;
    system("TASKKILL -F /im CPUusage.exe");

    // This structure will be used to create the keyboard
    // input event.
    INPUT ip;
    sleep(1);

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the "q" key
    ip.ki.wVk = 0x51; // virtual-key code for the "q" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    sleep(2);

    // Release the "q" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));

    remove("tmp");

    return res;

}

int memTest(int argc, char** argv) {

    char **buffer = {'\0'};
    struct user *config = NULL;
    char *tmpVar;
    int max = 0;
    unsigned int j = 0;
    FILE *tmp;
    char path[200];
    long result = 0;
    long long *mallocOK;
    pthread_t currentMemory;
    long long Resultat = 0;
    int finalResultat = 0;
    char bufferTmp[1024] = {0};

    config = allocateConfig(1);
    config = hardwaretoStruct(config);

    max = (int) (config->hardInfos.inf4 / 2) + 1;

    GetModuleFileName(NULL, path, sizeof(path));

    char evnTmp[10];
    tmp = fopen("tmpM", "a");

    if (argv[1] == NULL) {
        for (j = 0; j < max; j++) {
            sprintf(evnTmp, "tmpM%d", j);
            ShellExecute(0, "open", path, evnTmp, NULL, 0);
            sleep(1);
        }
        pthread_create(&currentMemory, NULL, current_Memory, NULL);
        sleep(60);
        pthread_kill(currentMemory, 0);
        system("TASKKILL -F /im CPUusage.exe");
    } else {
        do {
            mallocOK = malloc(sizeof(long long));
            result++;
        } while (mallocOK != NULL);
        if (result != 0) {
            fseek(tmp, 0, SEEK_END);
            fprintf(tmp, "%ld\n", result);
            fclose(tmp);
        }
        sleep(15);
        exit(EXIT_SUCCESS);
    }
    // This structure will be used to create the keyboard
    // input event.
    INPUT ip;
    sleep(1);

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the "q" key
    ip.ki.wVk = 0x51; // virtual-key code for the "q" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    sleep(2);

    // Release the "q" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));

    remove("tmp");
    fclose(tmp);
    tmp = fopen("tmpM", "r");
    if (tmp != NULL) {
        while (fgets(bufferTmp, 1024, tmp)) {
            Resultat += atoll(bufferTmp);
        }
    }
    fclose(tmp);
    remove("tmpM");

    //TODO trouver un resultat humain
    finalResultat = (int) (Resultat / j / 10000);
    return finalResultat;
}

char *trimwhitespace(char *str){
    char *end;
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0)  // All spaces?
        return str;
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    // Write new null terminator
    *(end+1) = 0;
    return str;
}

char** readFLinesConfigToBuffer(char** buffer){
    //char** buffer = {0};
    char* fileToRead = "config.ini";
    char bufferTmp[1024] = {0};
    char* bufferTmp2[1024] = {0};
    FILE *tmp;
    const char s[2] = "=";
    char *value;
    int j,i = 0;

    tmp = fopen(fileToRead, "r");

    if (tmp != NULL) {
        while (fgets(bufferTmp, 1024, tmp)) {
            strtok(bufferTmp, s);
            value = strtok(NULL, s);
            if (value){
                value = trimwhitespace(value);
                bufferTmp2[i] = malloc(sizeof(char)*(strlen(value)+1));
                strcpy(bufferTmp2[i], value);
                i++;
            }
        }
        fclose(tmp);
    }

    buffer = malloc(150 * sizeof(char));
    for (j = 0; j < i; j++){
        buffer[j] = malloc(sizeof(char) * strlen(bufferTmp2[j]));
        strcpy(buffer[j], bufferTmp2[j]);
    }
    if(!i){
        buffer = malloc(4);
        buffer[0] = malloc(4);
        strcpy(buffer[0],"\0");
    }
    return buffer;
}

int getId(char *username){
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    int id = 0;

    char getIdRequest[100] = {0};

    char** buffer = {'\0'};
    buffer = readFLinesConfigToBuffer(buffer);

    //TODO: Nom BDD dynamique
    if(mysql_real_connect(mysql,((strlen(buffer[0]))? buffer[19]:BDDADRESS),"root","",((strlen(buffer[0]))? buffer[18]:BDDNAME),0,NULL,0)) {
        sprintf(getIdRequest, "SELECT id FROM user WHERE username = '%s'", username);

        mysql_query(mysql, getIdRequest);

        MYSQL_RES *result = mysql_store_result(mysql);

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            id = atoi(row[0]);
        }

        mysql_free_result(result);
        mysql_close(mysql);
    } else {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }

    return id;
}

void createUser (char *username){
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    char createUserRequest[100] = {0};
    char getUserRequest[100] = {0};
    char** buffer = {'\0'};
    buffer = readFLinesConfigToBuffer(buffer);

    //TODO: mettre nom BDD dynamqiue
    if(mysql_real_connect(mysql,((strlen(buffer[0]))? buffer[19]:BDDADRESS),"root","",((strlen(buffer[0]))? buffer[18]:BDDNAME),0,NULL,0)) {
        sprintf(getUserRequest, "SELECT * FROM user WHERE username = '%s'", username);

        mysql_query(mysql, getUserRequest);

        MYSQL_RES *result = mysql_store_result(mysql);

        if(mysql_fetch_row(result) != NULL) {
            printf("L'utilisateur %s existe deja!\n", username);
        } else {
            sprintf(createUserRequest, "INSERT INTO user(username, creation_date) VALUES('%s', NOW())", username);
            mysql_query(mysql, createUserRequest);
            puts("L'utilisateur a bien ete cree!");
        }
        mysql_free_result(result);
        mysql_close(mysql);
    } else {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}

int getUser(char *username){
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    int i, j= 0;

    char getUserRequest[100] = {0};
    char** buffer = {'\0'};
    buffer = readFLinesConfigToBuffer(buffer);

    //TODO: mettre nom serveur dynamique
    if(mysql_real_connect(mysql,((strlen(buffer[0]))? buffer[19]:BDDADRESS),"root","",((strlen(buffer[0]))? buffer[18]:BDDNAME),0,NULL,0)) {
        sprintf(getUserRequest, "SELECT * FROM user WHERE username = '%s'", username);

        mysql_query(mysql, getUserRequest);

        MYSQL_RES *result = mysql_store_result(mysql);

        int num_fields = mysql_num_fields(result);

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            for(i = 0; i < num_fields; i++) {
                //printf(" %s ", row[i]);
                j++;
            }
            //printf("\n");
        }
        if(j == 0){
            mysql_free_result(result);
            mysql_close(mysql);
            return 0; //n'existe pas en base peu donc etre cree
        }else
            return 1; //existe deja en base, try again
    } else {
        perror("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}

//1CPU 2RAM 3Write 4Netw 5Glob
void createResult(int choiceLeaderboard, char *username, int testValue){
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    char createResultRequest[200] = {0};
    int user_id = 0;
    char** buffer = {'\0'};
    buffer = readFLinesConfigToBuffer(buffer);

    //TODO: nom BDD
    if(mysql_real_connect(mysql,((strlen(buffer[0]))? buffer[19]:BDDADRESS),"root","",((strlen(buffer[0]))? buffer[18]:BDDNAME),0,NULL,0)) {
        user_id = getId(username);
        strcpy(createResultRequest, "INSERT INTO result(user_id, ");

        switch(choiceLeaderboard) {
            case 1:
                strcat(createResultRequest, "cpu_test)");
                break;
            case 2:
                strcat(createResultRequest, "ram_test)");
                break;
            case 3:
                strcat(createResultRequest, "write_test)");
                break;
            case 4:
                strcat(createResultRequest, "network_test)");
                break;
            case 5:
                strcat(createResultRequest, "global_test)");
                break;
            default:
                puts("Le choix n'a pas été reconnu");
                break;
        }

        sprintf(createResultRequest + strlen(createResultRequest), " VALUES (%d, %d)", user_id, testValue);

        mysql_query(mysql, createResultRequest);

        mysql_close(mysql);
    } else {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}

void getLeaderboard(int choiceLeaderboard){
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    int i;

    char getLeaderboardRequest[200] = {0};
    char** buffer = {'\0'};
    buffer = readFLinesConfigToBuffer(buffer);

    //TODO: nom BDD
    if(mysql_real_connect(mysql,((strlen(buffer[0]))? buffer[19]:BDDADRESS),"root","",((strlen(buffer[0]))? buffer[18]:BDDNAME),0,NULL,0)) {
        sprintf(getLeaderboardRequest, "SELECT user.username, user.creation_date, result.");

        switch(choiceLeaderboard) {
            case 1:
                strcat(getLeaderboardRequest, "cpu_test");
                strcat(getLeaderboardRequest, " FROM user, result WHERE user.id = result.user_id ORDER BY result.");
                strcat(getLeaderboardRequest, "cpu_test");
                break;
            case 2:
                strcat(getLeaderboardRequest, "ram_test");
                strcat(getLeaderboardRequest, " FROM user, result WHERE user.id = result.user_id ORDER BY result.");
                strcat(getLeaderboardRequest, "ram_test");
                break;
            case 3:
                strcat(getLeaderboardRequest, "write_test");
                strcat(getLeaderboardRequest, " FROM user, result WHERE user.id = result.user_id ORDER BY result.");
                strcat(getLeaderboardRequest, "write_test");
                break;
            case 4:
                strcat(getLeaderboardRequest, "network_test");
                strcat(getLeaderboardRequest, " FROM user, result WHERE user.id = result.user_id ORDER BY result.");
                strcat(getLeaderboardRequest, "network_test");
                break;
            case 5:
                strcat(getLeaderboardRequest, "global_test");
                strcat(getLeaderboardRequest, " FROM user, result WHERE user.id = result.user_id ORDER BY result.");
                strcat(getLeaderboardRequest, "global_test");
                break;
            default:
                puts("Le choix n'a pas ete reconnu");
        }

        strcat(getLeaderboardRequest, " LIMIT 10");

        mysql_query(mysql, getLeaderboardRequest);

        MYSQL_RES *result = mysql_store_result(mysql);

        int num_fields = mysql_num_fields(result);

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            for(i = 0; i < num_fields; i++) {
                printf(" %s ", row[i]);
            }
            printf("\n");
        }

        mysql_free_result(result);
        mysql_close(mysql);
    } else {
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }
}

void updateResult(int choiceLeaderboard, char *username, int testValue){
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    char updateResultRequest[200] = {0};
    int user_id = 0;
    char** buffer = {'\0'};
    buffer = readFLinesConfigToBuffer(buffer);

    if(mysql_real_connect(mysql,((strlen(buffer[0]))? buffer[19]:BDDADRESS),"root","",((strlen(buffer[0]))? buffer[18]:BDDNAME),0,NULL,0)) {
        user_id = getId(username);
        strcpy(updateResultRequest, "UPDATE result SET ");

        switch(choiceLeaderboard) {
            case 1:
                strcat(updateResultRequest, "cpu_test = ");
                break;
            case 2:
                strcat(updateResultRequest, "ram_test = ");
                break;
            case 3:
                strcat(updateResultRequest, "write_test = ");
                break;
            case 4:
                strcat(updateResultRequest, "network_test = ");
                break;
            case 5:
                strcat(updateResultRequest, "global_test = ");
                break;
            default:
                puts("Le choix n'a pas été reconnu");
                break;
        }

        sprintf(updateResultRequest + strlen(updateResultRequest), "%d ", testValue);
        sprintf(updateResultRequest + strlen(updateResultRequest), "WHERE user_id = %d", user_id);

        mysql_query(mysql, updateResultRequest);

        mysql_close(mysql);
    } else {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}

void createOrUpdateResult(int choiceLeaderboard, char *username, int testValue){
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    char getUserRequest[200] = {0};
    int user_id = 0;
    char** buffer = {'\0'};
    buffer = readFLinesConfigToBuffer(buffer);




    if(mysql_real_connect(mysql,((strlen(buffer[0]))? buffer[19]:BDDADRESS),"root","",((strlen(buffer[0]))? buffer[18]:BDDNAME),0,NULL,0)) {
        user_id = getId(username);
        sprintf(getUserRequest, "SELECT * FROM result WHERE user_id = '%d'", user_id);

        mysql_query(mysql, getUserRequest);
        MYSQL_RES *result = mysql_store_result(mysql);

        if(mysql_fetch_row(result) == NULL) {
            createResult(choiceLeaderboard, username, testValue);
        } else {
            updateResult(choiceLeaderboard, username, testValue);
        }


        mysql_close(mysql);
    } else {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}

//

void startWSAS (){ //initialise l'utilisation de winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD (2,2), &wsaData) != 0){ //param 1 = version, param 2 = WSADATA structure
        printf("Echec inti winsock erreur : %d\n", WSAGetLastError());
    }
}

int sendToServer(SOCKET sockclt, SOCKADDR_IN *sin, char *buffer) {
    int result;
    if(result = sendto(sockclt, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin)  == -1){
        printf("ERREUR D'ENVOI DU PAQUET AU SERVEUR : %d", result);
    }
    return result;
}

float calculateSpeed(float timer, int sizeOfPacket){
    float result = 0;
    result = timer;
    return result;
}

int calculatePing(){
    int packetsize = 1;
    float timer = 0;
    char start = 's';
    char end = 'e';

    //const char* serverIP = "192.168.134.132";
    const char* serverIP = "81.57.99.100"; //SERVEUR AURELIEN

    int sendvalue;

    startWSAS ();//WSAStartup(MAKEWORD(2, 2), &wsaData); //utilisation de la dll winsock

    //Variable de réseau
    SOCKET sockc;
    SOCKADDR_IN server = {0};
    SOCKADDR_IN response = {0};

    //Buffer de réponse du serveur
    char responsebuffer [packetsize];
    int resplen = sizeof response; //longueur de la réponse

    if((sockc = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)//socket(AF_INET , SOCK_DGRAM  , IPPROTO_UDP )  TCP =  // int sockid = socket (PF_INET,SOCK_STREAM,IPPROTO_TCP);

    {
        printf("Le socket n'a pas pu etre cree. Erreur : %d" , WSAGetLastError());
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(serverIP);
    server.sin_port = htons( 2018 );

    //PREPARATION DU PAQUET
    char buffer [packetsize];
    int i,t =0;
    for (i=0;i<(packetsize)-1;i++){
        buffer[i]= t+'0';
        t++;
        if (t == 100) {
            t =0;
        }
    }

    if (sendToServer(sockc, &server, buffer) !=-1) { //Si des données sont envoyées au serveur
        timer = fTimer(start, timer);//temps à l'envoi
//        printf("\nPAQUET ENVOYE AU SERVEUR: \nIP du serveur %s\nPORT du serveur: %d\n\n",  inet_ntoa(server.sin_addr), ntohs(server.sin_port));
//        printf("\nEN ATTENTE D'UNE REPONSE...");
        if ( recvfrom(sockc, responsebuffer, packetsize-1,0, ( SOCKADDR *)&response, &resplen) < 0){
//            printf("\nPROBLEME DE REPECTION DU PAQUET");
        }
        timer = fTimer(end, timer);//temps à la reception
//        printf("Data:  \ndonnees recues de  %s:%d\n\n", inet_ntoa(response.sin_addr), ntohs(response.sin_port));
        responsebuffer[packetsize] = '\0';
    }
    printf("\nPaquet perdu: %d - ", packetsize - strlen(responsebuffer));
    //printf("%s", responsebuffer);
    //printf("speed = %lf", calculateSpeed(timer,packetsize));

    //Fermeture du socket
    closesocket(sockc);
    //fin d'utilisation de la dll winsock2
    WSACleanup();

    return (int) (calculateSpeed(timer,packetsize)*1000);
}

float sendPacketToServer(int packetsize){ //max 65000
    float timer = 0;
    char start = 's';
    char end = 'e';

    //const char* serverIP = "192.168.134.132";
    const char* serverIP = "81.57.99.100"; //SERVEUR AURELIEN

    int sendvalue;

    startWSAS ();//WSAStartup(MAKEWORD(2, 2), &wsaData); //utilisation de la dll winsock

    //Variable de réseau
    SOCKET sockc;
    SOCKADDR_IN server = {0};
    SOCKADDR_IN response = {0};

    //Buffer de réponse du serveur
    char responsebuffer [packetsize];
    int resplen = sizeof response; //longueur de la réponse

    if((sockc = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)//socket(AF_INET , SOCK_DGRAM  , IPPROTO_UDP )  TCP =  // int sockid = socket (PF_INET,SOCK_STREAM,IPPROTO_TCP);

    {
        printf("Le socket n'a pas pu etre cree. Erreur : %d" , WSAGetLastError());
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(serverIP);
    server.sin_port = htons( 2018 );

    //PREPARATION DU PAQUET
    char buffer [packetsize];
    int i,t =0;
    for (i=0;i<(packetsize)-1;i++){
        buffer[i]= t+'0';
        t++;
        if (t == 100) {
            t =0;
        }
    }

    if (sendToServer(sockc, &server, buffer) !=-1) { //Si des données sont envoyées au serveur
        timer = fTimer(start, timer);//temps à l'envoi
//        printf("\nPAQUET ENVOYE AU SERVEUR: \nIP du serveur %s\nPORT du serveur: %d\n\n",  inet_ntoa(server.sin_addr), ntohs(server.sin_port));
//        printf("\nEN ATTENTE D'UNE REPONSE...");
        if ( recvfrom(sockc, responsebuffer, packetsize-1,0, ( SOCKADDR *)&response, &resplen) < 0){
//            printf("\nPROBLEME DE REPECTION DU PAQUET");
        }
        timer = fTimer(end, timer);//temps à la reception
//        printf("Data:  \ndonnees recues de  %s:%d\n\n", inet_ntoa(response.sin_addr), ntohs(response.sin_port));
        responsebuffer[packetsize] = '\0';
    }
    //printf("\nPaquet perdu: %d - ", packetsize - strlen(responsebuffer));
    //printf("%s", responsebuffer);
    //printf("speed = %lf", calculateSpeed(timer,packetsize));

    //Fermeture du socket
    closesocket(sockc);
    //fin d'utilisation de la dll winsock2
    WSACleanup();

    return calculateSpeed(timer,packetsize);
}

//

void maxThread() {
    int err = 0, count = 0;
    pthread_t tid;

    // on success, pthread_create returns 0 and
    // on Error, it returns error number
    // So, while loop is iterated until return value is 0
    while (err == 0)
    {
        err = pthread_create (&tid, NULL, thread, NULL);
        count++;
    }
    printf("Maximum number of thread within a Process"
                   " is : %d\n", count);
}

float findCPUFreuency(){
    long cpt = 0;
    float timer = 0;
    char start = 's';
    char end = 'e';

    timer = fTimer(start, timer);
    while (cpt != 1000000000){
        cpt++;
    }
    timer = fTimer(end, timer);

    return timer;

}

void memoryTest(){

    long resultat = 0;
    long long* mallocOK;

    do{
        mallocOK = malloc(sizeof(long long));
        resultat++;
    }while (mallocOK != NULL);
    if(resultat != 0){
        execl("C:\\Users\\Zero\\CLionProjects\\test\\cmake-build-debug\\tests.exe", "testmemory");
    }

}

void cpuFrequency(){
    int cpuInfo[4] = { 0, 0, 0, 0 };
    __cpuid(0x0,cpuInfo[0],cpuInfo[1],cpuInfo[2],cpuInfo[3]);
    if (cpuInfo[0] >= 0x16) {
        __cpuid(0x16,cpuInfo[0],cpuInfo[1],cpuInfo[2],cpuInfo[3]);

        /*
        Example 1
        Intel Core i7-6700K Skylake-H/S Family 6 model 94 (506E3)
        cpuInfo[0] = 0x00000FA0; //= 4000 MHz
        cpuInfo[1] = 0x00001068; //= 4200 MHz
        cpuInfo[2] = 0x00000064; //=  100 MHz

        Example 2
        Intel Core m3-6Y30 Skylake-U/Y Family 6 model 78 (406E3)
        cpuInfo[0] = 0x000005DC; //= 1500 MHz
        cpuInfo[1] = 0x00000898; //= 2200 MHz
        cpuInfo[2] = 0x00000064; //=  100 MHz

        Example 3
        Intel Core i5-7200 Kabylake-U/Y Family 6 model 142 (806E9)
        cpuInfo[0] = 0x00000A8C; //= 2700 MHz
        cpuInfo[1] = 0x00000C1C; //= 3100 MHz
        cpuInfo[2] = 0x00000064; //=  100 MHz
        */

        printf("EAX: 0x%08x EBX: 0x%08x ECX: %08x\r\n", cpuInfo[0], cpuInfo[1], cpuInfo[2]);
        printf("Processor Base Frequency:  %04d MHz\r\n", cpuInfo[0]);
        printf("Maximum Frequency:         %04d MHz\r\n", cpuInfo[1]);
        printf("Bus (Reference) Frequency: %04d MHz\r\n", cpuInfo[2]);
        printf("Test:                      %d test\r\n", cpuInfo[3]);
        printf("Amount of core(s):         %d\r\n",omp_get_max_threads());
    } else {
        printf("CPUID level 16h unsupported\r\n");
    }
}

int testMemory() {
    int x = 0, y = 0;

    printf("x: %d, y: %d\n", x, y);

    char* allocOK = "debut";

    while(allocOK != NULL){
        allocOK = malloc(sizeof(double long));
    }

    pthread_t inc_ram_thread;
    pthread_t inc_y_thread;

    pthread_create(&inc_ram_thread, NULL, inc_ram, &x);
    pthread_create(&inc_y_thread, NULL, inc_ram, &y);

    pthread_join(inc_ram_thread, NULL);
    pthread_join(inc_y_thread, NULL);

    printf("x: %d, y: %d\n", x, y);

    return 0;
}

int test4GB(){
    size_t sz = 400000000;
    char *a = malloc(sz);

    memset(a, 'a', sz);

    printf("%.4s", &a[sz-5]);

    sleep(10);

    return 0;
}

int numBlocks(int nbLines,char* fileToRead){
    FILE *file;
    int numLines = 0;
    int numBlocks = 0;
    int ch = 0;

    file = fopen(fileToRead, "r");
    if (file == NULL)
        exit (EXIT_FAILURE);
    while ( ch != EOF ){
        ch = fgetc( file );
        if( ch == '\n' )
            numLines++;
    }
    while (numLines > 0){
        numBlocks++;
        numLines = numLines - nbLines;
    }
    fclose(file);
    return numBlocks;
}

char** readFileToBuffer(int nbBlocks, int nbLines, char* buffer[],char* fileToRead){
    FILE *file;
    int ch = 0;
    int numLines = 0;
    int i, j = 0;

    buffer = malloc(sizeof(double long)*nbBlocks);
    if (buffer == NULL)
        exit(EXIT_FAILURE);
    for( i = 0; i < nbBlocks; i++){
        buffer[i] = malloc(8192 * sizeof(char));
        if (buffer[i] == NULL)
            exit(EXIT_FAILURE);
    }

    file = fopen(fileToRead, "r");
    if (file == NULL)
        exit (EXIT_FAILURE);
    i = 0;
    while ( ch != EOF ){
        ch = fgetc( file );
        if( ch == '\n' ){
            numLines++;
            buffer[i][j] = (char) ch;
            j++;
            if(numLines == nbLines){
                buffer[i][j] = '\0';
                i++;
                numLines = 0;
                j=0;
            }
        }else if (ch > 0){
            buffer[i][j] = (char) ch;
            j++;
        }
    }
    fclose (file);
    return buffer;
}

int pthreadtest() {

    int x = 0, y = 0;

/* show the initial values of x and y */
    printf("x: %d, y: %d\n", x, y);

/* this variable is our reference to the second thread */
    pthread_t inc_x_thread;
    pthread_t inc_y_thread;

/* create a second thread which executes inc_x(&x) */
    if(pthread_create(&inc_x_thread, NULL, inc_x, &x)){

        fprintf(stderr, "Error creating thread\n");
        return 1;

    }

    if(pthread_create(&inc_y_thread, NULL, inc_y, &y)){

        fprintf(stderr, "Error creating thread\n");
        return 1;

    }

/* wait for the second thread to finish */
    if(pthread_join(inc_x_thread, NULL)) {

        fprintf(stderr, "Error joining thread\n");
        return 2;

    }
    if(pthread_join(inc_y_thread, NULL)) {

        fprintf(stderr, "Error joining thread\n");
        return 2;

    }


/* show the results - x is now 100 thanks to the second thread */
    printf("x: %d, y: %d\n", x, y);

    return 0;

}

int test() {
    int x = 0, y = 0;

    printf("x: %d, y: %d\n", x, y);

    pthread_t inc_x_thread;
    pthread_t inc_y_thread;

    pthread_create(&inc_x_thread, NULL, inc_x, &x);
    pthread_create(&inc_y_thread, NULL, inc_y, &y);

    pthread_join(inc_x_thread, NULL);
    pthread_join(inc_y_thread, NULL);

    printf("x: %d, y: %d\n", x, y);

    return 0;
}

void *inc_ram(void *x_void_ptr) {

/* increment x to 100 */
    int *x_ptr = (int *)x_void_ptr;
    char* allocOK = "debut";

    while(allocOK != NULL){
        allocOK = malloc(sizeof(double long));
        if (!allocOK){
            sleep(1);
            allocOK = (char*) 1;
        }

    }

    while(++(*x_ptr) < 100){
        printf("x");
    };

    printf("x increment finished\n");

/* the function must return something - NULL will do */
    return NULL;

}

void *inc_x(void *x_void_ptr) {

/* increment x to 100 */
    int *x_ptr = (int *)x_void_ptr;
    while(++(*x_ptr) < 100){
        printf("x");
    };

    printf("x increment finished\n");

/* the function must return something - NULL will do */
    return NULL;

}

void *inc_y(void *y_void_ptr) {

/* increment x to 100 */
    int *y_ptr = (int *)y_void_ptr;
    while(++(*y_ptr) < 100){
        printf("y");
    };

    printf("y increment finished\n");

/* the function must return something - NULL will do */
    return NULL;

}

void *thread ( void *vargp){     }
