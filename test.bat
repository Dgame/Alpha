@echo off
for %%a in (0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 16, 17, 18, 21, 22, 23) do gcc -o out.exe Output/out%%a.s rt.c && out.exe && del out.exe