#include<bits/stdc++.h>
using namespace std;

typedef struct sym_table
{
	string sym_no;
	string sym;
	string sym_addr;
}sym_table;

typedef struct lit_table
{
	string lit_no;
	string lit;
	string lit_addr;
}lit_table;


void tokenize(vector<string>& tmp,string instruction)
{
	stringstream checkl(instruction);
	string s;
	
	while(getline(checkl,s,' ')){
		tmp.push_back(s);
	}
}

int check(vector<sym_table>symbol_table,string s)
{
	for(int i=0;i<symbol_table.size();i++)
	{
		if(symbol_table[i].sym==s)
			return i;
	}
	return -1;
}

int check2(vector<lit_table>literal_table,string s,int start)
{
	for(int i=start;i<literal_table.size();i++)
	{
		if(literal_table[i].lit==s)
			return i;
	}
	return -1;
}

void create_mot_table(unordered_map<string,string>& mot_table)
{
	mot_table["mover"]="01";
	mot_table["movem"]="02";
	mot_table["add"]="03";
	mot_table["sub"]="04";
	mot_table["mult"]="05";
	mot_table["div"]="06";
	mot_table["bc"]="07";
	mot_table["comp"]="08";
	mot_table["print"]="09";
	mot_table["read"]="10";
}

void create_ad_table(unordered_map<string,string>& ad_table)
{
	ad_table["start"]="01";
	ad_table["end"]="02";
	ad_table["equ"]="03";
	ad_table["origin"]="04";
	ad_table["ltorg"]="05";
}

void create_dl_table(unordered_map<string,string>& dl_table)
{
	dl_table["ds"]="01";
	dl_table["dc"]="02";
}

void create_reg_table(unordered_map<string,string>& reg_table)
{
	reg_table["areg"]="01";
	reg_table["breg"]="02";
	reg_table["creg"]="03";
	reg_table["dreg"]="04";
}

