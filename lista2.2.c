#include <stdio.h>
#include <string.h>
#define QTD_DISCIPLINAS 2
#define MAX_ESTUDANTES_POR_DISCIPLINA 10
#define TOTAL_PROFS 3

typedef struct Estudante
{
    char nome[50];
    char matricula[10];
    int idade;
} ESTUDANTE;
typedef struct Professor
{
    char nome[50];
    char funcional[15];
    char titulacao[40];
} PROFESSOR;
typedef struct Disciplina
{
    char nome[50];
    char codigo[30];
    char carga_horaria[3];
    int qtd_estudantes;
    PROFESSOR professor_respon;
    ESTUDANTE estudantes[MAX_ESTUDANTES_POR_DISCIPLINA];
} DISCIPLINA;

void receberNomePessoa(char *nome);
void receberNomeDisciplina(char *nomeDisciplina);
void receberFuncional(char *funcional);
void receberMatricula(char *matricula);
void receberIdade(int *idade);
void receberTitulacao(char *titulacao);
void receberCodigoDisciplina(char *codigoDisciplina);
void receberCargaHoraria(int *cargaHoraria);
int receberEstudante(DISCIPLINA *disciplina, int disponivel);
void cadastrarProfessores(PROFESSOR *professores);
void cadastrarDisciplina(DISCIPLINA *disciplina, PROFESSOR *professores, int i);

// Operacoes
void ordenarEstudantesIdadeCrescente(DISCIPLINA *disciplina, int quantidadeDeEstudantes);
void ordenarEstudantesIdadeDecrescente(DISCIPLINA *disciplina, int quantidadeDeEstudantes);

// Outputs
void imprimirEstudantes(DISCIPLINA *disciplina, int quantidadeDeEstudantes);

int main()
{
    char tipo_de_ordenacao[12], respEstudante[1] = {'s'};
    int i = 0, j = 0, nao_alocados = 15, ja_alocados = 0, n = 0, limite = 10, disponivel = 15;

    PROFESSOR professores[TOTAL_PROFS];
    DISCIPLINA disciplinas[QTD_DISCIPLINAS];

    // I - ENTRADA de todos os professores, seguida dos dados da disciplina, bem como do professor responsável por ela e de seus alunos
    cadastrarProfessores(&professores[0]);
    system("clear");

    for (j = 0; j < 2; j++)
    {
        printf("================\n");
        printf("  DISCIPLINA %d", (j + 1));
        printf("\n================\n");

        // Parte exlusiva da disciplina
        receberNomeDisciplina(disciplinas[j].nome);
        receberCodigoDisciplina(&disciplinas[j].codigo[0]);
        receberCargaHoraria(&disciplinas[j].carga_horaria);

        // Escolha professor responsavel
        printf("---------------------\n");
        printf("Professor responsavel");
        printf("\n---------------------\n");
        escolherProfessor(&disciplinas[j], professores);

        // Receber estudantes
        printf("\n--------------\n");
        printf("Estudantes");

        n = 0;
        do
        {
            printf("\n--------------\n");
            printf("   Estudante %d  \n", (n + 1));
            receberNomePessoa(disciplinas[j].estudantes[n].nome);
            receberMatricula(disciplinas[j].estudantes[n].matricula);
            receberIdade(&disciplinas[j].estudantes[n].idade);

            printf("--------------\n");
            printf("Deseja continuar(s/n): ");
            scanf("%s", &respEstudante[0]);

            n++;
        } while (n < disponivel && respEstudante[0] == 's' && n < limite);

        // Aqui estamos armazenando quantos foram alocados para a ultima disciplina e armazenando a quantidade total de alocados.
        ja_alocados += (disciplinas[j].qtd_estudantes = n);
        disponivel -= n;

        // Limpando a tela para o próximo recebimento
        system("clear");
    }

    // II - PROCESSAMENTO consistindo na ordenação dos alunos por ordem crescente e decrescente para as turmas 0 e 1, respectivamente.
    ordenarEstudantesIdadeCrescente(&disciplinas[0], disciplinas[0].qtd_estudantes);

    ordenarEstudantesIdadeDecrescente(&disciplinas[1], disciplinas[1].qtd_estudantes);

    // III - SAÍDA da nova relação com os alunos ordenados na ordem crescente e descrescente nas respectivas disciplinas
    for (j = 0; j < 2; j++)
    {
        j == 0 ? strcpy(tipo_de_ordenacao, "crescente") : strcpy(tipo_de_ordenacao, "decrescente");

        printf("------------------\n");
        printf("DISCIPLINA %d - Ordem %s", (j + 1), tipo_de_ordenacao);
        printf("\n------------------\n");
        printf("Nome do professor: %s\nCodigo da disciplina:%s\n\n", disciplinas[j].professor_respon.nome, disciplinas[j].codigo);

        imprimirEstudantes(&disciplinas[j], disciplinas[j].qtd_estudantes);
    }

    return 0;
}

