## Sign Extension

- Task
  - Given w-bit signed interger x
  - Convert it to w + k integer with same value

- Rule
  - Make `k` copies of sign bit
  - x‘ = x<sub>w-1</sub>, ..., x<sub>3</sub>, x<sub>2</sub>, x<sub>1</sub>

### Example
 Give 4-bit signed int convert it to 6-bit
```
// sign bit 0
    0 1 1 0
  0 0 1 1 0
0 0 0 1 1 0

// sign bit 1
    1 1 1 0 =>           -8 + 4 + 2 + 0 = -2
  1 1 1 1 0 =>      -16 + 8 + 4 + 2 + 0 = -2
1 1 1 1 1 0 => -32 + 16 + 8 + 4 + 2 + 0 = -2

```


## Sign Truncating

- Bits are droped
```
// usigned
// mod operation
1 1 0 1 1 => 27
  1 0 1 1 => 27 mod 16 => 11

// signed
1 1 0 1 1 => -5
  1 0 1 1 => -5

// can deal with it as usigned
1 0 0 1 1 => -13
  0 0 1 1 => 19 mod 16 => 3

// no rule
0 1 0 1 1 => 11
  1 0 1 1 => -5
```

## Unsigned Addition
w-bit, will drop w + 1 bit when overflow

## Signd Addition
normally addition, magiclly

## Multiply with Shift
Historically, the integer multiply instruction on many machines was fairly slow, requiring 10 or more clock cycles, whereas other integer operations—such as addition, subtraction, bit-level operations, and shifting—required only 1 clock cycle. As a consequence, one important optimization used by compilers is to attempt to replace multiplications by constant factors with combinations of shift and addition operations. 

B2U<sub>w+k</sub>([x<sub>w-1</sub>, x<sub>w-2</sub>, ..., x<sub>0</sub>, 0, ..., 0]) = x2<sup>k</sup>;

When shifting left by `k` for a fixed w-bits, the high order `k` bits are discard
[x<sub>w−k−1</sub>, x<sub>w−k−2</sub>, . . . , x<sub>0</sub>, 0,  . . . , 0]

combine with addition
> x * 14 = (x<<3) + (x<<2) + (x<<1); 14 = 2<sup>3</sup> + 2<sup>2</sub> + 2<sup>1</sub>

## Divide with Shift(for ints)
- unsigned
  Right shift and round 0
- signed
  Right shift with basis
Right shift

## Byte Ordering
Conventions:
> Big Endian: Sun, PPC Mac, internet
  - Least signification byte has highest address
> Little Endian: x86, ARM processors runing Android, IOS, and Windows
  - Least signification byte has lowest address

## Reverse
reverse(x) = ~x + 1
0 1 1 1 => 7
1 0 0 0 + 1 => -7

1 1 1 1 => -1
0 0 0 0 + 1 => 1


## Extra
  ### Representing Strings
  - Represented by array of characters
  - Each character encode in ASCII format
    - Standrad 7-bit encoding of character set
    - Character "0" has code 0x30
      - Digit i has code 0x30+i
  - String should be null-terminated
    - Final character = 0
  - Byter ordering not an issue


## Fractional Binary Numbers
![Binary float](../assets/binary_numbers.png)

|                Value              | Binary |
|-----------------------------------|--------|
| 5<sup>3</sup>&frasl;<sub>4</sub>  | 101.11 |
| 2<sup>7</sup>&frasl;<sub>8</sub>  | 10.111 |
| 1<sup>7</sup>&frasl;<sub>16</sub> | 1.0111 |
<!-- 1.1 = 11/10 1 -->
- Divide by 2 by shifting right 1 bit
- Multiply by 2 by shifting left 1 bit
- Numbers of form 0.1111111111..... are just below 1.0


## IEEE Floating-Point Representation
The IEEE floating-point standard represents a number in a form V = (-1)<sup>s</sup> x M x 2<sup>E</sup>

![float point](../assets/float_point.png)

The bit representation of a floating-pointer number is didvided into three fields to encoded these value:
- The single sign bit *s* directly encodes the sign *s*
- The k-bit exponent field exp = e<sub>k-1</sub>...e<sub>1</sub>e<sub>0</sub> encodes the exponent E = exp - bias.
- The n-bit fraction field frac = f<sub>k-1</sub>...f<sub>1</sub>f<sub>0</sub> encodes the significand M, but the value encoded also depends on whether or not the exponent field equals 0.

The significand is defined to be M = 1 + f . This is sometimes called an implied leading 1 representation, because we can view M to be the number with binary representation 1.fn−1fn−2 . . . f0. This representation is a trick for getting an additional bit of precision for free, since we can always adjust the exponent E so that significand M is in the range 1 ≤ M < 2 (assuming there is no overflow). We therefore do not need to explicitly represent the leading bit, since it always equals 1.

## Categories of single-precision floating-point values.
![Categories](../assets/categories_of_single_precision_floating_point.png)

### Normalized values
- When exp != 000...0 and exp != 111...1
- Exponent coded as a biased value: E = Exp - Bias
  - Exp: unsigned value of exp field
  - Bias = 2<sup>k-1</sup> - 1, where k is the number if exponent bits

- Significand coded with implied leading 1: M = 1.xxx...x
  - xxx...x: bits of frac field
  - Minimum when frac = 000...0(M = 1.0)
  - Maximum when frac = 111...1(M = 2.0 - `e`)
  - Get extra leading bit for free

15213 = 11101101101101
      
      = 1.1101101101101 x 2<sup>13</sup>
M     = 1.1101101101101

frac  =   11011011011010000000000

E     = 13

Bias  = 127

Exp   = 140 = 10001100

-------------------
float a = 1.1;

a     = 0 01111111 00011001100110011001101

S     = 0

M     = 1.00011001100110011001101 x 2<sup>0</sup>

E     = 0

Bias  = 127

Exp   = 01111111 = 0 + 127 = 127

Actual Value = 1.10000002384185791015625

------------------
double b= 1.1;

Actual Value = 1.10000000000000008881784197001;
> with double we can only represent 1/2**51 about 4e-16, so 1.10000000000000008881784197001 will round to 1.1

## Denormalized Values
When the exponent field is all zeros, the represented number is in denormalized form. In this case, the exponent value is E = 1 − Bias, and the significand value is M = f , that is, the value of the fraction field without an implied leading 1.
Denormalized numbers serve two purposes. First, they provide a way to represent numeric value 0, since with a normalized number we must always have M ≥ 1, and hence we cannot represent 0. In fact, the floating-point representation of +0.0 has a bit pattern of all zeros: the sign bit is 0, the exponent field is all zeros (indicating a denormalized value), and the fraction field is all zeros, giving M = f = 0. Curiously, when the sign bit is 1, but the other fields are all zeros, we get the value −0.0. With IEEE floating-point format, the values −0.0 and +0.0 are considered different in some ways and the same in others.
A second function of denormalized numbers is to represent numbers that are very close to 0.0. They provide a property known as gradual underflow in which possible numeric values are spaced evenly near 0.0.

## Why set the bias this way for denormalized values?
![float point encoding](../assets/float_point_encoding_visualization.png)