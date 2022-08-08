#include "fcpp.hh"
#include <string.h> 
#include <iostream>
using namespace std;

// fuer strlen, Laenge eines C-Strings

// Definieren Sie hier Ihren Stack und legen Sie eine Instanz als globale
// Variable an

const int stacklength = 1000;

struct Stack
{
  int counter;
  int array[stacklength];
};

Stack stack;

// Danach koennen Sie die Funktionen push() und pop() implementieren, die auf dieser
// globalen Variable operieren

void push(int element)
{
  stack.counter += 1;
  stack.array[stack.counter - 1] = element;
}

int pop()
{
  stack.counter -= 1;
  return stack.array[stack.counter];
}

bool is_operator(char zeichen)
//gibt true aus, wenn zeichen ein operator ist
{
  if ( '+' == zeichen || '-' == zeichen || '*' == zeichen || '/' == zeichen )
  {
    return true;
  }
  return false;
}


bool is_ziffer(char zeichen)
//gibt true aus, wenn zeichen eine Ziffer ist
{
  if (zeichen == '0' || zeichen == '1' || zeichen == '2' ||zeichen == '3' ||zeichen == '4' ||zeichen == '5' ||zeichen == '6' ||zeichen == '7' ||zeichen == '8' ||zeichen == '9')
  {
    return true;
  }
  return false;
}

int ziffer(char zeichen)
//gibt die Ziffer als int aus, wenn der Buchstabe eine Ziffer ist.
//ansonsten fehlermeldung
{
  if (zeichen == '0')
  {
    return 0;
  }
  if (zeichen == '1')
  {
    return 1;
  }
  if (zeichen == '2')
  {
    return 2;
  }
  if (zeichen == '3')
  {
    return 3;
  }
  if (zeichen == '4')
  {
    return 4;
  }
  if (zeichen == '5')
  {
    return 5;
  }
  if (zeichen == '6')
  {
    return 6;
  }
  if (zeichen == '7')
  {
    return 7;
  }
  if (zeichen == '8')
  {
    return 8;
  }
  if (zeichen == '9')
  {
    return 9;
  }
  print("Das Argument ist keine Ziffer!");
}

int main(int argc, char* argv[])
{
  // Setzen Sie hier auf einen leeren Stack
  stack.counter = 0;

  // fange kein Kommandozeilenargument ab
  if(argc < 2)
  {
    print("Eingabe fuer den Taschenrechner erwartet!");
    return 1;
  }

  // arg enthaelt die als Eingabe von der Kommandozeile uebergebene Zeichenfolge
  char* arg = argv[1];

  // Schleife, die die Zeichen der Eingabe nacheinander ablaeuft
  // strlen gibt die Anzahl der Zeichen in der Zeichenkette
  int element = 0;
  bool lziffer = false;
  for (int i = 0; i <= strlen(arg); i = i+1)
  {
    char zeichen = arg[i]; // aktuelles Zeichen
    // Beachten Sie: der Inhalt der Variable zeichen ist der ASCII-Code
    // des entsprechenden Zeichens. Dieser stimmt im Falle der Zeichen '0'..'9'
    // nicht mit der entsprechenden Ziffer ueberein.

    // Fuegen Sie hier Code ein, der das Zeichen verarbeitet, also Ziffern
    // zu Zahlen zusammenfuegt, Operatoren anwendet und andere Zeichen
    // ignoriert

    if (is_ziffer(zeichen) && lziffer == false)
    //wenn eine neue zahl beginnt, dann setzen wir lziffer auf true
    //und element auf den Wert der aktuellen Ziffer
    {
      lziffer = true;
      element = ziffer(zeichen);
    }

    else if (is_ziffer(zeichen) && lziffer == true)
    //wenn eine Zahl bereits begonnen hat und nun eine weitere ziffer hinzukommt, 
    //so multiplizieren wir die bisherige zahl mit 10 und addieren die neue Ziffer
    {
      element = 10*element + ziffer(zeichen);
    }
    else //Zeichen ist keine Ziffer
    {
      if (lziffer == true)
      //wenn eine zahl bis hierher ging,
      //so pushen wir element in den stack
      {
        push(element);
      }

      lziffer = false; //da dieses Zeichen keine Ziffer ist, setzen wir lziffer auf false

      if (is_operator(zeichen))
      //handelt es sich bei dem Zeichen um einen Operator, so holen wir die obersten 2 zahlen vom stack
      {
        int ziffer2 = pop();
        int ziffer1 = pop();
        int result;
        //je nach Operation verknuepfen wir nun diese zahlen
        if (zeichen == '+')
        {
          result = ziffer1 + ziffer2;
        }
        else if (zeichen == '-')
        {
          result = ziffer1 - ziffer2;
        }
        else if (zeichen == '*')
        {
          result = ziffer1 * ziffer2;
        }
        else if (zeichen == '/')
        {
          result = ziffer1 / ziffer2;
        }
        //Das Resultat pushen wir in den stack
        push(result);
      }
    }
  }
  //bei korrekter Eingabe ist nach Durchlauf der gesamten Schleife der counter 1
  if (stack.counter == 1)
  {
    print("Ergebnis:");
    print(stack.array[0]);
  }
  else
  {
    print("Fehlerhafte Eingabe");
  }
  
}
