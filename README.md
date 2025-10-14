# CalcFlex2

functions:

NOTE: z = complex, x = real only

arithmetic operations:
+, -, *, /, ^

negation (-)

postfix operators (!)

isprime(z) // return 1 if z is prime else 0
sqrt(z) // sqrt of z
cbrt(z) // 3rd root of z
root(z, zn) // zn'th root of z
ln(z) // natural logarithm of z
log10(z) // 10'th logarithm of z
log2(z) // second logarithm of z
log(z, zn) //zn'th logarithm of z
exp(z) // z^e
gamma(z), fact(z) // factorial or gamma of z
sin, cos, tan, csc, sec, cot
asin, acos, atan, acsc, asec, acot
sinh, cosh, tanh, csch, sech, coth
asinh, acosh, atanh, acsch, asech, acoth (z)

re(z), im(z) // return real / imaginary part
conj(z) // conjugate z
magn(z), abs(z) // magnitude of z / abs of z
floor(z), ceil(z), round(z)
rand(z1, z2) // random number between z1 and z2

add(z1, z2), sub(z1, z2), mul(z1, z2), div(z1, z2), pow(z1, z2), mod(x1, x2), negate(z)


integrate(func, var, a, b)
sum(func, var, a, b)
prod(func, var, a, b)

pi, e, phi, y

z(z)
f(z)

## rules
functions and constants cannot contain brackets, separators, or operators, or have a postfix operator present


## tokenizer

stages:
2. bracket & separator tokenizer (done)
1. number tokenizer (done)
3. operator tokenizer (done)
6. postfix operator tokenizer
4. primitive tokenizer (done)
5. function bracket tokenizer

token types
- number
- bracket
- operator
- function
- constant
- function bracket
- separator
- string (unknown type)