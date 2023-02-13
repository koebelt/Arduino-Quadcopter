#include <Arduino.h>
#include "serial_management.h"
#include "config.h"

String inputString = "";        // chaine de caractères pour contenir les données
boolean stringComplete = false; // pour savoir si la chaine est complète
String command = "";            // init
String argument = "";           // init

void handleCommands()
{
    if (command == "" || argument == "") return;
    if (command == "M")
    {
        throttle = argument.toInt();
        Serial.print("consigneGAZ = ");
        Serial.println(throttle);
    }
    command = "";
    argument = "";

}


void serialEvent()
{
    while (Serial.available())
    {
        char inChar = (char)Serial.read(); // récupérer le prochain octet (byte ou char) et l'enlever
        inputString += inChar;             // concaténation des octets reçus
        if (inChar == '\n')
        { // caractère de fin pour notre chaine
            stringComplete = true;
        }
    }
    // seconde partie, le dialogue est terminé, il faut analyser ce qui est dit: "analyse syntaxique: to PARSE en anglais"
    // vérifs: si string complet & commence par 'D' => analyse, sinon sortie directe sans rien garder
    // c'est une analyse minimale ...
    if (stringComplete)
    {
        inputString.toUpperCase(); // tout en majuscules
        Serial.print("inputString =   ");
        Serial.println(inputString);
        int indexD = inputString.indexOf('D');
        int indexSpace = inputString.indexOf(' ');
        command = inputString.substring((indexD + 1), indexSpace);
        Serial.print("command=");
        Serial.println(command);
        argument = inputString.substring(indexSpace + 1);
        Serial.print("argument=");
        Serial.println(argument);
        //  Serial.print(consigneETAT);
        inputString = "";
        stringComplete = false;
    }
}