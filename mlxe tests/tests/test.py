import ctypes
import os

# Demander le PID du processus et l'adresse mémoire à l'utilisateur
pid = int(input("Entrez le PID du processus : "))
adresse_str = input("Entrez l'adresse mémoire (ex: 0x7ffc12345678): ")
adresse = int(adresse_str, 16)

# Ce code est spécifique à Linux
libc = ctypes.CDLL('libc.so.6')

# Constantes
PROT_READ = 0x1
PROT_WRITE = 0x2
MAP_SHARED = 0x01
MAP_PRIVATE = 0x02

# Ouverture du processus
with open(f"/proc/{pid}/mem", "rb+") as mem_file:
    # Déplacer le curseur à l'adresse mémoire spécifiée
    mem_file.seek(adresse)

    # Lire la valeur actuelle à l'adresse mémoire
    valeur_actuelle = ctypes.c_int()
    mem_file.readinto(valeur_actuelle)
    print(f"Valeur actuelle à l'adresse {adresse_str}: {valeur_actuelle.value}")

    # Modifier la valeur de la variable
    nouvelle_valeur = ctypes.c_int(100)

    # Déplacer le curseur à l'adresse mémoire spécifiée
    mem_file.seek(adresse)

    # Écrire la nouvelle valeur à l'adresse mémoire
    mem_file.write(nouvelle_valeur)
    print(f"Nouvelle valeur à l'adresse {adresse_str}: {nouvelle_valeur.value}")
