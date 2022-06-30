#include "bmp_header.h"
#include "cJSON.h"
#include "cJSON.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* task1(char* input){
    //Scriu numele fisierului, il creez, si il deschid pentru a-l scrie
    char* fileName = malloc(30);
    strcpy(fileName, "output_task1_board");
    for(int i = 0; i < strlen(input); i++){
        if(input[i] == 'b'){
            strncat(fileName, (input + i + 5), 2);
        }
    }
    strcat(fileName, ".bmp");
    FILE* outputFile; 
    if (( outputFile = fopen(fileName, "wb")) == NULL){
        fprintf(stderr, "Can't open %s\n", fileName);
        return fileName;
    }
    FILE* inputFile; 
    if (( inputFile = fopen(input, "r")) == NULL){
        fprintf(stderr, "Can't open %s\n" ,input);
        return fileName;
    }
    //Citim fisierul de input si ii dam parse
    fseek(inputFile, 0, SEEK_END);
    long fsize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    char *stringJson = malloc(fsize + 1);
    fread(stringJson, 1, fsize, inputFile);
    stringJson[fsize] = '\0';
    fclose(inputFile);

    cJSON *json = cJSON_Parse(stringJson);
    //scriem headerele
    cJSON *file_header = cJSON_GetObjectItem(json, "file_header");
 
    cJSON *offset = cJSON_GetObjectItem(file_header, "offset");
    cJSON *signature = cJSON_GetObjectItem(file_header, "signature");
    cJSON *reserved = cJSON_GetObjectItem(file_header, "reserved");
    cJSON *file_size = cJSON_GetObjectItem(file_header, "file_size");

    cJSON *info_header = cJSON_GetObjectItem(json, "info_header");

    cJSON *colors_used = cJSON_GetObjectItem(info_header, "colors_used");
    cJSON *size = cJSON_GetObjectItem(info_header, "size");
    cJSON *colors_important = cJSON_GetObjectItem(info_header, "colors_important");
    cJSON *image_size = cJSON_GetObjectItem(info_header, "image_size");
    cJSON *y_pixels_per_meter = cJSON_GetObjectItem(info_header, "y_pixels_per_meter");
    cJSON *x_pixels_per_meter = cJSON_GetObjectItem(info_header, "x_pixels_per_meter");
    cJSON *width = cJSON_GetObjectItem(info_header, "width");
    cJSON *planes = cJSON_GetObjectItem(info_header, "planes");
    cJSON *bit_count = cJSON_GetObjectItem(info_header, "bit_count");
    cJSON *compression = cJSON_GetObjectItem(info_header, "compression");
    cJSON *height = cJSON_GetObjectItem(info_header, "height");

    fwrite(&signature->valuestring[0], sizeof(char), 1, outputFile);
    fwrite(&signature->valuestring[1], sizeof(char), 1, outputFile);
    int   fileSize = file_size->valueint;
    fwrite(&fileSize, 4, 1, outputFile);
    int   reserved1 = reserved->valueint;
    int   reserved2 = reserved->valueint;
    fwrite(&reserved1, 2, 1, outputFile);
    fwrite(&reserved2, 2, 1, outputFile);
    int   offsetVal = offset->valueint;
    fwrite(&offsetVal, 4, 1, outputFile);
    int   sizeVal = size->valueint;
    fwrite(&sizeVal, 4, 1, outputFile);
    int   widthVal = width->valueint;
    int   heightVal = height->valueint;
    fwrite(&widthVal, 4, 1, outputFile);
    fwrite(&heightVal, 4, 1, outputFile);
    int   planesVal = planes->valueint;
    fwrite(&planesVal, 2, 1, outputFile);
    int   bitCount = bit_count->valueint;
    fwrite(&bitCount, 2, 1, outputFile);
    int   compressionVal = compression->valueint;
    fwrite(&compressionVal, 4, 1, outputFile);
    int   imageSize = image_size->valueint;
    fwrite(&imageSize, 4, 1, outputFile);
    int   xPixels = x_pixels_per_meter->valueint;
    int   yPixels = y_pixels_per_meter->valueint;
    fwrite(&xPixels, 4, 1, outputFile);
    fwrite(&yPixels, 4, 1, outputFile);
    int   colorsUsed = colors_used->valueint;
    int   colorsImp = colors_important->valueint;
    fwrite(&colorsUsed, 4, 1, outputFile);
    fwrite(&colorsImp, 4, 1, outputFile);

    cJSON *bitmapJson = cJSON_GetObjectItem(json, "bitmap");
    //scriem in bitmap-ul
    int n = 0; 
    for(int i = 72; i >= 0; i--){
        for(int j = 0; j < 219; j++){
            if(n == 218){                                               //73*3 (-1)
                fwrite(&reserved1, 2, 1, outputFile);
                n = 0;
            }else{
                cJSON* item = cJSON_GetArrayItem(bitmapJson, (i*219)+j);
                fwrite(&item->valueint,1,1,outputFile);
                n++;
            }
        }
    }
    cJSON_Delete(json);
    fclose(outputFile);
    free(stringJson);
    return fileName;
}

