#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CODONS 64
#define CODON_LENGTH 3
#define MAX_SIZE 1000
#define MOTIF_SIZE 4

typedef struct {
    char codon[CODON_LENGTH + 1];
    char aminoacid;
} Codon;

Codon codonTable[NUM_CODONS] = {
    {"TTT", 'F'}, {"TTC", 'F'}, {"TTA", 'L'}, {"TTG", 'L'},
    {"TCT", 'S'}, {"TCC", 'S'}, {"TCA", 'S'}, {"TCG", 'S'},
    {"TAT", 'Y'}, {"TAC", 'Y'}, {"TAA", '*'}, {"TAG", '*'},
    {"TGT", 'C'}, {"TGC", 'C'}, {"TGA", '*'}, {"TGG", 'W'},

    {"CTT", 'L'}, {"CTC", 'L'}, {"CTA", 'L'}, {"CTG", 'L'},
    {"CCT", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'},
    {"CAT", 'H'}, {"CAC", 'H'}, {"CAA", 'Q'}, {"CAG", 'Q'},
    {"CGT", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'},

    {"ATT", 'I'}, {"ATC", 'I'}, {"ATA", 'I'}, {"ATG", 'M'},
    {"ACT", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'},
    {"AAT", 'N'}, {"AAC", 'N'}, {"AAA", 'K'}, {"AAG", 'K'},
    {"AGT", 'S'}, {"AGC", 'S'}, {"AGA", 'R'}, {"AGG", 'R'},

    {"GTT", 'V'}, {"GTC", 'V'}, {"GTA", 'V'}, {"GTG", 'V'},
    {"GCT", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'},
    {"GAT", 'D'}, {"GAC", 'D'}, {"GAA", 'E'}, {"GAG", 'E'},
    {"GGT", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'}
};

void printGeneticTable() {
    printf("Tabela Genetica:\n");
    printf("Codon  | Aminoacido\n");
    printf("-------------------\n");

    int i;
	for (i = 0; i < NUM_CODONS; i++) {
        printf("%s  | %c\n", codonTable[i].codon, codonTable[i].aminoacid);
    }
}

typedef struct Node {
    char motif[MOTIF_SIZE + 1];
    int position;
    struct Node *next;
} Node;

typedef struct Stack {
    char data[MOTIF_SIZE + 1];
    int top;
} Stack;

typedef struct Queue {
    int data[MAX_SIZE];
    int front, rear;
} Queue;

bool isMotif(char *subsequence) {
    int subsequenceLength = strlen(subsequence);
    for (int i = 0; i + CODON_LENGTH <= subsequenceLength; i++) {
        char substring[CODON_LENGTH + 1];
        strncpy(substring, &subsequence[i], CODON_LENGTH);
        substring[CODON_LENGTH] = '\0'; // Marca o final da string

        for (int j = 0; j < NUM_CODONS; j++) {
            if (strcmp(substring, codonTable[j].codon) == 0) {
                return true; // A substring é um motivo genético
            }
        }
    }
    return false; // Nenhuma substring encontrada
}}

void addNodeToList(Node **head, char *motif, int position) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->motif, motif);
    newNode->position = position;
    newNode->next = *head;
    *head = newNode;
}

void printMotifs(Node *head) {
    printf("Motivos Geneticos Encontrados:\n");
    while (head != NULL) {
        printf("Motivo: %s, Posicao Inicial: %d\n", head->motif, head->position);
        head = head->next;
    }
}

int main() {
    int choice;
    char dnaSequence[MAX_SIZE];

    printf("Selecione a opcao desejada:\n");
    printf("1. Identificar Motivos Geneticos\n");
    printf("2. Exibir Tabela Genetica\n");
    printf("Opcao: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Digite a sequencia de DNA: ");
            scanf("%s", dnaSequence);

            int len = strlen(dnaSequence);

            Stack stack;
            stack.top = -1;

            Queue queue;
            queue.front = queue.rear = -1;

            Node *head = NULL;

            for (int i = 0; i < len; i++) {
                stack.data[++stack.top] = dnaSequence[i];

                if (stack.top >= MOTIF_SIZE - 1) {
                    char subsequence[MOTIF_SIZE + 1];
                    for (int j = 0; j < MOTIF_SIZE; j++) {
                        subsequence[j] = stack.data[stack.top - j];
                    }
                    subsequence[MOTIF_SIZE] = '\0';

                    if (isMotif(subsequence)) {
                        addNodeToList(&head, subsequence, i - MOTIF_SIZE + 1);
                        queue.data[++queue.rear] = i - MOTIF_SIZE + 1;
                    }

                    stack.top--;
                }
            }

            printMotifs(head);
            break;

        case 2:
            printGeneticTable();
            break;

        default:
            printf("Opcao invalida.\n");
    }

    return 0;
}
