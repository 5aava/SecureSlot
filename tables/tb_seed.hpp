struct st_seed {
    uint64_t pk = 1;
    uint32_t last = 1;

    uint64_t primary_key() const { return pk; }
};
typedef eosio::multi_index<N(seed), st_seed> tb_seed;