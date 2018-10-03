@echo off
REM executa os testes da pasta de scripts do projeto ModularT2
cd ..\Scripts\

..\Produto\TRAB2-1.EXE      /sTesteLista > TesteLista.log
..\Produto\TRAB2-2.EXE      /sTesteVertice > TesteVertice.log
..\Produto\TRAB2-3.EXE      /sTesteGrafo > TesteGrafo.log
