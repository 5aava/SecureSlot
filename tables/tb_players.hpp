// @abi table players i64
struct st_players {
    account_name player_name;
    uint64_t last_random;

    account_name primary_key() const { return player_name; }

    EOSLIB_SERIALIZE(
        st_players,
        (player_name)
        (last_random)
    )
};
typedef eosio::multi_index<N(players), st_players> tb_players;