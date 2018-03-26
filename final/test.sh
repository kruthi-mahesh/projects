#!/bin/bash

x=1
C=8
c=1 
B=32
b=1
M=32
E=3
e=1
ch=1


while [ $c -le 100 ]
do
  ./a.out $c $B $M $E $ch < sample.txt

  c=$(( $c + 1))	

done

ch=2
while [ $b -le 32 ]
do
  ./a.out $C $b $M $E $ch< sample.txt

  b=$(( $b + 1))	

done


ch=3

S=$(( ($C * 1024) / ($E * $B) ))

s=1
S1=1

while [ $S1 -lt $S ]
do
	S1=$(( $S1 * 2))
	s=$(( $s + 1 ))
done

S=$(( $S1 ))

while [ $e -le $S ]
do
  ./a.out $C $B $M $e $ch < sample.txt
  

  e=$(( $e + 1))	

done