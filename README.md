UNIVERSIDADE DE SÃO PAULO — USP ICMC
Trabalho Prático 1: polinômios esparsos 
Curso: Bacharelado em Ciência de Dados
Disciplina: Estruturas de Dados

Integrantes do Grupo
Vinicius Gesser Hsiao — Nº USP: 17933148
Cássio Kanomata Bones — Nº USP: 16984384
Adryann Henrique Oliveira Olivatti — Nº USP: 17363240
1. Projeto da Solução
Estrutura Escolhida para Representação: Lista Duplamente Encadeada Ordenada
1.1 Implementação Detalhada das Operações
Operação
Descrição 
Lógica de Implementação
 
DEF nome k
define nome (do polinômio) a partir das k linhas seguintes, cada uma com coef grau 
Aloca a estrutura para nome e lê k pares (coeficiente, grau), inserindo-os de forma ordenada por grau.
SOMA A B R
R = A + B
Percorre simultaneamente os polinômios A e B somando coeficientes de mesmo grau e criando os nós em R.
PROD A B R
R = A * B
Para cada termo (c, g) de A, multiplica por cada termo (c, g) de B e insere o produto (c_a * c_b, g_a + g_b) em R.
ADD A c g
soma a A o termo de coeficiente c e grau g 
Busca o nó de grau g em A: se existir, soma c ao coeficiente existente (removendo o nó se o resultado for 0); se não existir, insere mantendo a ordenação.
ESCALA A c
multiplica todo coeficiente de A pelo inteiro c 
Percorre todos os nós de A multiplicando cada coeficiente por c. Se c = 0, libera todos os nós e deixa o polinômio vazio.
COEF A g
coeficiente de grau g em A 
Percorre A até encontrar o grau g (retorna o coeficiente c) ou passar do grau desejado (retorna 0).
REMOVE A g
apaga de A o termo de grau g 
Busca o nó com grau g na estrutura de A, ajusta os ponteiros do nó anterior/seguinte e desaloca a memória do nó.
REMOVEMENOR A
apaga de A o termo de menor grau 
Remove diretamente o primeiro nó (cabeça) da lista encadeada ordenada por grau.
GRAU A
maior grau com coeficiente não nulo 
Acessa o último nó (cauda) da lista ordenada ou o elemento máximo em O(1).
IMPRIME A
Escreve A em ordem canônica.
Percorre a lista do maior grau para o menor usando ponteiro duplo exibindo os termos formatados.
IMPRIMEINV A
Escreve A em ordem crescente de grau.
Percorre a estrutura na ordem natural de armazenamento (do menor para o maior grau) imprimindo cada termo.
LIBERA A
Libera a memória de A; nome fica indefinido.
Percorre toda a lista liberando nó por nó da memória (free) e redefine o ponteiro como NULL.
FIM
Encerra a execução.
Finaliza a execução do programa.

2. Justificativa e Tabela de Custos

Operação
Lista Simplesmente Encadeada ordenada
LIsta duplamente encadeada Ordenada
Lista Sequencial Ordenada
LIsta Simplesmente encadeada não ordenada
Lista duplamente encadeada não ordenada
Lista Sequencial Não Ordenada
DEF k
O(K log K)
O(K log K)
O(K log K)
O(K^2)
O(K^2)
O(K^2)
SOMA
O(N + M)
O(N + M)
O(N + M)
O(N * M)
O(N * M)
O(N * M)
PROD
O(N * M * L)
O(N * M * L)
O(N * M * L)
O(N * M * L)
O(N * M * L)
O(N * M * L)
ADD c g
O(N)
O(N)
O(N)
O(N)
O(N)
O(N)
ESCALA c
O(N)
O(N)
O(N)
O(N)
O(N)
O(N)
COEF g
O(N)
O(N)
O(log N)
O(N)
O(N)
O(N)
REMOVE g
O(N)
O(N)
O(N)
O(N)
O(N)
O(N)
REMOVEMENOR
O(1)
O(1)
O(N)
O(N)
O(N)
O(N)
GRAU
O(1)
O(1)
O(1)
O(N)
O(N)
O(N)
IMPRIME
O(N)
O(N)
O(N)
O(N log N)
O(N log N)
O(N log N)
IMPRIMEINV
O(N)
O(N)
O(N)
O(N log N)
O(N log N)
O(N log N)
LIBERA
O(N)
O(N)
O(1)
O(N)
O(N)
O(1)
FIM
O(Soma N)
O(Soma N)
O(1)
O(Soma N)
O(Soma N)
O(1)



