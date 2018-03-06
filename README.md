# HavingGreatFunWithC

Description: Application permettant de faire des benchmark* de divers composants. Le but est de récupérer par l'API Windows les information système nécéssaire, les stocké et s'en servir pour faire des tests. Des tests sont envisagable sur la mémoire vive (charge maximum de stockage + vitesse), sur le CPU (nb d'instruction réel selon un temps + prise en charge du multi-thread) sur la vitesse de la mémoire ROM (temps d'écriture, lecture). D'autres options sont envisageable si le projet avance bien, par exemple: réseau, graphique, sonore, température interne et autres.  

*Un benchmark* est un test visant a connaitre les performances d'un composant interne.  

Système requis: Windows  

API: Oui Détails: Au minimum windows.h, math.h et time.h et une autre pour un accès BDD.  

Interface graphique: Oui 

Détails: Non choisi pour le moment  Exploitation de fichier: Oui Détails:  - config.ini => prise en compte de "profil utilisateur" ce dernier contiendras des chose basique tel que sa dernière visite, ses derniers score, la liste de ses composant, les derniers test utilisers, la langue utilisé, son pseudo, etc - scenario => suite de test sur plusieurs composant pouvant être sauvgardé afin d'avoir un "scénario typique" pour faire des tests sur plusieurs machine (par exemple) - stats globale => fichier mis à jour depuis un serveur regroupant les moyenne des tests ou les scores d'autres utilisateurs
