//calculate inverse matrix program using cofactor 
#include<iostream>

//고정된 상수값이 들어가야 하기때문에 const 이용, 
const int max = 10;

//함수를 이용하기 위한 표현
float cofactor(float m[][max], int r, int c, int s);
float det(float m[][max], int n);
void printMatrix(float m[][max], int n);

int main() { 
	//max값으로  큰 배열을 만들고 입력값(n)만큼을 이용 
	float mat[max][max];
	int n;
	int element;
	std::cout << "enter the matrix size  , n = ";
	std::cin >> n;
	std::cout << "Enter the elements of  " << n << " by " << n << " matrix : " << std::endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> element;
			mat[i][j] = element;
		}
	}

	std::cout << "-----Matrix-----" << std::endl;
	printMatrix(mat, n);
	
	float determinant = det(mat, n);
	
	if (determinant == 0) {
		// det(A) =0
		std::cout << "*** DON'T HAVE INVERSE MATRIX***" << std::endl;
		std::cout << "Determinant :   " << determinant << std::endl;
	}
	else {
		//Adjoint matrix
		float adj_m[max][max];

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				adj_m[i][j] = cofactor(mat, j, i, n);
			}
		}
		std::cout << "----Adjoint matrix----" << std::endl;
		printMatrix(adj_m, n);

		// det(A)!=0
		float inv_m[max][max];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				inv_m[i][j] = adj_m[i][j] / determinant;
			}
		}
		//Inverse matrix
		std::cout << "----Inverse Matrix ----" << std::endl;
		printMatrix(inv_m, n);

		//check the result , matrix*inverse = identity 
		float ident_m[max][max];

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				float v = 0;
				for (int k = 0; k < n; ++k) {
					v += mat[i][k] * inv_m[k][j];
				}
				ident_m[j][i] = v;
			}
		}

		std::cout << "----Identity Matrix----" << std::endl;
		printMatrix(ident_m, n);
		std::cout << "Determinant :   " << determinant << std::endl;
	}
}
//print the matrix
void printMatrix(float m[][max], int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << m[i][j] << '\t';
		}
		std::cout << '\n';
	}
}
//n by n matrix (n=size) cofactor = Ai(=row)j(=col)
float cofactor(float m[][max], int row, int col, int size) {
	float temp_m[max][max];
	//cofactor matrix , 
	//선택된 열과 행을 제거 하는 과정
	for (int i = 0, x = 0; i < size; ++i) {
		if (i != row) {
			for (int j = 0, y = 0; j < size; ++j) {
				if (j != col) {
					temp_m[x][y] = m[i][j];
					y++;
				}
			}
			x++;
		}
	}
	size--; // 원래의 사이즈보다 한 사이즈 작아짐
	//decide sign +/-
	if ((row + col) % 2 == 0) {
		return det(temp_m, size);
	}
	else
		return -det(temp_m, size);
}

//calculate determinant , 
float det(float m[][max], int n) {
	float detVal = 0;
	if (n == 1) {
		return m[0][0];
	}
	else if (n == 2) {
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	//recursive function call
	else {
		for (int i = 0; i < n; ++i) {
			detVal += m[0][i] * cofactor(m, 0, i, n);
		}
		return detVal;
	}
}
