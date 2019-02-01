#include<RTClib.h>
#include<Wire.h>
#include<ezTime.h>

//Declaration d'une variable de type RTC_DS3231 qui va permettre de manipuler le temps systéme retourné par l'arduino
RTC_DS3231 rtc;

//Cette fonction calcule puis retourne la date du dernier dimanche du mois passé en paramétre à l'heure passée en paramétre 0 minutes et 0 secondes
DateTime date_du_dernier_dimanche_du_mois_donne(uint16_t annee, uint8_t mois, uint8_t heure)
{
     //Déclaration des variables necessaires: la variable date_tm (de type DateTime) et mois_suivant (de type uint8_t, qui correspond au mois suivant celui passé en paramétre)
     DateTime date_tm;
     uint8_t mois_suivant = mois + 1;

     //la structure date_tm est modifiée pour correspondre au 1er du mois suivant de l'année annee (passée en paramétre) à heure heures (passée en paramétre) 0 minutes et 0 secondes
     date_tm = DateTime(annee, mois_suivant, (uint8_t)1, heure, (uint8_t)0, (uint8_t)0);

     //Ici, le programme procéde à une boucle infinie
     while(1){

              //On fait reculer d'un jour la valeur contenue dans la variable date_tm avant de l'affecter à ce dernier
              date_tm = date_tm - TimeSpan(1,0,0,0);

              //Si la date contenue dans la variable date_tm (DateTime) correspond au dernier dimanche (dayOfTheWeek) du mois passé en paramétre (month), on quitte définitivement la boucle
              if(date_tm.dayOfTheWeek() == 0 && date_tm.month() == mois)
              {
                      break;
              }
     }

     //On retourne alors le resultat obtenu sous forme d'un DateTime
     return date_tm;
}

//Cette fonction calcule puis retourne la date du deuxieme dimanche du mois passé en paramétre à l'heure passée en paramétre 0 minutes et 0 secondes
DateTime date_du_deuxieme_dimanche_du_mois_donne(uint16_t annee, uint8_t mois, uint8_t heure)
{
     //Déclaration de la variable date_tm (de type DateTime) et i (de type int)
     DateTime date_tm;
     int i;

     //la structure date_tm est modifiée pour correspondre au 1er du mois mois (passé en paramétre) de l'année annee (passée en paramétre) à heure heures (passée en paramétre) 0 minutes et 0 secondes
     date_tm = DateTime(annee, mois, (uint8_t)1, heure, (uint8_t)0, (uint8_t)0);

     //Si le jour de la semaine est dimanche, alors la variable i est initialisée à la valeur 1
     if(date_tm.dayOfTheWeek() == 0)
     {
         i = 1;
     }
     //Dans le cas contraire, la variable i est initialisée à la valeur 0
     else
     {
         i = 0;
     }

     //Ici, le programme procéde à une boucle infinie
     while(1){

              //On fait avancer d'un jour la valeur contenue dans la variable date_tm avant de l'affecter à ce dernier
              date_tm = date_tm + TimeSpan(1,0,0,0);

              //Si la date contenue dans la variable date_tm (DateTime) correspond au deuxieme dimanche (dayOfTheWeek) du mois passé en paramétre (month), on quitte définitivement la boucle
              if(date_tm.dayOfTheWeek() == 0 && date_tm.month() == mois && i == 1)
              {
                      break;
              }
              //Dans le cas contraire
              else
              {
                      //
                      if(date_tm.dayOfTheWeek() == 0 && date_tm.month() == mois)
                      {
                          i = i + 1;
                      }
              }
      }

      //On retourne alors le resultat obtenu sous forme d'un DateTime
      return date_tm;
}

