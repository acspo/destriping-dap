INC=-I. -I../destripe/ -I/usr/include -I/usr/include/hdf/
LIBS=-lfftw3f_omp -lfftw3f  -lmfhdf -ldf -lpthread -lm
CC=gcc
LD=gcc
CFLAGS=-g -fopenmp -O2 $(INC)
LDFLAGS=$(LIBS) -fopenmp
TARG=destripe_modis
OFILES=\
	destripe_modis.o\

HFILES=\
	readwrite_modis.c\
	../destripe/allocate_2d.c\
	../destripe/compute_binary_matrix.c\
	../destripe/compute_meshgrid_dct.c\
	../destripe/compute_nly_filter.c\
	../destripe/compute_poisson_rec.c\
	../destripe/destripe.h\
	../destripe/destripe_main.c\
	../destripe/destripe_main_padframe.c\
	../destripe/fill_restore_viirs_bowtie.c\
	../destripe/get_nif_ndf.c\

all: $(TARG)

$(TARG): $(OFILES)
	$(LD) -o $(TARG) $(OFILES) $(LDFLAGS)

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $<

install: $(TARG)
	cp $(TARG) /usr/local/bin/

clean:
	rm -f $(OFILES) $(TARG)
