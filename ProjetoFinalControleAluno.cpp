#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cstdio>  // Para manipulação de arquivos com FILE*

using namespace std;

// Estrutura do aluno
struct Aluno {
    char nome[50];
    int matricula;
    char curso[30];
    char status;
};

// Funções
int quantidadeAlunos(FILE* arq);
void cadastrarAluno(FILE* arq);
void consultarAluno(FILE* arq);
void excluirAluno(FILE* arq);
void gerarRelatorioAlunos(FILE* arq);
void editarAluno(FILE* arq); // Função para editar aluno

int main() {
    FILE* arq = fopen("alunos.dat", "rb+");

    // Caso o arquivo não exista, cria o arquivo para leitura e escrita
    if (!arq) {
        arq = fopen("alunos.dat", "wb+");
        if (!arq) {
            cout << "Erro ao abrir o arquivo!" << endl;
            return 1;
        }
    }

    int op;
    do {
        (void)system("clear");
        (void)system("cls");//Não funciona no replit

        cout << "╔═══════════════════════════════════════════════════════════╗\n";
        cout << "║                SISTEMA DE CONTROLE DE ALUNOS              ║\n";
        cout << "╠═══════════════════════════════════════════════════════════╣\n";
        cout << "║                  [ 1 ] Cadastrar Aluno                    ║\n";
        cout << "║                  [ 2 ] Consultar Aluno                    ║\n";
        cout << "║                  [ 3 ] Excluir Aluno                      ║\n";
        cout << "║                  [ 4 ] Gerar Relatório                    ║\n";
        cout << "║                  [ 5 ] Editar Aluno                       ║\n";  // Nova opção de editar
        cout << "║                  [ 6 ] Sair                               ║\n";
        cout << "╚═══════════════════════════════════════════════════════════╝\n";
        cout << "               Total de Alunos Matriculados: " << quantidadeAlunos(arq) << "  \n";
        cout << "╚═══════════════════════════════════════════════════════════╝\n";
        cout << "Escolha uma opção --> ";
        cin >> op;
        

        (void)system("clear");
        (void)system("cls");

        switch (op) {
            case 1:
                cadastrarAluno(arq);
                break;
            case 2:
                consultarAluno(arq);
                break;
            case 3:
                excluirAluno(arq);
                break;
            case 4:
                gerarRelatorioAlunos(arq);
                break;
            case 5:
                editarAluno(arq);  // Chama a função de editar aluno
                break;
            case 6:
                fclose(arq);
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }

        

    } while (op != 6);

    return 0;
}

// Função para calcular o número de alunos registrados no arquivo
int quantidadeAlunos(FILE* arq) {
    fseek(arq, 0, SEEK_SET);  // Move para o início do arquivo
    Aluno aluno;
    int contador = 0;

    // Lê todos os alunos e conta apenas os alunos ativos
    while (fread(&aluno, sizeof(Aluno), 1, arq)) {
        if (aluno.status == ' ') {  // Contar apenas os alunos ativos
            contador++;
        }
    }

    return contador;
}

// Função para cadastrar um novo aluno
void cadastrarAluno(FILE* arq) {
    Aluno aluno;
    char confirma;

    cout << "\nCadastro de novo aluno:" << endl;
    cout << "Nome: ";
    cin.ignore();  // Limpa o buffer antes de ler uma string
    cin.getline(aluno.nome, 50);

    cout << "Matrícula: ";
    cin >> aluno.matricula;

    cout << "Curso: ";
    cin.ignore();  // Limpa o buffer antes de ler uma string
    cin.getline(aluno.curso, 30);

    aluno.status = ' ';  // Definindo o aluno como ativo

    cout << "\nConfirma o cadastro (s/n): ";
    cin >> confirma;

    if (tolower(confirma) == 's') {
        fseek(arq, 0, SEEK_END);  // Move para o final do arquivo
        fwrite(&aluno, sizeof(Aluno), 1, arq);  // Grava o aluno no arquivo
        cout << "\nAluno cadastrado com sucesso!" << endl;
       
    }
    else{
        cout << "\nCadastro cancelado!" << endl;
    }
    cin.ignore();// OBS: Limpa o buffer após a leitura da matrícula (para garantir que a próxima leitura funcione corretamente)
    cin.get();
}

