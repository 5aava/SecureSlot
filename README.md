# SecureSlot
**The Best Secure Slot on EOS BlockChain**

## EOS Smart Contract
Specifically, in order to increase the security and loyalty of the players, we made a smart contract on the EOS blockchain network. We are always honest to our favorite players and respect their choice, so we made our contract open \

[https://github.com/5aava/SecureSlot](https://github.com/5aava/SecureSlot)

# Bingo
Our Super Prize is 100.0000 EOS
```cpp
    void sendtokens(account_name to) {

        // OUR PRISE 100.0000 EOS
        asset prise = string2asset("EOS", 1000000, 4);

        action(permission_level{_self, N(active) },
            N(eosio.token), N(transfer),
            make_tuple(_self, to, prise, string("BINGOOO Yuuuu-huuuu!!! Your prize is 100 EOS!!!"))
        ).send();
    }
```
## Rules
We have made for you a super cool safe slot machine. \
There is always a BIG chance to WIN.\
Our super prize gets the one who dropped result = 777 or < 1
```cpp
    // BINGO !!! ~ 0.02 %
    if(result == 777 || result < 1 ) {
        sendtokens(from);
    }
```

## Frontend
![Slot Frontend](//raw.githubusercontent.com/5aava/SecureSlot/master/slotunity.png "Slot Frontend") 


---
by @s5aava with love