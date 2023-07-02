/* 
    Note:
    - In this code, we implement LL(1) parsing grammar in C++.
    - The input is read from a file with the following format:
        - The first line contains the start symbol.
        - The following lines contain the production rules.
        - The last line contains the input string.
    
    The code performs the following steps:
    1. Read the grammar and input from the file.
    2. Build the grammar rules, variables, and terminals.
    3. Compute the First and Follow sets for each variable.
    4. Construct the LL(1) parsing table based on the First and Follow sets.
    5. Parse the input string using the constructed parsing table.

    Note that epsilon is represented by '@' symbol in this code due to limitations in inputting epsilon in C++.

    Written By: Sweta Singh
*/
    
#include<bits/stdc++.h>
using namespace std;

class Grammar{
    public:
        //for storing rules , variables and terminal
        map<char,vector<string>> rules;
        set<char> variables;
        set<char> terminals;
        char start;//start symbol
        // parsing table
        map<pair<char,char>,string> table;
        //for parsing First and Follow
        map<char,set<char>> first,follow;
        string inputString;

        
        // take i/p from file
        void initialize(){
            start='!';
            cout<<"Enter file name :- \n";
            string filename;
            cin>>filename;
            vector<string> lines;
            string line;

            ifstream input_file(filename);//open
            if (!input_file.is_open()) {//error
                cerr << "Could not open the file - '"<< filename << "'" << endl;
                exit(0);
            }

            while (getline(input_file, line)){//eof
                string nline="";
                for(auto it:line){
                    if(it!=' ')nline+=it;
                }
                if(nline.length()!=0)
                lines.push_back(nline);

            }
            //Initializing start symbol
            start=lines[0][0];
            for (int cnt=1;cnt<lines.size()-1;cnt++)
            {   
                auto line=lines[cnt];   
                int ind=0,n=line.length();
                //variable
                variables.insert(line[ind++]);
                //removing arrow(->)
                ind+=2;
                //add rules
                rules[line[ind-3]].push_back(line.substr(ind));
                while(ind<n)
                {
                    if(!(line[ind]>='A' && line[ind]<='Z'))
                    terminals.insert(line[ind++]);
                    else
                    variables.insert(line[ind++]);
                }
            }
            //Since I/P string is in last of file
            inputString=lines[lines.size()-1];
            //Priting grammar that we received from file
            cout<<"Start Variable :- "<<start<<"\n";
            cout<<"Variables :-  ";
            for(auto i : variables)
                cout<<i<<" ";
            cout<<"\n";
            cout<<"Terminals :-  ";
            for(auto i : terminals)
            cout<<i<<" ";
            cout<<"\n";
            cout<<"Production Rules :-\n";
            for(auto i : rules)
            {
                cout<<i.first<<" -> ";
                for(auto j : i.second){
                    cout<<j;
                    if(j!=i.second.back())cout<<" | ";
                }
                cout<<"\n";
            }
            input_file.close();
        }

        //i call j and visited[make_pair(i,j)] store first(j) wrt i
        map<pair<char,char>,set<char>> visited;
        //function find first of V when call by U like directed graph U->V 
        set<char> ffirst(char V,char U){//U call V
            auto pp=make_pair(U,V);
            if(!(V>='A' && V<='Z'))
            return  {V};
            if((visited.size())&&(visited.find(pp)!=visited.end())){
                return visited[pp];
            }

            visited[pp]={};//not-visited
       
            set<char> temp;
            for(auto i:rules[V]){
                if(i=="@")temp.insert('@'),visited[pp].insert('@');
            }
            for(auto i : rules[V])
            {   
                if(i=="@")continue;
                if(!(i[0]>='A'&&i[0]<='Z')){
                    temp.insert(i[0]);
                    visited[pp].insert(i[0]);
                }
                
                else {   
                    bool isEpi=false;
                    for(auto ch:i){
                        auto temp1=ffirst(ch,V);//i[0]->V ^
                        isEpi=false;
                        for(auto j:temp1)
                            if(j=='@')isEpi=true;
                            else {
                                temp.insert(j);
                                visited[pp].insert(j);
                            }
                        if(isEpi==false)break;
                    }
                    if(isEpi){
                        temp.insert('@');
                        visited[pp].insert('@');
                    }
                }
            }
            return temp;
        }
        // finding first for all variable
        void find_First(){
            for(auto V:variables){
                visited.clear();
                first[V]=ffirst(V,'!');
            }
            //printing first
            cout<<"\nFirst:-\n";
            for(auto it:first){
                cout<<it.first<<" -> { ";
                for(auto i:it.second){
                    cout<<i;
                    if(i!=(*it.second.rbegin()))
                    cout<<" , ";
                }
                cout<<" }\n";
            }
        }
        //function calculate first of a string consist of terminal and non-terminal
        set<char> findFirstOfString(string s)
        {
            set<char> ans;
            int count=0;
            for(auto i : s)
            {
                if(!(i>='A' && i<='Z'))
                {
                    ans.insert(i);
                    break;
                }
                else
                {
                    bool flag=false;
                    for(auto j : first[i])
                    {
                        if(j=='@')
                        flag=true;
                        else
                        ans.insert(j);
                    }
                    if(!flag)
                    break;
                }
                count++;
            }
            if(count==s.length())
            ans.insert('@');
            return ans;
        }