//Cette fonction calcule puis retourne la date du premier dimanche du mois passé en paramétre à l'heure passée en paramétre 0 minutes et 0 secondes
DateTime date_du_premier_dimanche_du_mois_donne(uint16_t annee, uint8_t mois, uint8_t heure)
{
      //Déclaration de la variable date_tm (de type DateTime) et i (de type int)
      DateTime date_tm;
      int i;

      //la structure date_tm est modifiée pour correspondre au 1er du mois mois (passé en paramétre) de l'année annee (passée en paramétre) à heure heures (passée en paramétre) 0 minutes et 0 secondes
      date_tm =  DateTime(annee, mois, (uint8_t)1, heure, (uint8_t)0, (uint8_t)0);

      //Ici, le programme procéde à une boucle infinie
      while(1){

          //Si la date contenue dans la variable date_tm (DateTime) correspond au premier dimanche (dayOfTheWeek) du mois passé en paramétre (tm_mon), on quitte définitivement la boucle
          if(date_tm.dayOfTheWeek() == 0 && date_tm.month() == mois)
          {
                break;
          }

          //On fait avancer d'un jour la valeur contenue dans la variable date_tm avant de l'affecter à ce dernier
          date_tm = date_tm + TimeSpan(1,0,0,0);
      }

      //On retourne alors le resultat obtenu sous forme d'un DateTime
      return date_tm;
}

//Cette fonction permet de calculer le decallage horaire de Canberra (Australie) avec l'heure française
int calcul_du_decalage_avec_canberra(DateTime date)
{
        //Définition des variables nécessaires au calcul du décalage
        uint32_t aujourdhui = date.unixtime();
        uint32_t date_passage_heure_d_ete_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)10 ,(uint8_t)3).unixtime();
        uint32_t date_passage_heure_d_ete_australie = date_du_premier_dimanche_du_mois_donne(date.year(), (uint8_t)10, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_australie = date_du_premier_dimanche_du_mois_donne(date.year(), (uint8_t)4, (uint8_t)3).unixtime();

        //Calcul du décalage en fonction de l'interval de temps dans lequel est la valeur passée en paramétre
        if((aujourdhui >= date_passage_heure_d_ete_europe && aujourdhui < date_passage_heure_d_hiver_australie) || (aujourdhui >= date_passage_heure_d_ete_australie && 
aujourdhui < date_passage_heure_d_hiver_europe))
        {
                return 1;
        }
        else if(aujourdhui >= date_passage_heure_d_hiver_australie && aujourdhui < date_passage_heure_d_ete_australie)
        {
                return 2;
        }
        else
        {
                return 0;
        }
}

//Cette fonction permet de calculer le decallage horaire de Canberra (Australie) avec l'heure française
int calcul_du_decalage_avec_wellington(DateTime date)
{
        //Définition des variables nécessaires au calcul du décalage
        uint32_t aujourdhui = date.unixtime();
        uint32_t date_passage_heure_d_ete_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)10 ,(uint8_t)3).unixtime();
        uint32_t date_passage_heure_d_ete_nouvelle_zelande = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)9, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_nouvelle_zelande = date_du_premier_dimanche_du_mois_donne(date.year(), (uint8_t)4, (uint8_t)3).unixtime();

        //Calcul du décalage en fonction de l'interval de temps dans lequel est la valeur passée en paramétre
        if((aujourdhui >= date_passage_heure_d_ete_europe && aujourdhui < date_passage_heure_d_hiver_nouvelle_zelande) || (aujourdhui >= date_passage_heure_d_ete_nouvelle_zelande && 
aujourdhui < date_passage_heure_d_hiver_europe))
        {
                return 1;
        }
        else if(aujourdhui >= date_passage_heure_d_hiver_nouvelle_zelande && aujourdhui < date_passage_heure_d_ete_nouvelle_zelande)
        {
                return 2;
        }
        else
        {
                return 0;
        }
}

//Cette fonction permet de calculer le decallage horaire de Los Angeles, de New York City (USA) et d'Ottawa (Canada) avec l'heure française
int calcul_du_decalage_avec_l_amerique_du_nord(DateTime date)
{
        //Définition des variables nécessaires au calcul du décalage
        uint32_t aujourdhui = date.unixtime();
        uint32_t date_passage_heure_d_ete_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)10 ,(uint8_t)3).unixtime();
        uint32_t date_passage_heure_d_ete_usa = date_du_deuxieme_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_usa = date_du_premier_dimanche_du_mois_donne(date.year(), (uint8_t)11, (uint8_t)2).unixtime();

        //Calcul du décalage en fonction de l'interval de temps dans lequel est la valeur passée en paramétre
        if((aujourdhui >= date_passage_heure_d_ete_usa && aujourdhui < date_passage_heure_d_ete_europe) || (aujourdhui >= date_passage_heure_d_hiver_europe && aujourdhui < date_passage_heure_d_hiver_usa))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