Análise comparativa das complexidades assintóticas em Notação Big-O, onde N e M representam o número de termos não nulos dos polinômios envolvidos.
2.1 Justificativa da Escolha Final
Por que uma estrutura ordenada, e não uma estrutura ordenada por inserção livre
O conjunto de comandos do trabalho é dominado por operações que se beneficiam diretamente de uma ordem canônica mantida em memória. SOMA e PROD dependem de comparar termos de mesmo grau entre dois polinômios, o que se resolve em uma única varredura linear quando ambos os operandos já estão ordenados por grau — contra uma varredura cruzada de custo quadrático se a ordem não existir. GRAU exige apenas consultar o extremo de maior grau, e REMOVEMENOR o extremo de menor grau: mantendo a lista ordenada, ambos os extremos são acessíveis em tempo constante através de ponteiros de cabeça e cauda, sem qualquer busca. IMPRIME não precisa fazer nada além de percorrer a lista já na ordem pedida pelo enunciado, e IMPRIMEINV percorre a mesma lista no sentido oposto. Em outras palavras, a maior parte do trabalho pesado de manter a ordem é pago uma única vez, na inserção, e todas as consultas subsequentes colhem esse investimento sem custo adicional. Isso torna qualquer estrutura ordenada estruturalmente superior a uma estrutura não ordenada para o perfil de comandos deste trabalho, e é a primeira decisão do projeto.
Por que lista encadeada, e não array ordenado
Descartado o não ordenado, resta decidir entre array ordenado e lista encadeada ordenada. O array ganha exatamente uma operação: COEF, que se resolve em O(log N) por busca binária graças ao acesso indexado, contra O(N) em qualquer lista encadeada, que só pode varrer sequencialmente. Esse é o único ponto em que o array vence de forma assintótica. Em contrapartida, toda operação que insere ou remove um termo no meio da estrutura — DEF quando há graus fora de ordem, ADD, REMOVE, e a própria SOMA e PROD ao construírem o polinômio resultado termo a termo — paga em um array o custo de deslocar todos os elementos posteriores à posição de inserção, um custo que a notação O(N) esconde mas que na prática envolve mover memória contígua repetidamente. Numa lista encadeada, o mesmo evento é resolvido apenas religando ponteiros, sem mover nenhum dado já existente. Como o enunciado deixa explícito na seção 6 que graus podem chegar em qualquer ordem e a inserção intermediária é frequente (DEF com termos fora de ordem, ADD sucessivos, construção de SOMA e PROD), o custo de deslocamento do array pesa sobre mais operações e mais vezes por execução do que o ganho pontual de COEF. A escolha por lista encadeada prioriza, portanto, o conjunto de operações que o trabalho de fato exercita com mais frequência, aceitando conscientemente que COEF deixa de ser logarítmico.
Por que duplamente encadeada, e não simplesmente encadeada
Ao comparar as duas variantes de lista ordenada na tabela de custos, nota-se que ambas alcançam exatamente as mesmas complexidades assintóticas em todas as operações do trabalho — inclusive REMOVEMENOR e GRAU em O(1), desde que a lista simples também mantenha um ponteiro de cauda para leitura e insira/remova pela extremidade de menor grau sem precisar de ponteiro anterior. A escolha da variante dupla não se justifica, portanto, pela complexidade assintótica, e seria incorreto alegar que ela é "mais rápida" nesse sentido; a justificativa correta é de custo constante e de robustez de implementação. A operação REMOVE(A, g), que localiza um grau arbitrário no meio da lista, precisa desconectar um nó de sua vizinhança; numa lista simples isso exige rastrear manualmente, durante a própria busca, um ponteiro auxiliar para o nó anterior, o que aumenta a complexidade do código e o risco de erros de borda (remoção da cabeça, lista com um único nó). Numa lista dupla, o nó já carrega a referência ao seu antecessor, e a remoção se reduz a religar dois pares de ponteiros de forma direta e simétrica, sem lógica auxiliar. De modo semelhante, IMPRIMEINV percorre a lista em ordem crescente de grau partindo da cauda: numa lista dupla isso é uma travessia direta pelos ponteiros anterior; numa lista simples, a mesma operação exigiria percorrer a lista inteira do início empilhando referências (ou usar recursão), consumindo memória auxiliar proporcional a N que a lista dupla dispensa. Essas vantagens são de constante, não de ordem de grandeza, mas reduzem a superfície de bugs do código e evitam alocação adicional em uma operação. O preço pago por essa escolha é justamente o esperado de uma estrutura com mais informação por nó: cada termo carrega um ponteiro extra (custo de memória por termo maior que o da lista simples), e cada inserção ou remoção precisa atualizar dois ponteiros em vez de um, o que se traduz em um fator constante levemente maior nessas operações — sem alterar sua ordem assintótica.


3. Medição de Desempenho
Análise dos Resultados: 

4. Ponto Fraco da Solução
A estrutura escolhida tem um ponto fraco identificável: cargas de trabalho dominadas por acesso aleatório a coeficientes (muitos comandos COEF sobre polinômios com muitos termos) penalizam a lista encadeada, ordenada ou não, porque não há atalho para o meio da estrutura — o array ordenado, nesse cenário específico, teria desempenho superior graças à busca binária. Da mesma forma, cargas com poucas modificações estruturais e muitas leituras repetidas reduziriam o custo de deslocamento do array a ponto de o array se tornar competitivo mesmo nas demais operações.

5. Casos de Teste Criados


