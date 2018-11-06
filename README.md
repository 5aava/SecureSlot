# SecureSlot
**The Best Secure Slot on EOS BlockChain**

## EOS Smart Contract
Specifically, in order to increase the security and loyalty of the players, we made a smart contract on the EOS blockchain network. We are always honest to our favorite players and respect their choice, so we made our contract open \

[https://github.com/5aava/SecureSlot](https://github.com/5aava/SecureSlot)

# Bingo
Our Super Prize is 10.0000 EOS
```cpp
    void sendtokens(account_name to) {

        // OUR PRISE 10.0000 EOS
        asset prise = string2asset("EOS", 100000, 4);

        action(permission_level{_self, N(active) },
            N(eosio.token), N(transfer),
            make_tuple(_self, to, prise, string("BINGOOO Yuuuu-huuuu!!! Your prize is 10 EOS!!!"))
        ).send();
    }
```
## Rules
We have made for you a super cool safe slot machine. \
There is always a BIG chance to WIN.\
Our super prize gets the one who dropped result = 777 or < 10
```cpp
    // BINGO !!!
    if(result == 777 || result < 10 ) {
        sendtokens(from);
    }
```
---
by @s5aava with love