// Recebimentos
void receberNomePessoa(char *nome)
{
    printf("Nome: ");
    scanf(" %[^\n]s\n", nome);
}

void receberNomeDisciplina(char *nomeDisciplina)
{
    printf("Nome da Disciplina: ");
    scanf(" %[^\n]s\n", nomeDisciplina);
}

void receberFuncional(char *funcional)
{
    printf("Funcional: ");
    scanf(" %[^\n]s\n", funcional);
}

void receberMatricula(char *matricula)
{
    printf("Matricula: ");
    scanf(" %[^\n]s\n", matricula);
}

void receberIdade(int *idade)

{
    printf("Idade: ");
    scanf("%d", idade);

    while (*idade < 16 ||
           *idade > 26)
    {
        printf("\n");
        printf("ATENCAO!! Digite uma idade que esteja entre 16 e 26, "
               "inclusive.\n");
        printf("Idade: ");
        scanf("%d", idade);
    }
    printf("\n");
}

void receberTitulacao(char *titulacao)
{
    int opcoes_titulacao = 0;
    do
    {
        printf("Titulacao:\n");
        printf("(1) ESPECIALISTA\n");
        printf("(2) MESTRE\n");
        printf("(3) DOUTOR\n");

        printf("> ");

        scanf(" %d", &opcoes_titulacao);

        switch (opcoes_titulacao)
        {

        case 1:

            // SUBSTITUINDO POR

            strcpy(titulacao, "ESPECIALISTA");
            //--------^~~~~~ Aqui se passa o endereco do primeiro elemento
            // do vetor?
            break;
        case 2:
            strcpy(titulacao, "MESTRE");
            break;

        case 3:
            strcpy(titulacao, "DOUTOR");
            break;
        default:
            printf("ATENCAO!! Selecione uma opcao valida.\n\n");
            break;
        }
        printf("\n");
    } while (opcoes_titulacao != 1 && opcoes_titulacao != 2 &&
             opcoes_titulacao != 3);
}

void receberCodigoDisciplina(char *codigoDisciplina)
{
    printf("Codigo da Disciplina: ");
    scanf(" %[^\n]s\n", codigoDisciplina);
}

void receberCargaHoraria(int *cargaHoraria)
{
    printf("Carga Horaria: ");
    scanf("%d", cargaHoraria);
    printf("\n");
}

