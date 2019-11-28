@echo off

for /L %%i in (1,1,10000000) do (
gen.exe || exit
main.exe || exit
stupid.exe || exit
fc .out 2.out || exit
echo Test %%i OK
)
