SHELL=/bin/sh
BENCHMARK=mg
BENCHMARKU=MG

include ../config/make.def

OBJS = mg.o ${COMMON}/w_c_print_results.o  \
       ${COMMON}/${RAND}.o ${COMMON}/timers.o ${COMMON}/rdtsc.o \
       mg_opt_helper.o ${COMMON}/s_sin.o

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

mg.o:		mg.f globals.h npbparams.h
	${FCOMPILE} mg.f

mg_opt_helper.o: mg_opt_helper.c
	${CCOMPILE} $<

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.h core



