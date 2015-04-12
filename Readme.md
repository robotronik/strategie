# Stratégie
Ce dépôt contiendra le code et les fichiers pour la stratégie des robots
(Table, mouvements, etc)

## Le dossier LowLevel
Sachant qu'il y a des cas limites (on ne peut pas ouvrir les 2 bras en même
temps), le fichier actionneurs.c sert de "gestionnaire d'actionneurs".

Les fonctions du dossier LowLevel ne doivent être appelées QUE depuis ce
fichier, et bien sûr uniquement si celui-ci a déterminé qu'il n'y a pas de
conflits entre les actionneurs ou avec les règles.
