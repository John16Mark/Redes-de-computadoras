@echo off
g++ trama\trama.cpp -o trama\tr.exe
cd trama
tr.exe > out.txt
cd ..