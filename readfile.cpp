#include<iostream>
#include<string.h>
#include<podofo/podofo.h>
//g++ readfile.cpp -lpodofo -lpthread -lfreetype -lfontconfig -ljpeg -lz -lcrypto

using namespace std;
int main()
{
	int fe=1;
	int se=0;
	int te=0;
	int be=0;
	PoDoFo::PdfMemDocument pdf("fe.pdf");
	cout<<"pg count ="<<pdf.GetPageCount();
	char ch[20];
	string s,*p;
	int i,len,col,loc;
	for (int pn = 0; pn < pdf.GetPageCount(); ++pn) {
		int res=0,line_no=1;
		//scanf("%s",ch);
		cout<<"\n Page no:"<<pn<<endl;
		if(pn==129 ||pn==0)
		{
    		PoDoFo::PdfPage* page = pdf.GetPage(pn);
		PoDoFo::PdfContentsTokenizer tok(page);
    		const char* token = nullptr;
		PoDoFo::PdfVariant var;
		PoDoFo::EPdfContentsType type;
		while (tok.ReadNext(type, token, var)) {
		        switch (type) {
		            case PoDoFo::ePdfContentsType_Keyword:
		                break;
		            case PoDoFo::ePdfContentsType_Variant:
				if(var.IsHexString()||var.IsString()){
					s=((var.GetString()).GetString());
							
							if((line_no==9||line_no==34||line_no==64||line_no==65||line_no==35||line_no==63)&&fe)
							cout<<line_no<<s<<endl;
						loc=0;	
					if((line_no==34||line_no==64||line_no==65||line_no==35||line_no==63)&&fe){//fe
					//if(line_no==34||line_no==64||line_no==65||line_no==35||line_no==63){//se
					//if(line_no==40||line_no==74||line_no==75||line_no==41||line_no==73){//te
						col=0;
						len=s.length();
						
						for (i = 0 ; i < len; i++){
					  		if(s[i]==':')
								col++;
							if(col==2){
								loc=i;
								break;
							}
						}
					}
					if(loc!=0){
						//was found
						//cout<<s[loc]<<s[loc+1]<<s[loc+2]<<endl;
						//cout<<s.substr(loc+1,len)<<"\n";
						stringstream geek(s.substr(loc+1,len)); 
						int x = 0; 
						geek >> x; 
						cout<<x<<endl;
						if(x>=25)
							cout<<"\033[1;4;32mPASS!!"<<endl;
						else
							cout<<"\033[1;4;31mFAIL!!"<<endl;
						cout<<"\033[0m";
						res++;
					}
				line_no++;
				}
		                break;
		            default:
		                break;
		        }
		}
		}
		/*
		if(res!=2){
		cout<<"pgno="<<pn<<endl;
			cout<<"\033[1;4;31m-------------------------------------------------"<<endl;
			cout<<"\033[0m";
			break;
		}else{
			cout<<"\033[1;4;32m-------------------------------------------------"<<endl;
			cout<<"\033[0m";
		}*/
	}
}
