!-------------------------------------------------------------------------!
!                                                                         !
!        N  A  S     P A R A L L E L     B E N C H M A R K S  3.3         !
!                                                                         !
!                      S E R I A L     V E R S I O N                      !
!                                                                         !
!                                   S P                                   !
!                                                                         !
!-------------------------------------------------------------------------!
!                                                                         !
!    This benchmark is a serial version of the NPB SP code.               !
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
c Author: R. Van der Wijngaart
c         W. Saphir
c         H. Jin
c---------------------------------------------------------------------

c---------------------------------------------------------------------
       subroutine npb_entry
c---------------------------------------------------------------------

       include  'header.h'
      
       integer          i, niter, step, fstatus, n3
       external         timer_read
       double precision mflops
       integer*8        t, tmax, timer_read, trecs(t_last)


       logical          verified
       character        class
       character        t_names(t_last)*8

c---------------------------------------------------------------------
c      Read input file (if it exists), else take
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
c         t_names(t_tzetar) = 'tzetar'
c         t_names(t_ninvr) = 'ninvr'
c         t_names(t_pinvr) = 'pinvr'
c         t_names(t_txinvr) = 'txinvr'
c         t_names(t_add) = 'add'
c         close(2)
c       else
         timeron = .false.
c       endif

c       write(*, 1000)
       call write_sp_1000
c       open (unit=2,file='inputsp.data',status='old', iostat=fstatus)

c       if (fstatus .eq. 0) then
c         write(*,233) 
c 233     format(' Reading from input file inputsp.data')
c         read (2,*) niter
cc         read (2,*) dt
c         read (2,*) grid_points(1), grid_points(2), grid_points(3)
c         close(2)
c       else
c         write(*,234) 
         call write_sp_234
         niter = niter_default
         dt    = dt_default
         grid_points(1) = problem_size
         grid_points(2) = problem_size
         grid_points(3) = problem_size
c       endif
 234   format(' No input file inputsp.data. Using compiled defaults')

c       write(*, 1001) grid_points(1), grid_points(2), grid_points(3)
       call write_sp_1001( grid_points(1), grid_points(2), 
     >                     grid_points(3) )
c       write(*, 1002) niter, dt
       call write_sp_1002(niter, dt)
c       write(*, *)

 1000 format(//,' NAS Parallel Benchmarks (NPB3.3-SER)',
     >          ' - SP Benchmark', /)
 1001     format(' Size: ', i4, 'x', i4, 'x', i4)
 1002     format(' Iterations: ', i4, '    dt: ', F10.6)

       if ( (grid_points(1) .gt. IMAX) .or.
     >      (grid_points(2) .gt. JMAX) .or.
     >      (grid_points(3) .gt. KMAX) ) then
c             print *, (grid_points(i),i=1,3)
c             print *,' Problem size too big for compiled array sizes'
             call write_sp_print1( grid_points(1),grid_points(2),
     >                             grid_points(3))
             call write_sp_print2
             goto 999
       endif
       nx2 = grid_points(1) - 2
       ny2 = grid_points(2) - 2
       nz2 = grid_points(3) - 2

       call set_constants

       do i = 1, t_last
          call timer_clear(i)
       end do

       call exact_rhs

       call initialize

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

          if (mod(step, 20) .eq. 0 .or. step .eq. 1) then
c             write(*, 200) step
             call write_sp_200(step)
 200         format(' Time step ', i4)
          endif

          call adi

       end do

       call timer_stop(1)
       tmax = timer_read(1)
       
       call verify(niter, class, verified)

       if( tmax .ne. 0. ) then
          n3 = grid_points(1)*grid_points(2)*grid_points(3)
          t = (grid_points(1)+grid_points(2)+grid_points(3))/3.0
          mflops = (881.174 * float( n3 )
     >             -4683.91 * t**2
     >             +11484.5 * t
     >             -19272.4) * float( niter ) / (tmax*1000000.0d0)
       else
          mflops = 0.0
       endif

      call w_c_print_results('SP',class, grid_points(1), 
     >     grid_points(2), grid_points(3), niter, 
     >     tmax, 
     >     verified)
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