char* task2(char* inputName){
    char* outputName = malloc(30);
    strcpy(outputName, "output_task2_board");
    for(int i = 0; i < strlen(inputName); i++){
        if(inputName[i] == 'b'){
            strncat(outputName, (inputName + i + 5), 2);
        }
    }
    strcat(outputName, ".bmp");

    FILE* outputFile; 
    if (( outputFile = fopen(outputName, "wb")) == NULL){
        fprintf(stderr, "Can't open %s\n", outputName);
        return outputName;
    }
    FILE* inputFile; 
    if (( inputFile = fopen(inputName, "rb")) == NULL){
        fprintf(stderr, "Can't openbbb %s\n" ,inputName);
        return inputName;
    }

    size_t n;
    char* buff = malloc(50);
    n = fread(buff,1,54,inputFile);
    fwrite(buff,1,n,outputFile);
    int row = 1;
    int numCols[9] = {3, 11, 19, 27, 35, 43, 51 ,59, 67};
    int normCols[28] = {1, 2, 8, 9, 10, 16, 17, 18, 25, 25, 26, 32, 33, 34, 40, 41, 42, 48, 49, 50, 56, 57, 58, 64, 65, 66, 72, 73};
    //scriem pixelii rand cu rand
    while (row <= 73) {
        for(int col = 1; col <= 73; col++){
            for(int i = 0; i < 10; i++){
                if(col == numCols[i]){
                    n = fread(buff,1,15,inputFile);
                    fwrite(buff + 12, 1, 3, outputFile);
                    fwrite(buff + 9, 1, 3, outputFile);
                    fwrite(buff + 6, 1, 3, outputFile);
                    fwrite(buff + 3, 1, 3, outputFile);
                    fwrite(buff, 1, 3, outputFile);
                }
            }
            for(int i = 0; i < 29; i++){
                if(col == normCols[i]){  
                    n = fread(buff,1,3,inputFile);
                    fwrite( buff, 1, n, outputFile ); 
                }
            }
        }
        n = fread(buff,1,1,inputFile);
        fwrite(buff,1,n,outputFile);
        row++;
    }
    fclose(inputFile);
    fclose(outputFile);
    free(buff);
    return outputName;
}

