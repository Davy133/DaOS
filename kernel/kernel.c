//Esse código ta com um problema, ele ta colocando 1 byte a mais do que deveria por algum motivo.

void charoutput(char c,int x, int y){
    short character = (0b00001110<< 8) | c;
    short* video_memory = (short *)0xB8000+(y*80+x);
    *video_memory = character;
}

void printf(char* string, int size){
    int x;
    for(x=0;x!=size;x++){
        charoutput(string[x],x,0);
    }
}

extern void main(){
    char teste[] = "Hello World!";
    int size = (sizeof(teste)/sizeof(teste[0]))-1; //Aqui ta tendo 1 byte a mais do que deveria.
    printf(teste,size);
}
