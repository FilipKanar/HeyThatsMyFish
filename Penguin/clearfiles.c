#include <stdio.h>

int main(){
	FILE *fp;
	fp = fopen ("player.txt","w");
	fclose(fp);
	fp = fopen ("idle.txt","w");
	fclose(fp);
	fp = fopen ("score.txt","w");
	fclose(fp);
	fp = fopen ("savedScores.txt","w");
	fclose(fp);
}
