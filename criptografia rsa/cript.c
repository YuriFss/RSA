/// Universidade Federal de Alagoas
/// Projeto de Criptografia RSA - Matemática Discreta
/// Alunos: Lucius Marques, Aldemir Melo, Yuri Fernandes
/// Professor: Lucas Amorim


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//FUNCAO RECURSIVA "COMMAND" PARA O CASO DE UMA ENTRADA INVALIDA
int command(int comando)
{
  if (comando == 1 || comando == 2 || comando == 3)
  {
    return comando;
  }
  else
  {
    printf("\nENTRADA INVALIDA\n");
    printf("INSIRA UMA NOVA ENTRADA\n");
    scanf("%d", &comando);
    return command(comando);
  }
}

//VERIFICA SE O NUMERO DIGITADO É PRIMO
long long int verificaPrimo(long long int n)
{
    int i;
    for(i = 3; i <= pow(n, 0.5); i+=2)
    {
        if(n % i == 0)
      return 0;
    }
    if (n == 2)
    {
        return 1;
    }
    if (n < 2)
    {
        return 0;
    }
    if (n % 2 == 0)
    {
        return 0;
    }
    return 1;
}


//CALCULAR OS VALORES DE e DE ACORDO COM O COEFICIENTE DE EULER
long long int verificaE(long long int e, long long int phi, long long int p, long long int p2, long long int n)
{
  long long int i;
    if(phi%e != 0 && verificaPrimo(e) && e != p && e != p2)
    {
      return e;
    }
    else
    {
      printf("\nVOCÊ NÃO DIGITOU UM VALOR VÁLIDO PARA e\nDIGITE NOVAMENTE\n");
      scanf("%lld", &e);
      return verificaE(e, phi, p, p2, n);
    }
  return e;
}

long long int encontrarD (long long int e, long long int phi)
{
  //ENCONTRAR d*e ≡ 1 mod(phi)
  //d --> inverso multiplicativo de e: funcao totiente em n -> ((p-1)*(q-1))
  long long int d = 1;
  while (d*e % phi != 1)
  {
    d++;
  }
  return d;
}

//ENCONTRAR OS VALORES CRIPTOGRAFADOS DE CADA CARACTERE A PARTIR DA TABELA ASCII
long long int Encript (int vmensagem, long long int e, long long int n)
{
  long long int resultado = 1;
  long long int resto;
  for (int i=0; i < e; i++)
  {
    resultado *= vmensagem % n;
  }
  resto = resultado % n;
  //printf("%lld\n", resultado2);
  //printf("%lf\n", resto);
  return resto;
}

//ENCONTRAR OS VALORES CRIPTOGRAFADOS DE CADA CARACTERE A PARTIR DA TABELA ASCII
long long int exponenciacaoE(long long int vmensagem, long long int e, long long int n)
{
	long long int resultado, pot;
	pot = vmensagem % n;
  	resultado = 1;

  	for ( ; e > 0; e /= 2)
  	{
    	if (e % 2 == 1)  /* O bit menos significativo eh 1 */
      		resultado = (resultado * pot) % n;

    	pot = (pot * pot) % n;
  	}
  	return resultado;
}


//DESCRIPTOGRAFA A MENSAGEM E TRANSFORMA PARA VALORES DA TABELA ASCII
long long int exponenciacaoD(long long int criptografado, long long int d, long long int n)
{
	long long int resultado, pot;
	pot = criptografado % n;
  	resultado = 1;

  	for ( ; d > 0; d /= 2)
  	{
    	if (d % 2 == 1)  /* O bit menos significativo eh 1 */
      		resultado = (resultado * pot) % n;

    	pot = (pot * pot) % n;
  	}
  	return resultado;
}

