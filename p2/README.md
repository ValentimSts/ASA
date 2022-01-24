

## Descrição do Problema

Uma árvore genealógica consiste num grafo dirigido em que cada nó representa uma pessoa e os vizinhos directos de um nó correspondem aos seus filhos, podendo existir 
nós orfãos, nós com um progenitor e nós com dois progenitores. Dados dois nós ``P1`` e ``P2`` de uma árvore genealógica:
 - ``P1`` diz-se **ancestral** de ``P2`` se é possível atingir ``P2`` a partir de ``P1`` na árvore genealógica;
 - ``P3`` diz-se um **ancestral comum mais próximo** de ``P1`` e ``P2``, se é **ancestral** de ``P1`` e ``P2``, e não existe um nó ``P4`` descendente de ``P3`` que seja também **ancestral** de ``P1`` e ``P2``.

Observamos que a definição de **ancestral comum mais próximo** permite que dois nós tenham vários **ancestrais comuns mais próximos**. Por exemplo, no grafo abaixo, ``v2`` e ``v4`` são ambos **ancestrais comuns mais próximos** de ``v5`` e ``v6``.
