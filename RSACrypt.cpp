#include "RSACrypt.h"

RSAInt RSA::make_prime()
{
    RSAInt p, a, b, pm1, quo, rem;
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227};
    bool flag = false;
    int it = 0;
    while (!flag)
    {
        it++;
        p.EZVal(1);
        p.number[(myBYTES >> 1) - 1] = 0x80;

        for (uint32_t i = 0; i < (myBYTES >> 1); i++)
            p.number[i] |= rand() & 0xFF;

        p.copy2(&pm1);
        pm1.number[0] &= ~0x01;

        flag = true;
        for (uint32_t i = 0; i < 30 & flag; i++)
        {
            a.EZVal(primes[i]);
            b.EZVal(1);

            for (uint32_t j = 0; j < (myBYTES >> 1); j++)
            {
                for (uint32_t k = 0, l = 1; k < 8; k++, l <<= 1)
                {

                    if (pm1.number[j] & l)
                    {
                        b.mul(&a);
                        if (b.Grt(&p))
                        {
                            b.divmod(&p, &quo, &rem);
                            rem.copy2(&b);
                        }
                    }

                    a.pow2();
                    if (a.Grt(&p))
                    {
                        a.divmod(&p, &quo, &rem);
                        rem.copy2(&a);
                    }
                }
            }

            if (!b.isOne())
                flag = false;
        }
    }

    return p;
}

void RSA::gcd(RSAInt a, RSAInt b, RSAInt *c, RSAInt *d)
{
    RSAInt newa, newb, x0, x1, q, r, tmp;
    a.copy2(&newa);
    b.copy2(&newb);

    x0.EZVal(0);
    x1.EZVal(1);

    while (!newa.isZero())
    {
        newb.divmod(&newa, &q, &r);
        newa.copy2(&newb);
        r.copy2(&newa);

        x1.copy2(&tmp);
        x1.mul(&q);
        x0.sub(&x1);
        x0.copy2(&x1);
        tmp.copy2(&x0);
    }

    newb.copy2(c);
    x0.copy2(d);
}

void RSA::RSAKey(RSAInt p, RSAInt q, Key *PublicKey, Key *PrivateKey)
{
    RSAInt n, Phi, e, d, g, qm1;
    bool flag;

    p.copy2(&n);
    n.mul(&q);

    n.copy2(&(PublicKey->n));
    n.copy2(&(PrivateKey->n));

    n.copy2(&Phi);
    Phi.sub(&p);
    q.copy2(&qm1);
    qm1.number[0] &= 0xFE;
    Phi.sub(&qm1);

    flag = true;
    while (flag)
    {
        e.EZVal(1);
        e.number[(myBYTES) - 2] = 0x80;

        for (uint32_t i = 0; i < (myBYTES) - 1; i++)
            e.number[i] |= rand() & 0xFF;

        this->gcd(e, Phi, &g, &d);

        if (g.isOne())
            flag = false;
    }


    while(d.number[2*myBYTES-1] > 127)
        d.sum(&Phi);

    e.copy2(&(PublicKey->e));
    d.copy2(&(PrivateKey->e));
}

RSAInt RSA::cryptor(Key theKey, RSAInt message)
{
    RSAInt a, b, quo, rem;
    message.copy2(&a);
    b.EZVal(1);

    for (uint32_t i = 0; i < myBYTES; i++)
    {
        for (uint32_t j = 0, k = 1; j < 8; j++, k <<= 1)
        {

            if (theKey.e.number[i] & k)
            {
                b.mul(&a);
                if (b.Gre(&(theKey.n)))
                {
                    b.divmod(&(theKey.n), &quo, &rem);
                    rem.copy2(&b);
                }
            }

            a.pow2();
            if (a.Gre(&(theKey.n)))
            {
                a.divmod(&(theKey.n), &quo, &rem);
                rem.copy2(&a);
            }
        }
    }

    return b;
}

void RSA::MakeKey()
{
    srand(time(0));
    RSAInt p = this->make_prime();
    RSAInt q = this->make_prime();
    RSAKey(p, q, &(this->PublicKey), &(this->PrivateKey));
}