//Cette fonction permet de calculer le decallage horaire de Londres avec l'heure française
int calcul_du_decallage_avec_la_grande_bretagne(DateTime date)
{
        //Définition des variables nécessaires au calcul du décalage
        uint32_t aujourdhui = date.unixtime();
        uint32_t date_passage_heure_d_ete_france = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_france = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)10 ,(uint8_t)3).unixtime();
        uint32_t date_passage_heure_d_ete_uk = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)1).unixtime();
        uint32_t date_passage_heure_d_hiver_uk = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)10 ,(uint8_t)2).unixtime();

        //Calcul du décalage en fonction de l'interval de temps dans lequel est la valeur passée en paramétre
        if(((aujourdhui > date_passage_heure_d_ete_uk) && (aujourdhui < date_passage_heure_d_ete_france)) || ((aujourdhui > date_passage_heure_d_hiver_uk) && (aujourdhui < date_passage_heure_d_hiver_france)))
        {
              return 1;
        }
        else
        {
            return 0;
        }
}

//Cette fonction permet de déterminer si il faut (ou non) en fonction du changement d'heure ajouter une heure (ou non) pour le calcul des fuseaux horaires de Pekin, Tokyo, Seoul, Moscou, et Vladivostok
int application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(DateTime date)
{
        //On calcul l'horaire de changement de l'heure d'été et de changement de l'heure d'hiver, et on stocke ces valeurs dans des variables de type time_t (timestamp) pour prrocéder aux calculs
        DateTime ete = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)2);
        DateTime hiver = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)10 ,(uint8_t)3);

        uint32_t date_timestamp = date.unixtime();
        uint32_t ete_timestamp = ete.unixtime();
        uint32_t hiver_timestamp = hiver.unixtime();
        //Ici, on vérifie (grace à des comparaison de valeurs entre timestamp) que la date se situe entre ete et hiver (inclus)
        //Si la date passée en paramétre se situe entre l'horaire de changement de l'heure d'été et celui de changement de l'heure d'hiver, 0 est retourné (il y à aucune heure à ajouter)
        if(date_timestamp >= ete_timestamp && date_timestamp <= hiver_timestamp)
        {
                return 0;
        }
        //Sinon, 1 est retourné (il faudra ajouter une heure)
        else
        {
                return 1;
        }
}

//Cette fonction permet de calculer le decallage horaire de Santiago du Chili (Chili) avec l'heure française
int calcul_du_decalage_avec_le_chili(DateTime date)
{
        //Définition des variables nécessaires au calcul du décalage
        uint32_t aujourdhui = date.unixtime();
        uint32_t date_passage_heure_d_ete_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)3, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_europe = date_du_dernier_dimanche_du_mois_donne(date.year(), (uint8_t)10 ,(uint8_t)3).unixtime();
        uint32_t date_passage_heure_d_ete_chili = date_du_deuxieme_dimanche_du_mois_donne(date.year(), (uint8_t)8, (uint8_t)2).unixtime();
        uint32_t date_passage_heure_d_hiver_chili = date_du_deuxieme_dimanche_du_mois_donne(date.year(), (uint8_t)5, (uint8_t)2).unixtime();

        //Calcul du décalage en fonction de l'interval de temps dans lequel est la valeur passée en paramétre
        if((aujourdhui >= date_passage_heure_d_ete_europe && aujourdhui < date_passage_heure_d_hiver_chili) || (aujourdhui >= date_passage_heure_d_ete_chili && aujourdhui < date_passage_heure_d_hiver_europe))
        {
                return 1;
        }
        else if(aujourdhui >= date_passage_heure_d_hiver_chili && aujourdhui < date_passage_heure_d_ete_chili && aujourdhui > date_passage_heure_d_ete_europe)
        {
                return 0;
        }
        else
        {
                return 2;
        }
}

