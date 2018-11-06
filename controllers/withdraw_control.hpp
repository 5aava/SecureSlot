/**
 * ZeroNight Vuln Smart Contract
 * The idea is to make vuln contract special for ZeroNight on EOS :)
 *
 * @author @s5aava
 */
#pragma once


class withdraw_control : public main_control {
private:
    account_name _self;
    tb_seed tbseed;

    asset string2asset(string symname, int quantity, int precision){
        string sym = symname;
        symbol_type symbolvalue = string_to_symbol(precision, sym.c_str());
        eosio::asset tosend;
        tosend.amount = quantity;
        tosend.symbol = symbolvalue;
        return tosend;
    }

    uint64_t random(int num) {
        checksum256 result;
        auto mixedBlock = tapos_block_prefix() * tapos_block_num();

        const char *mixedChar = reinterpret_cast<const char *>(&mixedBlock);
        sha256( (char *)mixedChar, sizeof(mixedChar), &result);
        const char *p64 = reinterpret_cast<const char *>(&result);

        auto itr_seed = tbseed.begin();
        if (itr_seed == tbseed.end()) {
            itr_seed = tbseed.emplace( _self, [&]( auto& r ) { });
        }

        auto new_seed = (itr_seed->last + now() + abs((int64_t)p64[3]) ) % 65537;
        tbseed.modify( itr_seed, _self, [&]( auto& s ) {
            s.last = new_seed;
        });
        return new_seed % num;
    }

    void sendtokens(account_name to) {

        // OUR PRISE 10.0000 EOS
        asset prise = string2asset("EOS", 100000, 4);

        action(permission_level{_self, N(active) },
            N(eosio.token), N(transfer),
            make_tuple(_self, to, prise, string("BINGOOO Yuuuu-huuuu!!! Your prise is 10 EOS!!!"))
        ).send();
    }

    void checkYourWin( account_name from, asset price ) {

        int rnd = random(999);        
        int result = rnd * price.amount;

        // BINGO !!!
        if(result == 777 || result < 10 ) {
            sendtokens(from);
        }

        print("Your result: ", result);

    }


public:
    withdraw_control(account_name _self)
        : _self(_self)
        , tbseed(_self, _self)
        {}


    void ntransfer(account_name from, account_name to, asset price, string memo){
        uint64_t getprice = price.amount;
        print(getprice);

        eosio_assert(getprice > 0, "must transfer positive balance");

        // lets play
        if(memo == "play") {
            checkYourWin( from, price );
        }

    };
};