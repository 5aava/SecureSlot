// @abi table winners i64
struct st_winners {
    uint64_t id;
    account_name winner_name;
    asset send_prize;

    uint64_t primary_key() const { return id; }

    EOSLIB_SERIALIZE(
        st_winners,
        (id)
        (winner_name)
        (send_prize)
    )
};
typedef eosio::multi_index<N(winners), st_winners> tb_winners;