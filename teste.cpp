/*
	Antes de compilar veja as dependências e use o Makefile
		
	Instalar MySQL(Ubuntu) Se não usas, comece agora;
	$ sudo apt-get install mysql-server mysql-client

	Para reiniciar o MySQL;
	$ sudo service mysql restart

	Iniciar o MySQL com cliente admin;
	$ mysql --user=root -p
	(Após o Enter será necessário a senha escolhida durante a instalação)

	mysql>
	Comandos do mysql já são aceitos aqui

	EX: CREATE DATABASE teste;

	Crie antes um Database com o nome "teste" e mude os defines para se adaptar
	aos seus dados como a senha que você escolheu para seu usuário do DB
	
	
	Para instalar a biblioteca mysql, necessária para manipulação no C++:
	$ sudo apt-get install libmysql++-dev

	Para compilar:
	$ make main
	Executar:
	$ ./teste
*/


#include <iostream>
#include <string>

#include <mysql/mysql.h>

using namespace std;

#define HOST "localhost"
#define USER "root"
#define PASS "alexandre"
#define DB "teste"

int main()
{


	//Conectando-se com o banco de dados
	MYSQL conexao;

	mysql_init(&conexao);
	if ( mysql_real_connect(&conexao, HOST, USER, PASS, DB, 0, NULL, 0) )
	{
		cout<<"conectado com sucesso!"<<endl;
	}	
	else
	{
		cout<<"Falha de conexao"<<endl;
		cout<<"Erro "<<mysql_errno(&conexao)<<" : "<<mysql_error(&conexao)<<endl;
		mysql_close(&conexao);
		return -1;
	}

	//Inserir
	/*
	*/
	int res = mysql_query(&conexao, "INSERT INTO aprendendo(nome, sexo) values('Alexandre Alves', 'M');");
	if (res == 0)
	{
		cout<<"Dados Inseridos"<<endl;
	}
	else
	{
		cout<<"Erro na inserção de dados "<<mysql_errno(&conexao)<<" : "<<mysql_error(&conexao)<<endl;
	}

	//Consulta
	MYSQL_RES *resp;
	MYSQL_ROW linhas;
	MYSQL_FIELD *campos;


	//DELETE FROM aprendendo WHERE ID=2;
	//SELECT * FROM aprendendo WHERE ID=1;
	string query = "SELECT * FROM aprendendo;"; //Altere para as outras funções do MySQL como as de remover e alterar
	int cont;

	//Mostrar os dados da tabela
	if (mysql_query(&conexao, query.c_str()))
	{
		cout<<"Erro SELECT"<<endl;
		return -1;
	}
	resp = mysql_store_result(&conexao);
	if (resp)
	{
		campos = mysql_fetch_fields(resp);
		for (cont = 0; cont < mysql_num_fields(resp); cont++)
		{
			cout<<(campos[cont]).name;
			if (mysql_num_fields(resp)>1){
				cout<<"\t";
			}
		}
		cout<<endl;
		while((linhas=mysql_fetch_row(resp))!=NULL)
		{
			for (cont = 0; cont < mysql_num_fields(resp); cont++)
			{
				cout<<linhas[cont]<<"\t";
			}
			cout<<endl;
		}
	}
	mysql_free_result(resp);

	mysql_close(&conexao);
	return 0;
}