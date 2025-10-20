

## Exercise Set 1.8


> Nomor 3-15, angka ganjil

### 3. find the domain and codomain of the transformation defined by the equations

**Domain**: number of possible input(input space) -> num of unknown var, represented as num of column in matrix form which have size of $\mathbb{R}^n$ 

**Codomain**: number of all output possibility -> all combination that can be outputed from the system, we can get the size if we turn linear system into mat-vector multiplication and see it in row view which:

$$
\begin{bmatrix}
a&b \\
c&d
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix}=
\begin{bmatrix}
ax_{1}+bx_{2} \\
cx_{1}+dx_{2}
\end{bmatrix}
$$
--- 

#### (3a)
$$
\begin{align}
& w_{1} = 4x_{1}+5x_{2} \\
& w_{2} = x_{1}-8x_{2}
\end{align}
$$


equation can be turn into matrix form:

$$
\begin{bmatrix}
4&5 \\
1&-8
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix} = \begin{bmatrix}
w_{1} \\
w_{2}
\end{bmatrix}
$$


domain size is ($\mathbb{R}^n$) = **2**
codomain size ($\mathbb{R}^m$) = **2**

#### (3b)
$$
\begin{align}
&w_{1}=5x_{1}-7x_{2} \\
&w_{2}=6x_{1}+x_{2} \\
&w_{3}=2x_{1}+3x_{2}
\end{align}
$$

in matrix form:

$$
\begin{bmatrix}
5&-7 \\
6&1 \\
2&3
\end{bmatrix} \begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix} =
\begin{bmatrix}
w_{1} \\
w_{2} \\
w_{3}
\end{bmatrix}
$$

Size of domain ($\mathbb{R}^n$): **2**
Size of codomain ($\mathbb{R}^m$): **3**


### 5.  find the domain and codomain of the transformation defined by the matrix product

#### (5a) 
$$
\begin{bmatrix}
3&1&2 \\
6&7&8
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3}
\end{bmatrix}
$$

Size of domain ($\mathbb{R}^n$): **3**
Size of codomain ($\mathbb{R}^m$): **2**


#### (5b)
$$
\begin{bmatrix}
2&-1 \\
4&3 \\
2&-5
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix}
$$

Size of domain ($\mathbb{R}^n$): **2**
Size of codomain ($\mathbb{R}^m$): **3**

### 7.  Find the domain and codomain of the transformation T defined by the formula 

#### (7a)
$$
T(x_{1},x_{2}) = (2x_{1}-x_{2}, x_{1}+x_{2})
$$

can be turn onto normal functions:

$$
\begin{align}
&T_{1} = 2x_{1}-x_{2}\\
&T_{2} = x_{1}+x_{2}
\end{align}
$$

then into matrix form:

$$
\begin{bmatrix}
2&-1 \\
1&1
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix}
=
\begin{bmatrix}
T_{1} \\
T_{2}
\end{bmatrix}
$$


Size of domain ($\mathbb{R}^n$): **2**
Size of codomain ($\mathbb{R}^m$): **2**

#### (7b)
$$
T(x_{1},x_{2},x_{3}) = (4x_{1}+x_{2},x_{1}+x_{2})
$$

in matrix form

$$
\begin{bmatrix}
4&1&0 \\
1&1&0 \\
0&0&0
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3}
\end{bmatrix}
$$

Size of domain ($\mathbb{R}^n$): **3**
Size of codomain ($\mathbb{R}^m$): **3**

### 9. Find the domain and codomain of the transformation T defined by the formula.


$$
T\begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix} = \begin{bmatrix}
4x_{1} \\
x_{1}-x_{2} \\
3x_{2}
\end{bmatrix}
$$

turn into standar mat-vector multplication form

$$
\begin{bmatrix}
4&0 \\
1&-1 \\
0&3
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix}
$$


Size of domain ($\mathbb{R}^n$): **2**
Size of codomain ($\mathbb{R}^n$): **3**

### 11.  Find the standard matrix for the transformation defined by the equations

#### (11a)
$$
\begin{align}
&w_{1} = 2x_{1}-3x_{2}+x_{3}\\
&w_{2}=3x_{1}+5x_{2}-x_{3}
\end{align}
$$

matrix form:

$$
\begin{bmatrix}
2&-3&1 \\
3&5&-1
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3}
\end{bmatrix} =
\begin{bmatrix}
w_{1} \\
w_{2}
\end{bmatrix}
$$

