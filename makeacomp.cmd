make /facomp.mak
tdump acomp.dll >#acomp.dmp
implib -f acomp acomp.dll
tlib  acomp.lib, #acomp.lst
pause