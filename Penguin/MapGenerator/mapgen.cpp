#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **playground;

void create_playground(int height, int width,int players,int penguins){
	srand(time(NULL));
	int one_on_playboard;
	do{
	one_on_playboard=0;
	playground = (int**)malloc(height*sizeof (int*));
	int i = 0;
	for(i; i < height; i ++)
	{
		playground[i] = (int*)malloc(width*sizeof(int));
		int j = 0;
		for(j; j < width; j ++)
		{
			int rando = rand() %3 +1;
			playground[i][j]= rando;
			if(rando == 1){
				one_on_playboard++;
			}
			printf("[%d,%d]=%d  ",i,j,playground[i][j]);
		}
		printf("\n");
	}
	}while (one_on_playboard<players*penguins);
}

void save_into_file(int height, int width){
	int i,j;
	printf("save_into_output\n");
	FILE *file;
	file = fopen("randgenmap.txt", "w");
	if (file) {
		fprintf(file, "%d,%d\n", height,width);
		for(i=0;i<height;i++){
			for(j=0;j<width;j++){
				if(i%2 == 0){
					if(j != width-1){
						fprintf(file, "%d ", playground[i][j]);
					} else {
						fprintf(file, "%d", playground[i][j]);
					}
					
				} else {
					fprintf(file, " %d", playground[i][j]);
				}
			}
			fprintf(file, "\n");
		}
		printf("\n");
	fprintf(file,"Programs and their score:");
	}
	fclose(file);
}

int main(){
	int players_ammount, penguins_ammount, height, width;
	printf("Enter ammount of players: \n");
	scanf("%d",&players_ammount);
	printf("Enter ammount of penguins per player: \n");
	scanf("%d",&penguins_ammount);
	printf("Enter height of board: \n");
	scanf("%d",&height);
	printf("Enter width of board: \n");
	scanf("%d",&width);
	create_playground(height,width,players_ammount,penguins_ammount);
	save_into_file(height,width);
}