int readNumber(FILE* file, int row, int col){
    //trecem peste primii 54 de biti de la inceputul fisierului .bmp
    fseek(file, 54, SEEK_SET);
    //ajungem la linia dorita (o "linie" = 8 linii de pixeli)
    //8 linii de piexli * numarul de linii pe care le vrem citite * 73*3
    // + 8 * numarul de linii pe care le vrem citite (1 bit padding) 
    // + 2*73*3 cele doua linii de pixeli pana la numar
    // + 2 bitii padding
    fseek(file,( 8*(9-row)*73*3 + 8*(9-row) + 2*73*3 + 2), SEEK_CUR);
    // 7*3(7 pixeli)* numarul de coloane pe care le vrem citite + 2 pixeli pana la inceputul numarului
    fseek(file, (8*3*(col-1) + 2*3), SEEK_CUR);
    fpos_t ptr;
    fgetpos(file, &ptr);
    //acum avem pozitia de la inceputul numarului (colt stanga-jos)
    char* buff = malloc(3);
    char* buff2 = malloc(3);
    //checking if empty and returning 0
    fseek(file, 12, SEEK_CUR);
    fread(buff,1,3,file);
    fsetpos(file, &ptr);
    fseek(file, (73*3+1),SEEK_CUR);
    fseek(file,3,SEEK_CUR);
    fread(buff2,1,3,file);
    if(strcmp(buff,buff2) == 0){
        free(buff);
        free(buff2);
        return 0;
    }
    //checking if 1,4 or 7
    fsetpos(file, &ptr);
    fread(buff, 1, 3, file);
    fseek(file, 9, SEEK_CUR);
    fread(buff2, 1, 3, file);
    if(strcmp(buff, buff2) != 0){
        fsetpos(file, &ptr);
        fseek(file, (4*73*3 + 4),SEEK_CUR);
        fread(buff, 1, 3, file);
        fread(buff2, 1, 3, file);
        if(strcmp(buff,buff2) != 0){
            free(buff);
            free(buff2);
            return 4;
        } 
        fseek(file, 6,SEEK_CUR);
        fread(buff2, 1, 3, file);
        if(strcmp(buff,buff2) != 0){
            free(buff);
            free(buff2);
            return 1;
        }
        free(buff);
        free(buff2);
        return 7;
    }
    //checking if 6 or 8
    fsetpos(file, &ptr);
    fseek(file, (73*3+1), SEEK_CUR);
    fread(buff, 1, 3, file);
    fseek(file,9,SEEK_CUR);
    fread(buff2, 1, 3, file);
    if(strcmp(buff,buff2) == 0){
        fsetpos(file,&ptr);
        fseek(file, (3*73*3 + 3),SEEK_CUR);
        fread(buff,1,3,file);
        fseek(file,9,SEEK_CUR);
        fread(buff2,1,3,file);
        if(strcmp(buff,buff2) == 0){
            free(buff);
            free(buff2);
            return 8;
        }
        free(buff);
        free(buff2);
        return 6;
    }
    //checking if 9
    fsetpos(file, &ptr);
    fseek(file, (3*73*3 + 3), SEEK_CUR);
    fread(buff,1,3,file);
    fseek(file, 9, SEEK_CUR);
    fread(buff2,1,3,file);
    if(strcmp(buff,buff2) == 0){
        free(buff);
        free(buff2);
        return 9;
    }
    //checking if 2 3 5  
    fsetpos(file, &ptr);
    fseek(file, (73*3 + 1), SEEK_CUR);
    fread(buff,1,3,file);
    fsetpos(file,&ptr);
    fseek(file,(3*73*3 + 3),SEEK_CUR);
    fread(buff2,1,3,file);
    if(strcmp(buff,buff2) == 0){
        free(buff);
        free(buff2);
        return 3;
    }
    fsetpos(file, &ptr);
    fseek(file, (73*3 + 1), SEEK_CUR);
    fread(buff,1,3,file);
    fread(buff2,1,3,file);
    if(strcmp(buff,buff2) == 0){
        free(buff);
        free(buff2);
        return 5;
    }
    free(buff);
    free(buff2);
    return 2;
}

