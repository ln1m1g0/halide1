# Atividade prática - Projeto Final
## Curso de Linguagem de Programação Específica para IA - Lux.AI

### Marcell Bruno Sousa e Silva - .github.

### Informações iniciais
Nesta atividade vocês devem exercitar, os conhecimentos abordados na segunda semana do curso. Vocês iram implementar o nonphotorrealistic rendering. A pipeline pode ser vista nos slides, bem como um protótipo em Python.

**LEIAM COM ATENÇÂO**
**VERIFIQUEM O QUE DEVE SER ENTREGUE NO CLASSROOM ATRAVÉS VÍDEO E/OU DENTRO DA ATIVIDADE NO CLASSROOM**
**SIGAM AS INFORMAÇÔES NOS COMENTÁRIOS DOS ARQUIVOS DA LISTA ABAIXO**

Ao realizar o commit, vocês DEVEM APENAS manter edições aos seguintes arquivos: 
-   HalideElementwiseMult.hpp
-   HalideNPR.hpp
-   HalideQuantize.hpp
-   HalideXDoG.hpp
-   README.md

Qualquer outra modificação poderá ser vista como interferência nos testes de código e, portanto, resultaram na penalização do aluno (ex.: anulação da atividade).


No topo deste README.md, no local indicado (".Seu nome aqui. - .github."), adicionar seu nome (da forma como se encontra na lista do classroom) e id do github.

### Executando o código
É necessário que pytest e OpenCV estejam instalados:
```
pip3 install pytest opencv-python
```
Para usar o Makefile, é necessário que o diretório do Halide esteja acessível através da variável de linha de comando HALIDE_ROOT (ex.: os includes estariam em $HALIDE_ROOT/include).

`make test` irá ser utilizado para obter sua pontuação final e roda os testes em `run_test.py` após executar sua versão da pipeline com combinações específicas dos argumentos.

Vocês podem simplesmente usar os inputs e o arquivo alteráveis (conforme lista acima), da forma que quiserem (ex.: criar um projeto separado no Visual Studio e depois apenas copiar para seu repositório da atividade) desde que não alterem os testes e sigam a lista de tarefas da seção de informações iniciais acima.

Busquem testar localmente antes de subirem. Evitem spam de commits no repositório de avaliação. Ele serve apenas para avaliação final. É preferível que subam seus arquivos para um serviço de cloud ou outro repositório caso o intuito seja apenas salvar o progresso.
