### Escalonador em um RTOS utilizando STM32F103

[Objetivos](#objetivos)

[Rate Monotonic (RM)](#rate-monotonic-rm)

[Implementação do escalonador](#implementação-do-escalonador)

[Utilização e Visualização](#utilização-e-visualização)

![BluepillStlink](/assets/bluepill_stlink.jpg)

## Objetivos
Esse repositório contém a implementação de um escalonador para tarefas periódicas. Ele foi implementado em um sistema de tempo real, mais especificamente o MInimal Real-time Operating System (MiROS). O algoritmo desenvolvido foi o Rate Monotonic (RM)

## Rate Monotonic (RM)
O algoritmo Rate Monotonic é muito utilizado em sistemas operacionais de tempo real (RTOS) como escalonador para tarefas periódicas. Ele é baseado em prioridades estaticas, de modo que elas são definidas de modo que quanto maior o período de uma tarefa, menor será a sua prioridade. Assim, é garantido que tarefas que devem ser executadas em ciclos menores possuam maior prioridade no sistema.

## Implementação do escalonador
Para implementar o RM, foi necessário alterar a função *OSThread_start*, que agora passa a receber o custo e o período da tarefa, denotados como *Ci* e *Ti*, respectivamente. Além disso, a *struct* da *OSThread* também foi modificada, de modo que foram adicionados o campo de *Ci* e *Ti*, assim como o tempo restante da tarefa, *remainingTime* e uma flag para verificar se a tarefa está ativa ou não, chamada *isActive*.

A maior mudança ocorreu na *OS_sched()*. Como dito anteriormente, o RM julga as tarefas de acordo com seu período, onde o menor período possuirá a maior prioridade. Assim, na *OS_sched()* primeiramente é chamada uma função auxiliar, *checkLowestPriorityThread()* que verifica qual tarefa possui a menor prioridade para atribuir a maior prioridade. Após isso, é verificado quais tarefas já foram completadas e por fim verifica-se qual deve ser a próxima tarefa a ser executada.

Na *main.c* também é chamada a função *TaskAction()*, que basicamente representa e simuka a tarefa em execução.

## Utilização e Visualização
Na STM32CubeIde, execute o código em modo *debug*. 

Após iniciar nesse modo, selecione a visualização das variáveis *task1Visualizer*, *task2Visualizer* e *task3Visualizer*. Elas indicarão a execução da tarefa.

Na *main.c*, estão representadas três tarefas, com os seguintes custo de executação e período:
|    | Ci | Ti |
|----|----|----|
| T1 | 3  | 5  |
| T2 | 1  | 8  |
| T3 | 1  | 10 |

Para verificar se esse conjunto de tarefas é escalonável pelo Rate Monotonic, podemos utilizar o teste de Liu and Layland:

$\sum_{i=1}^{n}\frac{Ci}{Ti} \le n\left( 2^{\frac{1}{n}}-1 \right)$ 

Onde $n$ representa o número de tarefas, $Ci$ o custo de execucação e $Ti$ o período da tarefa.

Com o conjunto de tarefas acima, é possível verificar que o teste de Liu and Layland falha, visto que U = $\frac{3}{5} + \frac{1}{8} + \frac{1}{10} = 0.825$ e $Ub = 3\left( 2^{\frac{1}{3}}-1 \right) = 0.779$. Assim, não é possível afirmar se o sistema é escalonável por RM.

Pode-se utilizar o teste hiperbólico, dado por $\prod_{i=i}^{n}(Ui + 1) \le 2 $. Como $\prod_{i=i}^{n}(Ui + 1) = 1.98$ para esse conjunto de tarefas, o sistema passa no teste hiperbólico e, portanto, pode-se concluir que ele é escalonável por RM.

Assim, ao executar o código em modo Debug e analisando as variáveis *task1Visualizer*, *task2Visualizer* e *task3Visualizer*, pode-se perceber que as tarefas são executadas exatamente como mostrado na seguinte figura:

![Escalonamento por RM](/assets/rmscheduling.png)