        //visited for follow
        set<char> visited1;
        // calculate follow for a Variable V
        set<char> ffollow(char V)
        {
            if(!(V>='A' && V<='Z'))
            return  {V};
            if((visited1.size())&&(visited1.find(V)!=visited1.end())){
                return {};
            }
            visited1.insert(V);
            set<char> temp;
            if(V==start)
            temp.insert('$');
            for(auto ele:rules)
            {
                for(auto rule : ele.second)
                {
                    int ind,n=rule.length();
                    bool checkf=false;
                    for(ind=0;ind<n-1;ind++)
                    {
                        if(rule[ind]==V)
                        {
                            auto nextf=findFirstOfString(rule.substr(ind+1));
                            for(auto i : nextf)
                            {
                                if(i!='@')
                                temp.insert(i);
                                else
                                checkf=true;
                            }
                            if(checkf)
                            {
                                auto nextf=ffollow(ele.first);
                                for(auto i : nextf)
                                {
                                    if(i!='@')
                                    temp.insert(i);
                                }
                                break;
                            }
                        }
                    }
                    if(rule[n-1]==V)
                    {
                        auto nextf=ffollow(ele.first);
                        for(auto i : nextf)
                        {
                            if(i!='@')
                            temp.insert(i);
                        }
                    } 
                }
            }
            auto itr=visited1.find(V);
            if(itr!=visited1.end())
            visited1.erase(itr);
            return temp;
        }

        //find follow for all Variable
        void find_Follow()
        {
            follow[start].insert('$');
            for(auto V:variables){
                visited.clear();
                auto x = ffollow(V);
                for(auto i : x)
                follow[V].insert(i);
            }
            // printing follow
            cout<<"\nFollow:-\n";
            for(auto it:follow){
                cout<<it.first<<" -> { ";
                for(auto i:it.second){
                    cout<<i;
                    if(i!=(*it.second.rbegin()))
                    cout<<" , ";
                }
                cout<<" }\n";
            }
        }

        //make parsing table
        void form_table(){
            bool notLL=false;
            for(auto rule:rules){
                for(auto oneR:rule.second){
                    auto fTemp=findFirstOfString(oneR);
                    bool isEpi=false;
                    for(auto ch:fTemp){
                        if(ch!='@'){
                            auto pp=make_pair(rule.first,ch);
                            auto it=table.find(pp);
                            if(it!=table.end()){
                                if(table[pp]==oneR)continue;
                                notLL=true;
                                break;
                            }
                            table[pp]=oneR;
                        }
                        else isEpi=true;
                    }
                    if(isEpi){
                        for(auto ch:follow[rule.first]){
                            auto pp=make_pair(rule.first,ch);
                            auto it=table.find(pp);
                            if(it!=table.end()){
                                if(table[pp]==oneR)continue;
                                notLL=true;
                                break;
                            }
                            table[pp]=oneR;
                        }
                    }
                    if(notLL)break;
                }
                if(notLL)break;
            }
            if(notLL){
                cout<<"Given Grammar is not LL(1)\n";
                exit(1);
            }


            //print table
            cout<<"\nTable :-\n";
            for(auto rule:table){
                cout<<"Variable :- "<<rule.first.first<<" Terminal :- "<<rule.first.second;
                cout<<" Rule :- "<<rule.second<<"\n";
            }
        }
        // main logic for parsing I/P string under given grammar
        void parsing_String(){
            cout<<"\n\nParsing Start.......\n\n";
            inputString+='$';
            string sstack="";
            sstack="$";
            sstack+=char(start);
            int ip=0,n=inputString.length();
            cout<<"\tSTACK\t\t\tINPUT\t\t\tACTION\n";
            for(ip=0;ip<n;ip++){
                char ch=inputString[ip];
                char sch=sstack.back();
                cout<<"\t"<<sstack<<"\t\t\t"<<inputString.substr(ip)<<"\t\t\t";
                if(ch=='$'){
                    cout<<"Done\n";
                    if(ip!=n-1)  cout<<"\nResult :- Invalid Sentence\n";
                    else  cout<<"\nResult :- Accepted\n";
                    exit(1);
                }
                auto it=terminals.find(ch);
                if(it==terminals.end()){
                    cout<<"Done\n";
                    cout<<"\nResult :- Invalid Sentence\n";
                    exit(1);
                }
                if(ch==sch){
                    cout<<"Reduce\n";
                    sstack.pop_back();//reduce
                }
                else if(!(sch>='A'&&sch<='Z')){
                    cout<<"Done\n";
                    cout<<"\nResult :- Invalid Sentence\n";
                    exit(1);   
                }
                else{
                    cout<<"Shift ,";
                    auto s=table[{sch,ch}];
                    cout<<sch<<"->"<<s<<"\n";
                    sstack.pop_back();
                    sstack.append(s.rbegin(),s.rend());
                    ip--;
                }
            }
            
        }
};

int main()
{
    //generating a new grammar
    Grammar *g=new Grammar();
    g->initialize();
    g->find_First();
    g->find_Follow();
    g->form_table();
    g->parsing_String();
}
