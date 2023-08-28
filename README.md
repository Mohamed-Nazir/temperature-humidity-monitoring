# temperature-humidity-monitor
**Projet de Surveillance de Température et d'Humidité avec Arduino et Firebase**

Ce projet consiste en la création d'un système de surveillance de la température et de l'humidité à l'aide d'un capteur DHT11, d'une carte Arduino et de l'intégration avec la base de données en temps réel Firebase. Le capteur DHT11 mesure les variations de température et d'humidité dans l'environnement, puis les données sont transmises à la base de données Firebase via une connexion WiFi.

**Configuration Matérielle Requise :**
- Une carte Arduino compatible (ex. ESP32, ESP8266)
- Un capteur DHT11 pour mesurer la température et l'humidité
- Accès à un réseau WiFi
- Compte Firebase avec projet créé et les informations d'authentification

**Configuration Logicielle Requise :**
- IDE Arduino installé
- Bibliothèques nécessaires installées :
  - WiFi
  - Firebase ESP Client
  - DHT Sensor
- Accès aux identifiants WiFi et Firebase (SSID, mot de passe, clé API)

**Fonctionnement :**

1. **Inclusions de Bibliothèques :** Les bibliothèques requises sont incluses pour permettre la communication WiFi, l'intégration Firebase, et la gestion du capteur DHT.

2. **Définition de Constantes :** Différentes constantes sont définies, comme le numéro de broche du capteur DHT, le type de capteur, les informations de connexion WiFi et Firebase.

3. **Fonction de Configuration (`setup`) :**
   - Initialisation de la communication série (pour les messages de débogage).
   - Initialisation du capteur DHT.
   - Connexion au réseau WiFi.
   - Configuration de Firebase avec la clé API et l'URL de la base de données.
   - Initialisation de Firebase avec la configuration et l'authentification.
   - Récupération de l'UID de l'utilisateur pour l'authentification.

4. **Fonction en Boucle (`loop`) :**
   - Lecture de la température et de l'humidité à partir du capteur DHT.
   - Vérification de la disponibilité de la connexion Firebase et de l'intervalle d'envoi des données (toutes les 5 secondes).
   - Si les conditions sont remplies :
     - Envoi des données de température et d'humidité à la base de données Firebase sous des chemins spécifiés.
     - Affichage de messages de succès ou d'échec avec les données pertinentes et les chemins.
     - Incrémentation d'un compteur.
     - (Ligne commentée pour envoyer le compteur à la base de données.)

**Utilisation :**

1. Connectez votre capteur DHT11 à la broche spécifiée (15 dans cet exemple) sur votre carte Arduino.
2. Configurez vos informations de connexion WiFi (SSID et mot de passe) et les informations d'authentification Firebase (clé API, URL de la base de données, email et mot de passe utilisateur).
3. Téléversez le code sur votre carte Arduino à l'aide de l'IDE Arduino.
4. Ouvrez le moniteur série pour afficher les messages de débogage et vérifier le fonctionnement du projet.
5. Les données de température et d'humidité seront envoyées à la base de données Firebase en temps réel.

Assurez-vous de vérifier la correspondance entre les broches utilisées dans le code et celles utilisées sur votre carte Arduino, ainsi que les mises à jour éventuelles des bibliothèques Firebase et DHT.
