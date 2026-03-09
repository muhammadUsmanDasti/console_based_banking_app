#pragma once

// Encode: [ 4 bits type ][ 28 bits amount ]
// Type 1=Deposit  2=Withdrawal  3=Transfer

inline unsigned int encodeTransaction(unsigned int type, unsigned int amount)
{
    return (type << 28) | (amount & 0x0FFFFFFF);
}

 inline void decodeTransaction(unsigned int encoded, unsigned int& type, unsigned int& amount)
{
    type   = (encoded >> 28) & 0xF;
    amount =  encoded & 0x0FFFFFFF;
}