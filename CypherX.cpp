#include <iostream>
#include "RSACrypt.cpp"

using namespace std;

int main()
{
    /**/
    RSA rsa;
    rsa.MakeKey();
    RSAInt message , Encrypt , Decrypt;
    message.EZVal(50);
    Encrypt = rsa.cryptor(rsa.PublicKey , message);
    Decrypt = rsa.cryptor(rsa.PrivateKey , Encrypt);

    message.print();
    Encrypt.print();
    Decrypt.print();
    /**/
    return 0;
}