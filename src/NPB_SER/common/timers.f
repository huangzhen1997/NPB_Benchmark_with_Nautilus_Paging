c---------------------------------------------------------------------
c---------------------------------------------------------------------
      
      subroutine timer_clear(n)

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      implicit none
      integer n
      
      integer*8 start(64), elapsed(64)
      common /tt/ start, elapsed

      elapsed(n) = 0.0
      return
      end


c---------------------------------------------------------------------
c---------------------------------------------------------------------

      subroutine timer_start(n)

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      implicit none
      external  elapsed_time
      integer*8 elapsed_time
      integer n
      integer*8 start(64), elapsed(64)
      common /tt/ start, elapsed

      start(n) = elapsed_time()

      return
      end
      

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      subroutine timer_stop(n)

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      implicit none
      external         elapsed_time
      integer*8 elapsed_time
      integer n
      integer*8 start(64), elapsed(64)
      common /tt/ start, elapsed
      integer*8 t, now
      now = elapsed_time()
      t = now - start(n)
      elapsed(n) = elapsed(n) + t

      return
      end


c---------------------------------------------------------------------
c---------------------------------------------------------------------

      integer*8 function timer_read(n)

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      implicit none
      integer n
      integer*8 start(64), elapsed(64)
      common /tt/ start, elapsed
      
      timer_read = elapsed(n)
      return
      end


c---------------------------------------------------------------------
c---------------------------------------------------------------------

      integer*8 function elapsed_time()

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      implicit none
      external rdtsc

      integer*8 t

c This function must measure wall clock time, not CPU time. 
c Since there is no portable timer in Fortran (77)
c we call a routine compiled in C (though the C source may have
c to be tweaked). 
      call rdtsc(t)
c The following is not ok for "official" results because it reports
c CPU time not wall clock time. It may be useful for developing/testing
c on timeshared Crays, though. 
c     call second(t)

      elapsed_time = t

      return
      end
