#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "curso.h"
using namespace std;

void inicializarAlunoAleatoriamente(Lei *meuCurso, Aluno *aluno, int ano, int semestre, int limInf, int limSup){
	Cadeira *p;
	bool avaliacaoContinua=true;
	srand(time(NULL));
	if(meuCurso->alunoExiste(aluno->id)){
		for(p=meuCurso->cadeiras; p!=NULL;p=p->proximaCadeira){
			if(p->ano<=ano && p->semestre<=semestre){
				avaliacaoContinua=rand()%2==1;
				if(avaliacaoContinua){
					meuCurso->inserirNota(aluno->id,p->id,(rand() % ((4*limSup/20)-(4*limInf/20)) ) + (4*limInf/20),(rand() % ((4*limSup/20)-(4*limInf/20)) ) + (4*limInf/20),(rand() % ((12*limSup/20)-(12*limInf/20)) ) + (12*limInf/20));		
				}else{
					meuCurso->inserirNota(aluno->id,p->id, (rand() % (limSup-limInf) ) + limInf );	
				}
			}
		}
	}
}
void removerNota(Lei *meuCurso){
	int opcaoIdAluno, opcaoIdCadeira;
	cout<<"\n ID Aluno : ";
	cin>>opcaoIdAluno;
	cout<<"\n ID Cadeira : ";
	cin>>opcaoIdCadeira;
	if(!meuCurso->alunoExiste(opcaoIdAluno)){
		cout<<"\n Aluno nao encontrado :( \n";
		return;
	}
	if(!meuCurso->cadeiraExiste(opcaoIdCadeira)){
		cout<<"\n Cadeira nao encontrada :( \n";
		return;
	}
	if(!meuCurso->obterNota(opcaoIdAluno, opcaoIdCadeira)){
		cout<<"\n Classificacao nao encontrada :( \n";
		return;	
	}
	meuCurso->eliminarNota(opcaoIdAluno, opcaoIdCadeira);
	cout<<"\n Nota Eliminada com sucesso :)\n";	
}
void mostrarCadeirasDoAluno(Lei *meuCurso){
	int opcaoIdAluno;
	cout << "\n Insira o ID do aluno : ";
	cin >> opcaoIdAluno;
	if(!meuCurso->alunoExiste(opcaoIdAluno)){
		cout<<"\n Aluno nao encontrado :( )\n";
		return;
	}
	Aluno *opcaoAluno = meuCurso->obterAluno(opcaoIdAluno);
	cout << "\n Cadeiras do " << opcaoAluno->nome << " : \n";
	meuCurso->listarCadeiras(opcaoIdAluno);		
}
void adicionarAluno(Lei *meuCurso){
	int opcaoIdAluno;
	string opcaoNomeAluno;
	cout<<"\n Insira o ID do aluno : ";
	cin>>opcaoIdAluno;
	if(meuCurso->alunoExiste(opcaoIdAluno)){
		cout<<"\n Aluno ja existe!! :( \n";
		return;
	}
	cout<<"\n Insira o Nome do aluno : ";
	cin>>opcaoNomeAluno;
	if(opcaoNomeAluno.size() < 2){
		cout<<"\n Nome Inválido!! :( \n";
		return;	
	}
	meuCurso->inserirAluno(opcaoIdAluno, opcaoNomeAluno);
	cout<<"\n"<<opcaoNomeAluno<<" inserido com sucesso!! :) \n";			
}
void mostrarMenuPrincipal(){
	cout<<"\n--------------------------------------\n";
	cout<<"\n Escolha uma das opcoes :  \n";
	cout<<"\n 1 - Cadeiras concluidas de um aluno \n"; 
	cout<<"\n 2 - Alunos aprovados numa cadeira \n"; 
	cout<<"\n 3 - Listar Cadeiras\n"; 
	cout<<"\n 4 - Listar Alunos\n";
	cout<<"\n 5 - Inserir Classificacao\n";
	cout<<"\n 6 - Eliminar Classificacao\n";
	cout<<"\n 7 - Cadeiras de um Aluno\n"; 
	cout<<"\n 8 - Inserir Aluno\n"; 
	cout<<"\n 9 - Eliminar Aluno\n";
	cout<<"\n10 - Inicializar Notas de um aluno aleatoriamente\n";
	cout<<"\n 0 - Sair\n";
	cout<<"\n Opcao : ";
}
void cadeirasConcluidasDoAluno(Lei *meuCurso){
	int opcaoIdAluno;
	cout << "\n Insira o ID do aluno : ";
	cin >> opcaoIdAluno;
	if(!meuCurso->alunoExiste(opcaoIdAluno)){
		cout<<"\n Aluno nao encontrado :( )\n";
		return;	
	}
	cout << "\n Cadeiras concluidas do " << meuCurso->obterAluno(opcaoIdAluno)->nome<<" : \n";
	meuCurso->listarCadeirasConcluidas(opcaoIdAluno); 
	cout << "\n Total de UC's' : " << meuCurso->contarCadeirasConcluidas(opcaoIdAluno);
	cout << "\n Total de ECTS : " << meuCurso->contarEcts(opcaoIdAluno);
	cout << "\n Media : " << meuCurso->calcularMediaAluno(opcaoIdAluno)<<"\n";
	if(meuCurso->contarEcts() == meuCurso->contarEcts(opcaoIdAluno)){
		cout << "\nParabens voce concluiu a " << meuCurso->nome << "!!!\n";
	}		
}
void aprovacaoCadeira(Lei *meuCurso){
	int opcaoIdCadeira;
	cout << "\n Insira o codigo da cadeira: ";
	cin >> opcaoIdCadeira;
	Cadeira *opcaoCadeira = meuCurso->obterCadeira(opcaoIdCadeira);
	if(!opcaoCadeira){
		cout<<"\n Cadeira nao encontrada :( \n";
	}
	cout<<"\n--------------------------------------------------";
	cout<<"\n " << opcaoCadeira->nome;
	cout<<"\n Total de alunos aprovados : " << meuCurso->contarAlunosAprovados(opcaoIdCadeira);
	cout<<"\n Media : " << meuCurso->calcularMediaCadeira(opcaoIdCadeira);
	cout<<"\n--------------------------------------------------\n";
}
bool verificarAluno(int opcaoIdAluno, Lei &meuCurso) {
    cout << "\n ID Aluno : ";
    cin >> opcaoIdAluno;
    if (!meuCurso.alunoExiste(opcaoIdAluno)) {
        cout << "\n Aluno nao encontrado :( \n";
        return false;
    }
    return true;
}

