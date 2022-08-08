#include <string>
#include <fstream>
#include <cmath>

void write_pgm(int* pixels, int horPixels, int vertPixels, std::string filename)
{
  if(horPixels == 0 || vertPixels == 0)
  {
    std::cerr << "Leeres Pixel Array" << std::endl;
    return;
  }

  // write file
  // unfortunately we cannot use C++-11 which would simplify our life in that case
  std::ofstream outfile;
  outfile.open(filename.c_str());

  outfile << "P2" << std::endl
          << horPixels << " " << vertPixels << std::endl;

  // renormalize if necessary
  int maxVal = 0;
  for(int entry=0; entry<horPixels*vertPixels; entry++)
    maxVal = std::max(pixels[entry],maxVal);

  // renormalizing output
  if(maxVal > 65535)
  {
    outfile << 65535 << std::endl;
    for(int j=0, entry=0; j<vertPixels; j++)
    {
      for(int i=0; i<horPixels; i++, entry++)
      {
        if(pixels[entry] < 0)
        {
          std::cerr << "Negativer Eintrag bei (" << i << ", " << j << ")" << std::endl;
          return;
        }
        outfile << std::floor(pixels[entry] * (65535./maxVal)) << " ";
      }
      outfile << std::endl;
    }
  }
  // normal output
  else
  {
    outfile << maxVal << std::endl;
    for(int j=0; j<vertPixels; j++)
    {
      for(int i=0; i<horPixels; i++)
      {
        int entry = i + horPixels*(vertPixels-1-j);
        if(pixels[entry] < 0)
        {
          std::cerr << "Negativer Eintrag bei (" << i << ", " << j << ")" << std::endl;
          return;
        }
        outfile << pixels[entry] << " ";
      }
      outfile << std::endl;
    }
  }
  outfile.close();
}
