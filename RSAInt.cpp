#include "RSAInt.h"

void RSAInt::ShiftLeft(void)
{
    for (std::int16_t i = (myBYTES<<1) - 1; i > 0; i--)
    {
        this->number[i] <<= 1;
        this->number[i] |= ((this->number[i - 1] & 0x80) > 0);
    }
    this->number[0] <<= 1;
}

bool RSAInt::isZero(void)
{
    for (std::uint32_t i = 0; i < (myBYTES<<1); i++)
        if (this->number[i] != 0)
            return false;

    return true;
}

bool RSAInt::isOne(void)
{
    if (this->number[0] != 1)
        return false;

    for (std::uint32_t i = 1; i > (myBYTES<<1); i++)
        if (this->number[i] != 0)
            return false;

    return true;
}

void RSAInt::EZVal(std::uint8_t a)
{
    for (std::uint32_t i = 1; i < (myBYTES<<1); i++)
        this->number[i] = 0;
    this->number[0] = a;
}

void RSAInt::print(void)
{
    for (std::int16_t i = (myBYTES<<1)-1; i >= 0; i--)
        std::cout << (int)this->number[i] << ",";
    std::cout << "\n\n";
}

void RSAInt::copy2(RSAInt *a)
{
    for (std::int16_t i = 0; i < (myBYTES<<1); i++)
        a->number[i] = this->number[i];
}

bool RSAInt::Grt(RSAInt *a)
{
    for (std::int16_t i = (myBYTES<<1) - 1; i >= 0; i--)
    {
        if (this->number[i] > a->number[i])
            return true;

        if (this->number[i] < a->number[i])
            return false;
    }

    return false;
}

bool RSAInt::Gre(RSAInt *a)
{
    for (std::int16_t i = (myBYTES<<1) - 1; i >= 0; i--)
    {
        if (this->number[i] > a->number[i])
            return true;

        if (this->number[i] < a->number[i])
            return false;
    }

    return true;
}

void RSAInt::sum(RSAInt *a)
{

    uint8_t carry = 0;
    uint16_t add;
    for (std::int16_t i = 0; i < (2*myBYTES); i++)
    {
        add = this->number[i] + a->number[i] + carry;
        carry = add >> 8;
        this->number[i] = add & 0xFF;
    }
}

void RSAInt::sub(RSAInt *a)
{
    uint8_t carry = 1;
    uint16_t add;
    for (std::int16_t i = 0; i < (2*myBYTES); i++)
    {
        add = this->number[i] + 255 - a->number[i] + carry;
        carry = add >> 8;
        this->number[i] = add & 0xFF;
    }
}

void RSAInt::mul(RSAInt *a)
{

    uint32_t carry = 0;
    uint32_t add = 0;
    std::uint8_t tmp[(2*myBYTES)];
    for (std::int16_t i = 0; i < (2*myBYTES); i++)
    {
        add = carry;
        for (std::uint8_t j = 0; j <= i; j++)
        {
            add += this->number[i - j] * a->number[j];
        }

        tmp[i] = add & 0xFF;
        carry = add >> 8;
    }

    for (std::int16_t i = 0; i < (2*myBYTES); i++)
        this->number[i] = tmp[i];
}

void RSAInt::pow2(void)
{

    uint32_t carry = 0;
    uint32_t add = 0;
    std::uint8_t tmp[(2*myBYTES)];
    for (std::int16_t i = 0; i < (myBYTES<<1); i++)
    {
        add = carry;
        for (std::uint8_t j = 0; j <= i; j++)
        {
            add += this->number[i - j] * this->number[j];
        }

        tmp[i] = add & 0xFF;
        carry = add >> 8;
    }

    for (std::int16_t i = 0; i < (myBYTES<<1); i++)
        this->number[i] = tmp[i];
}

void RSAInt::divmod(RSAInt *d, RSAInt *q, RSAInt *r)
{
    for (std::uint32_t i = 0; i < (myBYTES<<1); i++)
    {
        q->number[i] = 0;
        r->number[i] = 0;
    }

    for (std::int32_t i = (2*myBYTES) - 1; i >= 0; i--)
    {
        for (std::int8_t k = 7; k >= 0; k--)
        {
            r->ShiftLeft();
            r->number[0] |= (this->number[i] >> k) & 0x01;

            if (r->Gre(d))
            {
                r->sub(d);
                q->number[i] |= (1 << k);
            }
        }
    }
}