bool verificarCadeira(int opcaoIdCadeira, Lei &meuCurso) {
    cout << "\n ID Cadeira : ";
    cin >> opcaoIdCadeira;
    if (!meuCurso.cadeiraExiste(opcaoIdCadeira)) {
        cout << "\n Cadeira nao encontrada :( \n";
        return false;
    }
    return true;
}

void mostrarClassificacao(Lei &meuCurso, int opcaoIdAluno, int opcaoIdCadeira) {
    Aluno *opcaoAluno = meuCurso.obterAluno(opcaoIdAluno);
    Cadeira *opcaoCadeira = meuCurso.obterCadeira(opcaoIdCadeira);
    cout << "\n O " << opcaoAluno->nome << " ja foi aprovado a " << opcaoCadeira->nome 
         << " com " << meuCurso.calcularNota(opcaoIdAluno, opcaoIdCadeira) << "\n";
}

bool validarNota(float nota, float min, float max, string nomeNota) {
    if (nota < min || nota > max) {
        cout << "\n " << nomeNota << " Invalida! :)";
        return false;
    }
    return true;
}

void inserirNotaAvaliacaoContinua(Lei &meuCurso, int opcaoIdAluno, int opcaoIdCadeira) {
    float opcaoEFolioA, opcaoEFolioB, opcaoPFolio;
    
    cout << "\n Nota E FOLIO A : ";
    cin >> opcaoEFolioA;
    if (!validarNota(opcaoEFolioA, 0, 4, "Nota do EFOLIO A")) return;

    cout << "\n Nota E FOLIO B : ";
    cin >> opcaoEFolioB;
    if (!validarNota(opcaoEFolioB, 0, 4, "Nota do EFOLIO B")) return;

    cout << "\n Nota P FOLIO : ";
    cin >> opcaoPFolio;
    if (!validarNota(opcaoPFolio, 0, 12, "Nota do PFolio")) return;

    if ((opcaoEFolioA + opcaoEFolioB + opcaoPFolio) > meuCurso.calcularNota(opcaoIdAluno, opcaoIdCadeira)) {
        meuCurso.inserirNota(opcaoIdAluno, opcaoIdCadeira, opcaoEFolioA, opcaoEFolioB, opcaoPFolio);
        cout << "\n Classificacao inserida com sucesso! :)";
    } else {
        cout << "\n Nao conseguiste melhorar a tua classificacao :(";
        cout << "\n Nota Final : " << meuCurso.calcularNota(opcaoIdAluno, opcaoIdCadeira) << "\n";
    }
}

