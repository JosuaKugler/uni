#include <iostream>

int read()
{
    //this function returns the number a user entered to the console
    int neuezahl;
    std::cout << "Gib eine natürliche Zahl ein, oder '0', um das array auszugeben, oder -1, um zu terminieren." << std::endl;
    std::cin >> neuezahl;
    return neuezahl;
}

void program()
{
    //Initialisierung, jeder Eintrag von Feld wird gleich 0 gesetzt
    int feld[10];
    for (int i = 0; i < 10; i++)
    {
        feld[i] = 0;
    }

    //ist terminate falsch, so läuft das Programm weiter, ist terminate wahr, so terminiert es
    bool terminate = false;
    while (not terminate)
    {
        //lässt den Benutzer eine Zahl eingeben
        int zahl = read();
        //wenn die Zahl negativ ist, dann terminiert das Programm
        if (zahl < 0){
            terminate = true;
            //wenn sie dann auch noch kleiner -1 ist, dann gibt es sogar noch eine Fehlermeldung
            if (zahl < -1){
                std::cout << " Die Zahl ist kleiner -1, das ist nicht erlaubt!!" << std::endl;
            }
        }
        //wenn die Zahl 0 ist, dann soll das Feld ausgegeben werden.
        else if (zahl == 0){
            std::cout << "Array = [";
            for (int i = 0; i < 10; ++i)
            {
                std::cout << feld[i] << " ";
            }
            std::cout << "]"<<std::endl;
        }
        //ansonsten ist die Zahl größer 0
        else
        {   
            //zunächst wird bestimmt, ob das Feld schon voll ist.
            terminate = true;
            for (int i = 0; i < 10; ++i)
            {
                if (feld[i] == 0)
                {
                    terminate = false;
                }
            }
            //wenn das der Fall ist, dann wird eine Fehlermeldung ausgegeben
            if (terminate == true)
            {
                std::cout << "Feld ist bereits voll." << std::endl;
            }
            //ansonsten wird die Zahl in das Feld geschrieben
            else
            {
                //wir erstellen zuerst eine Kopie des Feldes
                int feldkopie[10];
                for (int i = 0; i < 10; ++i)
                {
                    feldkopie[i] = feld[i];
                }
                //ist zahldrin wahr, so wurde die Zahl bereits ins Feld geschrieben, andernfalls noch nicht
                bool zahldrin = false;
                for (int i = 0; i < 10; ++i)
                {
                    //sobald wir einen Eintrag finden, der größer ist als zahl und zahl noch nicht ins Feld eingetragen wurde,
                    //tragen wir die Zahl an dieser Stelle ins Feld ein
                    if (feld[i] > zahl && not zahldrin)
                    {
                        feld[i] = zahl;
                        zahldrin = true;
                    }
                    //wenn die Zahl bereits eingetragen wurde, 
                    //dann müssen die restlichen Einträge immer eins nach 'rechts' verschoben werden
                    //daher setzen wir den i-ten Eintrag des neuen Feldes gleich dem i-1-ten Eintrag des vorherigen Feldes
                    else if (zahldrin)
                    {
                        feld[i] = feldkopie[i-1];
                    }
                    //wurde die Zahl noch nicht eingetragen, aber der Eintrag des Feldes ist 0, 
                    //Daher waren alle bisherigen Zahlen kleiner als die neue Zahl
                    //folglich tragen wir die Zahl einfach hier ein
                    else if (not zahldrin && feld[i] == 0)
                    {
                        feld[i] = zahl;
                        zahldrin = true;
                    }
                }
            }   
        }
    }
}

int main()
{
    program();
    return 0;
}