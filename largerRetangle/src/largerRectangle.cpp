#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * @brief Calcula a maior area de um retangulo dentro de um histograma.
 * 
 * O algoritmo usa uma pilha para armazenar indices e calcular a area maxima pos
 * sivel.
 * 
 * @param pHeights (IN) - Vetor contendo as alturas do histograma.
 * @param iColumns (IN) - Numero de colunas do histograma.
 *
 * @return A maior area de um retangulo dentro do histograma.
 *******************************************************************************/
int largestRectangleInHistogram(int *pHeights, int iColumns)
{
	// Aloca a pilha para armazenar os indices das colunas do histograma
    int *pStack = (int *)malloc(iColumns * sizeof(int));
    // Indice do topo da pilha
	int iTop = -1;
    // Variavel para armazenar a maior area encontrada
	int iMaxArea = 0;

    // Percorre todas as colunas do histograma (incluindo um indice extra para
	// esvaziar a pilha no final).
    for (int i = 0; i <= iColumns; i++)
    {
        // Quando encontramos um valor menor que o topo  da  pilha ou chegamos
		// no final
        while (iTop != -1 && (i == iColumns || pHeights[i] < pHeights[pStack[iTop]]))
        {
			// Altura do retangulo
            int h = pHeights[pStack[iTop]];
            iTop--;

            // Calcula a largura do retangulo											  
            int w = (iTop == -1) ? i : i - pStack[iTop] - 1;
            // Atualiza a maior area encontrada												
            iMaxArea = (iMaxArea > h * w) ? iMaxArea : h * w;
        }
        pStack[++iTop] = i;
    }

    free(pStack);
    pStack = NULL;
	
    return iMaxArea;
}

/*******************************************************************************
 * @brief Encontra a maior area de um retangulo contendo apenas '1'  em  uma  ma
 * triz binaria.
 * 
 * Constroi histogramas a partir das linhas da matriz e aplica a funcao `largest
 * RectangleInHistogram()`.
 * 
 * @param matrix   (IN) - Matriz binaria contendo '0' e '1'.
 * @param iLines   (IN) - Numero de linhas da matriz.
 * @param iColumns (IN) - Numero de colunas da matriz.
 *
 * @return A maior area de um retangulo formado apenas por '1'.
 *******************************************************************************/
int maximalRectangle(char **matrix, int iLines, int iColumns)
{
    // Vetor que armazena as alturas das colunas do histograma
    int *pHeights = (int *)calloc(iColumns, sizeof(int));
	// Variavel para armazenar a maior area encontrada
    int iMaxArea = 0; 

	// Percorre todas as linhas da matriz									 
    for (int i = 0; i < iLines; i++)
    {
        for (int j = 0; j < iColumns; j++)
        {
            // Atualiza a altura do histograma
            pHeights[j] = (matrix[i][j] == '1') ? pHeights[j] + 1 : 0;
        }

        // Calcula a maior area com base no histograma
        int iArea = largestRectangleInHistogram(pHeights, iColumns);
        printf("Area: %d\n", iArea);

		 // Atualiza a maior area encontrada									
        iMaxArea = (iMaxArea > iArea) ? iMaxArea : iArea;
    }

	// Libera a memoria do vetor de alturas										
    free(pHeights);
    pHeights = NULL;
	
    return iMaxArea;
}

/*******************************************************************************
 * @brief Funcao principal que executa o programa.
 * 
 * Solicita ao usuario o numero de linhas e colunas, com os dados da matriz e re
 * aliza o calculp da maior area do retangulo.
 * 
 * @return 0 se o programa for executado corretamente.
 *******************************************************************************/   
int main()
{
    int iLines   = 0; // Numero de linhas
    int iColumns = 0; // Numero de colunas

    // Solicita ao usuario o numero de linhas e colunas
    printf("Digite o numero de linhas  ( iLines ) ............ : ");
    scanf("%d", &iLines);
    
    printf("Digite o numero de colunas (iColumns) ............ : ");
    scanf("%d", &iColumns);
  
    // Aloca dinamicamente a matriz
    char **matrix = (char **)malloc(iLines * sizeof(char *));
    for (int i = 0; i < iLines; i++)
    {
        matrix[i] = (char *)malloc(iColumns * sizeof(char));
    }

    // Solicita ao usuario os valores da matriz (apenas '0' e '1')
    printf("Digite os elementos da matriz (somente '0' ou '1') :\n");
    for (int i = 0; i < iLines; i++)
    {
        for (int j = 0; j < iColumns; j++)
        {
            do
            {
                printf("Elemento [%d][%d] (0 ou 1): ", i, j);
                scanf(" %c", &matrix[i][j]);
            } while (matrix[i][j] != '0' && matrix[i][j] != '1');
        }
    }

    // Calcula a maior area do retangulo formada por '1'
    int iMaxArea = maximalRectangle(matrix, iLines, iColumns);

    // Exibe o resultado
    printf("A maior area do retangulo entre o valores fornecidos e: %d\n", iMaxArea);

    // Libera a memoria alocada para a matriz
    for (int i = 0; i < iLines; i++)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;
    
    return 0;
}