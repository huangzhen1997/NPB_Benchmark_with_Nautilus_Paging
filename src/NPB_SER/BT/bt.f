!-------------------------------------------------------------------------!
!                                                                         !
!        N  A  S     P A R A L L E L     B E N C H M A R K S  3.3         !
!                                                                         !
!                      S E R I A L     V E R S I O N                      !
!                                                                         !
!                                   B T                                   !
!                                                                         !
!-------------------------------------------------------------------------!
!                                                                         !
!    This benchmark is a serial version of the NPB BT code.               !
!    Refer to NAS Technical Reports 95-020 and 99-011 for details.        !
!                                                                         !
!    Permission to use, copy, distribute and modify this software         !
!    for any purpose with or without fee is hereby granted.  We           !
!    request, however, that all derived work reference the NAS            !
!    Parallel Benchmarks 3.3. This software is provided "as is"           !
!    without express or implied warranty.                                 !
!                                                                         !
!    Information on NPB 3.3, including the technical report, the          !
!    original specifications, source code, results and information        !
!    on how to submit new results, is available at:                       !
!                                                                         !
!           http://www.nas.nasa.gov/Software/NPB/                         !
!                                                                         !
!    Send comments or suggestions to  npb@nas.nasa.gov                    !
!                                                                         !
!          NAS Parallel Benchmarks Group                                  !
!          NASA Ames Research Center                                      !
!          Mail Stop: T27A-1                                              !
!          Moffett Field, CA   94035-1000                                 !
!                                                                         !
!          E-mail:  npb@nas.nasa.gov                                      !
!          Fax:     (650) 604-3957                                        !
!                                                                         !
!-------------------------------------------------------------------------!

c---------------------------------------------------------------------
c
c Authors: R. Van der Wijngaart
c          T. Harris
c          M. Yarrow
c          H. Jin
c
c---------------------------------------------------------------------

c---------------------------------------------------------------------
       subroutine npb_entry
c---------------------------------------------------------------------

       include  'header.h'
      
       integer i, niter, step, fstatus
       double precision navg, mflops, n3

       external timer_read
       integer*8 tmax, timer_read, t, trecs(t_last)
       logical verified
       character class
       character        t_names(t_last)*8

c---------------------------------------------------------------------
c      Root node reads input file (if it exists) else takes
c      defaults from parameters
c---------------------------------------------------------------------
          
c       open (unit=2,file='timer.flag',status='old', iostat=fstatus)
c       if (fstatus .eq. 0) then
c         timeron = .true.
c         t_names(t_total) = 'total'
c         t_names(t_rhsx) = 'rhsx'
c         t_names(t_rhsy) = 'rhsy'
c         t_names(t_rhsz) = 'rhsz'
c         t_names(t_rhs) = 'rhs'
c         t_names(t_xsolve) = 'xsolve'
c         t_names(t_ysolve) = 'ysolve'
c         t_names(t_zsolve) = 'zsolve'
c         t_names(t_rdis1) = 'redist1'
c         t_names(t_rdis2) = 'redist2'
c         t_names(t_add) = 'add'
c         close(2)
c       else
         timeron = .false.
c       endif

c       write(*, 1000)
       call write_bt_1000
c       open (unit=2,file='inputbt.data',status='old', iostat=fstatus)

c       if (fstatus .eq. 0) then
c         write(*,233) 
c 233     format(' Reading from input file inputbt.data')
c         read (2,*) niter
c         read (2,*) dt
c         read (2,*) grid_points(1), grid_points(2), grid_points(3)
c         close(2)
c       else
c         write(*,234) 
         call write_bt_234
         niter = niter_default
         dt    = dt_default
         grid_points(1) = problem_size
         grid_points(2) = problem_size
         grid_points(3) = problem_size
c       endif
 234   format(' No input file inputbt.data. Using compiled defaults')

c       write(*, 1001) grid_points(1), grid_points(2), grid_points(3)
       call write_bt_1001(grid_points(1), grid_points(2), 
     >                    grid_points(3))
c       write(*, 1002) niter, dt
       call write_bt_1002(niter, dt)
c       write(*, *)

 1000  format(//, ' NAS Parallel Benchmarks (NPB3.3-SER)',
     >            ' - BT Benchmark',/)
 1001  format(' Size: ', i4, 'x', i4, 'x', i4)
 1002  format(' Iterations: ', i4, '    dt: ', F10.6)

       if ( (grid_points(1) .gt. IMAX) .or.
     >      (grid_points(2) .gt. JMAX) .or.
     >      (grid_points(3) .gt. KMAX) ) then
c             print *, (grid_points(i),i=1,3)
             call write_bt_001(grid_points(1), grid_points(2), 
     >                         grid_points(3))
c             print *,' Problem size too big for compiled array sizes'
             call write_bt_002
             goto 999
       endif


       call set_constants

       do i = 1, t_last
          call timer_clear(i)
       end do

       call initialize

       call exact_rhs

c---------------------------------------------------------------------
c      do one time step to touch all code, and reinitialize
c---------------------------------------------------------------------
       call adi
       call initialize

       do i = 1, t_last
          call timer_clear(i)
       end do
       call timer_start(1)

       do  step = 1, niter

          if (mod(step, 20) .eq. 0 .or. 
     >        step .eq. 1) then
c             write(*, 200) step
             call write_bt_200(step)
 200         format(' Time step ', i4)
          endif

          call adi

       end do

       call timer_stop(1)
       tmax = timer_read(1)
       
       call verify(niter, class, verified)

       n3 = 1.0d0*grid_points(1)*grid_points(2)*grid_points(3)
       navg = (grid_points(1)+grid_points(2)+grid_points(3))/3.0
       if( tmax .ne. 0. ) then
          mflops = 1.0e-6*float(niter)*
     >  (3478.8*n3-17655.7*navg**2+28023.7*navg)
     >  / tmax
       else
          mflops = 0.0
       endif
       call w_c_print_results('BT', class, grid_points(1), 
     >  grid_points(2), grid_points(3), niter,
     >  tmax, verified)
c---------------------------------------------------------------------
c      More timers
c---------------------------------------------------------------------
       if (.not.timeron) goto 999

       do i=1, t_last
          trecs(i) = timer_read(i)
       end do

       if (tmax .eq. 0.0) tmax = 1.0
c       write(*,800)
 800   format('  SECTION   Time (secs)')
       do i=1, t_last
c          write(*,810) t_names(i), trecs(i), trecs(i)*100./tmax
          if (i.eq.t_rhs) then
             t = trecs(t_rhsx) + trecs(t_rhsy) + trecs(t_rhsz)
c             write(*,820) 'sub-rhs', t, t*100./tmax
             t = trecs(t_rhs) - t
c             write(*,820) 'rest-rhs', t, t*100./tmax
          elseif (i.eq.t_zsolve) then
             t = trecs(t_zsolve) - trecs(t_rdis1) - trecs(t_rdis2)
c             write(*,820) 'sub-zsol', t, t*100./tmax
          elseif (i.eq.t_rdis2) then
             t = trecs(t_rdis1) + trecs(t_rdis2)
c             write(*,820) 'redist', t, t*100./tmax
          endif
 810      format(2x,a8,':',f9.3,'  (',f6.2,'%)')
 820      format('    --> ',a8,':',f9.3,'  (',f6.2,'%)')
       end do

 999   continue

       end

