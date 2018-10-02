@echo off
REM executa os testes da pasta de scripts do projeto ModularT2
cd ..\Scripts\

..\Produtos\TRAB1-1.EXE      /sTesteLista > TesteLista.log
..\Produtos\TRAB1-2.EXE      /sTesteVertice > TesteVertice.log
..\Produtos\TRAB1-3.EXE      /sTesteGrafo > TesteGrafo.log
