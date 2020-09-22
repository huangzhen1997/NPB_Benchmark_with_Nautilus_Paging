SHELL=/bin/sh
BENCHMARK=ep
BENCHMARKU=EP

include ../config/make.def

OBJS = ep.o ${COMMON}/w_c_print_results.o ${COMMON}/${RAND}.o \
       ${COMMON}/timers.o ${COMMON}/fdmlib.o \
       ${COMMON}/rdtsc.o ep_opt_helper.o ${COMMON}/fdmlib.o

include ../sys/make.common


${PROGRAM}: config ${OBJS}
	rm -rf ./tmp ;\
	mkdir tmp ;\
	cp ${OBJS} ./tmp ;\
	cd ./tmp ;\
	ar rcs libnpb.a *.o ;\
	mv libnpb.a ../../../../ ;\
	cd .. 
	

#${PROGRAM}: config ${OBJS}
#	ar rcs libep.a ${OBJS} ;\
#	mv libep.a /home/conghao/nautilus ;\

#${FLINK} ${FLINKFLAGS} -o ${PROGRAM} ${OBJS} ${F_LIB}


ep.o:		ep.f npbparams.h
	${FCOMPILE} ep.f

ep_opt_helper.o: ep_opt_helper.c
	${CCOMPILE} $<

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.h core



