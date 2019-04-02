/**
 * Sentiment Token implementation.
 * 
 * @author Craig Branscom
 * @contract sentiment
 */

#include "../include/sentiment.hpp"

sentiment::sentiment(name self, name code, datastream<const char*> ds) : contract(self, code, ds) {}

sentiment::~sentiment() {}

//======================== registration actions ========================

void sentiment::signup(name account_name) {
    //authenticate
    require_auth(account_name);

    //get profiles table
    profiles_table profiles(get_self(), get_self().value);
    auto prof = profiles.find(account_name.value);

    //validate
    check(prof == profiles.end(), "profile already exists");

    //emplace new profile
    profiles.emplace(account_name, [&](auto& row) {
        row.account_name = account_name;
        row.likes = asset(0, LIKE_SYM);
        row.dislikes = asset(0, DISLIKE_SYM);
        row.last_activity = now();
    });

}

//======================== activity actions ========================

void sentiment::like(name from, name to) {
    //authenticate
    require_auth(from);

    //get profiles table
    profiles_table profiles(get_self(), get_self().value);
    auto& prof = profiles.get(from.value, "account not found");

    //validate
    check(from == prof.account_name, "only profile owner is authorized to like content");
    check(is_account(to), "recipient account doesn't exist");
    check(prof.likes > asset(0, LIKE_SYM), "insufficient like balance");

    //charge 1 like from balance
    profiles.modify(prof, same_payer, [&](auto& row) {
        row.likes -= asset(1, LIKE_SYM);
    });

    //this action is recorded by an external service (demux + mongo)
    //the external service can rebuild assigned likes/dislikes through replaying the chain
    //mongo state can be served over a dedicated API endpoint
    //react components built for this project can then simply query the API instead of the chain
    //removes all reliance on Scatter/eosjs
    //removes the MASSIVE ram overhead of tracking assigned likes/dislikes on chain

}

void sentiment::dislike(name from, name to) {
    //authenticate
    require_auth(from);

    //get profiles table
    profiles_table profiles(get_self(), get_self().value);
    auto& prof = profiles.get(from.value, "account not found");

    //validate
    check(from == prof.account_name, "only profile owner is authorized to dislike content");
    check(is_account(to), "recipient account doesn't exist");
    check(prof.dislikes > asset(0, DISLIKE_SYM), "insufficient dislike balance");

    //charge 1 like from balance
    profiles.modify(prof, same_payer, [&](auto& row) {
        row.dislikes -= asset(1, DISLIKE_SYM);
    });

    //same as like action as far as technical implementation goes
    //except can be interpreted to mean different things when compared with like tokens

    //ex1: for our gambling game, we want to display a net value for likes/dislikes
    //therefore we interpret our net score as likes - dislikes

}

//======================== admin actions ========================



//========== functions ==========



//========== reactions ==========



//========== migration actions ==========

// void grassroots::rmvaccount(name account_name) {
//     accounts_table accounts(get_self(), get_self().value);
//     auto& acc = accounts.get(account_name.value, "account not found");
//     accounts.erase(acc);
// }

//========== dispatcher ==========

extern "C" {
    void apply(uint64_t receiver, uint64_t code, uint64_t action) {

        if (code == receiver)
        {
            switch (action)
            {
                EOSIO_DISPATCH_HELPER(sentiment, 
                    (signup) //registration
                    (like)(dislike)); //activity
            }
        }
    }
}