/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <math.h>



/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void maFonction(){
  // code
}

//Description : cela calcule le nbr necessaire de pulse pour atteindre une certaine distance puis fait une boucle pour que le robot se stope quand il a atteint cette distance
//Précondition : la valeur en centimetre de la distance a parcourir et la vitesse des moteurs
//Postcondition : le nombre de pulse pour atteindre cette distance

void distance (float vdistance, float vmoteura)
{
  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);
  int  a;
  float g,d;
  float circonference, pulse, vmoteurb = vmoteura;
  circonference = 7.62*3.14;
  pulse = (3200*vdistance)/circonference;
  
  a=ENCODER_Read(0);
  while (a<=pulse)
  {
    a=ENCODER_Read(0);
    MOTOR_SetSpeed(0, vmoteura);
    MOTOR_SetSpeed(1, vmoteurb);
    //vmoteurb = vmoteur (vmoteura);
    g = ENCODER_Read(0);
    d = ENCODER_Read(1);
    vmoteurb = vmoteurb + controlem(d,g,vmoteurb);
    
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);

}

//description : fait tourner le robot a gauche
//postcondition :  la valeur du moteur combien il a parcourut jusque la et l angle auquel ild oit tourner
//precondition
void tournantgauche (float vmoteura,  float angle)
{
  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);
  int a,g,d;
  float circonference, pulse, vmoteurb=vmoteura;
  circonference = 7.62*3.14;
  pulse = (3200*(((angle*2)/360)*3.14*18.5)/circonference);
  
  
  a=ENCODER_Read(1);
  
 
  while (a<=pulse )
  {
    a=ENCODER_Read(1);
    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, vmoteurb);
    //vmoteurb = vmoteur (vmoteura);
  
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
 

}

//description : fait tourner le robot a gauche
//postcondition :  la valeur du moteur combien il a parcourut jusque la et l angle auquel ild oit tourner
//precondition
void tournadroite (float vmoteura,  float angle)
{
  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);
  int a;
 
  float circonference, pulse1, vmoteurb=vmoteura;
  circonference = 7.62*3.14;
  pulse1 = (3200*(((angle*2)/360)*3.14*18.5)/circonference);

  a=ENCODER_Read(0);
  while (a<=pulse1)
  {
    a=ENCODER_Read(0);
  
    MOTOR_SetSpeed(1, 0);
    MOTOR_SetSpeed(0, vmoteurb);
    //vmoteurb = vmoteur (vmoteura);
    
  
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
  

}
//Description : pour faire en sorte que les deux moteurs aille a la mm vitesse
//precondition : la vitesse de ton moteur a qui est ton  point de reference il ne bouge jamais
//postcondition : la vitesse de ton moteurs b

/*************
float vmoteur (float vmoteura)
{
  
  int g, d;
  float  vmoteurd;
  vmoteurd = vmoteura;
  g = ENCODER_Read(0);
  d = ENCODER_Read(1);
  //Serial.println(g);
  //Serial.println(d);
  //delay(1000);
  if (g>d)
  {
    vmoteurd = vmoteurd + 0.08;
  }
  else if (g<d)
  {
    vmoteurd = vmoteurd - 0.08;
  }
 
  return vmoteurd;
  
}
***********/
//description : fait demitour
//postcondition :  la valeur du moteur combien il a parcourut jusque la et l angle auquel ild oit tourner
//precondition
void demitour (float vmoteura,  float angle)
{
  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);
  int a;
  float circonference, pulse1, vmoteurb=vmoteura;
  circonference = 7.62*3.14;
  pulse1 = (3200*(((angle*2)/360)*3.14*18.5)/circonference);

  a=ENCODER_Read(0);
  while (a<=pulse1)
  {
    a=ENCODER_Read(0);
    
    MOTOR_SetSpeed(1, -vmoteurb);
    MOTOR_SetSpeed(0, vmoteurb);
    //vmoteurb = vmoteur (vmoteura);
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
  

}

//Description : pour faire en sorte que les deux moteurs aille a la mm vitesse
//precondition : la vitesse de ton moteur a qui est ton  point de reference il ne bouge jamais
//postcondition : la vitesse de ton moteurs b

float controlem (float d, float g, float vmoteurb)
{
  float calcule = 0, corection1, corection2, Kp = 5, erreur_totale = 0, Ki = 0.0055, corection, circonference;
  
  calcule = g-d;
  calcule = (calcule*circonference)/3200;
  calcule = vmoteurb /calcule;
  calcule = 1 / calcule;
  Serial.println(calcule);
  corection1 = Kp*calcule;
  erreur_totale = erreur_totale + calcule;
  corection2 = Ki*erreur_totale;
  corection = corection1 + corection2;
  Serial.println(corection);
  
  return corection;
}


//Description : pour faire en sorte que les deux moteurs aille a la mm vitesse
//precondition : la vitesse de ton moteur a qui est ton  point de reference il ne bouge jamais
//postcondition : la vitesse de ton moteurs b
/**************
float controlem (float d, float pulse, float comptpulse)
{
  float valeur_lu=d, valeur_desire = pulse, valeur_erreur, ajustement1, ajustement2, nb_cycle,ajustement;
  nb_cycle = comptpulse / 3200;
  valeur_erreur = valeur_desire - valeur_lu;
  ajustement1 = valeur_erreur * 0.00015;
  ajustement2 = ((nb_cycle*valeur_desire)-comptpulse)*0.00002;
  ajustement = ajustement2 + ajustement1;
  return ajustement;
}
*********/

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  
  BoardInit();
  
  
  
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() 
{
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU


  /*************
  distance (105,0.4);
  tournantgauche (0.4, 90);
  distance (65,0.4);
  tournadroite (0.4, 90);
  distance (85,0.4);
  tournadroite (0.4, 45);
  distance (170,0.4);
  tournantgauche (0.4, 90);
  distance (47,0.4);
  tournadroite (0.4, 45);
  distance (75,0.4);
  demitour(0.4,90);
  *********/
 distance(200,0.4);
}