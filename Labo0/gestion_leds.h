/*----------------------------------------------------------------------------//
// Nom du projet 		: TP0_V02_Philou
// Nom du fichier 		: gestion_leds.h
// Date de cr�ation 	: 15.11.2021
// Date de modification : xx.xx.202x
//
// Auteur 				: Philou (Ph. Bovey)
//
// Description          : headerfile regroupant les prototypes de fonctions 
 *                        permettant de g�rer des leds sur le starterKit de l'ES 
 *                        bas� sur un PIC32MX
//
// Remarques :            
//----------------------------------------------------------------------------*/
//-- librairie pour les types utilis�e dans les prototypes --//
#include <stdint.h>

#ifndef GESTION_LEDS_H
#define	GESTION_LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif

//-- d�finition --// 

//-- prototypes --//     
void ChenillardHautBasSKPIC32(int8_t positionLeds); 

#ifdef	__cplusplus
}
#endif

#endif	/* GESTION_LEDS_H */