// Função para consultar um aluno pelo número da matrícula
void consultarAluno(FILE* arq) {
    int matricula;
    bool encontrado = false;
    Aluno aluno;

    cout << "\nConsulta por matrícula\n";
    cout << "Informe a matrícula: ";
    cin >> matricula;

    fseek(arq, 0, SEEK_SET);  // Move para o início do arquivo
    while (fread(&aluno, sizeof(Aluno), 1, arq)) {
        if (aluno.matricula == matricula && aluno.status == ' ') {
            cout << "\n╔════════════════════════════════════════════════════════════╗\n";
            cout << "║                      Aluno encontrado                      ║\n";
            cout << "╚════════════════════════════════════════════════════════════╝\n";
            cout << "  Matrícula: " << aluno.matricula << endl;
            cout << "  Nome: " << aluno.nome << endl;
            cout << "  Curso: " << aluno.curso << endl;
            cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nAluno não encontrado ou excluído!" << endl;
    }
    cin.ignore();
    cin.get();
}

// Função para excluir um aluno (marcar como excluído)
void excluirAluno(FILE* arq) {
    int matricula;
    char confirma;
    bool encontrado = false;
    Aluno aluno;
    
    cout << "\nExcluir por matrícula\n";
    cout << "Informe a matrícula: ";
    cin >> matricula;

    fseek(arq, 0, SEEK_SET);  // Move para o início do arquivo
    while (fread(&aluno, sizeof(Aluno), 1, arq)) {
        if (aluno.matricula == matricula && aluno.status == ' ') {
            cout << "\n╔════════════════════════════════════════════════════════════╗\n";
            cout << "║                      Aluno encontrado                      ║\n";
            cout << "╚════════════════════════════════════════════════════════════╝\n";
            cout << "  Matrícula: " << aluno.matricula << endl;
            cout << "  Nome: " << aluno.nome << endl;
            cout << "  Curso: " << aluno.curso << endl;
            cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;
            cout << "Confirma a exclusão (s/n): ";
            cin >> confirma;

            if (tolower(confirma) == 's') {
                aluno.status = '*';  // Marca como excluído
                fseek(arq, -static_cast<int>(sizeof(Aluno)), SEEK_CUR);  // Move para a posição do registro
                fwrite(&aluno, sizeof(Aluno), 1, arq);  // Sobrescreve o registro com status excluído
                cout << "\nAluno excluído com sucesso!" << endl;
            }
            else{
                cout << "\nExclusão cancelada!" << endl;
            }
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "/nAluno não encontrado ou já excluído!" << endl;
    }
    

    cin.ignore();
    cin.get();
}

// Função para editar um aluno
void editarAluno(FILE* arq) {
    int matricula;
    bool encontrado = false;
    Aluno aluno;

    cout << "\nInforme a matrícula do aluno para editar: ";
    cin >> matricula;
    cin.ignore();  // Limpa o buffer após a leitura da matrícula

    fseek(arq, 0, SEEK_SET);  // Move para o início do arquivo
    while (fread(&aluno, sizeof(Aluno), 1, arq)) {
        if (aluno.matricula == matricula && aluno.status == ' ') {
            cout << "╔════════════════════════════════════════════════════════════╗\n";
            cout << "║                      Aluno encontrado                      ║\n";
            cout << "╚════════════════════════════════════════════════════════════╝\n";
            cout << "  Matrícula: " << aluno.matricula << endl;
            cout << "  Nome: " << aluno.nome << endl;
            cout << "  Curso: " << aluno.curso << endl;
            cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;

            // Editando os campos
            char confirma;
            char novoNome[50], novoCurso[30];

            cout << "Digite o novo nome (deixe em branco para não alterar): ";
            cin.getline(novoNome, 50);
            if (strlen(novoNome) > 0) {
                strcpy(aluno.nome, novoNome);
            }

            cout << "Digite o novo curso (deixe em branco para não alterar): ";
            cin.getline(novoCurso, 30);
            if (strlen(novoCurso) > 0) {
                strcpy(aluno.curso, novoCurso);
            }

            // Confirma a edição
            cout << "Confirma a edição (s/n): ";
            cin >> confirma;

            if (tolower(confirma) == 's') {
                fseek(arq, -static_cast<int>(sizeof(Aluno)), SEEK_CUR);  // Move para a posição do registro
                fwrite(&aluno, sizeof(Aluno), 1, arq);  // Sobrescreve o registro com os novos dados
                cout << "\nAluno editado com sucesso!" << endl;
            }

            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Aluno não encontrado ou excluído!" << endl;
    }

    cin.ignore();
    cin.get();
}

// Função para gerar um relatório com todos os alunos ativos
void gerarRelatorioAlunos(FILE* arq) {
    Aluno aluno;
    fseek(arq, 0, SEEK_SET);  // Move para o início do arquivo

    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║                    RELATÓRIO DE ALUNOS ATIVOS              ║\n";
    cout << "╠════════════════════════════════════════════════════════════╣\n";
    cout << "║    Matrícula              Nome                  Curso      ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;

    // Lê os dados do arquivo e imprime os alunos ativos
    while (fread(&aluno, sizeof(Aluno), 1, arq)) {
        if (aluno.status == ' ') {  // Alunos ativos
            cout << "  "
                 << aluno.matricula << "  " // Matrícula
                 << " |  " << aluno.nome << "  "  // Nome
                 << " |  " << aluno.curso << "  \n" << endl;  // Curso
        }
    }

    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;

    cin.ignore();
    cin.get();
}