void inserirNotaExame(Lei &meuCurso, int opcaoIdAluno, int opcaoIdCadeira) {
    float opcaoExame;
    
    cout << "\n Nota do exame : ";
    cin >> opcaoExame;
    if (!validarNota(opcaoExame, 0, 20, "Nota do Exame")) return;

    if (opcaoExame > meuCurso.calcularNota(opcaoIdAluno, opcaoIdCadeira)) {
        meuCurso.inserirNota(opcaoIdAluno, opcaoIdCadeira, opcaoExame);
        cout << "\n Nota Inserida com sucesso! :)";
    } else {
        cout << "\n Nao conseguiste melhorar a tua classificacao :(";
        cout << "\n Nota Final : " << meuCurso.calcularNota(opcaoIdAluno, opcaoIdCadeira) << "\n";
    }
}

void processarMelhoria(Lei &meuCurso, int opcaoIdAluno, int opcaoIdCadeira, Classificacao *opcaoClassificacao) {
    char opcaoMelhoria;
    cout << "\n Pretende fazer melhoria? (s-sim, n-nao): ";
    cin >> opcaoMelhoria;

    if (opcaoMelhoria == 's' || opcaoMelhoria == 'S') {
        if (opcaoClassificacao->avaliacaoContinua) {
            cout << "\n --avaliacao continua-- \n";
            inserirNotaAvaliacaoContinua(meuCurso, opcaoIdAluno, opcaoIdCadeira);
        } else {
            cout << "\n --sem avaliacao continua-- \n";
            inserirNotaExame(meuCurso, opcaoIdAluno, opcaoIdCadeira);
        }
    } else if (opcaoMelhoria != 'n' && opcaoMelhoria != 'N') {
        cout << "\n Opcao Invalida :( ";
    }
}

