#include <stdio.h>

typedef struct Matrix2x2 {
  double M2x2[2][2];
} matrix2x2;

typedef struct Matrix3x3 {
  double M3x3[3][3];
} matrix3x3;

typedef struct Vector3D {
  double V3D[3];
} vector3d;

typedef struct Array {
  double A[9];
} array;

int invertNum (int num) {
  if (num == 1) {
    return 0;
  }
  else {
    return 1;
  }
}

int powClone(int base, int exponent) {
  int result = 1;
  for (int i = 0; i < exponent; i++) {
    result = result * base;
  }
  return result;
}

matrix2x2 multiplyMatricies2x2(matrix2x2 *ptr1, matrix2x2 *ptr2) {
  matrix2x2 result;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      result.M2x2[i][j] = 0;
      for (int k = 0; k < 2; k++) {
        result.M2x2[i][j] = result.M2x2[i][j] + (ptr1->M2x2[i][k])*(ptr2->M2x2[k][j]);
      }
    }
  }
  return result;
}

matrix3x3 multiplyMatricies3x3(matrix3x3 *ptr1, matrix3x3 *ptr2) {
  matrix3x3 result;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      result.M3x3[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        result.M3x3[i][j] = result.M3x3[i][j] + (ptr1->M3x3[i][k])*(ptr2->M3x3[k][j]);
      }
    }
  }
  return result;
}

void inputVector3D(vector3d *ptr) {
  printf("Enter Elements Of Vector\n");
  for (int i = 0; i < 3; i++) {
    scanf("%lf",&(ptr->V3D[i]));
  }
}

void inputMatrix2x2(matrix2x2 *ptr){
  printf("Enter Elements Of The Matrix\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      scanf("%lf",&(ptr->M2x2[i][j]));
    }
  }
  printf("\n");
}

void inputMatrix3x3 (matrix3x3 *ptr) {
  printf("Enter Elements of Matrix \n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      scanf("%lf",&(ptr->M3x3[i][j]));
    }
  }
  printf("\n");
}

void printVector3D(vector3d *ptr) {
  for (int i = 0; i < 3; i++) {
    if (i != 2) {
      printf("%f ",ptr->V3D[i]);
    }
    else {
      printf("%f",ptr->V3D[i]);
    }
  }
}

void printMatrix2x2(matrix2x2 *ptr) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (j != 1){
        printf("%lf, ",ptr->M2x2[i][j]);
      }
      else {
        printf("%lf\n",ptr->M2x2[i][j]);
      }
    }
  }
}

void printMatrix3x3(matrix3x3 *ptr) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j != 2){
        printf("%lf, ",ptr->M3x3[i][j]);
      }
      else {
        printf("%lf\n",ptr->M3x3[i][j]);
      }
    }
  }
}

double determinant2x2(matrix2x2 *ptr) {
  double result = 0;
  for (int j = 0; j < 2; j++) {
    result = result + (powClone(-1, j))*(ptr->M2x2[0][j])*(ptr->M2x2[1][invertNum(j)]);
  }
  return result;
}

array extractSubMatrices(matrix3x3 *ptr, int numberOfMatrices) {
  array result;
  for (int i = 0; i < numberOfMatrices / 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix2x2 tempMatrix;
      double tempArray[4];
      int h = 0;
      for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++) {
          if (k != i && l != j) {
            tempArray[h] = ptr->M3x3[k][l];
            h++;
          }
        }
      }
      for (int t = 0; t < 4; t++) {
        if (t < 2) {
          tempMatrix.M2x2[0][t] = tempArray[t];
        }
        else {
          tempMatrix.M2x2[1][t - 2] = tempArray[t];
        }
      }
      result.A[j + 3*i] = determinant2x2(&tempMatrix);
    }
  }
  return result;
}

double determinant3x3(matrix3x3 *ptr) {
  int result = 0;
  array R = extractSubMatrices(ptr,3);
  for (int i = 0; i < 3; i++) {
    result = ptr->M3x3[0][i]*powClone(-1,i)*(R.A[i]) + result;
  }
  return result;
}

matrix2x2 transpose2x2(matrix2x2 *ptr) {
  matrix2x2 result;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      result.M2x2[i][j] = ptr->M2x2[j][i];
    }
  }
  return result;
}

matrix3x3 transpose3x3(matrix3x3 *ptr) {
  matrix3x3 result;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      result.M3x3[i][j] = ptr->M3x3[j][i];
    }
  }
  return result;
}

matrix3x3 adjoint3x3(matrix3x3 *ptr) {
  matrix3x3 result;
  array R = extractSubMatrices(ptr,9);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      result.M3x3[i][j] = powClone(-1, i + j)*R.A[j + 3*i];
    }
  }
  return transpose3x3(&result);
} 

vector3d crossProduct(vector3d *ptr1, vector3d *ptr2) {
  matrix3x3 calcMatrix;
  vector3d result;
  calcMatrix.M3x3[0][0] = 1; calcMatrix.M3x3[0][1] = 1; calcMatrix.M3x3[0][2] = 1;
  for (int i = 0; i < 3; i++) {
    calcMatrix.M3x3[1][i] = ptr1->V3D[i];
    calcMatrix.M3x3[2][i] = ptr2->V3D[i];
  }
  array R = extractSubMatrices(&calcMatrix,3);
  for (int i = 0; i < 3; i++) {
    result.V3D[i] = powClone(-1,i)*R.A[i];
  }
  return result;
}

double dotProduct(vector3d *ptr1, vector3d *ptr2) {
  double result = 0;
  for(int i = 0; i < 3; i++) {
    result = result + (ptr1->V3D[i])*(ptr2->V3D[i]);
  }
  return result;
}

matrix3x3 invertMatrix3x3(matrix3x3 *ptr) {
  matrix3x3 result = { { {1,0,0}, {0,1,0}, {0,0,1} } };
  double det = determinant3x3(ptr);
  if (det == 0) {
    printf("Matrix is not invertible");
    return result;
  }
  else {
    result = adjoint3x3(ptr);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        result.M3x3[i][j] = result.M3x3[i][j] / det;
      }
    }
    return result;
  }
}
