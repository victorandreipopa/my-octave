//Copyright Popa Victor-Andrei 313CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>

void load(int ***a, int k, int *vm, int *vn, int *s)
{//incarca matricele in vector
	int i, j, n, m;
	scanf("%d%d", &m, &n);
	vm[k] = m;
	vn[k] = n;
	s[k] = 0;
	int **aux = (int **)malloc(m * sizeof(int *)); //linii
	for (i = 0; i < m; i++)
		aux[i] = (int *)malloc(n * sizeof(int)); //col
	a[k] = aux;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			scanf("%d", &a[k][i][j]);
			s[k] += a[k][i][j];
		}
	s[k] %= 10007;
	if (s[k] < 0)
		s[k] += 10007;
}

void dim(int *vm, int *vn, int k)
{//afisearea dimensiunilor unei matrici
	int index;
	scanf("%d", &index);
	if (index > k || index < 0)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", vm[index], vn[index]);
}

void print(int ***a, int *vm, int *vn, int k)
{//afisarea unei matrici
	int index, i, j;
	scanf("%d", &index);
	if (index > k || index < 0)
		printf("No matrix with the given index\n");
	else
		for (i = 0; i < vm[index]; i++) {
			for (j = 0; j < vn[index]; j++)
				printf("%d ", a[index][i][j]);
			printf("\n");
		}
}

void transpusa(int ****a, int *vm, int *vn, int *index)
{//se calculeaza transpusa unei matrici si se inlocuieste in vector
	int i, j;
	int **trans = (int **)malloc(vn[*index] * sizeof(int *)); //linii
	for (i = 0; i < vn[*index]; i++)
		trans[i] = (int *)malloc(vm[*index] * sizeof(int)); //col

	for (i = 0; i < vn[*index]; i++)
		for (j = 0; j < vm[*index]; j++)
			trans[i][j] = (*a)[*index][j][i];
	for (i = 0; i < vm[*index]; i++)
		free((*a)[*index][i]);
	free((*a)[*index]);
	(*a)[*index] = trans;
	int aux = vn[*index];
	vn[*index] = vm[*index];
	vm[*index] = aux;
}

int **inmultire(int ***a, int m, int n, int p, int i1, int i2, int *s, int k)
{//inmulteste 2 matrici si returneaza rezultatul,pe care il pun la sf de vector
	int i, j, l;
	int **aux = (int **)malloc(m * sizeof(int *)); //linii
	for (i = 0; i < m; i++)
		aux[i] = (int *)malloc(p * sizeof(int)); //col
	s[k] = 0;
	for (i = 0; i < m; i++)
		for (j = 0; j < p; j++) {
			aux[i][j] = 0;
			for (l = 0; l < n; l++)
				aux[i][j] += ((a[i1][i][l] * a[i2][l][j]) % 10007);
			aux[i][j] %= 10007;
			if (aux[i][j] < 0)
				aux[i][j] += 10007;
			s[k] += aux[i][j];
			s[k] %= 10007;
			if (s[k] < 0)
				s[k] += 10007;
		}
	return aux;
}

int **multiply(int **a, int **b, int m)
{//functie ajutatoare de inmultire a 2 matrici de care ma folosesc la ridicare
	int i, j, l;
	int **aux = (int **)calloc(m, sizeof(int *));
	for (i = 0; i < m; i++)
		aux[i] = (int *)calloc(m, sizeof(int));
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++) {
			aux[i][j] = 0;
			for (l = 0; l < m; l++)
				aux[i][j] += ((a[i][l] * b[l][j]) % 10007);
			aux[i][j] %= 10007;
			if (aux[i][j] < 0)
				aux[i][j] += 10007;
		}
return aux;
}

void sortare(int ****a, int *vm, int *vn, int *s, int k)
{//sortez matricile din vector dupa suma elementelor
	int aux, i, ok = 1;
	do {
		ok = 1;
		for (i = 0; i < k - 1; i++) {
			if (s[i] > s[i + 1]) {
				ok = 0;
				aux = s[i];
				s[i] = s[i + 1];
				s[i + 1] = aux;

				aux = vm[i];
				vm[i] = vm[i + 1];
				vm[i + 1] = aux;

				aux = vn[i];
				vn[i] = vn[i + 1];
				vn[i + 1] = aux;

				int **aux = (*a)[i];
				(*a)[i] = (*a)[i + 1];
				(*a)[i + 1] = aux;
			}
		}
	} while (ok == 0);
}

void eliberare(int ****a, int *vm, int *vn, int *s, int *k)
{//eliberez memoria matricei dorite
	//si mut celalte matrici cu o pozitie in stanga
	int i, index;
	scanf("%d", &index);
	if (index > *k - 1 || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		for (i = 0; i < vm[index]; i++)
			free((*a)[index][i]);
		free((*a)[index]);
		for (i = index; i < *k - 1; i++) {
			(*a)[i] = (*a)[i + 1];
			vm[i] = vm[i + 1];
			vn[i] = vn[i + 1];
			s[i] = s[i + 1];
		}
		(*a)[*k - 1] = NULL;
		(*a) = realloc((*a), (*k - 1) * sizeof(int **));
		*k = *k - 1;
	}
}

