/**
 * @file mendeleev.cpp
 *
 * @brief Periodic table to get some constants species related.
 *
 * @author Jordan Bieder <jordan.bieder@cea.fr>
 *
 * @copyright Copyright 2014 Jordan Bieder
 *
 * This file is part of AbiOut.
 *
 * AbiOut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AbiOut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AbiOut.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "base/mendeleev.hpp"
#include "base/utils.hpp"
#include <cmath>

using namespace Agate;
const char mendeleev::name[NELEMT][4] = {
  { "XXX"},  // The first is empty so we can call name directly without reindexing
  { "H  "},
  { "He "},
  { "Li "},
  { "Be "},
  { "B  "},
  { "C  "},
  { "N  "},
  { "O  "},
  { "F  "},
  { "Ne "},
  { "Na "},
  { "Mg "},
  { "Al "},
  { "Si "},
  { "P  "},
  { "S  "},
  { "Cl "},
  { "Ar "},
  { "K  "},
  { "Ca "},
  { "Sc "},
  { "Ti "},
  { "V  "},
  { "Cr "},
  { "Mn "},
  { "Fe "},
  { "Co "},
  { "Ni "},
  { "Cu "},
  { "Zn "},
  { "Ga "},
  { "Ge "},
  { "As "},
  { "Se "},
  { "Br "},
  { "Kr "},
  { "Rb "},
  { "Sr "},
  { "Y  "},
  { "Zr "},
  { "Nb "},
  { "Mo "},
  { "Tc "},
  { "Ru "},
  { "Rh "},
  { "Pd "},
  { "Ag "},
  { "Cd "},
  { "In "},
  { "Sn "},
  { "Sb "},
  { "Te "},
  { "I  "},
  { "Xe "},
  { "Cs "},
  { "Ba "},
  { "La "},
  { "Ce "},
  { "Pr "},
  { "Nd "},
  { "Pm "},
  { "Sm "},
  { "Eu "},
  { "Gd "},
  { "Tb "},
  { "Dy "},
  { "Ho "},
  { "Er "},
  { "Tm "},
  { "Yb "},
  { "Lu "},
  { "Hf "},
  { "Ta "},
  { "W  "},
  { "Re "},
  { "Os "},
  { "Ir "},
  { "Pt "},
  { "Au "},
  { "Hg "},
  { "Tl "},
  { "Pb "},
  { "Bi "},
  { "Po "},
  { "At "},
  { "Rn "},
  { "Fr "},
  { "Ra "},
  { "Ac "},
  { "Th "},
  { "Pa "},
  { "U  "},
  { "Np "},
  { "Pu "},
  { "Am "},
  { "Cm "},
  { "Bk "},
  { "Cf "},
  { "Es "},
  { "Fm "},
  { "Md "},
  { "No "},
  { "Lr "},
  { "Rf "},
  { "Db "},
  { "Sg "},
  { "Bh "},
  { "Hs "},
  { "Mt "},
  { "Ds "},
  { "Rg "},
  { "Cn "},
  { "Nh "},
  { "Fl "},
  { "Mc "},
  { "Lv "},
  { "Ts "},
  { "Og "},
  { "Lwf"}
};

mendeleev::mendeleev() :
/** Define the mass of each specie. */
mass{
  0.0e0       , // The first is empty so we can call name directly without reindexing
  1.00794e0   ,
  4.002602e0  ,
  6.941e0     ,
  9.012182e0  ,
  10.811e0    ,
  12.011e0    ,
  14.00674e0  ,
  15.9994e0   ,
  18.9984032e0,
  20.1797e0   ,
  22.989768e0 ,
  24.3050e0   ,
  26.981539e0 ,
  28.0855e0   ,
  30.973762e0 ,
  32.066e0    ,
  35.4527e0   ,
  39.948e0    ,
  39.0983e0   ,
  40.078e0    ,
  44.955910e0 ,
  47.88e0     ,
  50.9415e0   ,
  51.9961e0   ,
  54.93805e0  ,
  55.847e0    ,
  58.93320e0  ,
  58.69e0     ,
  63.546e0    ,
  65.39e0     ,
  69.723e0    ,
  72.61e0     ,
  74.92159e0  ,
  78.96e0     ,
  79.904e0    ,
  83.80e0     ,
  85.4678e0   ,
  87.62e0     ,
  88.90585e0  ,
  91.224e0    ,
  92.90638e0  ,
  95.94e0     ,
  98.9062e0   ,
  101.07e0    ,
  102.9055e0  ,
  106.42e0    ,
  107.8682e0  ,
  112.411e0   ,
  114.82e0    ,
  118.710e0   ,
  121.753e0   ,
  127.60e0    ,
  126.90447e0 ,
  131.29e0    ,
  132.90543e0 ,
  137.327e0   ,
  138.9055e0  ,
  140.115e0   ,
  140.90765e0 ,
  144.24e0    ,
  147.91e0    ,
  150.36e0    ,
  151.965e0   ,
  157.25e0    ,
  158.92534e0 ,
  162.50e0    ,
  164.93032e0 ,
  167.26e0    ,
  168.93421e0 ,
  173.04e0    ,
  174.967e0   ,
  178.49e0    ,
  180.9479e0  ,
  183.85e0    ,
  186.207e0   ,
  190.2e0     ,
  192.22e0    ,
  195.08e0    ,
  196.96654e0 ,
  200.59e0    ,
  204.3833e0  ,
  207.2e0     ,
  208.98037e0 ,
  209.0e0     ,
  210.0e0     ,
  222.0e0     ,
  223.0e0     ,
  226.0254e0  ,
  230.0e0     ,
  232.0381e0  ,
  231.0359e0  ,
  238.0289e0  ,
  237.0482e0  ,
  242.0e0     ,
  243.0e0     ,
  247.0e0     ,
  247.0e0     ,
  249.0e0     ,
  254.0e0     ,
  253.0e0     ,
  256.0e0     ,
  254.0e0     ,
  257.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
  260.0e0     ,
    1.0e0
},
/** Define the color of each specie. */
color{
  {0.5f, 0.5f, 0.5f}       , // The first is empty so we can call name directly without reindexing
  {1.000f, 1.000f, 1.000f}       ,
  {0.847f, 0.843f, 0.996f}       ,
  {0.804f, 0.475f, 0.984f}       ,
  {0.769f, 1.000f, 0.239f}       ,
  {0.898f, 0.776f, 0.757f}       ,
  {0.565f, 0.565f, 0.565f}       ,
  {0.082f, 0.000f, 0.980f}       ,
  {1.000f, 0.012f, 0.000f}       ,
  {0.702f, 1.000f, 1.000f}       ,
  {0.686f, 0.886f, 0.953f}       ,
  {0.667f, 0.337f, 0.933f}       ,
  {0.537f, 1.000f, 0.243f}       ,
  {0.820f, 0.647f, 0.647f}       ,
  {0.502f, 0.604f, 0.604f}       ,
  {1.000f, 0.506f, 0.102f}       ,
  {1.000f, 0.792f, 0.231f}       ,
  {0.098f, 0.949f, 0.247f}       ,
  {0.506f, 0.820f, 0.890f}       ,
  {0.557f, 0.220f, 0.812f}       ,
  {0.239f, 1.000f, 0.243f}       ,
  {0.902f, 0.902f, 0.894f}       ,
  {0.749f, 0.765f, 0.776f}       ,
  {0.655f, 0.647f, 0.675f}       ,
  {0.537f, 0.596f, 0.769f}       ,
  {0.612f, 0.475f, 0.765f}       ,
  {0.502f, 0.475f, 0.769f}       ,
  {0.369f, 0.404f, 0.984f}       ,
  {0.369f, 0.475f, 0.757f}       ,
  {1.000f, 0.486f, 0.384f}       ,
  {0.486f, 0.498f, 0.678f}       ,
  {0.765f, 0.565f, 0.565f}       ,
  {0.400f, 0.565f, 0.565f}       ,
  {0.737f, 0.490f, 0.875f}       ,
  {1.000f, 0.639f, 0.141f}       ,
  {0.647f, 0.129f, 0.122f}       ,
  {0.369f, 0.725f, 0.816f}       ,
  {0.439f, 0.137f, 0.682f}       ,
  {0.000f, 1.000f, 0.243f}       ,
  {0.588f, 0.992f, 1.000f}       ,
  {0.584f, 0.882f, 0.882f}       ,
  {0.455f, 0.765f, 0.796f}       ,
  {0.333f, 0.710f, 0.714f}       ,
  {0.235f, 0.620f, 0.659f}       ,
  {0.141f, 0.557f, 0.592f}       ,
  {0.035f, 0.486f, 0.549f}       ,
  {0.016f, 0.408f, 0.518f}       ,
  {0.604f, 0.769f, 0.992f}       ,
  {1.000f, 0.851f, 0.580f}       ,
  {0.655f, 0.459f, 0.447f}       ,
  {0.400f, 0.502f, 0.502f}       ,
  {0.620f, 0.380f, 0.698f}       ,
  {0.831f, 0.486f, 0.106f}       ,
  {0.576f, 0.000f, 0.565f}       ,
  {0.263f, 0.620f, 0.686f}       ,
  {0.337f, 0.000f, 0.545f}       ,
  {0.000f, 0.804f, 0.196f}       ,
  {0.443f, 0.863f, 0.996f}       ,
  {1.000f, 1.000f, 0.796f}       ,
  {0.847f, 1.000f, 0.796f}       ,
  {0.776f, 1.000f, 0.796f}       ,
  {0.639f, 1.000f, 0.796f}       ,
  {0.565f, 1.000f, 0.796f}       ,
  {0.388f, 1.000f, 0.796f}       ,
  {0.278f, 1.000f, 0.796f}       ,
  {0.196f, 1.000f, 0.796f}       ,
  {0.129f, 1.000f, 0.729f}       ,
  {0.016f, 1.000f, 0.635f}       ,
  {0.004f, 0.910f, 0.490f}       ,
  {0.000f, 0.835f, 0.365f}       ,
  {0.000f, 0.757f, 0.275f}       ,
  {0.000f, 0.682f, 0.208f}       ,
  {0.310f, 0.749f, 0.992f}       ,
  {0.310f, 0.643f, 0.988f}       ,
  {0.161f, 0.569f, 0.831f}       ,
  {0.157f, 0.490f, 0.671f}       ,
  {0.153f, 0.400f, 0.584f}       ,
  {0.102f, 0.322f, 0.522f}       ,
  {0.102f, 0.349f, 0.557f}       ,
  {1.000f, 0.827f, 0.227f}       ,
  {0.710f, 0.710f, 0.761f}       ,
  {0.655f, 0.329f, 0.302f}       ,
  {0.337f, 0.349f, 0.376f}       ,
  {0.620f, 0.294f, 0.698f}       ,
  {0.675f, 0.369f, 0.051f}       ,
  {0.459f, 0.310f, 0.267f}       ,
  {0.263f, 0.510f, 0.588f}       ,
  {0.259f, 0.000f, 0.392f}       ,
  {0.000f, 0.490f, 0.118f}       ,
  {0.443f, 0.659f, 0.973f}       ,
  {0.078f, 0.722f, 0.992f}       ,
  {0.078f, 0.620f, 0.988f}       ,
  {0.078f, 0.549f, 0.988f}       ,
  {0.071f, 0.486f, 0.937f}       ,
  {0.075f, 0.396f, 0.933f}       ,
  {0.333f, 0.325f, 0.933f}       ,
  {0.471f, 0.333f, 0.871f}       ,
  {0.541f, 0.278f, 0.871f}       ,
  {0.514f, 0.165f, 0.816f}       ,
  {0.702f, 0.000f, 0.816f}       ,
  {0.702f, 0.000f, 0.714f}       ,
  {0.702f, 0.000f, 0.643f}       ,
  {0.737f, 0.000f, 0.518f}       ,
  {0.784f, 0.000f, 0.388f}       ,
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {1.000f, 1.000f, 1.000f}       , 
  {0.996f, 0.235f, 1.000f}       , 
},

