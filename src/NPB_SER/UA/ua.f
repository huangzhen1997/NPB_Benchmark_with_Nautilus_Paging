c-------------------------------------------------------------------------c
c                                                                         c
c        N  A  S     P A R A L L E L     B E N C H M A R K S  3.3         c
c                                                                         c
c                      S E R I A L     V E R S I O N                      c
c                                                                         c
c                                   U A                                   c
c                                                                         c
c-------------------------------------------------------------------------c
c                                                                         c
c    This benchmark is a serial version of the NPB UA code.               c
c    Refer to NAS Technical Report NAS-04-006 for details                 c
c                                                                         c
c    Permission to use, copy, distribute and modify this software         c
c    for any purpose with or without fee is hereby granted.  We           c
c    request, however, that all derived work reference the NAS            c
c    Parallel Benchmarks 3.3. This software is provided "as is"           c
c    without express or implied warranty.                                 c
c                                                                         c
c    Information on NPB 3.3, including the technical report, the          c
c    original specifications, source code, results and information        c
c    on how to submit new results, is available at:                       c
c                                                                         c
c           http://www.nas.nasa.gov/Software/NPB/                         c
c                                                                         c
c    Send comments or suggestions to  npb@nas.nasa.gov                    c
c                                                                         c
c          NAS Parallel Benchmarks Group                                  c
c          NASA Ames Research Center                                      c
c          Mail Stop: T27A-1                                              c
c          Moffett Field, CA   94035-1000                                 c
c                                                                         c
c          E-mail:  npb@nas.nasa.gov                                      c
c          Fax:     (650) 604-3957                                        c
c                                                                         c
c-------------------------------------------------------------------------c

c---------------------------------------------------------------------
c
c Author: H. Feng
c         R. Van der Wijngaart
c---------------------------------------------------------------------

      subroutine npb_ua_entry()
      include 'header.h'

      integer          step, ie,iside,i,j,k, fstatus
      external         timer_read
      integer*8        timer_read, tmax, nelt_tot
      double precision mflops
      character        class
      logical          ifmortar, verified

      double precision t2, trecs(t_last)
      character t_names(t_last)*10
      external write_1000, write_234

c---------------------------------------------------------------------
c     Read input file (if it exists), else take
c     defaults from parameters
c---------------------------------------------------------------------
          
c      open (unit=2,file='timer.flag',status='old', iostat=fstatus)
c      if (fstatus .eq. 0) then
c         timeron = .true.
c         t_names(t_total) = 'total'
c         t_names(t_init) = 'init'
c         t_names(t_convect) = 'convect'
c         t_names(t_transfb_c) = 'transfb_c'
c         t_names(t_diffusion) = 'diffusion'
c         t_names(t_transf) = 'transf'
c         t_names(t_transfb) = 'transfb'
c         t_names(t_adaptation) = 'adaptation'
cc         t_names(t_transf2) = 'transf+b'
cc         t_names(t_add2) = 'add2'
c         close(2)
c      else
c         timeron = .false.
c      endif
      timeron = .false.
c      write (*,1000) 
      call write_1000()
c      open (unit=2,file='inputua.data',status='old', iostat=fstatus)

c      if (fstatus .eq. 0) then
c        write(*,233) 
c 233    format(' Reading from input file inputua.data')
c        read (2,*) fre
c        read (2,*) niter
c        read (2,*) nmxh
c        read (2,*) alpha
c        class = 'U'
c        close(2)
c      else
c        write(*,234) 
c        fre        = fre_default
c        niter      = niter_default
c        nmxh       = nmxh_default
c        alpha      = alpha_default
c        class      = class_default
c      endif
c 234  format(' No input file inputsp.data. Using compiled defaults')
      call write_234()
      fre        = fre_default
      niter      = niter_default
      nmxh       = nmxh_default
      alpha      = alpha_default
      class      = class_default

      dlmin = 0.5d0**refine_max
      dtime = 0.04d0*dlmin

c      write (*,1001) refine_max
c      write (*,1002) fre
c      write (*,1003) niter, dtime
c      write (*,1004) nmxh
c      write (*,1005) alpha

c 1000 format(//,' NAS Parallel Benchmarks (NPB3.3-SER)',
c     >          ' - UA Benchmark', /)
c 1001 format(' Levels of refinement: ', i8)
c 1002 format(' Adaptation frequency: ', i8)
c 1003 format(' Time steps:           ', i8, '    dt: ', g15.6)
c 1004 format(' CG iterations:        ', i8)
c 1005 format(' Heat source radius:   ', f8.4,/)
      call write_1001(refine_max)
      call write_1002(fre)
      call write_1003(niter, dtime)
      call write_1004(nmxh)
      call write_1005(alpha)
      

      do i = 1, t_last
         call timer_clear(i)
      end do
      if (timeron) call timer_start(t_init)

