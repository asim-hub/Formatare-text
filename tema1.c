//ASIMIONESEI DANIEl 311 CD
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define NMAX 8

void afisare(unsigned long long cH){
	int j;
	unsigned long long  mask;
	for(j = 63; j >= 0; j--){
		mask = 1;
        	if((j + 1) %NMAX == 0 && j != 63)
                	printf("\n");
        	mask = mask << j;
         	if((cH & mask))
          		printf("#");
          		else
          		printf(".");
	}
  	printf("\n");
	printf("\n"); 
}

void transformare(unsigned long long mask1, unsigned long long mask2,
 unsigned long long mask3, unsigned long long mask4, int T,
 unsigned long long *P, unsigned long long H){
	while(T != 0)
        	if(T > 0){
			if((*P) & mask2){ 
				break;
			}
 			if((*P) & mask4){ 
				break;
			}
       			(*P) = (*P) >> 1; T--;
        		if((*P) & H){
				(*P) = (*P) << 1; break;
			}
        	} else if (T < 0){
		       		if((*P) & mask1){ 
					break;
				}
   				if((*P) & mask3){
					break;
				}
                		(*P) = (*P) << 1; T++;
                 		if((*P) & H){
					(*P) = (*P) >> 1; break;
				}
        		} else if( T == 0){
                                break;
                		}
}

void cobor_piesa(unsigned long long *P){
	(*P) = (*P) >> NMAX;
}

void score(unsigned long long H, int nrlinie){
	int i, nrzero = 0;
	unsigned long long mask = 1;
  	for( i = 0; i <= 63; i++)
 	if(!((mask << i) & H))
		nrzero++;
	printf("Score:%.2f", sqrt(nrzero) + pow(1.25, nrlinie));
}

int main (){ 
	unsigned long long H, mask1 = 1, mask2 = 1, mask3 = 1, mask4 = 1, P, newH, cpH, a;
	int i, M, k, l, ok, nrlinie=0, T[NMAX];
	a=255;
	scanf("%llu", &H);
	scanf("%d", &M);
	afisare(H);
	if(M == 0){
	printf("GAME OVER!\n");
	score(H, nrlinie);
	}
	for(i = 1; i <= M; i++){
 		mask1 = mask2 = mask3 = mask4 = 1;
		scanf("%llu", &P);
		for(k = 1; k <= NMAX; k++){
			scanf("%d", &T[k]);
		}
		P = P << 48;
		mask1 = mask1 << 63;
		mask2 = mask2 << 56;
		mask3 = mask3 << 55;
		mask4 = mask4 << 48;
		if((P << NMAX) & H){
			afisare(H);
			printf("GAME OVER!\n");
			score(H, nrlinie);
			return 0;
		}
  		while(T[1] != 0)
        		if(T[1] > 0){
				if(((mask2 & P)) || ((mask4&P))){
				       	break;
				}
         			P = P >> 1; T[1]--;
        			if((P << NMAX) & H){
				P = P << 1; break;
				}
        		}else if(T[1] < 0){
			      		if(((mask1&P)) || ((mask3&P))){
					       	break;
					}
                			P = P << 1; T[1]++;
                 			if((P << NMAX) & H){
					P = P >> 1; break;
					}
        			}else if(T[1] == 0){
                                	break;
					}
	newH = H | (P << NMAX);
	afisare(newH);
	unsigned long long msk = 255;
	msk = msk << 56;
	if(P & msk)
		if(P & H){
			afisare(newH);
			printf("GAME OVER!\n");
			score(newH, nrlinie);
			return 0;
		}

   	if(!(P & msk) && (P & H))
		H = newH;
		else{
		transformare(mask1, mask2, mask3, mask4, T[2], &P, H);
		newH = H | P;
		afisare(newH);
	for(k = 2; k <= 7; k++){
		mask1 = mask2 = mask3 = mask4 = 1;
		mask1 = mask1 << (NMAX*(10-k-1)-1);
		mask2 = mask2 << (NMAX*(9-k-1));
		mask3 = mask3 << (NMAX*(9-k-1)-1);
		mask4 = mask4 << (NMAX*(8-k-1));

		cobor_piesa(&P);
		if(P&H){	
			P =P << NMAX;
			H = H | P;
			ok = 0;
			l = 0;

			while(l <= 7){
				if(((a << (l * NMAX)) & H) == (a << (l * NMAX))){
					cpH = H;
					cpH = cpH >> ((l + 1) * NMAX);
					cpH = cpH << (l * NMAX);
					H = H << ((NMAX - l) *NMAX);
					H = H >> ((NMAX - l) * NMAX);
					H = H | cpH;
					cpH = H;
					ok = 1;
					nrlinie++;
					l--;
				}
				l = l +1;
			}

			if(ok == 1){
				afisare(H);
			}
			break;
		}
	transformare(mask1, mask2, mask3, mask4, T[k+1], &P, H);
	newH = H | P;
	afisare(newH);
	if(k == 7){
		H = H | P;
		ok = 0;
		l = 0;
		while(((a << (l * NMAX)) & H) == (a << (l*NMAX))){
			H = H >> NMAX;
        		ok = 1;
			nrlinie++;
		}
		l = 1;
		while(l <= 7){
			if(((a << (l * NMAX)) & H) == (a << (l * NMAX))){
				cpH = H;
				cpH = cpH >> ((l + 1) * NMAX);
				cpH = cpH << (l * NMAX);
				H = H << ((NMAX - l) * NMAX);
				H = H >> ((NMAX - l) * NMAX);
				H = H | cpH;
				cpH = H;
				ok = 1;
				l = l -1;
				nrlinie++;
			}
			l = l + 1;
		}
		if(ok == 1){
			afisare(H);
		}

	}

	}


	}


	if(i == M){
		printf("GAME OVER!\n");
		score(H, nrlinie);
	}
}

return 0;
}