radius{
  1.00e0       , // The first is empty so we can call name directly without reindexing
  0.32e0 ,
  0.93e0 ,
  1.23e0 ,
  0.90e0 ,
  0.80e0 ,
  0.77e0 ,
  0.74e0 ,
  0.73e0 ,
  0.72e0 ,
  0.71e0 ,
  1.54e0 ,
  1.36e0 ,
  1.18e0 ,
  1.11e0 ,
  1.06e0 ,
  1.02e0 ,
  0.99e0 ,
  0.98e0 ,
  2.03e0 ,
  1.74e0 ,
  1.44e0 ,
  1.32e0 ,
  1.22e0 ,
  1.18e0 ,
  1.17e0 ,
  1.17e0 ,
  1.16e0 ,
  1.15e0 ,
  1.17e0 ,
  1.25e0 ,
  1.26e0 ,
  1.22e0 ,
  1.20e0 ,
  1.16e0 ,
  1.14e0 ,
  1.12e0 ,
  2.16e0 ,
  1.91e0 ,
  1.62e0 ,
  1.45e0 ,
  1.34e0 ,
  1.30e0 ,
  1.27e0 ,
  1.25e0 ,
  1.25e0 ,
  1.28e0 ,
  1.34e0 ,
  1.48e0 ,
  1.44e0 ,
  1.41e0 ,
  1.40e0 ,
  1.36e0 ,
  1.33e0 ,
  1.31e0 ,
  2.35e0 ,
  1.98e0 ,
  1.69e0 ,
  1.65e0 ,
  1.65e0 ,
  1.64e0 ,
  1.64e0 ,
  1.62e0 ,
  1.85e0 ,
  1.61e0 ,
  1.59e0 ,
  1.59e0 ,
  1.57e0 ,
  1.57e0 ,
  1.56e0 ,
  1.70e0 ,
  1.56e0 ,
  1.44e0 ,
  1.34e0 ,
  1.30e0 ,
  1.28e0 ,
  1.26e0 ,
  1.27e0 ,
  1.30e0 ,
  1.34e0 ,
  1.49e0 ,
  1.48e0 ,
  1.47e0 ,
  1.46e0 ,
  1.46e0 ,
  1.45e0 ,
  1.45e0 ,
  2.50e0 ,
  2.10e0 ,
  1.85e0 ,
  1.65e0 ,
  1.50e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
},

