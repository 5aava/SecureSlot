/**
 * ZeroNight Vuln Smart Contract
 * The idea is to make vuln contract special for ZeroNight 2018 on EOS :)
 *
 * @author @s5aava
 */
#pragma once


class withdraw_control : public main_control {
private:
    account_name _self;
    tb_seed tbseed;
    tb_players tbplayers;
    tb_winners tbwinners;

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

        // OUR PRIZE 100.0000 EOS
        asset prize = string2asset("EOS", 1000000, 4);

        action(permission_level{_self, N(active) },
            N(eosio.token), N(transfer),
            make_tuple(_self, to, prize, string("BINGOOO Yuuuu-huuuu!!! 100 EOS PRIZE !!!"))
        ).send();

        // add to table winners
        tbwinners.emplace(_self, [&](auto & row) {
            row.id = tbwinners.available_primary_key();
            row.winner_name = to;
            row.send_prize = prize;
        });
    }

    void checkYourWin( account_name from, asset price ) {

        int rnd = random(999);
        int result = rnd * price.amount;
        uint64_t prize = 0;

        print("Result:", result);

        // BINGO 777 or 000 !!! ~ 0.02% 
        if(result == 777 || result < 1 ) {
            prize = 100;
            sendtokens(from);
        }

        // add to table players
        auto itr_player = tbplayers.find(from);

        if (itr_player == tbplayers.cend()) {
            itr_player = tbplayers.emplace(_self, [&](auto & row) {
                row.player_name = from;
                row.last_random = result / 10000;
                row.prize = prize;
            });
        }else{
            tbplayers.modify( itr_player, _self, [&]( auto& row ) {
                row.player_name = from;
                row.last_random = result / 10000;
                row.prize = prize;
            });
        }

    }


public:
    withdraw_control(account_name _self)
        : _self(_self)
        , tbseed(_self, _self)
        , tbplayers(_self, _self)
        , tbwinners(_self, _self)
        {}


    void ntransfer(account_name from, account_name to, asset price, string memo){
        uint64_t getprice = price.amount;        

        eosio_assert(getprice > 0, "must transfer positive balance");

        // lets play
        if(memo == "play") {
            print(" play ");
            
            checkYourWin( from, price );
        }

    };

    // admin function
    void clrall(){
        require_auth(_self);

		auto iter = tbplayers.begin();
		while (iter != tbplayers.cend()) {
			iter = tbplayers.erase(iter);
		}

		auto iter2 = tbwinners.begin();
		while (iter2 != tbwinners.cend()) {
			iter2 = tbwinners.erase(iter2);
		}
    }
};