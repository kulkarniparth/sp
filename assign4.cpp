#include<bits/stdc++.h>
using namespace  std;

typedef struct KEY
{
	int index;
	string keyword;
}KEY;

typedef struct LIT
{
	int index;
	string literal;	
}LIT;

typedef struct UST
{
	int index;
	string token;
	string classification;
}UST;

typedef struct TER
{
	int index;
	char terminal;	
}TER;

typedef struct IDN
{
	int index;
	string identifier;	
}IDN;

int isterminal(char ch)
{
	if(ch==' ' || ch=='\n' || ch==';' || ch==',' || ch=='=' || ch=='+' || ch=='(' || ch==')' || ch=='{' || ch=='}')
		return 1;
	return 0;
}

int iskeyword(string s)
{
	if(s=="int" || s=="break" || s=="if" || s=="else" || s=="return" || s=="void")
		return 1;
	return 0;
}

void showKeyword(vector<KEY>keyword_table,int keyword_table_index)
{
	cout<<"Keyword Table is:\n";
	for(int i=0;i<keyword_table_index;i++)
	{
		cout<<keyword_table[i].index<<"\t"<<keyword_table[i].keyword<<"\n";
	}
}

void showTerminal(vector<TER>terminal_table,int terminal_table_index)
{
	cout<<"Terminal Table is:\n";
	for(int i=0;i<terminal_table_index;i++)
	{
		cout<<terminal_table[i].index<<"\t"<<terminal_table[i].terminal<<"\n";
	}
}

void showIdentifier(vector<IDN>identifier_table,int identifier_table_index)
{
	cout<<"Identifier Table is:\n";
	for(int i=0;i<identifier_table_index;i++)
	{
		cout<<identifier_table[i].index<<"\t"<<identifier_table[i].identifier<<"\n";
	}
}

void showLiteral(vector<LIT>literal_table,int literal_table_index)
{
	cout<<"Literal Table is:\n";
	for(int i=0;i<literal_table_index;i++)
	{
		cout<<literal_table[i].index<<"\t"<<literal_table[i].literal<<"\n";
	}	
}

void showUniformSymbol(vector<UST>uniform_symbol_table,int uniform_symbol_table_index)
{
	cout<<"Uniform Symbol Table is:\n";
	for(int i=0;i<uniform_symbol_table_index;i++)
	{
		cout<<uniform_symbol_table[i].index<<"\t"<<uniform_symbol_table[i].token<<"\t"<<uniform_symbol_table[i].classification<<"\n";
	}	
}

int searchTerminal(vector<TER>terminal_table,int terminal_table_index,char ch)
{
	for (int i = 0; i < terminal_table_index; ++i)
	{
		if(terminal_table[i].terminal==ch)
			return 0;
	}
	return 1;
}


int searchIdentifier(vector<IDN>identifier_table,int identifier_table_index,string ch)
{
	for (int i = 0; i < identifier_table_index; ++i)
	{
		if(identifier_table[i].identifier==ch)
			return 0;
	}
	return 1;
}

int main()
{
	ifstream fin("assign4Input.txt");
	if (!fin.is_open())
	{
		cout<<"Error opening file\n";
	}
	string s;
	vector<TER>terminal_table(20);
	vector<LIT>literal_table(20);
	vector<UST>uniform_symbol_table(20);
	vector<KEY>keyword_table(20);
	vector<IDN>identifier_table(20);

	int terminal_table_index=0;
	int literal_table_index=0;
	int uniform_symbol_table_index=0;
	int keyword_table_index=0;
	int identifier_table_index=0;
	int flag=0;
	while(!fin.eof())
	{
		char ch=fin.get();
		if(ch=='"')
			flag=flag^1;
		if(flag!=1 && isterminal(ch))
		{
			if(ch!=' ' && ch!='\n')
			{
				if(searchTerminal(terminal_table,terminal_table_index,ch))
				{
					uniform_symbol_table[uniform_symbol_table_index].index=terminal_table_index;
					uniform_symbol_table[uniform_symbol_table_index].token=ch;
					uniform_symbol_table[uniform_symbol_table_index].classification="TER";
					uniform_symbol_table_index++;

					terminal_table[terminal_table_index].index=terminal_table_index;
					terminal_table[terminal_table_index].terminal=ch;
					terminal_table_index++;

				}
			}

			string tmp=s;
			s="";

			if(iskeyword(tmp))
			{
				uniform_symbol_table[uniform_symbol_table_index].index=keyword_table_index;
				uniform_symbol_table[uniform_symbol_table_index].token=tmp;
				uniform_symbol_table[uniform_symbol_table_index].classification="KEY";
				uniform_symbol_table_index++;

				keyword_table[keyword_table_index].index=keyword_table_index;
				keyword_table[keyword_table_index].keyword=tmp;
				keyword_table_index++;
			}
			else if(tmp!="")
			{
				if(tmp[tmp.length()-1]=='"')
				{
					uniform_symbol_table[uniform_symbol_table_index].index=literal_table_index;
					uniform_symbol_table[uniform_symbol_table_index].token=tmp;
					uniform_symbol_table[uniform_symbol_table_index].classification="LIT";
					uniform_symbol_table_index++;					

					literal_table[literal_table_index].index=literal_table_index;
					literal_table[literal_table_index].literal=tmp;
					literal_table_index++;
				}
				else if(searchIdentifier(identifier_table,identifier_table_index,tmp))
				{	
					uniform_symbol_table[uniform_symbol_table_index].index=identifier_table_index;
					uniform_symbol_table[uniform_symbol_table_index].token=tmp;
					uniform_symbol_table[uniform_symbol_table_index].classification="IDN";
					uniform_symbol_table_index++;

					identifier_table[identifier_table_index].index=identifier_table_index;
					identifier_table[identifier_table_index].identifier=tmp;
					identifier_table_index++;
				}
			}
		}
		else
		{
			s=s+ch;
		}

	}

	showKeyword(keyword_table,keyword_table_index);
	showTerminal(terminal_table,terminal_table_index);
	showIdentifier(identifier_table,identifier_table_index);
	showLiteral(literal_table,literal_table_index);
	showUniformSymbol(uniform_symbol_table,uniform_symbol_table_index);
	return 0;
}