void task3(char* inputName){
    char* outputName = malloc(30);
    strcpy(outputName, inputName);
    outputName[11] = '3';
    outputName[21] = 'j';
    outputName[22] = 's';
    outputName[23] = 'o';
    outputName[24] = 'n';
    FILE* outputFile; 
    if (( outputFile = fopen(outputName, "wt")) == NULL){
        fprintf(stderr, "Can't open %s\n", outputName);
        return;
    }
    FILE* inputFile; 
    if (( inputFile = fopen(inputName, "rb")) == NULL){
        fprintf(stderr, "Can't openbbb %s\n" ,inputName);
        return;
    }
    
    fprintf(outputFile, "{\n");
    fprintf(outputFile, "\t\"input_file\":\t\"%s\",\n", (outputName+13));
    fprintf(outputFile, "\t\"game_state\":\t");

    //verificam fiecare linie
    for(int i = 1; i<=9; i++){  
        for(int j = 1; j<=9; j++){
            for(int k = j+1; k<=9; k++){
                if((readNumber(inputFile, i, j) == readNumber(inputFile, i, k)) | (readNumber(inputFile, i, j) == 0)){
                    fprintf(outputFile, "\"Loss :(\"\n");
                    fprintf(outputFile,"}\n");
                    fclose(inputFile);
                    fclose(outputFile);
                    free(outputName);
                    return;
                }
            }
        }
    }

    //verificam fiecare coloana
    for(int i = 1; i<=9; i++){  
        for(int j = 1; j<=9; j++){
            for(int k = j+1; k<=9; k++){
                if(readNumber(inputFile, j, i) == readNumber(inputFile, k, i)){
                    fprintf(outputFile, "\"Loss :(\"\n");
                    fprintf(outputFile,"}\n");
                    fclose(inputFile);
                    fclose(outputFile);
                    free(outputName);
                    return;
                }
            }
        }
    }

    //verificam fiecare patrat
    int num;
    for(int i = 1; i<=9; i+=3){
        for(int j = 1; j<=9; j+=3){
            for(int k = 0; k<3; k++){
                for(int t = 0; t<3; t++){
                    num = readNumber(inputFile, (i+k), (j+t));
                    for(int m = k; m<3; m++){
                        for(int n = t+1; n<3; n++){
                            if(num == readNumber(inputFile,(i+m),(j+n))){
                                fprintf(outputFile, "\"Loss :(\"\n");
                                fprintf(outputFile,"}\n");
                                fclose(inputFile);
                                fclose(outputFile);
                                free(outputName);
                                return;
                            }
                        }
                    }        
                }
            }
        }
    }
    fprintf(outputFile, "\"Win!\"\n");
    fprintf(outputFile,"}\n");
    fclose(inputFile);
    fclose(outputFile);
    free(outputName);
    return;
}

void writeNumber(FILE* file, int num, int row, int col){
    fseek(file, 54, SEEK_SET);
    fseek(file,( 8*(9-row)*73*3 + 8*(9-row) + 2*73*3 + 2), SEEK_CUR);
    fseek(file, (8*3*(col-1) + 2*3), SEEK_CUR);
    fpos_t ptr;
    fgetpos(file, &ptr);
    char buff[3] = {255,0,255};
    switch (num){
    case 0:
        return;
    case 1:
        for(int i = 0; i < 5; i++){
            fsetpos(file, &ptr);
            fseek(file, 73*3*i + i, SEEK_CUR);
            fseek(file, 12, SEEK_CUR);
            fwrite(buff,1,3,file);
        }
        return;
    case 2:
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3 + 1, SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*2 + 2, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        fsetpos(file, &ptr);
        fseek(file, 73*3*3 + 3, SEEK_CUR);    
        fseek(file,12,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);        
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }          
        return;
    case 3:
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3 + 1, SEEK_CUR);
        fseek(file,12,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*2 + 2, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        fsetpos(file, &ptr);
        fseek(file, 73*3*3 + 3, SEEK_CUR);    
        fseek(file,12,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);        
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        return;                
    case 4:
        for(int i = 0; i < 2; i++){
            fsetpos(file, &ptr);
            fseek(file, 73*3*i + i, SEEK_CUR);
            fseek(file, 12, SEEK_CUR);
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3*2 + 2, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        } 
        fsetpos(file, &ptr);
        fseek(file, 73*3*3 + 3, SEEK_CUR);
        fwrite(buff,1,3,file);    
        fseek(file,9,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);
        fwrite(buff,1,3,file);    
        fseek(file,9,SEEK_CUR);
        fwrite(buff,1,3,file);
        return;
    case 5:
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3 + 1, SEEK_CUR);
        fseek(file,12,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*2 + 2, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        fsetpos(file, &ptr);
        fseek(file, 73*3*3 + 3, SEEK_CUR);    
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);        
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        return;
    case 6:
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3 + 1, SEEK_CUR);
        fwrite(buff,1,3,file);
        fseek(file,9,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*2 + 2, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        fsetpos(file, &ptr);
        fseek(file, 73*3*3 + 3, SEEK_CUR);    
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);        
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        return;
    case 7:
        for(int i = 0; i < 4; i++){
            fsetpos(file, &ptr);
            fseek(file, 73*3*i + i, SEEK_CUR);
            fseek(file, 12, SEEK_CUR);
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        } 
        return;
    case 8:
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3 + 1, SEEK_CUR);
        fwrite(buff,1,3,file);
        fseek(file,9,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*2 + 2, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        fsetpos(file, &ptr);
        fseek(file, 73*3*3 + 3, SEEK_CUR);    
        fwrite(buff,1,3,file);
        fseek(file,9,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);        
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }  
        return;
    case 9:
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }
        fsetpos(file, &ptr);
        fseek(file, 73*3 + 1, SEEK_CUR);
        fseek(file,12,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*2 + 2, SEEK_CUR);
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }    
        fsetpos(file, &ptr);
        fseek(file, 73*3*3 + 3, SEEK_CUR);    
        fwrite(buff,1,3,file);
        fseek(file,9,SEEK_CUR);
        fwrite(buff,1,3,file);
        fsetpos(file, &ptr);
        fseek(file, 73*3*4 + 4, SEEK_CUR);        
        for(int i = 0; i < 5; i++){
            fwrite(buff,1,3,file);
        }  
        return;                                                       
    default:
        return;
    }

}