//Cette fonction permet de déterminer si il faut (ou non) en fonction du changement d'heure ajouter une heure (ou non) pour le calcul des fuseaux horaires
DateTime application_de_l_heure_d_ete_pour_l_heure_courante(DateTime date_tm)
{
  //On calcul l'horaire de changement de l'heure d'été et de changement de l'heure d'hiver, et on stocke ces valeurs dans des variables de type uint32_t (timestamp) pour prrocéder aux calculs
  uint32_t ete = date_du_dernier_dimanche_du_mois_donne(date_tm.year(), (uint8_t)3, (uint8_t)2).unixtime();
  uint32_t hiver = date_du_dernier_dimanche_du_mois_donne(date_tm.year(), (uint8_t)10 ,(uint8_t)3).unixtime();
  uint32_t date = date_tm.unixtime();

  //Variable (de type DateTime) qui contient le resultat à retourner
  DateTime resultat_tm;

  //Ici, on vérifie (grace à des comparaison de valeurs entre timestamp) que la date se situe entre ete et hiver (inclus)
  //Si la date passée en paramétre se situe entre l'horaire de changement de l'heure d'été et celui de changement de l'heure d'hiver, 1 est retourné (il y à une heure à ajouter pour etre à l'heure)
  if(date >= ete && date <= hiver)
  {
              //return 1;
              resultat_tm = DateTime(date_tm.year(),  
                                     date_tm.month(), 
                                     date_tm.day(), 
                                     date_tm.hour() + 1, 
                                     date_tm.minute(), 
                                     date_tm.second());
  }
  //Sinon, 1 est retourné (il faudra ajouter une heure)
  else
  {
              resultat_tm = date_tm;
  }

  //La variable resultat_tm (de type DateTime) est retournée
  return resultat_tm;
}

//Cette fonction permet de calculer et d'afficher les horaires 
void calcul_et_affichage_horaire(DateTime horaire, String ville)
{
        //Declaration des variables
        String jour_semaine;
        String mois;

        //Definition du mois en court en fonction du champs tm_mon de la structure tm
        switch(horaire.month())
        {
                case 1: mois = "Janvier"; break;
                case 2: mois = "Fevrier"; break;
                case 3: mois = "Mars"; break;
                case 4: mois = "Avril"; break;
                case 5: mois = "Mai"; break;
                case 6: mois = "Juin"; break;
                case 7: mois = "Juillet"; break;
                case 8: mois = "Aout"; break;
                case 9: mois = "Septembre"; break;
                case 10: mois = "Octobre"; break;
                case 11: mois = "Novembre"; break;
                case 12: mois = "Decembre"; break;
        }       

        //Definition du jour de la semaine en fonction du champs tm_wday de la structure tm
        switch(horaire.dayOfTheWeek())
        {
                case 0: jour_semaine = "Dimanche"; break;
                case 1: jour_semaine = "Lundi"; break;
                case 2: jour_semaine = "Mardi"; break;
                case 3: jour_semaine = "Mercredi"; break;
                case 4: jour_semaine = "Jeudi"; break;
                case 5: jour_semaine = "Vendredi"; break;
                case 6: jour_semaine = "Samedi"; break;
        }

        //Affichage de l'horaire
        Serial.println(ville + " : " + String(horaire.hour()) + ":" + String(horaire.minute()) + ":" + String(horaire.second()) + " - " + jour_semaine + " " + String(horaire.day()) + " " + mois + " " + String(horaire.year()));
}