void redimensionare(int ****a, int *vm, int *vn, int *s, int k)
{//redimensionez matricea dorita
	int index;
	scanf("%d", &index);
	int i, j, x, y, l[1000], c[1000];

	scanf("%d", &x);
	for (i = 0; i < x; i++)
		scanf("%d", &l[i]);

	scanf("%d", &y);
	for (i = 0; i < y; i++)
		scanf("%d", &c[i]);

	if (index > k - 1 || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		s[index] = 0;
		int **aux = (int **)malloc(x * sizeof(int *)); //linii
		for (i = 0; i < x; i++)
			aux[i] = (int *)malloc(y * sizeof(int)); //col

		for (i = 0; i < x; i++)
			for (j = 0; j < y; j++) {
				aux[i][j] = (*a)[index][l[i]][c[j]];
				s[index] += aux[i][j];
			}
		s[index] %= 10007;
		if (s[index] < 0)
			s[index] += 10007;
		for (i = 0; i < vm[index]; i++)
			free((*a)[index][i]);
		free((*a)[index]);
		(*a)[index] = aux;
		vm[index] = x;
		vn[index] = y;
	}
}

void ridicare(int ****a, int *vm, int *vn, int *s, int k)
{//ridic matricea la puterea dorita in timp logaritmic
	//si ma ajut de functia multiply
	int index, i, j, p;
	scanf("%d%d", &index, &p);
	if (index > k || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (p < 0) {
		printf("Power should be positive\n");
		return;
	}
	if (vm[index] != vn[index]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	int **aux;
	int **rez = (int **)calloc(vm[index], sizeof(int *)); //linii
	for (i = 0; i < vm[index]; i++)
		rez[i] = (int *)calloc(vn[index], sizeof(int)); //col
	for (i = 0; i < vm[index]; i++)
		rez[i][i] = 1;
	while (p > 0) {
		if (p % 2 == 1) {
			aux = multiply(rez, (*a)[index], vm[index]);
			for (i = 0; i < vm[index]; i++)
				free(rez[i]);
			free(rez);
		rez = aux;
		}
		aux = multiply((*a)[index], (*a)[index], vm[index]);
		for (i = 0; i < vm[index]; i++)
			free((*a)[index][i]);
		free((*a)[index]);
		(*a)[index] = aux;
		p /= 2;
	}
	for (i = 0; i < vm[index]; i++)
		free((*a)[index][i]);
	free((*a)[index]);
	(*a)[index] = rez;
	s[index] = 0;
	for (i = 0; i < vm[index]; i++)
		for (j = 0; j < vm[index]; j++)
			s[index] += rez[i][j];
	s[index] %= 10007;
	if (s[index] < 0)
		s[index] += 10007;
}

int main(void)
{
	int ***A = NULL, k = 0, i, j, vm[10000], vn[10000], s[10000], index, litera;
	char l, c;
	do {//aplic functiile declarate mai sus in functie de literele citite
		scanf("%s", &l);
		litera = 0;
		if (l == 'L') {//maresc dimensiunea vectorului
			A = realloc(A, (k + 1) * sizeof(int **));
			load(A, k, vm, vn, s); k++; litera = 1;
		}
		if (l == 'D') {
			dim(vm, vn, k - 1); litera = 1;
		}
		if (l == 'P') {
			print(A, vm, vn, k - 1); litera = 1;
		}
		if (l == 'T') {
			litera = 1;
			scanf("%d", &index);
			if (index > (k - 1) || index < 0)
				printf("No matrix with the given index\n");
			else
				transpusa(&A, vm, vn, &index);
		}
		if (l == 'M') {
			int index1, index2, m, n, p, ok = 1; litera = 1;
			scanf("%d %d", &index1, &index2);//verific daca este valida inmult
			if (index1 > (k - 1) || index1 < 0)
				ok = 0;
			if (index2 > (k - 1) || index2 < 0)
				ok = 0;
			if (ok == 0) {
				printf("No matrix with the given index\n");
			} else {
				m = vm[index1]; n = vn[index1]; p = vn[index2];
				if (n != vm[index2]) {
					printf("Cannot perform matrix multiplication\n"); ok = 0;
				}
			}
			if (ok == 1) {
				A = realloc(A, (k + 1) * sizeof(int **));
				A[k] = inmultire(A, m, n, p, index1, index2, s, k);
				vm[k] = m; vn[k] = p; k++;
			}
		}
		if (l == 'O') {
			sortare(&A, vm, vn, s, k);
			litera = 1;
		}
		if (l == 'F') {
			litera = 1;
			eliberare(&A, vm, vn, s, &k);
		}
		if (l == 'C') {
			litera = 1;
			redimensionare(&A, vm, vn, s, k);
		}
		if (l == 'R') {
			litera = 1;
			ridicare(&A, vm, vn, s, k);
		}
		if (l == 'Q')
			litera = 1;
		if (litera == 0)//daca nu s a citit o litera dorita,atunci spun asta
			printf("Unrecognized command\n");
		scanf("%c", &c);//citesc enterul
	} while (l != 'Q');//dupa ce ma opresc,eliberez vectorul de matrici
	for (i = 0; i < k; i++) {
		for (j = 0; j < vm[i]; j++)
			if (A[i][j])
				free(A[i][j]);
		if (A[i])
			free(A[i]);
	}
	if (A)
		free(A);
	return 0;
}
