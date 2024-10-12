#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
class Aluno{
	public:
		Aluno(int i, string n){
			nome=n;
			id=i;
			proximoAluno=NULL;
		}
		int id;
		string nome;
		Aluno *proximoAluno;
};

class Cadeira{
	public:
		Cadeira(int i, string n, int a, int s, int e){
			id=i;
			nome=n;
			ano=a;
			semestre=s;
			ects=e;
			proximaCadeira=NULL;
		}
		int id;
		string nome;
		int ano;
		int semestre;
		int ects;
		Cadeira *proximaCadeira;
};

class Classificacao{
	public:
		Classificacao(int a, int c, int efa, int efb, int pF){
		/*AVALIACAO CONTINUA*/
			idAluno=a;
			idCadeira=c;
			eFolioA=efa;
			eFolioB=efb;
			pFolio=pF;
			avaliacaoContinua=true;
			exame=0;				
		}
		Classificacao(int a, int c, int e){
		/*EXAME*/
			idAluno=a;
			idCadeira=c;
			exame=e;
			eFolioA=0;
			eFolioB=0;
			pFolio=0;
			avaliacaoContinua=false;		
		}
		int idAluno;
		int idCadeira;
		int eFolioA;
		int eFolioB;
		int pFolio;
		int exame;
		bool avaliacaoContinua;
		Classificacao *proximaClassificacao;
};

