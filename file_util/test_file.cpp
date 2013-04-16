#include <iostream>

using namespace std;

struct Student
{
	char name[20];
	long math;
	long eng;	
	long total;
};

int main()
{
	FILE *fp;
	Student bb;
	if((fp = fopen("test.txt","w+")) == NULL)
	{
		cout << "error in open file" << endl;
	}
	cin >> bb.name >> bb.math >> bb.eng >> bb.total;
//	fseek(fp,10*sizeof(st),0);
	fwrite(&bb,sizeof(bb),2,fp);
	fseek(fp,0,SEEK_SET);
	fread(&bb,sizeof(bb),1,fp);
	cout << bb.name << bb.math << bb.eng << bb.total << endl;

	fclose(fp);
	
	system("pause");
	return 0;
}
