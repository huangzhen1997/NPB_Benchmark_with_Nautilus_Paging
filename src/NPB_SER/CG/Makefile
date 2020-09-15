SHELL=/bin/sh
BENCHMARK=cg
BENCHMARKU=CG

include ../config/make.def

OBJS = cg.o  \
       ${COMMON}/${RAND}.o ${COMMON}/timers.o ${COMMON}/rdtsc.o \
       ${COMMON}/w_c_print_results.o ${COMMON}/s_sin.o

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
#	${FLINK} ${FLINKFLAGS} -o ${PROGRAM} ${OBJS} ${F_LIB}

cg.o:		cg.f  globals.h npbparams.h
	${FCOMPILE} cg.f

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.h core



