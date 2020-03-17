#include "fcpp.hh"
#include <string>

const int board_size = 8;         // globale Konstante
typedef int columns[board_size];  // neuer Datentyp "columns"

bool good_position (int new_row, columns queen_cols, int new_col)
{
  for (int row=0; row<new_row; row=row+1)
    if ((queen_cols[row] == new_col) ||
	(new_row-row == abs(queen_cols[row]-new_col)))
      return false;
  return true;
}

void display_board (columns queen_cols)
{
  for (int i=0; i<board_size; i=i+1)
    {
      std::string s("");
      for (int j=0; j<board_size; j=j+1)
        if (j!= queen_cols[i])
          s = s + ".";
        else
          s = s + "D";
      print(s);
    }
  print(" ");
}

int queen_configs (int row, columns queen_cols)
{
  if (row == board_size) {
    display_board (queen_cols);
    return 1;
  }
  else {
    int nr_configs = 0;
    for (int col=0; col<board_size; col=col+1)
      if (good_position (row, queen_cols, col))
        {
          queen_cols[row] = col;
          nr_configs = nr_configs +
            queen_configs (row+1, queen_cols);
        }
    return nr_configs;
  }
}

int main ()
{
  columns queen_cols;
  print("Anzahl Loesungen");
  print(queen_configs(0,queen_cols));
  return 0;
}
