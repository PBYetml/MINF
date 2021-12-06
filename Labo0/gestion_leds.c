//----------------------------------------------------------------------------//
// Nom du projet 		: TP0_V02_Philou
// Nom du fichier 		: gestion_leds.c
// Date de cr�ation 	: 15.11.2021
// Date de modification : xx.xx.202x
//
// Auteur 				: Philou (Ph. Bovey)
//
// Description          : fichiers regroupant plusieurs fonctions permettant de 
//                        g�rer des leds sur le starterKit de l'ES bas� sur un 
//                        PIC32MX
//
// Remarques :            
//----------------------------------------------------------------------------//
//-- d�claration de libraires --// 
//--- standart ---//
#include <stdint.h>             // type entier noramalis� 
#include <stdbool.h>            // type bool normalis� 

//--- li� au PIC ---// 
#include <xc.h>                             // lib li� au compilateur XC32

#include "system_config.h"
#include "system_definitions.h"
#include "peripheral/ports/plib_ports.h"    // lib li� aux fonctions PLIB_port 

//--- perso ---// 
#include "gestion_leds.h"

/*******************************************************************************
 * Function Name                : ChenillardHautBasSKPIC32
 * IN/OUT/INOUT Parameters      : - / - / -
 * Description                  : permet de faire d�filer de haut en bas les 
 *                                leds, pas de cadencement g�rer dans cette 
 *                                fonction 
 *
 * Remarque                     : utilisation des fonctions de la PLIB 
 * 
 * Creation date                : 15.11.2021
 * Modification date            : xx.xx.xxxx
 * 
 * Auteur                       : Ph. Bovey (philou) 
 * Version                      : 0.1 
*******************************************************************************/
void ChenillardHautBasSKPIC32(int8_t positionLeds)
{
    //-- d�claraation de variables --//
    
    //-- algorithme pour cr�er le chenillard --//
    //-- test si la pin s�lectionn�e est a une valeur 1 ou 0 --// 
    /* si la fonction renvoit un 0 => led allum�e 
       si la fonction renvoit un 1 => led �teinte 
       si la led est �teinte (valeur 1) on veut l'allumer (valeur 0) et v�rifier  
       la led pr�c�dente est �teinte (valeur 1) */
    //-- test LED0 -> LED --//
    if((PLIB_PORTS_PinGet(PORTS_ID_0, PO, PORT_CHANNEL_B, PORTS_BIT_POS_10))
    {
        //-- �teindre la led test�e --//
        PLIB_PORTS_PinWrite(PORTS_ID_0, PO, PORT_CHANNEL_B, PORTS_BIT_POS_10, 1); 
                
        //-- allum� la suivante --//
        PLIB_PORTS_PinWrite(PORTS_ID_0, PO, PORT_CHANNEL_A, PORTS_BIT_POS_0, 0);         
    }
    
    //-- test LED1 -> LED 1--//
    
    //-- test LED2 -> LED 0--//
    
    //-- test LED3 -> LED 0--//
    
    //-- test LED4 -> LED 0--//
    
    //-- test LED5 -> LED 0--//
    
    //-- test LED6 -> LED 0--//
    
    //-- test LED7 -> LED 0--//
    
    
    
    
    
    
}