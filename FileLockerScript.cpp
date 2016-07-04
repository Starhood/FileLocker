#include <bits/stdc++.h>
#include <windows.h>
#include <direct.h>
#include <fstream>

using namespace std;


bool fileExist(string Xfile)
{	
		
		DWORD file = GetFileAttributesA(Xfile.c_str());
		if (file==INVALID_FILE_ATTRIBUTES)
			return false;
		else return true;
}

void mkFolder(char primFileName[])
{
	ofstream passW;
	string password;

	char passPath[100];
	sprintf(passPath,"%s%s",primFileName,"/passW.txt");
	
	
	cout<<"\t**********************************************************";
	cout<<"\n\n\t\t\tFile created successfully\n\n";
	cout<<"\t Please set a password to lock and unlock the folder with\n\n";
	cout<<"\t***********************************************************\n\n";
	
	
	cout<<"Password-> ";
	cin>>password;
	
	
	mkdir(primFileName);
	
	passW.open(passPath);
	passW<<password;
	passW.close();
	
	SetFileAttributes(passPath,FILE_ATTRIBUTE_HIDDEN);
}

void lockDir(char pFile[],char sFile[])
{
	ifstream filePass;
	string supPass;
	string password;
	
	cout<<"Please Enter your Password to Lock the Folder\n";
	cout<<"Password-> ";
	cin>>supPass;
	
	char passPath[100];
	sprintf(passPath,"%s%s",pFile,"/passW.txt");
	
	filePass.open(passPath);
	getline(filePass,password);
	filePass.close();
	
	
	while(password!=supPass)
	{
		cout<<"Password incorrect Please try again\n";
		cin>>supPass;
	}
	
	rename( pFile , sFile );
	SetFileAttributes(sFile,FILE_ATTRIBUTE_HIDDEN);	
}

void unlockDir(char pFile[],char sFile[])
{
	ifstream filePass;
	string supPass;
	string password;
	
	cout<<"Please Enter your Password to unLock the Folder\n";
	cout<<"Password-> ";
	cin>>supPass;
	
	char passPath[100];
	sprintf(passPath,"%s%s",sFile,"/passW.txt");
	
	filePass.open(passPath);
	getline(filePass,password);
	filePass.close();
	
	
	while(password!=supPass)
	{
		cout<<"Password incorrect Please try again\n";
		cin>>supPass;
	}
	
	rename( sFile , pFile );
	SetFileAttributes(pFile,FILE_ATTRIBUTE_NORMAL);	
}

int main(){
	
	char primeFile[]="Private";
	char secFile[]="Starhood";
	
	if (fileExist(primeFile))
		lockDir(primeFile,secFile);
	else if (fileExist(secFile))
		unlockDir(primeFile,secFile);
	else mkFolder(primeFile);
		
}
