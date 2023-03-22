#ifndef RSACRYPT_H
#define RSACRYPT_H

#include <time.h>
#include <cstdlib>
#include "RSAInt.h"

typedef struct Key
{
    RSAInt e;
    RSAInt n;
} Key;

class RSA
{
private:
    RSAInt make_prime();
    void RSAKey(RSAInt, RSAInt, Key *, Key *);
    void gcd(RSAInt, RSAInt, RSAInt *, RSAInt *);

public:
    Key PrivateKey;
    Key PublicKey;
    void MakeKey();
    RSAInt cryptor(Key, RSAInt);
};

#endif