int main()
{
  int comando;
  FILE* public;
  FILE* private;
  printf("\nOLA USUARIO!\n");
  printf("\nPARA COMECAR, ESCOLHA O QUE QUER FAZER:\n");
  printf("\nDIGITE '1' SE QUISER GERAR UMA CHAVE PUBLICA\n");
  printf("DIGITE '2' SE QUISER CRIPTOGRAFAR UMA MENSAGEM\n");
  printf("DIGITE '3' SE QUISER DESCRIPTOGRAFAR UMA MENSAGEM\n");
  scanf("%d", &comando);
  comando = command(comando);

  long long int i;
  long long int p, p2, n, phi, e, d;

  //OPCAO 1, GERAR CHAVE PUBLICA:
  if (comando == 1)
  {
    printf ("\nDIGITE O PRIMEIRO NUMERO PRIMO\n");
    scanf("%lld", &p);
    if (verificaPrimo(p) != 1)
    {
      while(verificaPrimo(p) != 1)
      {
        printf("VOCE NAO DIGITOU UM NUMERO PRIMO\n");
        printf ("\nDIGITE O PRIMEIRO NUMERO PRIMO\n");
        scanf("%lld", &p);
      }
    }
    printf ("\nDIGITE O SEGUNDO NUMERO PRIMO\n");
    scanf("%lld", &p2);
    if (verificaPrimo(p2) != 1)
    {
      while(verificaPrimo(p2) != 1)
      {
        printf("VOCE NAO DIGITOU UM NUMERO PRIMO\n");
        printf ("\nDIGITE O PRIMEIRO NUMERO PRIMO\n");
        scanf("%lld", &p2);
      }
    }
    n = p * p2;
    if (n <= 256)
    {
      while (n <= 256)
      {
        printf("\nVALORES MUITO PEQUENOS, DIGITE NOVAMENTE OS DOIS NUMEROS PRIMOS\n");
        printf ("\nDIGITE O PRIMEIRO NUMERO PRIMO\n");
        scanf("%lld", &p);
        if (verificaPrimo(p) != 1)
        {
          while(verificaPrimo(p) != 1)
          {
            printf("VOCE NAO DIGITOU UM NUMERO PRIMO\n");
            printf ("\nDIGITE O PRIMEIRO NUMERO PRIMO\n");
            scanf("%lld", &p);
          }
        }
        printf ("\nDIGITE O SEGUNDO NUMERO PRIMO\n");
        scanf("%lld", &p2);
        if (verificaPrimo(p2) != 1)
        {
          while(verificaPrimo(p2) != 1)
          {
            printf("VOCE NAO DIGITOU UM NUMERO PRIMO\n");
            printf ("\nDIGITE O SEGUNDO NUMERO PRIMO\n");
            scanf("%lld", &p2);
          }
        }
        n = p * p2;
      }
    }
    //Calcula o quociente de euler
    phi = (p - 1)*(p2 - 1);
    printf("\nINSIRA UM VALOR PARA e\n");
    printf("POR EXEMPLO: \n");
    long long int v;
    v = rand() % phi;
    while (phi%v == 0 || !verificaPrimo(v) || v == p || v == p2)
    {
    	v = rand() % phi;
    	if(phi%v != 0 && verificaPrimo(v) && v != p && v != p2)
    	{
    		break;
    	}
    }
    printf("%lld  ", v);
    v = rand() % phi;
    while (phi%v == 0 || !verificaPrimo(v) || v == p || v == p2)
    {
    	v = rand() % phi;
    	if(phi%v != 0 && verificaPrimo(v) && v != p && v != p2)
    	{
    		break;
    	}
    }
    printf("%lld  ", v);
    v = rand() % phi;
    while (phi%v == 0 || !verificaPrimo(v) || v == p || v == p2)
    {
    	v = rand() % phi;
    	if(phi%v != 0 && verificaPrimo(v) && v != p && v != p2)
    	{
    		break;
    	}
    }
    printf("%lld  ", v);
    v = rand() % phi;
    while (phi%v == 0 || !verificaPrimo(v) || v == p || v == p2)
    {
    	v = rand() % phi;
    	if(phi%v != 0 && verificaPrimo(v) && v != p && v != p2)
    	{
    		break;
    	}
    }
    printf("%lld  ", v);
    printf("\n");
    scanf("%lld", &e);
    e = verificaE(e, phi, p, p2, n);
    //Calcula o d para a chave privada
    d = encontrarD(e, phi);
    printf("\n");
    printf("CHAVE PRIVADA: (%lld, %lld)\n", d, n);
    printf("\nCHAVE PUBLICA: (%lld, %lld)\n", e, n);
    public = fopen("public.txt", "w+");
    fprintf(public, "CHAVE PUBLICA: (%lld, %lld)\n", e, n);
    fclose(public);
    private = fopen("private.txt", "w+");
    fprintf(private, "CHAVE PRIVADA: (%lld, %lld)\n", d, n);
    fclose(private);
  }
  //OPCAO 2, CRIPTOGRAFAR:
  else if (comando == 2)
  {
    FILE* crep;
    long long int e1;
    long long int n1;
    long long int d1;
    long long int n2;
    char mensagem[100];
    int valoresM[100];
    long long int vcrpt[100];
    char carac;
    printf("INSIRA O VALOR DE e\n");
    scanf("%lld", &e1);
    printf("INSIRA O VALOR DE n\n");
    scanf("%lld", &n1);
    printf("DIGITE A MENSAGEM A SER CRIPTOGRAFADA\n");
    printf("obs: A MENSAGEM NÃO PODE TER MAIS QUE 100 CARACTERES\n");
    scanf(" %[^\n]s", mensagem);
    for (i = 0; i < strlen(mensagem); i++)
    {
      valoresM[i] = mensagem[i];
    }
    //printf("%d %lld %lld\n", valoresM[0], e1, n1);
    printf("\nMENSAGEM CRIPTOGRAFADA: \n");
    crep = fopen("criptografados.txt", "w+");
    for (i = 0; i < strlen(mensagem); i++)
    {
      vcrpt[i] = exponenciacaoE(valoresM[i], e1, n1);
      //printf("%d ", valoresM[i]);
      printf("%lld ", vcrpt[i]);
      fprintf(crep, "%lld\n", vcrpt[i]);
    }
    fprintf(crep, "0");
    fclose(crep);
  }
  //OPCAO 3, DESCRIPTOGRAFAR:
  else if (comando == 3)
  {
    FILE* decrep;
    long long int d1;
    long long int n2;
    int valoresM2[100];
    long long int vcrpt2[100];
    int k, i;
    int j;
    long long int descrip[100];
    printf("INSIRA O VALOR DE d\n");
    scanf("%lld", &d1);
    printf("INSIRA O VALOR DE n\n");
    scanf("%lld", &n2);
    printf("DIGITE A MENSAGEM CRIPTOGRAFADA ATÉ QUE SEJA INFORMADO 0\n");
    for (i=0; i < 100; i++)
    {
      scanf("%lld", &vcrpt2[i]);
      if (vcrpt2[i] == 0)
      {
        break;
      }
    }
    printf("\nMENSAGEM DESCRIPTOGRAFADA:\n");
    for (j = 0; j < i; j++)
    {
      descrip[j] = exponenciacaoD(vcrpt2[j], d1, n2);
    }
    decrep = fopen("descriptografada.txt", "w+");
    for (i=0; i < j; i++)
    {
      printf("%c", descrip[i]);
      fprintf(decrep, "%c", descrip[i]);
    }
    fclose(decrep);
    printf("\n");
  }
  return 0;
}
