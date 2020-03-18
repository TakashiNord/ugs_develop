#

$fnm='jhkiokn'

;# где все это лежит
$fn1="param.txt" ;
$fn2="uf_param_indices.h" ;


$s1=0.0;
$s2=0.0;
; # -------------------------------------------------------------------------

  open (FH1, "+< $fn1") or die "Open: $'" ;
  @arrFile1=<FH1> ;


  open (FH2, "+< $fn2") or die "Open: $'" ;
  @arrFile2=<FH2> ;

  @arrFiled= grep { $_!~ m/($fnm)/i } @arrFile1 ;

  print @arrFiled  ;
  ;## print FH @arrFiled or die "Printing: $!" ;


  close(FH1) or die "Closing: $!" ;
  close(FH2) or die "Closing: $!" ;


; # -------------------------------------------------------------------------

print "Ready _END_ \n"  ;

__END__