//Fonction de test pour les calculs d'horaires mises au point dans le fichier heure_monde.c
void affichage_de_l_horloge(DateTime date)
{     
        /*Calcul des horaires de différents villes du monde et affectation de la valeur calculée à une variable correspondante*/
        DateTime heure_los_angeles = date - TimeSpan((int16_t) 0, (int8_t) 9 - calcul_du_decalage_avec_l_amerique_du_nord(date), (int8_t) 0, (int8_t) 0);//Los Angeles
        DateTime heure_de_nyc = date - TimeSpan((int16_t) 0, (int8_t) 6 - calcul_du_decalage_avec_l_amerique_du_nord(date), (int8_t) 0, (int8_t) 0);//New York City
        DateTime heure_d_ottawa = date - TimeSpan((int16_t) 0, (int8_t) 6 - calcul_du_decalage_avec_l_amerique_du_nord(date), (int8_t) 0, (int8_t) 0);//Ottawa
        DateTime heure_de_phoenix = date - TimeSpan((int16_t) 0, (int8_t) 9 - application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Phoenix
        DateTime heure_moscou = date + TimeSpan((int16_t) 0, (int8_t) 1 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Moscou
        DateTime heure_vladivostok = date + TimeSpan((int16_t) 0, (int8_t) 8 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Vladivostok
        DateTime heure_canberra = date + TimeSpan((int16_t) 0, (int8_t) 10 - calcul_du_decalage_avec_canberra(date), (int8_t) 0, (int8_t) 0);//Canberra
        DateTime heure_londres = date - TimeSpan((int16_t) 0, (int8_t) 1 - calcul_du_decallage_avec_la_grande_bretagne(date), (int8_t) 0, (int8_t) 0);//Londres
        DateTime heure_johannesburg = date + TimeSpan((int16_t) 0, (int8_t) 0 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Johannesburg
        DateTime heure_windhoek = date + TimeSpan((int16_t) 0, (int8_t) 0 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Windhoek
        DateTime heure_buenos_aires = date - TimeSpan((int16_t) 0, (int8_t) 5 - application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Buenos Aires
        DateTime heure_antananarivo = date + TimeSpan((int16_t) 0, (int8_t) 1 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Antananarivo
        DateTime heure_lima = date - TimeSpan((int16_t) 0, (int8_t) 7 - application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Lima
        DateTime heure_wellington = date + TimeSpan((int16_t) 0, (int8_t) 12 - calcul_du_decalage_avec_wellington(date), (int8_t) 0, (int8_t) 0);//Wellington
        DateTime heure_santiago_chili = date - TimeSpan((int16_t) 0, (int8_t) 6 - calcul_du_decalage_avec_le_chili(date), (int8_t) 0, (int8_t) 0);//Santiago du Chili
        DateTime heure_seoul = date + TimeSpan((int16_t) 0, (int8_t) 7 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Seoul
        DateTime heure_tokyo = date + TimeSpan((int16_t) 0, (int8_t) 7 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Tokyo
        DateTime heure_pekin = date + TimeSpan((int16_t) 0, (int8_t) 6 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(date), (int8_t) 0, (int8_t) 0);//Pekin

        /*Affichage des différents horiares calculés à coté des villes correspondantes*/        
        Serial.println("\n");
        calcul_et_affichage_horaire(date, "Perpignan");
        calcul_et_affichage_horaire(heure_los_angeles, "Los Angeles");
        calcul_et_affichage_horaire(heure_de_nyc, "New York City");
        calcul_et_affichage_horaire(heure_d_ottawa, "Ottawa");
        calcul_et_affichage_horaire(heure_de_phoenix, "Phoenix");
        calcul_et_affichage_horaire(heure_moscou, "Moscou");
        calcul_et_affichage_horaire(heure_vladivostok, "Vladivostok");
        calcul_et_affichage_horaire(heure_canberra, "Canberra");
        calcul_et_affichage_horaire(heure_londres, "Londres");
        calcul_et_affichage_horaire(heure_johannesburg, "Johannesburg");
        calcul_et_affichage_horaire(heure_windhoek, "Winhoek");
        calcul_et_affichage_horaire(heure_buenos_aires, "Buenos Aires");
        calcul_et_affichage_horaire(heure_antananarivo, "Antananarivo");
        calcul_et_affichage_horaire(heure_lima, "Lima");
        calcul_et_affichage_horaire(heure_wellington, "Wellington");
        calcul_et_affichage_horaire(heure_santiago_chili, "Santiago du Chili");
        calcul_et_affichage_horaire(heure_seoul, "Seoul");
        calcul_et_affichage_horaire(heure_tokyo, "Tokyo");
        calcul_et_affichage_horaire(heure_pekin, "Pekin");
        Serial.println("\n");
}

//Cette fonction permet de prendre en compte le décallage observé sur le RTC (3 minutes et 22 secondes)
DateTime renvoie_du_temps_courant_avec_prise_en_compte_du_decallage_rtc()
{
  return rtc.now() + TimeSpan((int16_t) 0, (int8_t) 0, (int8_t) 3, (int8_t) 22);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Petit message de démarage
  Serial.println("Début du test, vous pouvez commencer....\n");
  
  //Déclaration de la variable date de type DateTime (pour les tests)
  DateTime date;

  //Concernant le RTC
  if(! rtc.begin())
  {
    Serial.println("Impossible d'initialiser RTC");
    while(1);
  }

  if (rtc.lostPower()) {
   //Sets the code compilation time to RTC DS3231
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 }

 //
 DateTime la = application_de_l_heure_d_ete_pour_l_heure_courante(renvoie_du_temps_courant_avec_prise_en_compte_du_decallage_rtc());

 //Tests effectués sur les décallages horaires
 Serial.println("Voici le décallage de Santiago du Chili: -" + String(6 - calcul_du_decalage_avec_le_chili(la)));
 Serial.println("Voici le décallage de Canberra: +" + String(10 - calcul_du_decalage_avec_canberra(la)));
 Serial.println("Voici le décallage de Londres: -" + String(1 - calcul_du_decallage_avec_la_grande_bretagne(la)));
 Serial.println("Voici le décalage de Johannesburg : +" + String(0 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Windhoek : +" + String(0 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Buenos Aires: -" +  String(5 - application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le decalage de Antananarivo: +" + String(1 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Lima : -" + String(7 - application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Wellington : +" + String(12 - calcul_du_decalage_avec_wellington(la)));
 Serial.println("Voici le décalage de Los Angeles : -" + String(9 - calcul_du_decalage_avec_l_amerique_du_nord(la)));
 Serial.println("Voici le décalage de New York City : -" + String(6 - calcul_du_decalage_avec_l_amerique_du_nord(la)));
 Serial.println("Voici le décalage de Phoenix: -" +  String(9 - application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le decalage de Ottawa: -" + String(6 - calcul_du_decalage_avec_l_amerique_du_nord(la)));
 Serial.println("Voici le décalage de Moscou : +" + String(1 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Vladivostok : +" + String(8 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Seoul : +" + String(7 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Tokyo: +" + String(7 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));
 Serial.println("Voici le décalage de Pekin : +" + String(6 + application_de_l_heure_d_ete_pour_les_fuseaux_sans_changements(la)));

 //Sauts de lignes (x3)
 Serial.println("\n\n\n");
 
 //Calcul du passage à l'heure d'été pour l'Europe
 date = date_du_dernier_dimanche_du_mois_donne(la.year(), (uint8_t)3, (uint8_t)2);
 Serial.println("heure d'hiver -> heure d'ete pour l'Europe: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'hiver pour l'Europe
 date = date_du_dernier_dimanche_du_mois_donne(la.year(), (uint8_t)10 ,(uint8_t)3);
 Serial.println("heure d'ete -> heure d'hiver pour l'Europe: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

  //Calcul du passage à l'heure d'été pour l'Amérique du Nord
 date = date_du_deuxieme_dimanche_du_mois_donne(la.year(), (uint8_t)3, (uint8_t)2);
 Serial.println("heure d'hiver -> heure d'ete pour l'Amerique du Nord: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'hiver pour l'Amérique du Nord
 date = date_du_premier_dimanche_du_mois_donne(la.year(), (uint8_t)11, (uint8_t)2);
 Serial.println("heure d'ete -> heure d'hiver pour l'Amerique du Nord: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'hiver pour l'Australie
 date = date_du_premier_dimanche_du_mois_donne(la.year(), (uint8_t)4, (uint8_t)3);
 Serial.println("heure d'ete -> heure d'hiver pour l'Australie: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'ete pour l'Australie
 date = date_du_premier_dimanche_du_mois_donne(la.year(), (uint8_t)10, (uint8_t)2);
 Serial.println("heure d'hiver -> heure d'ete pour l'Australie: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'hiver pour la Nouvelle Zelande
 date = date_du_premier_dimanche_du_mois_donne(la.year(), (uint8_t)4, (uint8_t)2);
 Serial.println("heure d'ete -> heure d'hiver pour la Nouvelle Zelande: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'ete pour la Nouvelle Zelande
 date = date_du_dernier_dimanche_du_mois_donne(la.year(), (uint8_t)9, (uint8_t)2);
 Serial.println("heure d'hiver -> heure d'ete pour la Nouvelle Zelande: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'hiver pour le Chili
 date = date_du_deuxieme_dimanche_du_mois_donne(la.year(), (uint8_t)5, (uint8_t)2);
 Serial.println("heure d'ete -> heure d'hiver pour le Chili: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 //Calcul du passage à l'heure d'ete pour le Chili
 date = date_du_deuxieme_dimanche_du_mois_donne(la.year(), (uint8_t)8, (uint8_t)2);
 Serial.println("heure d'hiver -> heure d'ete pour le Chili: " + String(date.day()) + "/" + String(date.month()) + "/" + String(date.year()) + "\n");

 affichage_de_l_horloge(la);
}

void loop() {
  // put your main code here, to run repeatedly:

}
