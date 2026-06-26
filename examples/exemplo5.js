function funcao(chave)
{
 let i=0;
 nomes = ["Joao", "Jose", "Maria"];
 numeros = [17, 123, 33];
 console.table(nomes);
 console.table(numeros);
 lista_mista = ["ola", 2.0, 5*2, [10, 20]];

 while(i<lista_mista.length && chave!=lista_mista[i])
 i++;
 if (i<lista_mista.length)
 return "S";
 return "N";
}

let ret = funcao("ola");
if (ret == "S")
 console.log("Econtrou!!!");