rcov{
  1.00e0       , // The first is empty so we can call name directly without reindexing
  0.32e0 ,
  0.93e0 ,
  1.23e0 ,
  0.90e0 ,
  0.80e0 ,
  0.77e0 ,
  0.74e0 ,
  0.73e0 ,
  0.72e0 ,
  0.71e0 ,
  1.54e0 ,
  1.36e0 ,
  1.18e0 ,
  1.11e0 ,
  1.06e0 ,
  1.02e0 ,
  0.99e0 ,
  0.98e0 ,
  2.03e0 ,
  1.74e0 ,
  1.44e0 ,
  1.32e0 ,
  1.22e0 ,
  1.18e0 ,
  1.17e0 ,
  1.17e0 ,
  1.16e0 ,
  1.15e0 ,
  1.17e0 ,
  1.25e0 ,
  1.26e0 ,
  1.22e0 ,
  1.20e0 ,
  1.16e0 ,
  1.14e0 ,
  1.12e0 ,
  2.16e0 ,
  1.91e0 ,
  1.62e0 ,
  1.45e0 ,
  1.34e0 ,
  1.30e0 ,
  1.27e0 ,
  1.25e0 ,
  1.25e0 ,
  1.28e0 ,
  1.34e0 ,
  1.48e0 ,
  1.44e0 ,
  1.41e0 ,
  1.40e0 ,
  1.36e0 ,
  1.33e0 ,
  1.31e0 ,
  2.35e0 ,
  1.98e0 ,
  1.69e0 ,
  1.65e0 ,
  1.65e0 ,
  1.64e0 ,
  1.64e0 ,
  1.62e0 ,
  1.85e0 ,
  1.61e0 ,
  1.59e0 ,
  1.59e0 ,
  1.57e0 ,
  1.57e0 ,
  1.56e0 ,
  1.70e0 ,
  1.56e0 ,
  1.44e0 ,
  1.34e0 ,
  1.30e0 ,
  1.28e0 ,
  1.26e0 ,
  1.27e0 ,
  1.30e0 ,
  1.34e0 ,
  1.49e0 ,
  1.48e0 ,
  1.47e0 ,
  1.46e0 ,
  1.46e0 ,
  1.45e0 ,
  1.45e0 ,
  2.50e0 ,
  2.10e0 ,
  1.85e0 ,
  1.65e0 ,
  1.50e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
  1.42e0 ,
}
{
  ;
}

/**
 * find the znucl corresponding to a string
 */
unsigned mendeleev::znucl(const std::string &inname) {
  std::locale loc;
  std::string locname = utils::tolower(inname);
  locname[0] = std::toupper(locname[0],loc);
  utils::trim(locname);
  for ( unsigned sp = 1 ; sp < NELEMT ; ++sp ) {
    std::string specie(mendeleev::name[sp]);
    utils::rtrim(specie);
    if ( locname.compare(specie) == 0 ) {
      return sp;
    }
  }
  throw EXCEPTION("Unable to find znucl for "+inname,ERRDIV);
  return (unsigned)-1;
}

/**
 * find the znucl corresponding to a mass
 */
unsigned mendeleev::znucl(const double inmass) {
  for ( unsigned sp = 1 ; sp < NELEMT ; ++sp ) {
    if( fabs( (Mendeleev.mass[sp]-inmass)/Mendeleev.mass[sp] ) < 1e-3){
      return sp;
    }
  }
  throw EXCEPTION("Unable to find znucl for "+utils::to_string(inmass),ERRDIV);
  return (unsigned)-1;
}
