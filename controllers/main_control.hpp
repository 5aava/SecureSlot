/**
 * ZeroNight Vuln Smart Contract
* The idea is to make vuln contract special for ZeroNight 2018 on EOS :)
 *
 * @author @s5aava
 */
#pragma once


class main_control {
protected:

    void assert_true(bool test, const char* cstr) {
        eosio_assert(test ? 1 : 0, cstr);
    }

public:

    asset string2asset(string symname, int quantity, int precision){
        string sym = symname;
        symbol_type symbolvalue = string_to_symbol(precision, sym.c_str());
        eosio::asset tosend;
        tosend.amount = quantity;
        tosend.symbol = symbolvalue;
        return tosend;
    }

};