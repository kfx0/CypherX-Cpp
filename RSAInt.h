#ifndef RSAINT_H
#define RSAINT_H

#include <iostream>
#include <cassert>

#define myBYTES 17

class RSAInt
{
public:
    std::uint8_t number[myBYTES<<1];
    void ShiftLeft(void);
    void EZVal(std::uint8_t);
    void BigVal(std::uint8_t*, const std::uint32_t);
    void sum(RSAInt *);
    void mul(RSAInt *);
    void sub(RSAInt *);
    void pow2(void);
    bool Grt(RSAInt *);
    bool Gre(RSAInt *);
    void divmod(RSAInt *, RSAInt *, RSAInt *);
    void copy2(RSAInt *);
    void print(void);
    bool isZero(void);
    bool isOne(void);
};

#endif