void fazerMelhoriaNota(Lei &meuCurso) {
    int opcaoIdAluno, opcaoIdCadeira;
    Classificacao *opcaoClassificacao;

    if (!verificarAluno(opcaoIdAluno, meuCurso)) return;
    if (!verificarCadeira(opcaoIdCadeira, meuCurso)) return;

    opcaoClassificacao = meuCurso.obterNota(opcaoIdAluno, opcaoIdCadeira);
    if (opcaoClassificacao == nullptr) {
        cout << "\n Classificacao nao encontrada :( \n";
        return;
    }

    mostrarClassificacao(meuCurso, opcaoIdAluno, opcaoIdCadeira);
    processarMelhoria(meuCurso, opcaoIdAluno, opcaoIdCadeira, opcaoClassificacao);
}
void eliminarAluno(Lei &meuCurso){
	int opcaoIdAluno;
	if (!verificarAluno(opcaoIdAluno, meuCurso)) return;
	Aluno *opcaoAluno = meuCurso.obterAluno(opcaoIdAluno);
	string opcaoNomeAluno = opcaoAluno->nome;
	meuCurso.eliminarAluno(opcaoIdAluno);
	cout << "\n Aluno " << opcaoNomeAluno << " eliminado com sucesso!! :)\n";
}
void adicionarAluno(Lei &meuCurso){
	int opcaoIdAluno;
	int opcaoAno, opcaoSemestre, opcaoNotaMinima, opcaoNotaMaxima;
	cout << "\n Insira o ID do aluno : ";
	cin >> opcaoIdAluno;
	if (verificarAluno(opcaoIdAluno, meuCurso)) {
		return; 
	}
	
	cout << "\n em que ano esta o " << opcaoIdAluno << " ? : ";
	cin >> opcaoAno;

	if (opcaoAno <= 0 || opcaoAno >= 4) {
		cout << "\n Ano invalido! :( \n";
		return; 
	}

	cout << "\n em que semestre esta o " << opcaoIdAluno << " ? : ";
	cin >> opcaoSemestre;

	if (opcaoSemestre <= 0 || opcaoSemestre >= 3) {
		cout << "\n Semestre invalido! :( \n";
		return; 
	}

	cout << "\n Nota minima : ";
	cin >> opcaoNotaMinima;
	cout << "\n Nota Maxima : ";
	cin >> opcaoNotaMaxima;

	if (!notaValida(opcaoNotaMinima) || !notaValida(opcaoNotaMaxima) || opcaoNotaMaxima < opcaoNotaMinima) {
		cout << "\n Nota invalida :( \n";	
		return; 
	}
	inicializarAlunoAleatoriamente(&meuCurso, meuCurso.obterAluno(opcaoIdAluno), opcaoAno, opcaoSemestre, opcaoNotaMinima, opcaoNotaMaxima);
	cout << "\n Notas do Aluno " << opcaoIdAluno << " inseridas com sucesso! :) ";
}
bool notaValida(int nota){
	return nota >=0 && nota <=20;
}
int main(int argc, char** argv) {
	
	Lei meuCurso;
	int opcao;
	
	meuCurso.inserirAluno(1,"Pedro");
	meuCurso.inserirAluno(2,"Alberto");
	meuCurso.inserirAluno(3, "Alzira");
	meuCurso.inserirAluno(4, "Jambe");
	meuCurso.inserirAluno(5, "Felizmino");

	inicializarAlunoAleatoriamente(&meuCurso, meuCurso.obterAluno("Pedro"), 1, 2, 7, 20);
	inicializarAlunoAleatoriamente(&meuCurso, meuCurso.obterAluno("Alberto"), 2, 2, 7, 20);
	inicializarAlunoAleatoriamente(&meuCurso, meuCurso.obterAluno("Alzira"), 3, 1,7,20);
	inicializarAlunoAleatoriamente(&meuCurso, meuCurso.obterAluno("Jambe"), 3, 2, 10, 20);
	inicializarAlunoAleatoriamente(&meuCurso, meuCurso.obterAluno("Felizmino"), 3, 2, 10, 20);
	
	do{
		do{
			mostrarMenuPrincipal();
			cin >> opcao;
			switch(opcao){
				case 1: cadeirasConcluidasDoAluno(&meuCurso);
				break;
				
				case 2: aprovacaoCadeira(&meuCurso); 
				break;
				
				case 3: meuCurso.listarCadeiras();
				break;
				
				case 4: meuCurso.listarAlunos();
				break;
				
				case 5: fazerMelhoriaNota(meuCurso);
				break;
				
				case 6: removerNota(&meuCurso);
				break;
				
				case 7: mostrarCadeirasDoAluno(&meuCurso);		
				break;
				
				case 8: adicionarAluno(&meuCurso);	
				break;
				
				case 9: eliminarAluno(meuCurso);
				break;
				
				case 10: adicionarAluno(meuCurso);
				break;
			};
		}while(opcao < 0 || opcao > 6);
	}while(opcao != 0);
	return 0;	
}
	
	

