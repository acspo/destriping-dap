#include <stdio.h>
#include "hdf5.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int readwrite_viirs(unsigned short **buffer, unsigned long long * dimsizes, float * gain, float * offset, char * filename, char * BTstr, int readwrite) {

  hid_t   file_id, dataset, dataset_factors, dataspace;
  herr_t  hdferr;
  int     info, rank_BT, i, iprint = 1;
  float   gain_offset[2];
  unsigned long long   dims[2], maxdimsizes[2];

  char BTFstr[256];
  sprintf(BTFstr,"%sFactors", BTstr);

  if(iprint>0) printf("BTstr  = %s\n", BTstr);
  if(iprint>0) printf("BTFstr = %s\n", BTFstr);

  hdferr = H5open();
  if(hdferr!=0) { printf("Cannot initialize HDF5 library!\n"); return -1; }
  if(readwrite==0)  file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);
  else              file_id = H5Fopen(filename, H5F_ACC_RDWR,   H5P_DEFAULT);
  if(file_id<0) { printf("Cannot open HDF5 file %s!\n", filename); return -1; }
  dataset_factors = H5Dopen(file_id, BTFstr, H5P_DEFAULT);
  if(dataset_factors<0) {  printf("Cannot open HDF5 dataset %s!\n", BTFstr); return -1; }
  dims[1] = 2;
  dims[2] = 0;
  hdferr = H5Dread(dataset_factors, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, gain_offset);
  if(hdferr<0) { printf("Cannot read BT factors!\n"); return -1; }
  *gain   = gain_offset[0];
  *offset = gain_offset[1];
  if(iprint>0) printf("gain = %3.8e  offset = %3.8e\n", *gain, *offset);
  hdferr = H5Dclose(dataset_factors);
  if(hdferr<0) { printf("Cannot close HDF5 dataset %s!\n", BTFstr); return -1; }

  dataset = H5Dopen(file_id, BTstr, H5P_DEFAULT);
  if(dataset<0) {  printf("Cannot open HDF5 dataset %s!\n", BTstr); return -1; }
  dataspace = H5Dget_space(dataset);
  if(dataspace<0) { printf("Cannot open HDF5 dataspace for dataset %s!\n", BTstr); return -1; }
  rank_BT = H5Sget_simple_extent_ndims(dataspace);
  if(rank_BT!=2) { printf("Unexpected rank of dataspace %i expected 2\n", rank_BT); return -1; }
  rank_BT = H5Sget_simple_extent_dims(dataspace, dimsizes, maxdimsizes);
  if(rank_BT<0)  { printf("Cannot get dataspace dimensions!\n"); return -1; }
  if(iprint>0) printf("dimsizes = %i  %i\n", dimsizes[0], dimsizes[1]);

  if(readwrite==0) {
    *buffer = (unsigned short *) malloc(dimsizes[0]*dimsizes[1]*sizeof(unsigned short));
    if(*buffer==NULL) { printf("Cannot allocate memory\n"); return -1; }
    hdferr = H5Dread( dataset, H5T_NATIVE_USHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, *buffer);
    if(hdferr<0) { printf("Cannot read data to hdf!\n"); return -1; }
  } else {
    hdferr = H5Dwrite(dataset, H5T_NATIVE_USHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, *buffer);
    if(hdferr<0) { printf("Cannot write data to hdf!\n"); return -1; }
  }

  // close everything
  hdferr = H5Dclose(dataset);
  if(hdferr<0) { printf("Cannot close HDF5 dataset %s!\n", BTstr); return -1; }
  hdferr = H5Fclose(file_id);
  if(hdferr<0) { printf("Cannot close HDF5 file %s!\n", filename); return -1; }
  hdferr = H5close();
  if(hdferr<0) { printf("Cannot close HDF5 library!\n"); return -1; }

  return 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int readwrite_viirs_float(float **buffer, unsigned long long * dimsizes, char * filename, char * BTstr, int readwrite) {

  hid_t   file_id, dataset, dataset_factors, dataspace;
  herr_t  hdferr;
  int     info, rank_BT, i, iprint = 1;
  unsigned long long   dims[2], maxdimsizes[2];

  if(iprint>0) printf("BTstr  = %s\n", BTstr);

  hdferr = H5open();
  if(hdferr!=0) { printf("Cannot initialize HDF5 library!\n"); return -1; }
  if(readwrite==0)  file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);
  else              file_id = H5Fopen(filename, H5F_ACC_RDWR,   H5P_DEFAULT);
  if(file_id<0) { printf("Cannot open HDF5 file %s!\n", filename); return -1; }
  dims[1] = 2;
  dims[2] = 0;

  dataset = H5Dopen(file_id, BTstr, H5P_DEFAULT);
  if(dataset<0) {  printf("Cannot open HDF5 dataset %s!\n", BTstr); return -1; }
  dataspace = H5Dget_space(dataset);
  if(dataspace<0) { printf("Cannot open HDF5 dataspace for dataset %s!\n", BTstr); return -1; }
  rank_BT = H5Sget_simple_extent_ndims(dataspace);
  if(rank_BT!=2) { printf("Unexpected rank of dataspace %i expected 2\n", rank_BT); return -1; }
  rank_BT = H5Sget_simple_extent_dims(dataspace, dimsizes, maxdimsizes);
  if(rank_BT<0)  { printf("Cannot get dataspace dimensions!\n"); return -1; }
  if(iprint>0) printf("dimsizes = %i  %i\n", dimsizes[0], dimsizes[1]);

  if(readwrite==0) {
    *buffer = (float *) malloc(dimsizes[0]*dimsizes[1]*sizeof(float));
    if(*buffer==NULL) { printf("Cannot allocate memory\n"); return -1; }
    hdferr = H5Dread( dataset, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, *buffer);
    if(hdferr<0) { printf("Cannot read data to hdf!\n"); return -1; }
  } else {
    hdferr = H5Dwrite(dataset, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, *buffer);
    if(hdferr<0) { printf("Cannot write data to hdf!\n"); return -1; }
  }

  // close everything
  hdferr = H5Dclose(dataset);
  if(hdferr<0) { printf("Cannot close HDF5 dataset %s!\n", BTstr); return -1; }
  hdferr = H5Fclose(file_id);
  if(hdferr<0) { printf("Cannot close HDF5 file %s!\n", filename); return -1; }
  hdferr = H5close();
  if(hdferr<0) { printf("Cannot close HDF5 library!\n"); return -1; }

  return 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int write_viirs_destriping_attribute(char * filename, char * attrFieldStr, char * attrNameStr, float destrval){

  hid_t   file_id, dataset;
  herr_t  hdferr;
  int     retval = 0;

  hdferr = H5open();
  if(hdferr!=0) { printf("Cannot initialize HDF5 library!\n"); return -1; }
  file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
  if(file_id<0) { printf("Cannot open HDF5 file %s!\n", filename); return -1; }
  dataset = H5Dopen(file_id, attrFieldStr, H5P_DEFAULT);
  if(dataset<0) {  printf("Cannot open HDF5 dataset %s!\n", attrFieldStr); return -1; }

  if(H5Aexists(dataset, attrNameStr)>0) {
    // attribute already exists
    printf("WARNING! Data was already destriped\n");
    retval = 1;
  }
  else {
    // attribute does not exist, create it
    hid_t type_id = H5Tcopy(H5T_NATIVE_FLOAT);
    if(type_id<0)  {  printf("Cannot create a new datatype!\n"); return -1; }
    hid_t space_id = H5Screate(H5S_SCALAR);
    if(space_id<0)  {  printf("Cannot create a new dataspace!\n"); return -1; }
    hid_t attr_id = H5Acreate( dataset, attrNameStr, type_id, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if(attr_id<0) { printf("Cannot create a HDF5 attribute\n"); return -1; }
    float destrval = 1.0; 
    float *pdestrval = &destrval;
    hdferr = H5Awrite( attr_id, H5T_NATIVE_FLOAT, (const void *) pdestrval );
      if(hdferr==-1) {  printf("Cannot write attribute!\n"); return -1; }
  }
 
  // close everything
  hdferr = H5Dclose(dataset);
  if(hdferr<0) { printf("Cannot close HDF5 dataset %s!\n", attrFieldStr); return -1; }
  hdferr = H5Fclose(file_id);
  if(hdferr<0) { printf("Cannot close HDF5 file %s!\n", filename); return -1; }
  hdferr = H5close();
  if(hdferr<0) { printf("Cannot close HDF5 library!\n"); return -1; }

  return retval;
}