SHELL=/bin/sh
BENCHMARK=is
BENCHMARKU=IS

include ../config/make.def

include ../sys/make.common

OBJS = is.o \
       ${COMMON}/c_print_results.o \
       ${COMMON}/c_timers.o \
       ${COMMON}/rdtsc.o


#${PROGRAM}: config ${OBJS}
#	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}
${PROGRAM}: config ${OBJS}
	rm -rf ./tmp ;\
	mkdir tmp ;\
	cp ${OBJS} ./tmp ;\
	cd ./tmp ;\
	ar rcs libnpb.a *.o ;\
	mv libnpb.a ../../../../ ;\
	cd .. 

.c.o:
	${CCOMPILE} $<

is.o:             is.c  npbparams.h


clean:
	- rm -f *.o *~ mputil*
	- rm -f npbparams.h core
