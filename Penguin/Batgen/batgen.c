#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int i,j,players_ammount, penguins_ammount, height, width;
	char **names,temp[30];
	printf("Enter ammount of players: \n");
	scanf("%d",&players_ammount);
	printf("Enter ammount of penguins per player: \n");
	scanf("%d",&penguins_ammount);
	printf("Enter height of board: \n");
	scanf("%d",&height);
	printf("Enter width of board: \n");
	scanf("%d",&width);
	names = (char**)malloc(players_ammount*sizeof (char*));
	for(i=0;i<players_ammount;i++){
		printf("Enter player %d name: (with .exe/.out)",i+1);
		scanf("%s",&temp);
		//printf("%d, %s\n",strlen(temp),temp);
		names[i] = (char*)malloc((strlen(temp)+1)*sizeof(char));
		strcpy(names[i],temp);
		//printf("%d, %s\n",strlen(names[i]),names[i]);
	}
	int cont=0;
	FILE *fp;
	fp = fopen("run.bat","w");
	fprintf(fp,"clearfiles.exe\n");
	for(i=0;i<penguins_ammount;i++){
		for(j=0;j<players_ammount;j++){
			fprintf(fp,"%s phase=placement penguins=%d board%d.txt board%d.txt\n",names[j],penguins_ammount,cont,cont+1);
			cont++;
		}
	}
	for(i=0;i<((height*width)/players_ammount);i++){
		for(j=0;j<players_ammount;j++){
			fprintf(fp,"%s phase=movement board%d.txt board%d.txt\n",names[j],cont,cont+1);
			cont++;
		}

		
	}
	fclose(fp);
	
	return 0;
}