void display(vector<vector<string>>input)
{
	for(int i=0;i<input.size();i++)	
	{
		cout<<i<<"\t";
		for(int j=0;j<input[i].size();j++)
		{
			cout<<input[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

void error()
{
	cout<<"error in code.\n";
}

int main()
{
	unordered_map<string,string>mot;
	create_mot_table(mot);
	
	unordered_map<string,string>ad;
	create_ad_table(ad);
	
	unordered_map<string,string>dl;
	create_dl_table(dl);
	
	unordered_map<string,string>reg;
	create_reg_table(reg);
			
	string instruction;
	ifstream f("input.txt");
	
	vector<vector<string>>input;
	vector<string>tmp;
	
	vector<sym_table>symbol_table;
	vector<lit_table>literal_table;
		
	vector<vector<string>>output;
	
	while(getline(f,instruction))
	{
		tokenize(tmp,instruction);
		input.push_back(tmp);
		tmp.erase(tmp.begin(),tmp.end());
	}

	cout<<"input is :\n\n\n";
	display(input);
	cout<<"\n";
	int i=1;
	int lc=0;
	int size=1;
	int start=0;
	int symbol_table_count=1;
	int literal_table_count=1;
	
	if(input[0][1]=="start")  //start case
	{
		if(input[0][3]!="-")
			lc=stoi(input[0][3]);
		vector<string>tmp;
		tmp.push_back("0 ) ");
		tmp.push_back("(AD," + ad[input[0][1]]+ ")");
		tmp.push_back("-");
		tmp.push_back("(C,"+to_string(lc)+")");
		output.push_back(tmp);
	}
	else {
		error();
		return 0;
	}
	while(i<input.size())
	{	
		vector<string>ic;
	
		if(input[i][1]=="origin")	
		{
			lc=stoi(input[i][3]);
			i++;
			continue;
		}
		else
		{
			ic.push_back(to_string(lc)+" ) ");
		}
		
		if(input[i][0]!="-") // adding label in symbol table
		{
			sym_table sti; 
			sti.sym_no=to_string(symbol_table_count);
			sti.sym=input[i][0];
			sti.sym_addr=to_string(lc);
			symbol_table.push_back(sti);
			symbol_table_count++;
		}
	
			
			
		if(ad.find(input[i][1])!=ad.end() && input[i][1]!="ltorg" && input[i][1]!="origin")
		{
			ic.push_back("(AD,"+ad[input[i][1]]+")");
		}
		else if(mot.find(input[i][1])!=mot.end())
		{
			ic.push_back("(IS,"+mot[input[i][1]]+")");
		}
		else if(input[i][1]=="ltorg")
		{
			for(int j=start;j<literal_table.size();j++)
			{
				vector<string>v;
				literal_table[j].lit_addr=to_string(lc);
				v.push_back(to_string(lc)+" ) ");
				v.push_back("(AD," + ad[input[i][1]]+")");
				v.push_back("-");
				v.push_back(literal_table[j].lit);
				output.push_back(v);
				lc++;
			}
			start=literal_table.size();
		}
		
		if(input[i][2]=="-")				
		{
			ic.push_back("-");
		}
		else if(input[i][2]=="ds")
		{
			ic.push_back("(DL,"+dl[input[i][2]]+")");
			ic.push_back("-");
		}
		else if(input[i][2]=="dc")
		{
			ic.push_back("(DC,"+dl[input[i][2]]+")");
			ic.push_back("-");
		}
		else
		{
			if(reg.find(input[i][2])!=reg.end())
			{
				ic.push_back(reg[input[i][2]]);
			}
			else
			{
				int x=check(symbol_table,input[i][2]);
				if(x==-1)
				{
					sym_table sti;
					sti.sym_no=to_string(symbol_table_count);
					sti.sym=input[i][2];
					symbol_table.push_back(sti);
					symbol_table_count++;
					ic.push_back("(S," + to_string(symbol_table_count-1) + ")");
				}
				else
				{
					if(input[i][1]=="equ")
					{
						symbol_table[symbol_table_count-2].sym_addr= symbol_table[x].sym_addr;
					}
					else
					{
						ic.push_back("(S," + to_string(x+1)+ ")");
					}
				}
			}
		}
		
		if(input[i][3]=="-" && input[i][1]!="end")				
		{
			ic.push_back("-");
		}
		else if(input[i][3]>="0" and input[i][3]<="9")
		{
			ic.push_back(input[i][3]);
		}
		else if(input[i][1]=="end")
		{
			ic.push_back(literal_table[literal_table_count-2].lit);
			literal_table[literal_table_count-2].lit_addr=to_string(lc);
		}
		else
		{
			if(reg.find(input[i][3])!=reg.end())
			{
				ic.push_back(reg[input[i][3]]);
			}
			else
			{
				if(input[i][3][0]!='=')
				{
					int x=check(symbol_table,input[i][3]);
					if(x==-1)
					{
						sym_table sti;
						sti.sym_no=to_string(symbol_table_count);
						sti.sym=input[i][3];
						symbol_table.push_back(sti);
						symbol_table_count++;
						ic.push_back("(S," + to_string(symbol_table_count-1) + ")");
					}
					else
					{
						ic.push_back("(S," + to_string(x+1)+ ")");
					}
				}
				else
				{
					int y=check2(literal_table,input[i][3].substr(1),start);
					if(y==-1)
					{
						lit_table lti;
						lti.lit_no=to_string(literal_table_count);
						lti.lit=input[i][3].substr(1);
						literal_table.push_back(lti);
						literal_table_count++;
						ic.push_back("(L," + to_string(literal_table_count-1) + ")");
					}
					else
					{
						ic.push_back("(L," + to_string(y+1)+ ")");
					}
				}
			}
		}
		if(input[i][1]!="ltorg" and input[i][1]!="equ")
		{
			lc=lc+size;
			output.push_back(ic);
		}
		i++;			
	}
	
	cout<<"output is:\n";
	for(int i=0;i<output.size();i++)
	{
		for(int j=0;j<output[i].size();j++)
		{
			cout<<output[i][j]<<"\t";
		}
		cout<<"\n";
	}

	cout<<"\nliteral table is:\n";
	for(int i=0;i<literal_table.size();i++)
	{
		cout<<literal_table[i].lit_no<<"\t"<<literal_table[i].lit<<"\t"<<literal_table[i].lit_addr<<"\n";
	}
	
	cout<<"\nsymbol table is:\n";
	for(int i=0;i<symbol_table.size();i++)
	{
		cout<<symbol_table[i].sym_no<<"\t"<<symbol_table[i].sym<<"\t"<<symbol_table[i].sym_addr<<"\n";
	}
		
	return 0;
}
