
c---------------------------------------------------------------------
c---------------------------------------------------------------------

      subroutine read_input

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      implicit none

      include 'applu.incl'

      integer  fstatus


c---------------------------------------------------------------------
c    if input file does not exist, it uses defaults
c       ipr = 1 for detailed progress output
c       inorm = how often the norm is printed (once every inorm iterations)
c       itmax = number of pseudo time steps
c       dt = time step
c       omega 1 over-relaxation factor for SSOR
c       tolrsd = steady state residual tolerance levels
c       nx, ny, nz = number of grid points in x, y, z directions
c---------------------------------------------------------------------

c         write(*, 1000)
         call write_read_input_1000()

c         open (unit=3,file='inputlu.data',status='old',
c     >         access='sequential',form='formatted', iostat=fstatus)
c         if (fstatus .eq. 0) then

c            write(*, *) 'Reading from input file inputlu.data'

c            read (3,*)
c            read (3,*)
c            read (3,*) ipr, inorm
c            read (3,*)
c            read (3,*)
c            read (3,*) itmax
c            read (3,*)
c            read (3,*)
c            read (3,*) dt
c            read (3,*)
c            read (3,*)
c            read (3,*) omega
c            read (3,*)
c            read (3,*)
c            read (3,*) tolrsd(1),tolrsd(2),tolrsd(3),tolrsd(4),tolrsd(5)
c            read (3,*)
c            read (3,*)
c            read (3,*) nx0, ny0, nz0
c            close(3)
c         else
            ipr = ipr_default
            inorm = inorm_default
            itmax = itmax_default
            dt = dt_default
            omega = omega_default
            tolrsd(1) = tolrsd1_def
            tolrsd(2) = tolrsd2_def
            tolrsd(3) = tolrsd3_def
            tolrsd(4) = tolrsd4_def
            tolrsd(5) = tolrsd5_def
            nx0 = isiz1
            ny0 = isiz2
            nz0 = isiz3
c         endif

c---------------------------------------------------------------------
c   check problem size
c---------------------------------------------------------------------

         if ( ( nx0 .lt. 4 ) .or.
     >        ( ny0 .lt. 4 ) .or.
     >        ( nz0 .lt. 4 ) ) then

c            write (*,2001)
            call write_ri_2001()
 2001       format (5x,'PROBLEM SIZE IS TOO SMALL - ',
     >           /5x,'SET EACH OF NX, NY AND NZ AT LEAST EQUAL TO 5')
c            stop                   
c            CL:stop statment generates some complex functions, instead I use return
            return

         end if

         if ( ( nx0 .gt. isiz1 ) .or.
     >        ( ny0 .gt. isiz2 ) .or.
     >        ( nz0 .gt. isiz3 ) ) then

c            write (*,2002)
            call write_ri_2002()
 2002       format (5x,'PROBLEM SIZE IS TOO LARGE - ',
     >           /5x,'NX, NY AND NZ SHOULD BE EQUAL TO ',
     >           /5x,'ISIZ1, ISIZ2 AND ISIZ3 RESPECTIVELY')
c            stop
c            CL:stop statment generates some complex functions, instead I use return
            return

         end if


c         write(*, 1001) nx0, ny0, nz0
         call write_ri_1001(nx0,ny0,nz0)
c         write(*, 1002) itmax
         call write_ri_1002(itmax)
c         write(*, *)


 1000 format(//,' NAS Parallel Benchmarks (NPB3.3-SER)',
     >          ' - LU Benchmark', /)
 1001    format(' Size: ', i4, 'x', i4, 'x', i4)
 1002    format(' Iterations: ', i4)



      return
      end


