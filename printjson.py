import sys

EMAIL_FROM='andre@delphix.com'
TEMPLATE_NAME='usersgroupmodelo1'
CONFIG_SET='usersgroup'
DEFAULT_NAME='Caro'

if len(sys.argv) < 2:
    print("Lack of parameter")
    quit()
cont=-1
size=0
sizelen=0

try:
   arqin = open(sys.argv[1], 'r')
   data = arqin.readlines()
except OSError as err:
    print("OS error: {0}".format(err))
except IOError as err:
   print("IO error: {0}".format(err))
else:
   arqin.close()
   print("{\n  \"Source\": \"", EMAIL_FROM, "\",\n  \"Template\": \"",TEMPLATE_NAME,"\",\n  \"ConfigurationSetName\": \"",CONFIG_SET,"\",\n  \"Destinations\":[", sep='', end='\n', file=sys.stdout)
   sizelen=len(data)
   for eachLine in data:
      cont=cont+1
      valores=eachLine.split(' ')
      email = valores[0]
      nome = valores[1].rstrip('\n')
      print("    {\n      \"Destination\":{\n       \"ToAddresses\":[\n       \"", email,"\"\n       ]\n       },\n       \"ReplacementTemplateData\":\"{ \\\"name\\\":\\\"", nome, "\\\"}\"\n       }", sep='', end='\n', file=sys.stdout)
      size=size+1
	  
      if(cont>=49):
         print("  ],\n  \"DefaultTemplateData\":\"{ \\\"name\\\":\\\"", DEFAULT_NAME, "\\\"}\"\n}\n\n", sep='', end='\n', file=sys.stdout)
         print("{\n  \"Source\": \"", EMAIL_FROM, "\",\n  \"Template\": \"",TEMPLATE_NAME,"\",\n  \"ConfigurationSetName\": \"",CONFIG_SET,"\",\n  \"Destinations\":[", sep='', end='\n', file=sys.stdout)
         cont=-1;
      elif(cont>=0 and cont<49 and size!=sizelen):
         print(",", cont, sep='', end='\n', file=sys.stdout)

if(cont>=0 and cont<50):
    print("  ],\n  \"DefaultTemplateData\":\"{ \\\"name\\\":\\\"", DEFAULT_NAME, "\\\"}\"\n}\n\n", sep='', end='\n', file=sys.stdout)

quit()
