SHELL=/bin/sh
BENCHMARK=ft
BENCHMARKU=FT

include ../config/make.def

include ../sys/make.common

OBJS = appft.o auxfnct.o fft3d.o mainft.o verify.o \
       ${COMMON}/${RAND}.o ${COMMON}/w_c_print_results.o \
       ${COMMON}/timers.o ${COMMON}/rdtsc.o ft_opt_helper.o \
       ${COMMON}/s_sin.o

#${PROGRAM}: config ${OBJS}
#	${FLINK} ${FLINKFLAGS} -o ${PROGRAM} ${OBJS} ${F_LIB}

${PROGRAM}: config ${OBJS}
	rm -rf ./tmp ;\
	mkdir tmp ;\
	cp ${OBJS} ./tmp ;\
	cd ./tmp ;\
	ar rcs libnpb.a *.o ;\
	mv libnpb.a ../../../../ ;\
	cd .. 



.f.o:
	${FCOMPILE} $<

appft.o:	appft.f  global.h npbparams.h
auxfnct.o:	auxfnct.f  global.h npbparams.h
fft3d.o:	fft3d.f  global.h npbparams.h
mainft.o:	mainft.f  global.h npbparams.h
verify.o:	verify.f  global.h npbparams.h
ft_opt_helper.o: ft_opt_helper.c
	${CCOMPILE} ft_opt_helper.c

clean:
	- rm -f *.o *~ mputil*
	- rm -f ft npbparams.h core
