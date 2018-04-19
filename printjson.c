#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMAIL_FROM "andre@delphix.com"
#define TEMPLATE_NAME "usersgroupmodelo1"
#define CONFIG_SET "usersgroup"
#define DEFAULT_NAME "Caro"

int main(int argc, char *argv[]) {
   FILE *arqin;
   char linha[160];
   char *nome, *email, *str;
   int cont=0;
      
   memset(linha, '\0', sizeof(linha));

   arqin = fopen(argv[1], "r+");
   if(arqin==NULL) {
      fprintf(stdout,"Erro ao abrir arquivo: %s\n",argv[1]);
      exit(1);
   }

   fseek(arqin, 0, SEEK_SET);
   cont=-1;
   fprintf(stdout, "{\n  \"Source\": \"%s\",\n  \"Template\": \"%s\",\n  \"ConfigurationSetName\": \"%s\",\n  \"Destinations\":[\n", EMAIL_FROM, TEMPLATE_NAME, CONFIG_SET);

   while( fgets(linha, sizeof(linha), arqin) != NULL) {
      cont++;
      if(cont>0 && cont<49) {
         fprintf(stdout,",\n");
      } else {
         if(cont>=48) {
            fprintf(stdout, "  ],\n  \"DefaultTemplateData\":\"{ \\\"name\\\":\\\"%s\\\"}\"\n}\n\n\n", DEFAULT_NAME);
            fprintf(stdout, "{\n  \"Source\": \"%s\",\n  \"Template\": \"%s\",\n  \"ConfigurationSetName\": \"%s\",\n  \"Destinations\":[\n", EMAIL_FROM, TEMPLATE_NAME, CONFIG_SET);
            cont=-1;
         }
      }
      str=(char *)malloc(sizeof(linha));
      linha[strlen(linha)-1]='\0';
      strcpy(str, linha);
      email = strsep(&str, " ");
      nome = strsep(&str, " ");
      fprintf(stdout, "    {\n      \"Destination\":{\n       \"ToAddresses\":[\n       \"%s\"\n       ]\n       },\n       \"ReplacementTemplateData\":\"{ \\\"name\\\":\\\"%s\\\"}\"\n       }\n", email, nome);
      nome=NULL;
      email=NULL;
      memset(linha, '\0', sizeof(linha));
   }
   if(cont<48)
      fprintf(stdout, "  ],\n  \"DefaultTemplateData\":\"{ \\\"name\\\":\\\"%s\\\"}\"\n}\n\n\n", DEFAULT_NAME);
   
   free(str);
   fclose(arqin);

   exit(0);
}