#### (11b)
$$
\begin{align}
&w_{1}=7x_{1}+2x_{2}-8x_{3} \\
&w_{2}=-x_{2}+5x_{3} \\
&w_{3}=4x_{1}+7x_{2}-x_{3}
\end{align}
$$

matrix-vec mult form:

$$
\begin{bmatrix}
7&2&-8 \\
0&-1&5 \\
4&7&1
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3}
\end{bmatrix}
=
\begin{bmatrix}
w_{1} \\
w_{2} \\
w_{3}
\end{bmatrix}
$$

### 13. Find the standard matrix for the transformation T defined by the formula

$$
\begin{align}
&(a)\; T(x_1, x_2) = (x_2 - x_1, x_1 + 3x_2, x_1 - x_2)\\
&(b)\; T(x_1, x_2, x_3, x_4) = (7x_1 + 2x_2 - x_3 + 4x_4, x_2 + x_3, -x_1)\\
&(c)\; T(x_1, x_2, x_3) = (0, 0, 0, 0)\\
&(d)\; T(x_1, x_2, x_3, x_4) = (x_4, x_1, x_3, x_2, x_1 - x_3)
\end{align}
$$

#### (13a)
$$
\begin{bmatrix}
1 & -1 & 3 & 0 \\
1 & 0 & 0 & 0 \\
-1 & 1 & -1 & 0
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3} \\
x_{4}
\end{bmatrix}
=
\begin{bmatrix}
w_{1} \\
w_{2} \\
w_{3}
\end{bmatrix}
$$


#### (13b)
$$
\begin{bmatrix}
7 & 2 & -1 & 4 \\
0 & 1 & 1 & 0 \\
-1 & 0 & 0 & 0
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3} \\
x_{4}
\end{bmatrix}
=
\begin{bmatrix}
w_{1} \\
w_{2} \\
w_{3}
\end{bmatrix}
$$

#### (13c)
$$
\begin{bmatrix}
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3}
\end{bmatrix}
=
\begin{bmatrix}
w_{1} \\
w_{2} \\
w_{3} \\
w_{4}
\end{bmatrix}
$$

#### (13d)
$$
\begin{bmatrix}
0 & 0 & 0 & 1 \\
1 & 0 & 0 & 0 \\
0 & 0 & 1 & 0 \\
1 & 0 & -1 & 0
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3} \\
x_{4}
\end{bmatrix}
=
\begin{bmatrix}
w_{1} \\
w_{2} \\
w_{3} \\
w_{4}
\end{bmatrix}
$$


### 15. Find the standard matrix for the operator $T : \mathbb{R}^3→\mathbb{R}^3$ defined by this function below,and then compute $T (−1, 2, 4)$ by directly substituting in the equations and then by matrix multiplication:

$$
\begin{align}
&w_{1}=3z_{1}+5x_{2}-x_{3} \\
&w_{2}=4x_{1}-x_{2}+x_{3} \\
&w_{3}=3x_{1}+2x_{2}-3x_{3}
\end{align}
$$

$$
\begin{bmatrix}
0 & 5 & 3 \\
4 & -1 & 1 \\
3 & 2 & -3
\end{bmatrix}
\begin{bmatrix}
x_{1} \\
x_{2} \\
x_{3}
\end{bmatrix}
=
\begin{bmatrix}
w_{1} \\
w_{2} \\
w_{3}
\end{bmatrix}
$$


#### Direct substitution for $T(-1, 2, 4)$:

- $w_1 = 3(-1) + 5(2) - 4 = -3 + 10 - 4 = 3$
- $w_2 = 4(-1) - 2 + 4 = -4 - 2 + 4 = -2$
- $w_3 = 3(-1) + 2(2) - 3(4) = -3 + 4 - 12 = -11$



#### Matrix multiplication for $T(-1, 2, 4)$:

$$
\begin{bmatrix}
0 & 5 & 3 \\
4 & -1 & 1 \\
3 & 2 & -3
\end{bmatrix}
\begin{bmatrix}
-1 \\
2 \\
4
\end{bmatrix}
=
\begin{bmatrix}
(0 \cdot -1) + (5 \cdot 2) + (3 \cdot 4) \\
(4 \cdot -1) + (-1 \cdot 2) + (1 \cdot 4) \\
(3 \cdot -1) + (2 \cdot 2) + (-3 \cdot 4)
\end{bmatrix}
=
\begin{bmatrix}
0 + 10 + 12 \\
-4 - 2 + 4 \\
-3 + 4 - 12
\end{bmatrix}
=
\begin{bmatrix}
22 \\
-2 \\
-11
\end{bmatrix}
$$

