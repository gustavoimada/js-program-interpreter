function juros_composto(P, i, n)
{
 let M = P*(1 + i/100)**n;
 return M;
}
res = juros_composto(2000, 1.5, 10);
console.log("Resultado = " + res);