class Curso{
		protected:
		Cadeira *cadeiras=NULL;
		Classificacao *notas=NULL;
		Aluno *alunos=NULL; 
		public:
			string nome;
			Curso(string n){
				nome=n;
			}
			/****** METODOS DE INSERCAO *************************************************************************/
			void inserirCadeira(int idCadeira, string nomeCadeira, int ano, int semestre, int ects){
				Cadeira *novaCadeira = new Cadeira(idCadeira, nomeCadeira, ano, semestre, ects);
				if(cadeiras==NULL){
					cadeiras=novaCadeira;
					
				}else{
					novaCadeira->proximaCadeira=cadeiras;
					cadeiras=novaCadeira;
				}	
			}
			void inserirAluno(int idAluno, string nomeAluno){
				Aluno *novoAluno = new Aluno(idAluno, nomeAluno);
				if(alunos==NULL){
					alunos=novoAluno;
					
				}else{
					novoAluno->proximoAluno=alunos;
					alunos=novoAluno;
				}	
			}
			void inserirNota(int idAluno, int idCadeira, int eFolioA, int eFolioB, int pFolio){
				Classificacao *novaNota=new Classificacao(idAluno, idCadeira, eFolioA, eFolioB, pFolio);
				Classificacao *p;
				p=obterNota(idAluno, idCadeira);
				if(notas==NULL){
					notas=novaNota;
				}else if(p==NULL){
					novaNota->proximaClassificacao=notas;
					notas=novaNota;
					}else{
						p->eFolioA=eFolioA;
						p->eFolioB=eFolioB;
						p->pFolio=pFolio;
						p->avaliacaoContinua=true;
					}
			}
			void inserirNota(int idAluno, int idCadeira, int exame){
				Classificacao *novaNota=new Classificacao(idAluno, idCadeira, exame);
				Classificacao *p;
				p=obterNota(idAluno, idCadeira);
				if(notas==NULL){
					notas=novaNota;
				}else if(p==NULL){
					novaNota->proximaClassificacao=notas;
					notas=novaNota;
				}else{
					p->exame=exame;
					p->avaliacaoContinua=false;
				}
			}
			/****** METODOS DE ELIMINACAO ***********************************************************/
			void eliminarCadeira(int idCadeira){
				Cadeira *p, *pp;
				if(cadeiras->id==idCadeira){
					cadeiras=cadeiras->proximaCadeira;
				}else{
					for(pp=cadeiras, p=cadeiras->proximaCadeira;p!=NULL;p=p->proximaCadeira, pp=pp->proximaCadeira){
						if(p->id==idCadeira){
							if(p->proximaCadeira==NULL){
								pp->proximaCadeira=NULL;
							}else{
								pp->proximaCadeira=p->proximaCadeira;
							}
						}
					}	
				}
			}
			void eliminarAluno(int idAluno){
				Aluno *p, *pp;
				Classificacao *c;
				if(alunos->id==idAluno){
					alunos=alunos->proximoAluno;
				}else{
					for(pp=alunos, p=alunos->proximoAluno;p!=NULL;p=p->proximoAluno, pp=pp->proximoAluno){
						if(p->id==idAluno){
							if(p->proximoAluno==NULL){
								pp->proximoAluno=NULL;
							}else{
								pp->proximoAluno=p->proximoAluno;
							}
						}
					}	
				}
				/*eliminar as notas do aluno*/
				for(c=notas;c!=NULL; c=c->proximaClassificacao){
					if(c->idAluno==idAluno){
						eliminarNota(idAluno,c->idCadeira);
					}
				}
			}
			void eliminarNota(int idAluno, int idCadeira){
				Classificacao *p, *pp;
				if(notas->idCadeira==idCadeira && alunos->id==idAluno){
					notas=notas->proximaClassificacao;
				}else{
					for(pp=notas, p=notas->proximaClassificacao;p!=NULL;p=p->proximaClassificacao, pp=pp->proximaClassificacao){
						if(p->idCadeira==idCadeira && p->idAluno==idAluno){
							if(p->proximaClassificacao==NULL){
								pp->proximaClassificacao=NULL;
							}else{
								pp->proximaClassificacao=p->proximaClassificacao;
							}
						}
					}	
				}
			}
			/************* METODOS DE OBTENCAO **********************************************************/
			Cadeira *obterCadeira(int idCadeira){
				Cadeira *p;
				for(p=cadeiras;p!=NULL;p=p->proximaCadeira){
					if(p->id==idCadeira){
						return p;
					}
				}
				return NULL;
			}
			Aluno *obterAluno(int idAluno){
				Aluno *p;
				for(p=alunos;p!=NULL;p=p->proximoAluno){
					if(p->id==idAluno){
						return p;
					}
				}
				return NULL;
			}
			Aluno *obterAluno(string nomeAluno){
				Aluno *p;
				for(p=alunos;p!=NULL;p=p->proximoAluno){
					if(p->nome==nomeAluno){
						return p;
					}
				}
				return NULL;
			}
			Classificacao *obterNota(int idAluno, int idCadeira){
				Classificacao *p;
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idCadeira==idCadeira && p->idAluno==idAluno){
						return p;
					}
				}
				return NULL;
			}
			/************* METODOS DE VERIFICACAO **********************************************/
			bool alunoExiste(int idAluno){
				Aluno *p;
				for(p=alunos;p!=NULL;p=p->proximoAluno){
					if(p->id==idAluno){
						return true;
					}
				}
				return false;
			}
			bool cadeiraExiste(string nomeCadeira){
				Cadeira *p;
				for(p=cadeiras; p!=NULL; p=p->proximaCadeira){
					if(p->nome==nomeCadeira){
						return true;
					}
				}
				return false;
			}
			bool cadeiraExiste(int idCadeira){
				Cadeira *p;
				for(p=cadeiras; p!=NULL; p=p->proximaCadeira){
					if(p->id==idCadeira){
						return true;
					}
				}
				return false;
			}
			/************* METODOS DE LISTAGEM **********************************************/
			void listarAlunos(){
				Aluno *p;
				cout<<"\n ID - NOME ";
				cout<<"\n-----------------------------\n";
				for(p=alunos;p!=NULL;p=p->proximoAluno){
					cout<<"\n "<<p->id<<" - "<<p->nome<<" \n";
				}
			}
			void listarCadeirasConcluidas(int idAluno){
				Classificacao *p;
				Cadeira *c;
				float notaFinal;
				cout<<"\n ID - UC - ECTS - EFOLIOA - EFOLIOB - PFOLIO - EXAME - CLASSIFICACAO \n";
				cout<<"----------------------------------------------------------------------- \n";
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idAluno==idAluno){
						notaFinal=calcularNota(idAluno, p->idCadeira); 
						if(notaFinal>=10 && notaFinal<=20){
							c=obterCadeira(p->idCadeira);
							cout<<c->id<<" - "<<c->nome<<" - "<<c->ects<<" - "<<p->eFolioA<<" - "<<p->eFolioB<<" - "<<p->pFolio<<" - "<<p->exame<<" - "<<notaFinal<<"\n";	
						}
					}
				}
			}
			void listarCadeiras(){
				Cadeira *p;
				cout<<"\n   ID - NOME - ECTS - ANO - SEMESTRE	\n";
				cout<<"----------------------------------------\n";
				for(p=cadeiras; p!=NULL; p=p->proximaCadeira){
					cout<<"\n "<< p->id <<" - "<< p->nome <<" - "<< p->ano << " - " << p->semestre;
				}
			}
			void listarCadeiras(int idAluno){
				Classificacao *p;
				Cadeira *c;
				float notaFinal;
				cout<<"\n ID - UC - ECTS - EFOLIOA - EFOLIOB - PFOLIO - EXAME - CLASSIFICACAO \n";
				cout<<"----------------------------------------------------------------------- \n";
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idAluno==idAluno){
						notaFinal=calcularNota(idAluno, p->idCadeira); 
						c=obterCadeira(p->idCadeira);
						cout<<c->id<<" - "<<c->nome<<" - "<<c->ects<<" - "<<p->eFolioA<<" - "<<p->eFolioB<<" - "<<p->pFolio<<" - "<<p->exame<<" - "<<notaFinal<<"\n";	
					}
				}
			}
			/************* METODOS DE CONTAGEM **********************************************/
			int contarCadeirasConcluidas(int idAluno){
				Classificacao *p;
				float notaFinal;
				int c=0;
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idAluno==idAluno){
						notaFinal=calcularNota(p->idAluno,p->idCadeira);
						if(notaFinal>=10 && notaFinal<=20){
							c++;
						}	
					}
				}
				return c;
			}
			int contarAlunosAprovados(int idCadeira){
				Classificacao *p;
				float notaFinal;
				int c=0;
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idCadeira==idCadeira){
						notaFinal=calcularNota(p->idAluno,p->idCadeira);
						if(notaFinal>=10 && notaFinal<=20 ){
							c++;
						}		
					}
				}
				return c;
			}
			int contarEcts(int idAluno){
				Classificacao *p;
				Cadeira *c;
				float notaFinal;
				int t=0;
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idAluno==idAluno){
						notaFinal=calcularNota(p->idAluno, p->idCadeira);
						if(notaFinal>=10 && notaFinal<=20 ){
							c=obterCadeira(p->idCadeira);
							t+=c->ects;
						}	
					}
				}
				return t;
			}
			int contarEcts(){
				Cadeira *p;
				int t=0;
				for(p=cadeiras;p!=NULL;p=p->proximaCadeira){
					t+=p->ects;
				}
				return t;
			}
			/************* METODOS DE CALCULO **********************************************/
			float calcularMediaAluno(int idAluno){
				Classificacao *p;
				Cadeira *c;
				float somaNotas=0;
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idAluno==idAluno){
						c=obterCadeira(p->idCadeira);
						somaNotas+=(calcularNota(p->idAluno,p->idCadeira)*c->ects);
					}
				}
				return somaNotas/contarEcts(idAluno);
			}
			float calcularMediaCadeira(int idCadeira){
				Classificacao *p;
				int totalNotas=0;
				float somaNotas=0;
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idCadeira==idCadeira){
						somaNotas+=calcularNota(p->idAluno, p->idCadeira);
						totalNotas++;
					}
				}
				return somaNotas/totalNotas;
			}
			float calcularNota(int idAluno, int idCadeira){
				Classificacao *p;
				float notaFinal=0;
				for(p=notas;p!=NULL;p=p->proximaClassificacao){
					if(p->idAluno==idAluno && p->idCadeira==idCadeira){
						if(p->avaliacaoContinua){
							notaFinal= p->eFolioA + p->eFolioB + p->pFolio;
						}else{
							notaFinal= p->exame;
						}	
					}
					
				}
				return notaFinal;
			}
			
			
};
class Lei: public Curso{
	public:
	Lei():Curso("Engenharia Informatica"){
		inserirCadeira(21002,"Algebra Linear l",1,1, 6);
		inserirCadeira(21175,"Analise Infinitesimal",1,1, 6);
		inserirCadeira(21010,"Arquitectura de Computadores",1,1, 6);
		inserirCadeira(21176,"Etica e Praticas de Engenharia",1,1, 2);
		inserirCadeira(21173,"Introducao a Programacao",1,1, 6);
		inserirCadeira(21174,"Sistemas Computacionais",1,1, 4);
		inserirCadeira(21037,"Elementos de Probabilidades e Estatistica",1,2, 6);
		inserirCadeira(21178,"Laboratorio de Programacao",1,2, 6);
		inserirCadeira(21082,"Matematica Finita",1,2, 6);
		inserirCadeira(21177,"Modelacao de Sistemas de Informacao",1,2, 6);
		inserirCadeira(21111,"Sistemas Operativos",1,2, 6);
		inserirCadeira(21048,"Fisica Geral",2,1, 6);
		inserirCadeira(21053,"Fundamentos de Bases de Dados",2,1, 6);
		inserirCadeira(21078,"Linguagens e Computacao",2,1, 6);
		inserirCadeira(21093,"Programacao por Objetos",2,1, 6);
		inserirCadeira(21106,"Sistemas em Rede",2,1, 6);
		inserirCadeira(21046,"Estruturas de Dados e Algoritmos Fundamentais",2,2, 6);
		inserirCadeira(21071,"Introducao a Inteligencia Artificial",2,2, 6);
		inserirCadeira(21076,"Investigacao Operacional",2,2, 6);
		inserirCadeira(21179,"Laboratorio de Desenvolvimento de Software",2,2, 6);
		inserirCadeira(21077,"Linguagens de Programacao",2,2, 6);
		inserirCadeira(21020,"Computacao Grafica",3,1, 6);
		inserirCadeira(21180,"Computacao Numerica",3,1, 4);
		inserirCadeira(21062,"Gestao de Projetos Informaticos",3,1, 6);
		inserirCadeira(21181,"Segurança em Redes e Computadores",3,1, 2);
		inserirCadeira(21103,"Sistemas de Gestao de Bases de Dados",3,1, 6);
		inserirCadeira(21110,"Sistemas Multimedia",3,1, 6);
		inserirCadeira(21018,"Compilacao",3,2, 6);
		inserirCadeira(21182,"Laboratorio de Sistemas e Serviços Web",3,2, 6);
		inserirCadeira(21184,"Projeto de Engenharia Informatica",3,2, 6);
		inserirCadeira(21097,"Raciocinio e Representacao do Conhecimento",3,2, 6);
		inserirCadeira(21108,"Sistemas Distribuidos",3,2, 6);
	}
	friend void inicializarAlunoAleatoriamente(Lei *meuCurso, Aluno *aluno, int ano, int semestre, int limInf, int limSup);
	
};