void cadastrarProfessores(PROFESSOR *professores)
{
    int i = 0, j = 0, limite = TOTAL_PROFS;
    PROFESSOR aux;

    printf("================\n");
    printf("  CADASTRO PROFESSORES   ");
    printf("\n================\n");

    for (i = 0; i < limite; i++)
    {
        printf("--------------\n");
        printf("  Professor %d\n", i + 1);
        receberNomePessoa((*(professores + i)).nome);
        receberFuncional((*(professores + i)).funcional);
        receberTitulacao((*(professores + i)).titulacao);
    }
    for (i = 0; i < limite; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if ((*(professores + j)).titulacao[0] == 'D')
            {
                aux = *(professores + j);
                *(professores + j) = *(professores + j + 1);
                *(professores + j + 1) = aux;
            }
            else if ((*(professores + j)).titulacao[0] == 'M' && (*(professores + i + 1)).titulacao[0] == 'E')
            {
                aux = *(professores + j);
                *(professores + j) = *(professores + j + 1);
                *(professores + j + 1) = aux;
            }
        }
        limite--;
    }
}

void escolherProfessor(DISCIPLINA *disciplina, PROFESSOR *professores)
{
    int i = 0, escolhaProfessor = 0;

    do
    {
        printf("Selecione o professor responsavel: \n");
        for (i = 0; i < 3; i++)
        {
            printf("- (%d) %s, %s\n", (i + 1), (*(professores + i)).nome, (*(professores + i)).titulacao);
        }
        printf("\n");
        printf("> ");
        scanf("%d", &escolhaProfessor);

        // Validacao Professores
        switch (escolhaProfessor)
        {

        case 1:
            strcpy((*disciplina).professor_respon.nome, (*(professores + 0)).nome);
            break;
        case 2:
            strcpy((*disciplina).professor_respon.nome, (*(professores + 1)).nome);
            break;

        case 3:
            strcpy((*disciplina).professor_respon.nome, (*(professores + 2)).nome);
            break;
        default:
            printf("\nATENCAO!!Selecione uma opcao valida.\n");
            break;
        }
    } while (escolhaProfessor != 1 && escolhaProfessor != 2 &&
             escolhaProfessor != 3);
}

int receberEstudante(DISCIPLINA *disciplina, int disponivel)
{
    int n = 0, limite = 10;
    char resp[1] = {'s'};
    do
    {
        printf("\n--------------\n");
        printf("   Estudante %d  \n", (n + 1));
        receberNomePessoa((*disciplina).estudantes[n].nome);
        receberMatricula((*disciplina).estudantes[n].matricula);
        receberIdade(&(*disciplina).estudantes[n].idade);

        printf("Deseja continuar(s/n): ");
        scanf("%s", &resp[0]);

        n++;
    } while (n <= disponivel && resp[0] == 's' && n < limite);

    return n;
}

// Operacoes
void ordenarEstudantesIdadeCrescente(DISCIPLINA *disciplina, int quantidadeDeEstudantes)
{
    int k = 0, b = 0;
    ESTUDANTE aux;
    for (k = quantidadeDeEstudantes - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*disciplina).estudantes[b].idade >
                (*disciplina).estudantes[b + 1].idade)
            {
                aux = (*disciplina).estudantes[b];
                (*disciplina).estudantes[b] = (*disciplina).estudantes[b + 1];
                (*disciplina).estudantes[b + 1] = aux;
            }
        }
    }
}

void ordenarEstudantesIdadeDecrescente(DISCIPLINA *disciplina, int quantidadeDeEstudantes)
{
    int k = 0, b = 0;
    ESTUDANTE aux;
    for (k = quantidadeDeEstudantes - 1; k > 0; k--)
    {
        for (b = 0; b < k; b++)
        {
            if ((*disciplina).estudantes[b].idade <
                (*disciplina).estudantes[b + 1].idade)
            {
                aux = (*disciplina).estudantes[b];
                (*disciplina).estudantes[b] = (*disciplina).estudantes[b + 1];
                (*disciplina).estudantes[b + 1] = aux;
            }
        }
    }
}

// Outputs
void imprimirEstudantes(DISCIPLINA *disciplina, int quantidadeDeEstudantes)
{
    int i = 0;
    for (i = 0; i < quantidadeDeEstudantes; i++)
    {
        printf("-%s, %d anos\n", (*disciplina).estudantes[i].nome, (*disciplina).estudantes[i].idade);
    }
}
