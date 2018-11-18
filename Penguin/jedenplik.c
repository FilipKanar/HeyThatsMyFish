#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//player1.out phase=placement penguins=2 board0.txt board1.txt 
int ammount_of_penguins;
char *input,*output;
int **tab;


int phase_checker(int argc,char *argv[]){ //returns:  0- error, 1 - placement, 2 - movement
	int phase_checker = 0,i; 
	char phase[] = "phase=";
	for(i=1; i<argc;i++){
   		if(strstr(argv[i], phase) != NULL){
   			//printf("Phase: ");
   			if(strstr(argv[i], "movement") != NULL){
   				//printf("movement\n");
   				phase_checker=2;
			   } else {
			   	if(strstr(argv[i], "placement") != NULL){
			   		//printf("placement\n");
			   		phase_checker=1;
				   }else {
				   	//printf("Phase Error\n");
				   }
			   }
			   //printf("Phase: %d\n",phase_checker);
		   }
	}
	return phase_checker;
}
int penguins_per_player(int argc,char *argv[]){
 	char penguins[] = "penguins=";
	int penguins_ammount,i;
	for(i=1; i<argc;i++){
		if(strstr(argv[i], penguins) != NULL){
			penguins_ammount=argv[i][9]-'0';
			//printf("Penguins : %d\n",penguins_ammount);
		}
	}
	return penguins_ammount;
}
void get_input_and_output_filename(int argc,char *argv[]){ //saves input and output file names in arrays input and output
   char txt[] = ".txt";
   int i=1,j=0; 
   while(strstr(argv[i], txt) == NULL){
   	i++;
   }
   input = (char*) malloc (strlen(argv[i])+1);
   output = (char*) malloc (strlen(argv[i+1])+1);
   for(j=0;j<strlen(argv[i]);j++){
   		input[j] = argv[i][j];
   }
   input[strlen(argv[i])]='\0';
   i++; 
   printf("i = %d ,%s\n",i,argv[i]);
   for(j=0;j<strlen(argv[i]);j++){
   		output[j] = argv[i][j];
   }
   output[strlen(argv[i])]='\0';
}
int return_height(){ //Blad z nazwa naprawic ale chwilowo na tym pliku sie bawic
	//printf("Size : %d %s\n", strlen(input), input);
	int height,width;
	char board_size_char[4];
	int temp;
	FILE *file;
	file = fopen(input, "r");
	if (file) {
    	fscanf(file,"%d,%d",&height,&width);
    	//printf("%s\n", board_size_char);
    	//temp= board_size_char[2]-'0';
    	//printf("Return height: %d\n", height);
    	fclose(file);
    	return height;
	}
	return 0;		
}
int return_width(){ // same
	int height,width;
	char board_size_char[4];
	int temp;
	FILE *file;
	file = fopen(input, "r");
	if (file) {
    	fscanf(file,"%d,%d",&height,&width );
    	//printf("%s\n", board_size_char);
    	//temp= board_size_char[2]-'0';
    	//printf("Return width: %d\n", width);
    	fclose(file);
    	return width;
	}
	return 0;	
}
void create_tab_and_get_values_from_file(){
	FILE *file;
	FILE *secondfile;
	int height = return_height();
	int width = return_width();
	int x=0;
	tab = (int**)malloc(height*sizeof (int*));
	int i=0;
	for(i; i < height; i ++)
	{
		tab[i] = (int*)malloc(width*sizeof(int));
	}
	char single_line_char[150];
	file = fopen(input, "r");
	int contr=0;
	while(!feof(file)){
		int y=0;
		fgets(single_line_char,150,file);
		if(contr==0){
		//printf("contr =0 \t\t%s",single_line_char);
		contr++;
		continue;
		}
		if(contr<=height){
			//printf("contr <= height \t%s",single_line_char);
			int i;
			for(i=0;i<strlen(single_line_char)-1;i++){
				if(single_line_char[i]==' ' || single_line_char[i]=='\n'){
					continue;
				}else{
					if(single_line_char[i+1]!=' ' && single_line_char[i+1]!='\n' ){
						int player_number=0;
						while(single_line_char[i] != ' ' && single_line_char[i]!='\n'){
							player_number=(10*player_number)+single_line_char[i]-'0';
							//printf("player_number=%d\n",player_number);
							i++;
						}
						tab[x][y]=player_number;
					} else {
					tab[x][y]=single_line_char[i]-'0';
					}
					y++;
				}
			}
			x++;
		}
		if(contr==height+1){
			secondfile = fopen("savedScores.txt", "w"); //tworzy plik gdy nie istnieje i zapisuje do niego pierwsza linijke wynikow <napisz Programs and their score>
			fprintf(secondfile,single_line_char);
			fclose(secondfile);
		}
		if(contr>height+1){
			secondfile = fopen("savedScores.txt", "a");//dopisuje wyniki az do ostatniego
			fprintf(secondfile,single_line_char);
			fclose(secondfile);
		}
			
		
		contr++;		
	}
	fclose(file);
}
void print_playground(){
	int i = 0,height = return_height(), width = return_width();
	for (i; i < height; ++i, printf("\n") )
		{
			if(i%2==1) printf("\t");

			int j = 0;
			 for ( j; j < width; ++j)
			 {
					 printf("%d[%d,%d]\t\t",tab[i][j],i,j);

			 }
		}

}
void print_table(){
	int i,j;
	for(i=0;i<return_height();i++){
		for(j=0;j<return_width();j++){
			printf("%d ",tab[i][j]);
		}
		printf("\n");
	}
}
void find_player_number_and_save_to_file(){
	int i,j,contr=4;
	for(i=0;i<return_height();i++){
		for(j=0;j<return_width();j++){
			if(contr <= tab[i][j]){
				contr = tab[i][j]+1;
			}
		}
	}
	printf("contr: %d\n",contr);
	FILE *file;
	file = fopen("player.txt", "w");
	if (file) {
		fprintf(file, "%d",contr);
	}
	fclose(file);
	file = fopen("idle.txt", "w");
	fclose(file);
}
int check_if_file_with_player_ID_is_empty(){ // 0 empty, 1 player number
	FILE *fx;
	int size;
	fx = fopen("player.txt", "r");
	fseek (fx, 0, SEEK_END);
    size = ftell(fx);
	fclose(fx);
    if (0 == size) {
        return 0;
    } else{
    	return 1;
	}
}
int check_if_file_idle_is_empty(){ // 0 empty, 1 player number
	FILE *fx;
	int size;
	fx = fopen("idle.txt", "r");
	fseek (fx, 0, SEEK_END);
    size = ftell(fx);
	fclose(fx);
    if (0 == size) {
        return 0;
    } else{
    	return 1;
	}
}
int get_player_ID_from_file(){
	char player_number_check[5];
	int i,player_number=0;
	FILE *file;
	file = fopen("player.txt", "r");
	if (file) {
		fgets(player_number_check, 5,file);
	}
	fclose(file);
	i=0;
	while(player_number_check[i] >=48 && player_number_check[i] <= 57){
		player_number= player_number*10+player_number_check[i]-'0';
		i++;
	}
	return player_number;
}
int change_x_according_to_direction(int check_x,int direction){ //0 right, 1 left, 2 down-right, 3 down-left, 4 up-right, 5 up-left
	if(check_x%2==0){
		switch(direction){
			case 0: //right
				//check_y++;
				break;
			case 1: //left
				//check_y--;
				break;
			case 2: //down-right
				check_x++;
				break;
			case 3: //down-left
				check_x++;
				//check_y--;
				break;
			case 4: //up-right
				check_x--;
				break;
			case 5: //up-left
				check_x--;
				//check_y--;		
				break;
			default:
				printf("\n0-5 dude !\n");
		}
	} else{
		switch(direction){
			case 0: //right
				//check_y++;						
				break;
			case 1: //left
				//check_y--;						
				break;
			case 2: //down-right
				check_x++;
				//check_y++;					
				break;
			case 3: //down-left
				check_x++;					
				break;
			case 4: //up-right
				check_x--;
				//check_y++;					
				break;
			case 5: //up-left
				check_x--;
				break;
			default:
				printf("\n0-5 dude !\n");
		}
	}
	return check_x;
}
int change_y_according_to_direction(int check_x,int check_y,int direction){
	if(check_x%2==0){
		switch(direction){
			case 0: //right
				check_y++;
				break;
			case 1: //left
				check_y--;
				break;
			case 2: //down-right
				//check_x++;
				break;
			case 3: //down-left
				//check_x++;
				check_y--;
				break;
			case 4: //up-right
				//check_x--;
				break;
			case 5: //up-left
				//check_x--;
				check_y--;		
				break;
			default:
				printf("\n0-5 dude !\n");
		}
	} else{
		switch(direction){
			case 0: //right
				check_y++;						
				break;
			case 1: //left
				check_y--;						
				break;
			case 2: //down-right
				//check_x++;
				check_y++;					
				break;
			case 3: //down-left
				//check_x++;					
				break;
			case 4: //up-right
				//check_x--;
				check_y++;					
				break;
			case 5: //up-left
				//check_x--;
				break;
			default:
				printf("\n0-5 dude !\n");
		}
	}
	return check_y;
}
int check_ammount_of_jumps_in_direction(int direction,int x, int y, int save){ //save 0 - nie, 1 - tak, Zwraca iloœæ skoków które gracz mo¿e wykonaæ w dan¹ stronê i zapisuje mo¿liwe pozycje do pliku.
	//printf("check_ammount_of_jumps_in_direction\n");
	int i,j,jumps=0, height = return_height(), width = return_width();
	FILE *file;
	int temp_i=x,temp_j=y;	
	do{
		if(change_x_according_to_direction(temp_i,direction) <0 || change_x_according_to_direction(temp_i,direction) >= height ){
		//	printf("Returns 0 x: %d\n",change_x_according_to_direction(temp_i,direction));
			return jumps;
		}		
		if(change_y_according_to_direction(temp_i,temp_j,direction) <0 || change_y_according_to_direction(temp_i,temp_j,direction) >= width ){
			//printf("Returns 0 y: %d\n",change_y_according_to_direction(temp_i,temp_j,direction));
			return jumps;
		}
		if(tab[change_x_according_to_direction(temp_i,direction)][change_y_according_to_direction(temp_i,temp_j,direction)] > 3 
		|| tab[change_x_according_to_direction(temp_i,direction)][change_y_according_to_direction(temp_i,temp_j,direction)] <=0){
			//printf("Returns 0 tab[%d,%d]=%d\n",change_x_according_to_direction(temp_i,direction),
				//change_y_according_to_direction(temp_i,temp_j,direction),
				//tab[change_x_according_to_direction(temp_i,direction)][change_y_according_to_direction(temp_i,temp_j,direction)]);
			return jumps;
		}
		temp_j = change_y_according_to_direction(temp_i,temp_j,direction); // MEGA wa¿na kolejnoœæ
		temp_i = change_x_according_to_direction(temp_i,direction);
		jumps++;
		//printf("jumps++ %d %d %d\n",direction,temp_i,temp_j);
		if(save==1){
			file = fopen("possibleFields.txt", "a");
			fprintf(file,"x=%d y=%d\n",temp_i,temp_j);
			fclose(file);
		}
		//printf("\t Wykonal jumps: [%d, %d] = %d jumps: %d\n",temp_i,temp_j,tab[temp_i][temp_j],jumps);
	}while(tab[temp_i][temp_j] > 0 && tab[temp_i][temp_j] < 4 && temp_i < height && temp_i >= 0 && temp_j < width && temp_j >= 0);
	return jumps;;
}
int return_points_for_fishes(int x,int y){
	int points=0;
	if(tab[x][y]==1){
		return 1;
	}
	if(tab[x][y]==2){
		return 3;
	}
	if(tab[x][y]==3){
		return 6;
	}
	return points;
}
int return_points_for_directions(int x, int y){
//printf("return_points_for_directions\n");
	int temp=0,i;
	for(i=0;i<6;i++){ // sprawdzenie w ile stron mo¿ê siê ruszyæ
		if(check_ammount_of_jumps_in_direction(i,x,y,0)>0)
		temp++;
	}
	if(temp == 0){
		return 0;
	}
	if(temp == 1){
		return 1;
	}
	if(temp == 2){
		return 2;
	}
	if(temp == 3){
		return 3;
	}
	if(temp == 4){
		return 4;
	}
	if(temp == 5){
		return 5;
	}
	if(temp == 6){
		return 6;
	}
	return 0;
}
int return_points_for_fishes_in_next_jump(int x, int y){
//printf("return_points_for_fishes_in_next_jump\n");
	int i,j, possible_jumps,temp_x,temp_y,points=0;
	int points_1 =1;
	int points_2 =2;
	int points_3 =3;
	for(i =0;i<6;i++){
		possible_jumps = check_ammount_of_jumps_in_direction(i,x,y,0);
		//printf("Possible jumps in dir %d : %d\n",i,possible_jumps);
		temp_x =x;
		temp_y =y;
		for(j=0; j < possible_jumps; j++){	
			//printf("%d  tab[%d][%d] = %d\n",i,temp_x,temp_y, tab[temp_x][temp_y]);	
			temp_y = change_y_according_to_direction(temp_x,temp_y, i);
			temp_x = change_x_according_to_direction(temp_x, i);
			if(tab[temp_x][temp_y] ==1){
				if(points_1 >= points){
					//printf("%d Points 1 : tab[%d][%d] = %d\n",i,temp_x,temp_y, tab[temp_x][temp_y]);
					points = points_1;
				}
			}
			if(tab[temp_x][temp_y] == 2){
				if(points_2 >= points){
					//printf("%d Points 2 : tab[%d][%d] = %d\n",i,temp_x,temp_y, tab[temp_x][temp_y]);
					points = points_2;
				}
			}
			if(tab[temp_x][temp_y] == 3){
				if(points_3 >= points){	
					//printf("%d Points 3 : tab[%d][%d] = %d\n",i,temp_x,temp_y, tab[temp_x][temp_y]);
					points = points_3;
				}
			}
		}
	}
	return points;
}
int return_points_for_blocking_another_player(int x, int y){ //100 if yes
//printf("return_points_for_blocking_another_player\n");
	int j,points=0, height = return_height(), width = return_width(),player_number=get_player_ID_from_file();
		for(j=0;j<6;j++){
			if(change_x_according_to_direction(x, j)>=0
			&& change_x_according_to_direction(x, j) < height
			&& change_y_according_to_direction(x,y, j) >= 0
			&& change_y_according_to_direction(x,y, j) < width
			&& tab[change_x_according_to_direction(x, j)][change_y_according_to_direction(x,y, j)]>3) {
				if(tab[change_x_according_to_direction(x, j)][change_y_according_to_direction(x,y, j)] != player_number
					&& return_points_for_directions(change_x_according_to_direction(x, j),change_y_according_to_direction(x,y, j))==1){
					printf("Player to block: [%d,%d]\n",change_x_according_to_direction(x, j),change_y_according_to_direction(x,y, j));
					points = 100;
				}
			}
		}
	return points;
}
int return_points_for_possible_getting_blocked(int x, int y){ // -200 if yes
//printf("return_points_for_possible_getting_blocked %d %d\n",x,y);
	int i,j,possible_jumps,points=0,check_directions,temp_x=x,temp_y=y, 
	height = return_height(), width = return_width(),
	player_number=get_player_ID_from_file();
	for(i =0;i<6;i++){
		
		possible_jumps = check_ammount_of_jumps_in_direction(i,x,y,0);
		for(j=0;j<=possible_jumps;j++){
			if(change_y_according_to_direction(x,y,i)  <0 
		|| change_y_according_to_direction(x,y,i) >=width
		|| change_x_according_to_direction(x,i) <0
		|| change_x_according_to_direction(x,i) >= height){
			continue;
		}
			y = change_y_according_to_direction(x,y,i);
			x = change_x_according_to_direction(x,i);
			if(x>=0 && y >=0 && x < height && y <width)
			if(j == possible_jumps){
				check_directions = return_points_for_directions(temp_x,temp_y);
			}
		}
		if(x>=0 && x < height && y >=0 && y <width)
			if(tab[x][y] > 3 || tab[x][y] ==0){
			if(tab[x][y] != player_number && check_directions <2 ){
				printf("%d %d %d\n",x,y,check_directions);
				points = -200;
			}
		}
	}
	return points;
}
int count_points_for_field(int x,int y){ //Returns points for single field
	int total_points=0,a,b,c,d,e;	
	
	a=return_points_for_fishes(x,y);
	//printf("Points for fishes: %d\n", a);
	b=return_points_for_directions(x,y);
	//printf("Points for directions: %d\n", b);
	c=return_points_for_fishes_in_next_jump(x,y);
	//printf("Points for fishes in next jump: %d\n", c);
	d=return_points_for_blocking_another_player(x,y);
	//printf("Points for blocking_another_player: %d\n", d);
	e=return_points_for_possible_getting_blocked(x,y);	
	//printf("Points for getting_blocked: %d\n", e);
	//printf("[%d][%d] = %d\n",x,y,a+b+c+d+e);
	return a+b+c+d+e;
}
void fill_table_for_placing_pengus(int temp_tab[4],int x, int y, int score){
	//printf("fill_table_for_placing_pengus\n");
	temp_tab[0] = x;
	temp_tab[1] = y;
	temp_tab[2] = score;
}
void save_score_in_file(int score){
	FILE *file;
		file = fopen("score.txt", "w");
			fprintf(file, "%d\n", score);
		fclose(file);
}
int get_points_from_file(){
	int points;
	FILE *file;
		file = fopen("score.txt", "r");
			fscanf(file, "%d\n", &points);
		fclose(file);
		printf("POINTS FROM FILE: %d\n",points);
		return points;
}
void save_into_output(int fishes){
	printf("save_into_output\n");
	int c,x=0,i,j, height = return_height(), width = return_width(),points=get_points_from_file();
	FILE *file;
	FILE *secondfile;
	printf("Output: %s",output);
	file = fopen(output, "w");
	if (file) {
		fprintf(file, "%d,%d\n", height,width);
		for(i=0;i<return_height();i++){
			for(j=0;j<return_width();j++){
				if(i%2 == 0){
					if(j != width-1){
						fprintf(file, "%d ", tab[i][j]);
					} else {
						fprintf(file, "%d", tab[i][j]);
					}
					
				} else {
					fprintf(file, " %d", tab[i][j]);
				}
			}
			fprintf(file, "\n");
		}
		printf("\n");
	char board_size_char[50];
	secondfile = fopen("savedScores.txt", "r");
	while(!feof(secondfile)){
		int y=0;
		fgets(board_size_char,50,secondfile);
		/*if(board_size_char[7] -'0'+3 == get_player_ID_from_file()){
			i=1;
			while(board_size_char[i]!=' '){
				i++;
			}
			i++;
			while(board_size_char[i] <58 && board_size_char[i] >47){
				points = 10*points+board_size_char[i]-'0';
				//printf("Points %d\ti=%d\t%d\n",points,i,board_size_char[i]);
				i++;
			}
		}*/
		fprintf(file,"%s", board_size_char);
	}
	fprintf(file,"\nprogram%d.exe %d",get_player_ID_from_file()-3,points+fishes);
	printf("P: %d\tF: %d\n",points,fishes);
	save_score_in_file(points+fishes);
	fclose(secondfile);
	}
	fclose(file);
}
int place_penguin(int player_number){  
//printf("Place Penguin\n");
	int i,j,score,one_round_score=0;
	int place_temp[4];
	place_temp[2]=-10000;
	place_temp[2]=0;
	for(i=0;i<return_height();i++){
		for(j=0;j<return_width();j++){
			score =0;
			if(tab[i][j] == 1){
				score = count_points_for_field(i,j);
				if(score > place_temp[2]){
				fill_table_for_placing_pengus(place_temp,i,j,score);
				}
			}
		}
	}
	one_round_score = tab[place_temp[0]][place_temp[1]]; // zapisuje punkty z wybranego pola
	tab[place_temp[0]][place_temp[1]]=player_number; //zmienia pole na nasz numer gracza
	printf("WYBRANE POLE - [%d][%d] = %d\n",place_temp[0],place_temp[1],tab[place_temp[0]][place_temp[1]]);
	return one_round_score;
}
void placement(){
	int fishes;
	if (check_if_file_with_player_ID_is_empty() == 0){
		find_player_number_and_save_to_file();
		FILE *file;
		file = fopen("score.txt", "w");
		fprintf(file,"%d",0);
		fclose(file);
		file = fopen("idle.txt", "w");
		fclose(file);
	}
		int player_number=get_player_ID_from_file();
		fishes = place_penguin(player_number);
		save_into_output(fishes);
}
void movement(){
	int i,j,k,l,jumps,x,y,points,place_temp[4],height = return_height(), width = return_width(),one_round_score,temp_x,temp_y;
	place_temp[2]=-20000;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(tab[i][j]==get_player_ID_from_file()){
				for(k=0;k<6;k++){
					y=j;
					x=i;
					jumps=check_ammount_of_jumps_in_direction(k,i,j,0);
					for(l=0;l<jumps; l++){
						y = change_y_according_to_direction(x,y,k);
						x = change_x_according_to_direction(x,k);
						points = count_points_for_field(x,y);
						printf("[%d,%d] = %d \tPoints: %d\n",x,y,tab[x][y],points);
						if(points > place_temp[2]){
							temp_x=i;
							temp_y=j;
							fill_table_for_placing_pengus(place_temp,x,y,points);
						}
					}
					printf("\n");
				}
			}
		}
	}
	one_round_score = tab[place_temp[0]][place_temp[1]];
	tab[place_temp[0]][place_temp[1]]=get_player_ID_from_file();
	printf("WYBRANE POLE - [%d][%d] = %d\n",place_temp[0],place_temp[1],tab[place_temp[0]][place_temp[1]]);
	tab[temp_x][temp_y]=0;
	save_into_output(one_round_score);
}
void idle_function(){
	FILE *file;
	FILE *secondfile;
	int player_number,score;
	if(check_if_file_idle_is_empty()==0){
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		player_number=get_player_ID_from_file();
		score=get_points_from_file();
		file = fopen("idle.txt", "w"); 
		fprintf(file,"%d %d",player_number,score);
		fclose(file);
		file=fopen("player.txt","w");
		fclose(file);
		file=fopen("score.txt","w");
		fclose(file);
	}
	char single_line_char[50];
	file = fopen("idle.txt", "r"); 
	fscanf(file,"%d %d",&player_number,&score);
	printf("player_number: %d\t score: %d\n",player_number,score);
	fclose(file);
	file = fopen(output, "w");
	fclose(file);
	file = fopen(output, "a");
	secondfile = fopen(input, "r");
	while(!feof(secondfile)){
		fgets(single_line_char,50,secondfile); //wczytuje po linijce z input i wpisuje do output
		fprintf(file, "%s",single_line_char);
	}
	fprintf(file,"\nprogram%d.exe %d",player_number-3,score);
	fclose(file);
	fclose(secondfile);	
}
int check_possible_move(){
	int i,j,k,sum=0,height = return_height(), width = return_width();
	char single_line_char[50];
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(tab[i][j]==get_player_ID_from_file()){
				for(k=0;k<6;k++){
					sum+=check_ammount_of_jumps_in_direction(k,i, j, 0);
				}
			}
		}
	}
	return sum;
}
int check_possible_move_idle(){
	int i,j,k,sum=0,height = return_height(), width = return_width();
	int player_ID;
	FILE *fp;
	fp = fopen("idle.txt","r");
	fscanf(fp,"%d",&player_ID);
	fclose(fp);
	char single_line_char[50];
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(tab[i][j]==player_ID){
				for(k=0;k<6;k++){
					sum+=check_ammount_of_jumps_in_direction(k,i, j, 0);
				}
			}
		}
	}
	return sum;
}
void turbo_idle_jp2gmd(){
	FILE *file;
	FILE *secondfile;
	int player_number,score;
	char single_line_char[50];
	file = fopen("idle.txt", "r"); 
	fscanf(file,"%d %d",&player_number,&score);
	printf("player_number: %d\t score: %d\n",player_number,score);
	fclose(file);
	file = fopen(output, "w");
	fclose(file);
	file = fopen(output, "a");
	secondfile = fopen(input, "r");
	while(!feof(secondfile)){
		fgets(single_line_char,50,secondfile); //wczytuje po linijce z input i wpisuje do output
		fprintf(file, "%s",single_line_char);
	}
	fprintf(file,"\nprogram%d.exe %d",player_number-3,score);
	fclose(file);
	fclose(secondfile);	
}

int main(int argc,char *argv[]){	
	get_input_and_output_filename(argc,argv);
	create_tab_and_get_values_from_file();
	if(phase_checker(argc,argv) == 1){
		printf("Placement: \n");
		ammount_of_penguins = penguins_per_player(argc,argv); 
		placement();
	}
	if(phase_checker(argc,argv) == 2){
		printf("Movement:\n");
		if(check_if_file_with_player_ID_is_empty() == 1){
			if(check_possible_move()>0){
				printf("possible_move>0\n");
				movement();
			} else {
				if(check_possible_move()==0){
					printf("possible_move==0\n");
					idle_function();
				}
			}
		}else{
			if(check_possible_move_idle()==0){
					printf("possible_move==0 was idle\n");
					turbo_idle_jp2gmd();
				}
		}
	}

	return 0;
}
