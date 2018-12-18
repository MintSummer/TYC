@echo off 
g++ -g rand.cpp -o rand
g++ -g 2151.cpp -o 2151

:loop
rand > rand.in
2151 < rand.in > tyc.out
ans < rand.in > ans.out
fc ans.out tyc.out
if not errorlevel 1 goto loop
pause