void task4(char* inputFileName){
    char* fileName = malloc(30);
    strcpy(fileName, "output_task4_board");
    for(int i = 0; i < strlen(inputFileName); i++){
        if(inputFileName[i] == 'b'){
            strncat(fileName, (inputFileName + i + 5), 2);
        }
    }
    strcat(fileName, ".bmp");
    FILE* outputFile; 
    if (( outputFile = fopen(fileName, "wb")) == NULL){
        fprintf(stderr, "Can't open %s\n", fileName);
        return;
    }
    FILE* inputFile; 
    if (( inputFile = fopen(inputFileName, "rb")) == NULL){
        fprintf(stderr, "Can't openbbb %s\n" ,inputFileName);
        return;
    }
    
    // scriem fisierul
    size_t n;
    char* buff = malloc(16115);
    while(feof(inputFile) == 0){
        n = fread(buff,1,16114,inputFile);
        fwrite(buff,1,n,outputFile);
    }
    free(buff);

    // incepem sa completam patratele goale
    // Stim ca suma de pe o linie/coloana trebuie sa fie 45 ((9(9+1))/2)
    int mat[9][9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            mat[i][j] = readNumber(inputFile,i+1,j+1);
        } 
    }
                
    int sum;
    int numI;
    int numJ;
    int count;
    for(int i = 0; i < 9; i++){
        sum = 0;
        numI = 0;
        numJ = 0;
        count = 0;
        for(int j = 0; j < 9; j++){
            if(mat[i][j] == 0){
                numI = i+1;
                numJ = j+1;
                count++;
            }
            sum+=mat[i][j];
        }
        if(count == 1){
            writeNumber(outputFile,(45-sum),numI,numJ);
            mat[numI][numJ] = (45-sum);
        }
    }

    for(int i = 0; i < 9; i++){
        sum = 0;
        numI = 0;
        numJ = 0;
        count = 0;
        for(int j = 0; j < 9; j++){
            if(mat[j][i] == 0){
                numI = i+1;
                numJ = j+1;
                count++;
            }
            sum+=mat[j][i];
        }
        if(count == 1){
            writeNumber(outputFile,(45-sum),numJ,numI);
            mat[numJ][numI] = (45-sum);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    free(fileName);
}

int main(int argc, char* argv[]){
    if(strcmp(argv[2], "123") == 0){
        char* fileName = task1(argv[1]);
        char* fileName2 = task2(fileName);
        free(fileName);
        task3(fileName2);
        free(fileName2);
    }

    if(strcmp(argv[2], "4") == 0){      
        task4(argv[1]);
    }
}