c.....set up initial mesh (single element) and solution (all zero)
      call create_initial_grid

      call r_init(ta1,ntot,0.d0)
      call nr_init(sje,4*6*nelt,0)

c.....compute tables of coefficients and weights      
      call coef 
      call geom1

c.....compute the discrete laplacian operators
      call setdef

c.....prepare for the preconditioner
      call setpcmo_pre

c.....refine initial mesh and do some preliminary work
      time = 0.d0
      call mortar
      call prepwork
      call adaptation(ifmortar,0)
      if (timeron) call timer_stop(t_init)

      call timer_clear(1)

      time = 0.d0
      do step= 0, niter

        if (step .eq. 1) then
c.........reset the solution and start the timer, keep track of total no elms
          call r_init(ta1, ntot, 0.d0)
          time = 0.d0
          nelt_tot = 0.d0
          do i = 1, t_last
             if (i.ne.t_init) call timer_clear(i)
          end do
          call timer_start(1)          
        endif

c.......advance the convection step 
        call convect(ifmortar)

        if (timeron) call timer_start(t_transf2)
c.......prepare the intital guess for cg
        call transf(tmort,ta1)

c.......compute residual for diffusion term based on intital guess

c.......compute the left hand side of equation, lapacian t
        do ie = 1,nelt
          call laplacian(ta2(1,1,1,ie),ta1(1,1,1,ie),size_e(ie))
        end do
c.......compute the residual 
        do ie = 1, nelt
          do k=1,lx1
            do j=1,lx1
              do i=1,lx1
                trhs(i,j,k,ie) = trhs(i,j,k,ie) - ta2(i,j,k,ie)
              end do
            end do
          end do
        end do
c.......get the residual on mortar 
        call transfb(rmor,trhs)
        if (timeron) call timer_stop(t_transf2)

c.......apply boundary condition: zero out the residual on domain boundaries

c.......apply boundary conidtion to trhs
        do ie=1,nelt  
          do iside=1,nsides
            if (cbc(iside,ie).eq.0) then
              call facev(trhs(1,1,1,ie),iside,0.d0)
            end if
          end do
        end do
c.......apply boundary condition to rmor
        call col2(rmor,tmmor,nmor)

c.......call the conjugate gradient iterative solver
        call diffusion(ifmortar)

c.......add convection and diffusion
        if (timeron) call timer_start(t_add2)
        call add2(ta1,t,ntot)
        if (timeron) call timer_stop(t_add2)

c.......perform mesh adaptation
        time=time+dtime
        if ((step.ne.0).and.(step/fre*fre .eq. step)) then
           if (step .ne. niter) then
             call adaptation(ifmortar,step)
           end if
        else
          ifmortar = .false.
        end if
        nelt_tot = nelt_tot + dble(nelt)
      end do

      call timer_stop(1)
      tmax = timer_read(1)
       
      call verify(class, verified)

c.....compute millions of collocation points advanced per second.
c.....diffusion: nmxh advancements, convection: 1 advancement
      mflops = nelt_tot*dble(lx1*lx1*lx1*(nmxh+1))/(tmax*1.d6)

      call w_c_print_results(class, refine_max, 0, 0, niter, 
     &     tmax, mflops, verified)

c---------------------------------------------------------------------
c      More timers
c---------------------------------------------------------------------
      if (.not.timeron) goto 999

c      do i=1, t_last
c         trecs(i) = timer_read(i)
c      end do
c      if (tmax .eq. 0.0) tmax = 1.0

c      write(*,800)
c 800  format('  SECTION     Time (secs)')
c      do i=1, t_last
c         write(*,810) t_names(i), trecs(i), trecs(i)*100./tmax
c         if (i.eq.t_transfb_c) then
c            t2 = trecs(t_convect) - trecs(t_transfb_c)
c            write(*,820) 'sub-convect', t2, t2*100./tmax
c         else if (i.eq.t_transfb) then
c            t2 = trecs(t_diffusion) - trecs(t_transf) - trecs(t_transfb)
c            write(*,820) 'sub-diffuse', t2, t2*100./tmax
c         endif
c 810     format(2x,a10,':',f9.3,'  (',f6.2,'%)')
c 820     format('    --> ',a11,':',f9.3,'  (',f6.2,'%)')
c      end do

 999  continue

      end 

