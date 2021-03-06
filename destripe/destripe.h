
/////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------------------------------------------------------------- //
// This code was developed in NOAA/NESDIS/STAR SST and Ocean Color groups by Karlis Mikelsons. //
//                                                                                             //
// Please report any bugs to Karlis.Mikelsons@noaa.gov                                         //
// ------------------------------------------------------------------------------------------- //
/////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef DESTRIPE_H_DEFINED
#define DESTRIPE_H_DEFINED

#define PI 3.1415926535897932384626433832795

#include "destripe_main_padframe.c"

int destripe_main      (float ** input_image, float ** output_image, int ** binary_M,  int number_detectors, int number_iterations, float NEdT, float thresh_x, float thresh_y, float Tmin, float Tmax, int sx, int sy);
int destripe_main_frame(float ** input_image, float ** output_image, int ** binary_M,  int number_detectors, int number_iterations, float NEdT, float thresh_x, float thresh_y, float Tmin, float Tmax, int sx, int sy);


#endif
