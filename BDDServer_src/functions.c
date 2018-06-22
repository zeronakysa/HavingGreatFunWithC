#include "functions.h"

void createDatabase() {
    char *createUserTableRequest = "CREATE TABLE IF NOT EXISTS `user` (`id` int(11) NOT NULL AUTO_INCREMENT,`config_id` int(11) DEFAULT NULL,`username` varchar(60) NOT NULL,`creation_date` DATETIME,PRIMARY KEY (`id`),UNIQUE KEY `username` (`username`),UNIQUE KEY `config_id` (`config_id`))";
    char *createConfigTableRequest = "CREATE TABLE IF NOT EXISTS `user_config` ( `id` int(11) NOT NULL AUTO_INCREMENT,`user_id` int(11) NOT NULL,`totalVirtualMem` double DEFAULT NULL,`totalPhysicalMem` double DEFAULT NULL, `OEM_id` int(11) DEFAULT NULL,`nbProcessors` int(11) DEFAULT NULL,`pageSize` int(11) DEFAULT NULL,`processorType` int(11) DEFAULT NULL,`minAppAdress` varchar(8) DEFAULT NULL,`maxAppAdress` varchar(8) DEFAULT NULL,`activeProcMask` int(11) DEFAULT NULL,`procBaseFrequency` int(11) DEFAULT NULL,`maxFrequency` int(11) DEFAULT NULL,`BusFrequency` int(11) DEFAULT NULL,`nbCores` int(11) DEFAULT NULL, PRIMARY KEY (`id`),UNIQUE KEY `user_id` (`user_id`)) ";
    char *createResultTableRequest = "CREATE TABLE IF NOT EXISTS `result` (`id` int(11) NOT NULL AUTO_INCREMENT,`user_id` int(11) NOT NULL,`cpu_test` int(11) DEFAULT NULL,`ram_test` int(11) DEFAULT NULL,`write_test` int(11) DEFAULT NULL,`network_test` int(11) DEFAULT NULL,`global_test` int(11) DEFAULT NULL,PRIMARY KEY (`id`))";

    char databaseName[50] = {0};

    puts("Veuillez entrer un nom de base de donnees : ");
    fflush(stdin);
    fgets(databaseName, 50, stdin);

    if (strlen(databaseName) < 49) {
        databaseName[strlen(databaseName) -1] = '\0';

    }

    char createDatabaseRequest[250] = {0};

    MYSQL *mysql;
    mysql = mysql_init(NULL);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    if(mysql_real_connect(mysql,"localhost","root","",NULL,0,NULL,0)) {

        //Création de la requête
        sprintf(createDatabaseRequest, "CREATE DATABASE IF NOT EXISTS %s", databaseName);

        printf("%s", createDatabaseRequest);

        //exécution de la requête
        mysql_query(mysql, createDatabaseRequest);

        //Fermeture de MySQL
        mysql_close(mysql);
    } else {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }

    MYSQL *mysql2;
    mysql2 = mysql_init(NULL);
    mysql_options(mysql2,MYSQL_READ_DEFAULT_GROUP,"option");

    if(mysql_real_connect(mysql2,"localhost","root","",databaseName,0,NULL,0)) {

        //exécution de la requête
        mysql_query(mysql2, createUserTableRequest);
        mysql_query(mysql2, createConfigTableRequest);
        mysql_query(mysql2, createResultTableRequest);

        printf("%s", createUserTableRequest);
        printf("%s", createConfigTableRequest);
        printf("%s", createResultTableRequest);

        //Fermeture de MySQL
        mysql_close(mysql2);
    } else {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}

