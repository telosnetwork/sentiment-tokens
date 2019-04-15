/**
 * Sentiment Token interface.
 * 
 * @author Craig Branscom
 * @contract sentiment
 */

#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/ignore.hpp>

using namespace std;
using namespace eosio;

class [[eosio::contract("sentiment")]] sentiment : public contract {

public:

    sentiment(name self, name code, datastream<const char*> ds);

    ~sentiment();

    const name CONTRACT_ACCOUNT = name("sentimenttkn"); //TODO: replace with mainnet contract account
    const symbol LIKE_SYM = symbol("LIKE", 0);
    const symbol DISLIKE_SYM = symbol("DISLIKE", 0);

    //======================== tables ========================

    //@scope get_self().value
    //@ram 
    TABLE profile {
        name account_name;

        asset likes;
        asset dislikes;
        //TODO: expand for other tokens or redesign data model...

        uint32_t last_activity; //TODO: use time_point instead?
        
        uint64_t primary_key() const { return account_name.value; }
        EOSLIB_SERIALIZE(profile, (account_name)
            (likes)(dislikes)
            (last_activity))
    };

    typedef multi_index<name("profiles"), profile> profiles_table;

   //======================== registration actions ========================

    //registers a new profile on the sentiment platform
    ACTION signup(name account_name);

    //======================== activity actions ========================

    //assigns a like token to an account
    ACTION like(name from, name to);

    //assigns a dislike token to an account
    ACTION dislike(name from, name to);

    //======================== admin actions ========================

    //
    // ACTION adminaction(string memo);

    //========== functions ==========

    //
    // bool is_valid();

    //========== reactions ==========

    //
    // void catch_transfer(name from, name to, asset quantity, string memo);

    //========== migration actions ==========

    // ACTION rmvaccount(name account_name);

};