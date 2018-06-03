# Monitoria
## O Problema

O departamento de ciência da computação de uma universidade tem um
assistente de ensino (AE) que ajuda os estudantes de graduação em suas
tarefas de programação durante as horas normais de expediente. O
escritório do AE é pequeno e só tem espaço para uma mesa com uma
cadeira e um computador. Quando não há estudantes que precisem de
ajuda durante as horas de expediente, o AE senta-se à mesa e tira uma
soneca. Se um estudante chega durante as horas de expediente e
encontra o AE dormindo, deve acordá-lo para pedir ajuda. Se um
estudante chega e encontra o AE ajudando outro estudante, deve sentarse
em uma das cadeiras do corredor e esperar. Se não houver cadeiras
disponíveis, o estudante voltará mais tarde.
Usando threads, locks mutex e semáforos do POSIX, implemente uma
solução que coordene as atividades do AE e os estudantes. Detalhes desse
exercício são fornecidos abaixo.

_Os Estudantes e o AE_

Usando o Pthreads, comece criando n estudantes (n aleatório, podendo
variar de 3 até 40). Cada estudante será executado como um thread
separado. O AE também será executado como um thread separado. Os
threads de estudantes se alternarão entre a programação por um período
de tempo aleatório e a busca de ajuda do AE. Se o AE estiver disponível,
eles obterão ajuda e, após receber ajuda 3 vezes, encerrarão sua
execução. Caso contrário, sentarão em uma cadeira no corredor (a
quantidade c de cadeiras deve ser igual a metade da quantidade n de
estudantes) ou, se não houver cadeiras disponíveis, voltarão a programar
e procurarão ajuda em um momento posterior. Se um estudante chegar
e notar que o AE está dormindo, deve notificar o AE usando um semáforo.
Quando o AE terminar de ajudar um estudante, deve verificar se há
estudantes esperando por ajuda no corredor. Se houver, o AE deve ajudar
esses estudantes, um de cada vez. Se não houver estudantes presentes,
o AE pode voltar a dormir. Talvez a melhor opção para a simulação da
programação dos estudantes — assim como do AE fornecendo ajuda a um
estudante — seja fazer os threads apropriados adormecerem por um
período de tempo aleatório.

Sempre que o estado de algum thread mudar, uma mensagem na tela
deve ser exibida indicando seu novo estado. Por exemplo, quando o AE
estiver atendendo o estudante 3, deve-se imprimir na tela “AE ajudando
o estudante 3”. Quando um estudante estiver sentado na fila, deve-se
imprimir “Estudante 3 sentado na cadeira” e assim por diante.

Caso não tenha o gcc instalado localmente, utilize a seção [Usando o docker](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-docker) ou [Usando o makefile](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-makefile)

## Como usar

1. Instale o [Docker CE](https://docs.docker.com/install/) ***

2. Clone esse repositório - `git clone https://github.com/FSO-DOS-AMIGOS/sudoku.git`

3. Navegue até a pasta recém-clonada.

4. Siga alguma das seções de execução: [Docker](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-docker), [Makefile](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-makefile) ou [Gcc](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-gcc)

*** _Passo Opcional_

NOTA: Se você não seguiu os [passos pós-instalação](https://docs.docker.com/install/linux/linux-postinstall/) para o docker você precisará usar `sudo` junto as intruções das seções [Usando o docker](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-docker) ou [Usando o makefile](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-makefile), por exemplo:

`sudo docker build -t sudoku .`
ou
`sudo make build`

### Usando o gcc
1. Compile o arquivo c 
``` bash
gcc -o monitoria src/main.c
```

2. Execute o binário gerado
``` bash
./monitoria
```

### Usando o makefile
1. Construa o ambiente:

``` bash
make build 
```

2. Rode o ambiente pré-construído

``` bash
make run
```

#### Outros comandos úteis

Remove o ambiente encapsulado
``` bash
make rm
```

Remove a rede local encapsulada
``` bash
make rm-network
```

Remove a imagem criada pelo `make build`
``` bash
make rm-img
```

Mostra uma listagem de todos os comandos e uma breve descrição deles
``` bash
make help
```

### Usando o docker

1. _Builde_ o ambiente do _Dockerfile_
``` bash
docker build -t monitoria .
```

2. Execute o app
``` bash
docker run -w /monitoria/src monitoria:latest bash -c "./monitoria"
```