      subroutine verify(class, verified)

      include 'header.h'

      double precision norm, calc_norm, epsilon, norm_dif, norm_ref
      external         calc_norm
      character        class
      logical          verified
       
c.....tolerance level
      epsilon = 1.0d-08

c.....compute the temperature integral over the whole domain
      norm = calc_norm()

      verified = .true.
      if     ( class .eq. 'S' ) then
        norm_ref = 0.1890013110962D-02
      elseif ( class .eq. 'W' ) then
        norm_ref = 0.2569794837076D-04
      elseif ( class .eq. 'A' ) then
        norm_ref = 0.8939996281443D-04
      elseif ( class .eq. 'B' ) then
        norm_ref = 0.4507561922901D-04
      elseif ( class .eq. 'C' ) then
        norm_ref = 0.1544736587100D-04
      elseif ( class .eq. 'D' ) then
        norm_ref = 0.1577586272355D-05
      else
        class = 'U'
        norm_ref = 1.d0
        verified = .false.
      endif         

      norm_dif = dabs((norm - norm_ref)/norm_ref)

c---------------------------------------------------------------------
c    Output the comparison of computed results to known cases.
c---------------------------------------------------------------------

c      print *

      if (class .ne. 'U') then
c         write(*, 1990) class
c 1990    format(' Verification being performed for class ', a)
         call write_verify_1990(class)
c         write (*,2000) epsilon
c 2000    format(' accuracy setting for epsilon = ', E20.13)
         call write_verify_2000(epsilon)
      else 
c         write(*, 1995)
c 1995    format(' Unknown class')
         call write_verify_1995()
      endif

      if (class .ne. 'U') then
c         write (*,2001) 
         call write_verify_2001()
      else
c         write (*, 2005)
         call write_verify_2005()
      endif

c 2001 format(' Comparison of temperature integrals')
c 2005 format(' Temperature integral')
      if (class .eq. 'U') then
c         write(*, 2015) norm
         call write_verify_2015(norm)
      else if (norm_dif .le. epsilon) then
c         write (*,2011) norm, norm_ref, norm_dif
         call write_verify_2011(norm, norm_ref, norm_dif)
      else 
         verified = .false.
c         write (*,2010) norm, norm_ref, norm_dif
         call write_verify_2010(norm, norm_ref, norm_dif)
      endif

 2010 format(' FAILURE: ', E20.13, E20.13, E20.13)
 2011 format('          ', E20.13, E20.13, E20.13)
 2015 format('          ', E20.13)
        
      if (class .eq. 'U') then
c        write(*, 2022)
        call write_verify_2022()
c        write(*, 2023)
        call write_verify_2023()
 2022   format(' No reference values provided')
 2023   format(' No verification performed')
      else if (verified) then
c        write(*, 2020)
        call write_verify_2020()
 2020   format(' Verification Successful')
      else
c        write(*, 2021)
        call write_verify_2021()
 2021   format(' Verification failed')
      endif

      return
      end
